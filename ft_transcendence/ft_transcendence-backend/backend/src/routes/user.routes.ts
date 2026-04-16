import { FastifyInstance, FastifyPluginAsync } from 'fastify';
import multipart from '@fastify/multipart';
import { authenticate } from '../middleware/auth.middleware.js';
import {
    getMyProfile,
    getUserProfile,
    updateProfile,
    changePassword,
    uploadAvatar,
    deleteUserAvatar,
    getMatchHistory,
    getUserStats,
    searchUsers,
    getOnlineUsers,
} from '../controllers/user.controller.js';
import { getUserRank } from '../controllers/stats.controller.js';
import { env } from '../config/env.js';

export const userRoutes: FastifyPluginAsync = async (fastify: FastifyInstance) => {
    await fastify.register(multipart, {
        limits: {
            fileSize: env.upload.maxFileSize,
            files: 1,
        },
    });

    fastify.get('/search', {
        schema: {
            querystring: {
                type: 'object',
                properties: {
                    q: { type: 'string', minLength: 2, maxLength: 50 },
                    limit: { type: 'string' },
                },
                required: ['q'],
            },
            response: {
                200: {
                    type: 'object',
                    properties: {
                        success: { type: 'boolean' },
                        data: {
                            type: 'object',
                            properties: {
                                users: {
                                    type: 'array',
                                    items: {
                                        type: 'object',
                                        properties: {
                                            id: { type: 'number' },
                                            display_name: { type: 'string' },
                                            avatar_url: { type: 'string' },
                                            is_online: { type: 'boolean' },
                                        },
                                    },
                                },
                            },
                        },
                    },
                },
            },
        },
    }, searchUsers);

    fastify.get('/online', getOnlineUsers);

    fastify.get('/:id', {
        schema: {
            params: {
                type: 'object',
                properties: {
                    id: { type: 'string' },
                },
                required: ['id'],
            },
        },
    }, getUserProfile);

    fastify.get('/:id/matches', {
        schema: {
            params: {
                type: 'object',
                properties: {
                    id: { type: 'string' },
                },
                required: ['id'],
            },
            querystring: {
                type: 'object',
                properties: {
                    page: { type: 'string' },
                    limit: { type: 'string' },
                },
            },
        },
    }, getMatchHistory);

    fastify.get('/:id/stats', {
        schema: {
            params: {
                type: 'object',
                properties: {
                    id: { type: 'string' },
                },
                required: ['id'],
            },
        },
    }, getUserStats);

    fastify.get('/:id/rank', {
        schema: {
            params: {
                type: 'object',
                properties: {
                    id: { type: 'string' },
                },
                required: ['id'],
            },
            response: {
                200: {
                    type: 'object',
                    properties: {
                        success: { type: 'boolean' },
                        data: {
                            type: 'object',
                            properties: {
                                rank: { type: 'number' },
                                totalPlayers: { type: 'number' },
                            },
                        },
                    },
                },
            },
        },
    }, getUserRank);

    fastify.get('/me', {
        preHandler: [authenticate],
    }, getMyProfile);

    fastify.patch('/me', {
        preHandler: [authenticate],
        schema: {
            body: {
                type: 'object',
                properties: {
                    displayName: { type: 'string', minLength: 3, maxLength: 32 },
                    email: { type: 'string', format: 'email' },
                },
            },
        },
    }, updateProfile);

    fastify.put('/me/password', {
        preHandler: [authenticate],
        schema: {
            body: {
                type: 'object',
                properties: {
                    currentPassword: { type: 'string', minLength: 1 },
                    newPassword: { type: 'string', minLength: 8 },
                },
                required: ['currentPassword', 'newPassword'],
            },
        },
    }, changePassword);

    fastify.post('/me/avatar', {
        preHandler: [authenticate],
    }, uploadAvatar);

    fastify.delete('/me/avatar', {
        preHandler: [authenticate],
    }, deleteUserAvatar);
};
