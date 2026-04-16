import { FastifyInstance, FastifyRequest, FastifyReply } from 'fastify';
import { extractTokenFromHeader, verifyJwtToken } from '../services/jwt.service.js';
import { userModel } from '../models/user.model.js';
import { errorResponse, ErrorCodes } from '../utils/response.js';

declare module 'fastify' {
    interface FastifyRequest {
        user: {
            id: number;
            email: string;
            displayName: string;
        };
    }
}

export const authenticate = async (
    request: FastifyRequest,
    reply: FastifyReply
): Promise<void> => {
    const token = extractTokenFromHeader(request);

    if (!token) {
        return reply.status(401).send(
            errorResponse(ErrorCodes.UNAUTHORIZED, 'Authorization token required')
        );
    }

    const server = request.server as FastifyInstance;
    const payload = verifyJwtToken(server, token);

    if (!payload) {
        return reply.status(401).send(
            errorResponse(ErrorCodes.TOKEN_INVALID, 'Invalid or expired token')
        );
    }

    if (payload.type !== 'access') {
        return reply.status(401).send(
            errorResponse(ErrorCodes.TOKEN_INVALID, 'Invalid token type')
        );
    }

    const user = userModel.findById(payload.userId);
    if (!user) {
        return reply.status(401).send(
            errorResponse(ErrorCodes.UNAUTHORIZED, 'User not found')
        );
    }

    userModel.update(payload.userId, {
        last_seen_at: new Date().toISOString(),
    });

    request.user = {
        id: payload.userId,
        email: payload.email,
        displayName: payload.displayName,
    };
};

export const optionalAuth = async (
    request: FastifyRequest,
    _reply: FastifyReply
): Promise<void> => {
    const token = extractTokenFromHeader(request);

    if (!token) {
        return;
    }

    const server = request.server as FastifyInstance;
    const payload = verifyJwtToken(server, token);

    if (payload && payload.type === 'access') {
        const user = userModel.findById(payload.userId);
        if (user) {
            request.user = {
                id: payload.userId,
                email: payload.email,
                displayName: payload.displayName,
            };
        }
    }
};

export const isAuthenticated = (request: FastifyRequest): boolean => {
    return request.user !== undefined;
};

export const getCurrentUserId = (request: FastifyRequest): number => {
    if (!request.user) {
        throw new Error('User not authenticated');
    }
    return request.user.id;
};
