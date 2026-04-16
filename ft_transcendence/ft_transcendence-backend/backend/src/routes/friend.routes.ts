import { FastifyInstance, FastifyPluginAsync } from 'fastify';
import { authenticate } from '../middleware/auth.middleware.js';
import {
    sendFriendRequest,
    acceptFriendRequest,
    rejectFriendRequest,
    cancelFriendRequest,
    removeFriend,
    getFriends,
    getOnlineFriends,
    getPendingRequests,
    getSentRequests,
    blockUser,
    unblockUser,
    getBlockedUsers,
    getFriendshipStatus,
} from '../controllers/friend.controller.js';

export const friendRoutes: FastifyPluginAsync = async (fastify: FastifyInstance) => {
    fastify.addHook('preHandler', authenticate);

    fastify.get('/', getFriends);

    fastify.get('/online', getOnlineFriends);

    fastify.post('/requests', {
        schema: {
            body: {
                type: 'object',
                properties: {
                    userId: { type: 'number' },
                },
                required: ['userId'],
            },
        },
    }, sendFriendRequest);

    fastify.get('/requests/pending', getPendingRequests);

    fastify.get('/requests/sent', getSentRequests);

    fastify.post('/requests/:id/accept', {
        schema: {
            params: {
                type: 'object',
                properties: {
                    id: { type: 'string' },
                },
                required: ['id'],
            },
        },
    }, acceptFriendRequest);

    fastify.post('/requests/:id/reject', {
        schema: {
            params: {
                type: 'object',
                properties: {
                    id: { type: 'string' },
                },
                required: ['id'],
            },
        },
    }, rejectFriendRequest);

    fastify.delete('/requests/:id', {
        schema: {
            params: {
                type: 'object',
                properties: {
                    id: { type: 'string' },
                },
                required: ['id'],
            },
        },
    }, cancelFriendRequest);

    fastify.get('/status/:id', {
        schema: {
            params: {
                type: 'object',
                properties: {
                    id: { type: 'string' },
                },
                required: ['id'],
            },
        },
    }, getFriendshipStatus);

    fastify.delete('/:id', {
        schema: {
            params: {
                type: 'object',
                properties: {
                    id: { type: 'string' },
                },
                required: ['id'],
            },
        },
    }, removeFriend);

    fastify.get('/blocked', getBlockedUsers);

    fastify.post('/block', {
        schema: {
            body: {
                type: 'object',
                properties: {
                    userId: { type: 'number' },
                },
                required: ['userId'],
            },
        },
    }, blockUser);

    fastify.delete('/block/:id', {
        schema: {
            params: {
                type: 'object',
                properties: {
                    id: { type: 'string' },
                },
                required: ['id'],
            },
        },
    }, unblockUser);
};
