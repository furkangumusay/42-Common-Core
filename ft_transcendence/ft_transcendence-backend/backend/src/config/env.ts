import { config } from 'dotenv';
import { z } from 'zod';

config();

const envSchema = z.object({

    PORT: z.string().default('3000'),
    HOST: z.string().default('0.0.0.0'),
    NODE_ENV: z.enum(['development', 'production', 'test']).default('development'),

    DATABASE_PATH: z.string().default('./database/transcendence.db'),

    JWT_SECRET: z.string().min(32, 'JWT_SECRET must be at least 32 characters'),
    JWT_ACCESS_EXPIRY: z.string().default('15m'),
    JWT_REFRESH_EXPIRY: z.string().default('7d'),


    FORTYTWO_CLIENT_ID: z.string().optional(),
    FORTYTWO_CLIENT_SECRET: z.string().optional(),
    FORTYTWO_CALLBACK_URL: z.string().optional(),

    SMTP_HOST: z.string().default('smtp.gmail.com'),
    SMTP_PORT: z.string().default('587'),
    SMTP_USER: z.string().optional(),
    SMTP_PASS: z.string().optional(),
    SMTP_FROM: z.string().default('ft_transcendence <noreply@ft-transcendence.com>'),

    SSL_KEY_PATH: z.string().default('./certs/key.pem'),
    SSL_CERT_PATH: z.string().default('./certs/cert.pem'),

    CORS_ORIGIN: z.string().default('https://localhost:8443'),

    RATE_LIMIT_MAX: z.string().default('100'),
    RATE_LIMIT_WINDOW_MS: z.string().default('60000'),

    UPLOAD_DIR: z.string().default('./uploads'),
    MAX_FILE_SIZE: z.string().default('5242880'),

    BCRYPT_SALT_ROUNDS: z.string().default('12'),
});

const parseEnv = () => {
    try {
        return envSchema.parse(process.env);
    } catch (error) {
        if (error instanceof z.ZodError) {
            const missing = error.errors.map((e) => e.path.join('.')).join(', ');
            throw new Error(`Missing or invalid environment variables: ${missing}`);
        }
        throw error;
    }
};

const parsedEnv = parseEnv();

export const env = {
    port: parseInt(parsedEnv.PORT, 10),
    host: parsedEnv.HOST,
    nodeEnv: parsedEnv.NODE_ENV,
    isDevelopment: parsedEnv.NODE_ENV === 'development',
    isProduction: parsedEnv.NODE_ENV === 'production',
    isTest: parsedEnv.NODE_ENV === 'test',

    databasePath: parsedEnv.DATABASE_PATH,

    jwt: {
        secret: parsedEnv.JWT_SECRET,
        accessExpiry: parsedEnv.JWT_ACCESS_EXPIRY,
        refreshExpiry: parsedEnv.JWT_REFRESH_EXPIRY,
    },

    oauth: {
        fortyTwo: {
            clientId: parsedEnv.FORTYTWO_CLIENT_ID,
            clientSecret: parsedEnv.FORTYTWO_CLIENT_SECRET,
            callbackUrl: parsedEnv.FORTYTWO_CALLBACK_URL,
        },
    },

    smtp: {
        host: parsedEnv.SMTP_HOST,
        port: parseInt(parsedEnv.SMTP_PORT, 10),
        user: parsedEnv.SMTP_USER,
        pass: parsedEnv.SMTP_PASS,
        from: parsedEnv.SMTP_FROM,
    },

    ssl: {
        keyPath: parsedEnv.SSL_KEY_PATH,
        certPath: parsedEnv.SSL_CERT_PATH,
    },

    corsOrigin: parsedEnv.CORS_ORIGIN,

    rateLimit: {
        max: parseInt(parsedEnv.RATE_LIMIT_MAX, 10),
        windowMs: parseInt(parsedEnv.RATE_LIMIT_WINDOW_MS, 10),
    },

    upload: {
        dir: parsedEnv.UPLOAD_DIR,
        maxFileSize: parseInt(parsedEnv.MAX_FILE_SIZE, 10),
    },

    bcryptSaltRounds: parseInt(parsedEnv.BCRYPT_SALT_ROUNDS, 10),
} as const;

export type Env = typeof env;
