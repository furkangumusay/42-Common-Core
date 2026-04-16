import { FastifyInstance, FastifyPluginAsync, FastifyRequest, FastifyReply } from 'fastify';
import { authenticate } from '../middleware/auth.middleware.js';
import {
    getProviders,
    initiateOAuth,
    oauthCallback,
    linkOAuth,
    unlinkOAuth,
} from '../controllers/oauth.controller.js';

export const oauthRoutes: FastifyPluginAsync = async (fastify: FastifyInstance) => {

    fastify.get('/providers', getProviders);

    fastify.get('/:provider', {
        schema: {
            params: {
                type: 'object',
                properties: {
                    provider: { type: 'string', enum: ['42'] },
                },
                required: ['provider'],
            },
        },
    }, initiateOAuth as (request: FastifyRequest, reply: FastifyReply) => Promise<void>);

    fastify.get('/:provider/callback', {
        schema: {
            params: {
                type: 'object',
                properties: {
                    provider: { type: 'string', enum: ['42'] },
                },
                required: ['provider'],
            },
            querystring: {
                type: 'object',
                properties: {
                    code: { type: 'string' },
                    state: { type: 'string' },
                    error: { type: 'string' },
                },
            },
        },
    }, oauthCallback as (request: FastifyRequest, reply: FastifyReply) => Promise<void>);


    fastify.post('/:provider/link', {
        preHandler: [authenticate],
        schema: {
            params: {
                type: 'object',
                properties: {
                    provider: { type: 'string', enum: ['42'] },
                },
                required: ['provider'],
            },
        },
    }, linkOAuth as (request: FastifyRequest, reply: FastifyReply) => Promise<void>);

    fastify.delete('/unlink', {
        preHandler: [authenticate],
    }, unlinkOAuth);
};
