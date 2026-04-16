import { FastifyInstance, FastifyPluginAsync } from 'fastify';
import { authenticate } from '../middleware/auth.middleware.js';
import {
    getTwoFactorStatus,
    initTwoFactorSetup,
    confirmTwoFactor,
    disableTwoFactor,
    verifyTwoFactor,
    sendTwoFactorCode,
} from '../controllers/twoFactor.controller.js';

export const twoFactorRoutes: FastifyPluginAsync = async (fastify: FastifyInstance) => {

    fastify.post('/send-code', {
        schema: {
            body: {
                type: 'object',
                properties: {
                    userId: { type: 'number' },
                },
                required: ['userId'],
            },
        },
    }, sendTwoFactorCode);

    fastify.post('/verify', {
        schema: {
            body: {
                type: 'object',
                properties: {
                    userId: { type: 'number' },
                    code: { type: 'string', minLength: 6, maxLength: 6 },
                },
                required: ['userId', 'code'],
            },
        },
    }, verifyTwoFactor);

    fastify.get('/status', {
        preHandler: [authenticate],
    }, getTwoFactorStatus);

    fastify.post('/setup', {
        preHandler: [authenticate],
    }, initTwoFactorSetup);

    fastify.post('/confirm', {
        preHandler: [authenticate],
        schema: {
            body: {
                type: 'object',
                properties: {
                    code: { type: 'string', minLength: 6, maxLength: 6 },
                },
                required: ['code'],
            },
        },
    }, confirmTwoFactor);

    fastify.post('/disable', {
        preHandler: [authenticate],
        schema: {
            body: {
                type: 'object',
                properties: {
                    password: { type: 'string' },
                },
                required: ['password'],
            },
        },
    }, disableTwoFactor);
};
