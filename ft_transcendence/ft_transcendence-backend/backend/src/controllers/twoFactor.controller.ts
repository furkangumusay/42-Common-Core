import { FastifyRequest, FastifyReply } from 'fastify';
import { userModel } from '../models/user.model.js';
import { generateVerificationCode, storeVerificationCode, verifyCode } from '../services/twoFactor.service.js';
import { sendVerificationCode, send2FAEnabledNotification } from '../services/email.service.js';
import { verifyPassword } from '../services/hash.service.js';
import { successResponse, errorResponse, ErrorCodes } from '../utils/response.js';

export const getTwoFactorStatus = async (
    request: FastifyRequest,
    reply: FastifyReply
): Promise<void> => {
    try {
        const userId = request.user.id;
        const user = userModel.findById(userId);

        if (!user) {
            return reply.status(404).send(
                errorResponse(ErrorCodes.NOT_FOUND, 'User not found')
            );
        }

        return reply.send(
            successResponse({
                enabled: user.two_factor_enabled === 1,
            })
        );
    } catch (error) {
        request.log.error(error);
        return reply.status(500).send(
            errorResponse(ErrorCodes.INTERNAL_ERROR, 'Failed to get 2FA status')
        );
    }
};

export const initTwoFactorSetup = async (
    request: FastifyRequest,
    reply: FastifyReply
): Promise<void> => {
    try {
        const userId = request.user.id;
        const user = userModel.findById(userId);

        if (!user) {
            return reply.status(404).send(
                errorResponse(ErrorCodes.NOT_FOUND, 'User not found')
            );
        }

        if (user.two_factor_enabled === 1) {
            return reply.status(400).send(
                errorResponse(ErrorCodes.VALIDATION_ERROR, '2FA is already enabled')
            );
        }

        const code = generateVerificationCode();
        storeVerificationCode(`2fa-setup:${userId}`, code, 5);

        await sendVerificationCode(user.email, code);

        return reply.send(
            successResponse(
                { message: 'Verification code sent to your email' },
                'Verification code sent'
            )
        );
    } catch (error) {
        request.log.error(error);
        return reply.status(500).send(
            errorResponse(ErrorCodes.INTERNAL_ERROR, 'Failed to send verification code')
        );
    }
};

export const confirmTwoFactor = async (
    request: FastifyRequest,
    reply: FastifyReply
): Promise<void> => {
    try {
        const userId = request.user.id;
        const { code } = request.body as { code: string };

        if (!code) {
            return reply.status(400).send(
                errorResponse(ErrorCodes.VALIDATION_ERROR, 'Verification code is required')
            );
        }

        const user = userModel.findById(userId);
        if (!user) {
            return reply.status(404).send(
                errorResponse(ErrorCodes.NOT_FOUND, 'User not found')
            );
        }

        if (user.two_factor_enabled === 1) {
            return reply.status(400).send(
                errorResponse(ErrorCodes.VALIDATION_ERROR, '2FA is already enabled')
            );
        }

        if (!verifyCode(`2fa-setup:${userId}`, code)) {
            return reply.status(400).send(
                errorResponse(ErrorCodes.VALIDATION_ERROR, 'Invalid or expired verification code')
            );
        }

        userModel.update(userId, {
            two_factor_enabled: true,
        });

        try {
            await send2FAEnabledNotification(user.email);
        } catch {
        }

        return reply.send(
            successResponse(
                { enabled: true },
                '2FA enabled successfully'
            )
        );
    } catch (error) {
        request.log.error(error);
        return reply.status(500).send(
            errorResponse(ErrorCodes.INTERNAL_ERROR, 'Failed to enable 2FA')
        );
    }
};

export const disableTwoFactor = async (
    request: FastifyRequest,
    reply: FastifyReply
): Promise<void> => {
    try {
        const userId = request.user.id;
        const { password } = request.body as { password: string };

        if (!password) {
            return reply.status(400).send(
                errorResponse(ErrorCodes.VALIDATION_ERROR, 'Password is required to disable 2FA')
            );
        }

        const user = userModel.findById(userId);
        if (!user) {
            return reply.status(404).send(
                errorResponse(ErrorCodes.NOT_FOUND, 'User not found')
            );
        }

        if (user.two_factor_enabled !== 1) {
            return reply.status(400).send(
                errorResponse(ErrorCodes.VALIDATION_ERROR, '2FA is not enabled')
            );
        }

        if (!user.password_hash || !(await verifyPassword(password, user.password_hash))) {
            return reply.status(401).send(
                errorResponse(ErrorCodes.INVALID_CREDENTIALS, 'Invalid password')
            );
        }

        userModel.update(userId, {
            two_factor_enabled: false,
        });

        return reply.send(
            successResponse(null, '2FA disabled successfully')
        );
    } catch (error) {
        request.log.error(error);
        return reply.status(500).send(
            errorResponse(ErrorCodes.INTERNAL_ERROR, 'Failed to disable 2FA')
        );
    }
};

export const sendTwoFactorCode = async (
    request: FastifyRequest,
    reply: FastifyReply
): Promise<void> => {
    try {
        const { userId } = request.body as { userId: number };

        if (!userId) {
            return reply.status(400).send(
                errorResponse(ErrorCodes.VALIDATION_ERROR, 'userId is required')
            );
        }

        const user = userModel.findById(userId);
        if (!user) {
            return reply.status(404).send(
                errorResponse(ErrorCodes.NOT_FOUND, 'User not found')
            );
        }

        if (user.two_factor_enabled !== 1) {
            return reply.status(400).send(
                errorResponse(ErrorCodes.VALIDATION_ERROR, '2FA is not enabled for this user')
            );
        }

        const code = generateVerificationCode();
        storeVerificationCode(`2fa-login:${userId}`, code, 5);

        await sendVerificationCode(user.email, code);

        return reply.send(
            successResponse(
                { message: 'Verification code sent to your email' },
                'Verification code sent'
            )
        );
    } catch (error) {
        request.log.error(error);
        return reply.status(500).send(
            errorResponse(ErrorCodes.INTERNAL_ERROR, 'Failed to send verification code')
        );
    }
};

export const verifyTwoFactor = async (
    request: FastifyRequest,
    reply: FastifyReply
): Promise<void> => {
    try {
        const { userId, code } = request.body as { userId: number; code: string };

        if (!userId || !code) {
            return reply.status(400).send(
                errorResponse(ErrorCodes.VALIDATION_ERROR, 'Missing userId or code')
            );
        }

        const user = userModel.findById(userId);
        if (!user) {
            return reply.status(404).send(
                errorResponse(ErrorCodes.NOT_FOUND, 'User not found')
            );
        }

        if (user.two_factor_enabled !== 1) {
            return reply.status(400).send(
                errorResponse(ErrorCodes.VALIDATION_ERROR, '2FA is not enabled for this user')
            );
        }

        if (!verifyCode(`2fa-login:${userId}`, code)) {
            return reply.status(401).send(
                errorResponse(ErrorCodes.INVALID_CREDENTIALS, 'Invalid or expired verification code')
            );
        }

        return reply.send(
            successResponse({ verified: true }, '2FA verified successfully')
        );
    } catch (error) {
        request.log.error(error);
        return reply.status(500).send(
            errorResponse(ErrorCodes.INTERNAL_ERROR, 'Failed to verify 2FA')
        );
    }
};
