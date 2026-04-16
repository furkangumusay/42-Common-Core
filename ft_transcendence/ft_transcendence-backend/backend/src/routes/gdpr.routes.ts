import { FastifyInstance, FastifyPluginAsync } from 'fastify';
import { authenticate } from '../middleware/auth.middleware.js';
import {
    exportUserData,
    anonymizeAccount,
    deleteAccount,
    getPrivacyInfo,
    getRetentionInfo,
} from '../controllers/gdpr.controller.js';

export const gdprRoutes: FastifyPluginAsync = async (fastify: FastifyInstance) => {

    fastify.get('/info', getPrivacyInfo);

    fastify.get('/export', {
        preHandler: [authenticate],
    }, exportUserData);

    fastify.get('/retention', {
        preHandler: [authenticate],
    }, getRetentionInfo);

    fastify.post('/anonymize', {
        preHandler: [authenticate],
        schema: {
            body: {
                type: 'object',
                properties: {
                    password: { type: 'string' },
                    confirmation: { type: 'string' },
                },
                required: ['confirmation'],
            },
        },
    }, anonymizeAccount);

    fastify.delete('/delete', {
        preHandler: [authenticate],
        schema: {
            body: {
                type: 'object',
                properties: {
                    password: { type: 'string' },
                    confirmation: { type: 'string' },
                },
                required: ['confirmation'],
            },
        },
    }, deleteAccount);
};
