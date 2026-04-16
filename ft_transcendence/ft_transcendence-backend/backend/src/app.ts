import Fastify, { FastifyInstance } from 'fastify';
import cors from '@fastify/cors';
import helmet from '@fastify/helmet';
import rateLimit from '@fastify/rate-limit';
import fastifyStatic from '@fastify/static';
import { readFileSync, existsSync } from 'fs';
import { join } from 'path';
import { env } from './config/env.js';
import { initializeDatabase, closeDatabase } from './database/index.js';
import { registerJwtPlugin } from './services/jwt.service.js';
import { metricsRegistry, httpRequestsTotal, httpRequestDurationSeconds } from './services/metrics.service.js';
import { authRoutes } from './routes/auth.routes.js';
import { userRoutes } from './routes/user.routes.js';
import { friendRoutes } from './routes/friend.routes.js';
import { oauthRoutes } from './routes/oauth.routes.js';
import { twoFactorRoutes } from './routes/twoFactor.routes.js';
import { gdprRoutes } from './routes/gdpr.routes.js';
import { statsRoutes } from './routes/stats.routes.js';
import { matchRoutes } from './routes/match.routes.js';
import { localTournamentRoutes } from './routes/localTournament.routes.js';
import { registerSwagger } from './plugins/swagger.js';
import { sessionModel } from './models/session.model.js';

const createServer = (): FastifyInstance => {
    const httpsOptions =
        env.isProduction || existsSync(env.ssl.keyPath)
            ? {
                https: {
                    key: readFileSync(env.ssl.keyPath),
                    cert: readFileSync(env.ssl.certPath),
                },
            }
            : {};

    const server = Fastify({
        logger: {
            level: env.isDevelopment ? 'debug' : 'info',
            transport: env.isDevelopment
                ? {
                    target: 'pino-pretty',
                    options: {
                        colorize: true,
                        translateTime: 'HH:MM:ss Z',
                        ignore: 'pid,hostname',
                    },
                }
                : undefined,
        },
        ...httpsOptions,
    });

    return server;
};

const registerPlugins = async (server: FastifyInstance): Promise<void> => {
    await server.register(helmet, {
        contentSecurityPolicy: env.isProduction,
        crossOriginResourcePolicy: { policy: 'cross-origin' },
    });

    await server.register(cors, {
        origin: env.corsOrigin,
        credentials: true,
        methods: ['GET', 'POST', 'PUT', 'PATCH', 'DELETE', 'OPTIONS'],
        allowedHeaders: ['Content-Type', 'Authorization'],
    });

    await server.register(rateLimit, {
        max: env.rateLimit.max,
        timeWindow: env.rateLimit.windowMs,
    });

    const uploadRoot = env.upload.dir.startsWith('/') 
        ? env.upload.dir 
        : join(process.cwd(), env.upload.dir);
    
    await server.register(fastifyStatic, {
        root: uploadRoot,
        prefix: '/uploads/',
        decorateReply: false,
    });

    await registerJwtPlugin(server);

    server.addHook('onRequest', async (request, _reply) => {
        (request as any).startTime = Date.now();
    });

    server.addHook('onResponse', async (request, reply) => {
        const duration = (Date.now() - ((request as any).startTime ?? Date.now())) / 1000;
        const route = request.routerPath ?? request.url ?? 'unknown';
        const labels = {
            method: request.method,
            route,
            status_code: String(reply.statusCode),
        };
        httpRequestsTotal.inc(labels);
        httpRequestDurationSeconds.observe(labels, duration);
    });
};

const registerRoutes = async (server: FastifyInstance): Promise<void> => {
    server.get('/health', async () => {
        return {
            status: 'ok',
            timestamp: new Date().toISOString(),
            uptime: process.uptime(),
        };
    });

    server.get('/metrics', async (_request, reply) => {
        reply.header('Content-Type', metricsRegistry.contentType);
        return metricsRegistry.metrics();
    });

    server.get('/api', async () => {
        return {
            name: 'ft_transcendence API',
            version: '1.0.0',
            documentation: '/api/docs',
        };
    });

    await server.register(authRoutes, { prefix: '/api/auth' });

    await server.register(userRoutes, { prefix: '/api/users' });

    await server.register(friendRoutes, { prefix: '/api/friends' });

    await server.register(oauthRoutes, { prefix: '/api/oauth' });

    await server.register(twoFactorRoutes, { prefix: '/api/2fa' });

    await server.register(gdprRoutes, { prefix: '/api/gdpr' });

    await server.register(statsRoutes, { prefix: '/api/stats' });

    await server.register(matchRoutes, { prefix: '/api/matches' });

    await server.register(localTournamentRoutes, { prefix: '/api/local-tournament' });

    await registerSwagger(server);
};

const registerErrorHandler = (server: FastifyInstance): void => {
    server.setErrorHandler((error, _request, reply) => {
        server.log.error(error);

        if (error.validation) {
            return reply.status(400).send({
                success: false,
                error: {
                    code: 'VALIDATION_ERROR',
                    message: 'Invalid request data',
                    details: error.validation,
                },
            });
        }

        if (error.code === 'FST_JWT_NO_AUTHORIZATION_IN_HEADER') {
            return reply.status(401).send({
                success: false,
                error: {
                    code: 'UNAUTHORIZED',
                    message: 'Authorization token required',
                },
            });
        }

        if (error.statusCode === 429) {
            return reply.status(429).send({
                success: false,
                error: {
                    code: 'RATE_LIMITED',
                    message: 'Too many requests, please try again later',
                },
            });
        }

        const statusCode = error.statusCode || 500;
        return reply.status(statusCode).send({
            success: false,
            error: {
                code: 'INTERNAL_ERROR',
                message: env.isProduction ? 'An error occurred' : error.message,
            },
        });
    });
};

const registerNotFoundHandler = (server: FastifyInstance): void => {
    server.setNotFoundHandler((request, reply) => {
        reply.status(404).send({
            success: false,
            error: {
                code: 'NOT_FOUND',
                message: `Route ${request.method} ${request.url} not found`,
            },
        });
    });
};

const bootstrap = async (): Promise<void> => {
    const server = createServer();

    try {
        await initializeDatabase();
        server.log.info('Database initialized');
    } catch (error) {
        server.log.error({ err: error }, 'Database initialization failed');
        process.exit(1);
    }

    await registerPlugins(server);
    await registerRoutes(server);
    registerErrorHandler(server);
    registerNotFoundHandler(server);

    const SESSION_CLEANUP_INTERVAL = 30 * 60 * 1000; 
    const cleanupTimer = setInterval(() => {
        try {
            const cleaned = sessionModel.cleanupExpired();
            if (cleaned > 0) {
                server.log.info(`🧹 Cleaned up ${cleaned} expired sessions`);
            }
        } catch (error) {
            server.log.error({ err: error }, 'Session cleanup failed');
        }
    }, SESSION_CLEANUP_INTERVAL);

    const shutdown = async (signal: string): Promise<void> => {
        server.log.info(`Received ${signal}, shutting down gracefully...`);
        clearInterval(cleanupTimer);
        closeDatabase();
        await server.close();
        process.exit(0);
    };

    process.on('SIGINT', () => shutdown('SIGINT'));
    process.on('SIGTERM', () => shutdown('SIGTERM'));

    try {
        await server.listen({
            port: env.port,
            host: env.host,
        });

        const protocol = existsSync(env.ssl.keyPath) ? 'https' : 'http';
        server.log.info(`Server running at ${protocol}://${env.host}:${env.port}`);
        server.log.info(`Health check at ${protocol}://${env.host}:${env.port}/health`);
    } catch (error) {
        server.log.error(error);
        process.exit(1);
    }
};

bootstrap();
