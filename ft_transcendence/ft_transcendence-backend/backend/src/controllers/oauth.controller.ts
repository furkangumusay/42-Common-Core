import { FastifyRequest, FastifyReply } from 'fastify';
import { userModel } from '../models/user.model.js';
import { sessionModel } from '../models/session.model.js';
import {
    OAuthProvider,
    isProviderConfigured,
    getAuthorizationUrl,
    handleOAuthCallback,
    generateOAuthState,
} from '../services/oauth.service.js';
import {
    generateTokenPair,
} from '../services/jwt.service.js';
import { hashToken } from '../services/hash.service.js';
import { successResponse, errorResponse, ErrorCodes } from '../utils/response.js';
import { env } from '../config/env.js';

const oauthStates = new Map<string, { provider: OAuthProvider; expiresAt: number; linkUserId?: number }>();

setInterval(() => {
    const now = Date.now();
    for (const [state, data] of oauthStates) {
        if (data.expiresAt < now) {
            oauthStates.delete(state);
        }
    }
}, 60000);

export const getProviders = async (
    _request: FastifyRequest,
    reply: FastifyReply
): Promise<void> => {
    const providers: { name: string; id: OAuthProvider; enabled: boolean }[] = [
        { name: '42', id: '42', enabled: isProviderConfigured('42') },
    ];

    return reply.send(
        successResponse({
            providers: providers.filter((p) => p.enabled),
        })
    );
};

export const initiateOAuth = async (
    request: FastifyRequest<{ Params: { provider: string } }>,
    reply: FastifyReply
): Promise<void> => {
    try {
        const provider = request.params.provider as OAuthProvider;

        if (provider !== '42') {
            return reply.status(400).send(
                errorResponse(ErrorCodes.VALIDATION_ERROR, 'Invalid OAuth provider')
            );
        }

        if (!isProviderConfigured(provider)) {
            return reply.status(400).send(
                errorResponse(ErrorCodes.VALIDATION_ERROR, `${provider} OAuth is not configured`)
            );
        }

        const state = generateOAuthState();

        oauthStates.set(state, {
            provider,
            expiresAt: Date.now() + 10 * 60 * 1000,
        });

        const authUrl = getAuthorizationUrl(provider, state);

        return reply.send(
            successResponse({
                authUrl,
                state,
            })
        );
    } catch (error) {
        request.log.error(error);
        return reply.status(500).send(
            errorResponse(ErrorCodes.INTERNAL_ERROR, 'Failed to initiate OAuth')
        );
    }
};

export const oauthCallback = async (
    request: FastifyRequest<{
        Params: { provider: string };
        Querystring: { code?: string; state?: string; error?: string };
    }>,
    reply: FastifyReply
): Promise<void> => {
    try {
        const { code, state, error: oauthError } = request.query;
        const provider = request.params.provider as OAuthProvider;

        if (oauthError) {
            return reply.status(400).send(
                errorResponse(ErrorCodes.VALIDATION_ERROR, `OAuth error: ${oauthError}`)
            );
        }

        if (!code || !state) {
            return reply.status(400).send(
                errorResponse(ErrorCodes.VALIDATION_ERROR, 'Missing code or state parameter')
            );
        }

        const storedState = oauthStates.get(state);
        if (!storedState || storedState.provider !== provider) {
            return reply.status(400).send(
                errorResponse(ErrorCodes.VALIDATION_ERROR, 'Invalid or expired state')
            );
        }

        oauthStates.delete(state);

        if (storedState.expiresAt < Date.now()) {
            return reply.status(400).send(
                errorResponse(ErrorCodes.VALIDATION_ERROR, 'OAuth session expired')
            );
        }

        const profile = await handleOAuthCallback(provider, code);

        let user = userModel.findByOAuth(provider, profile.id);

        if (storedState.linkUserId) {
            if (user && user.id !== storedState.linkUserId) {
                return reply.status(409).send(
                    errorResponse(ErrorCodes.ALREADY_EXISTS, 'This OAuth account is already linked to another user')
                );
            }

            userModel.update(storedState.linkUserId, {
                oauth_provider: provider,
                oauth_id: profile.id,
            });

            user = userModel.findById(storedState.linkUserId);

            return reply.send(
                successResponse({
                    message: 'OAuth account linked successfully',
                    user: {
                        id: user!.id,
                        email: user!.email,
                        display_name: user!.display_name,
                        avatar_url: user!.avatar_url,
                    },
                })
            );
        }

        if (!user) {
            user = userModel.findByEmail(profile.email);
        }

        if (user && !user.oauth_provider) {
            userModel.update(user.id, {
                oauth_provider: provider,
                oauth_id: profile.id,
            });
        }

        if (!user) {
            let displayName = profile.displayName.replace(/[^\p{L}\p{N}_-]/gu, '_');
            if (displayName.length < 3) displayName = `user_${displayName}`;
            if (displayName.length > 32) displayName = displayName.substring(0, 32);

            let suffix = 1;
            let uniqueName = displayName;
            while (userModel.displayNameExists(uniqueName)) {
                uniqueName = `${displayName.substring(0, 28)}_${suffix}`;
                suffix++;
            }

            user = userModel.create({
                email: profile.email,
                display_name: uniqueName,
                avatar_url: profile.avatarUrl || 'default-avatar.png',
                oauth_provider: provider,
                oauth_id: profile.id,
            });
        }

        const tokens = generateTokenPair(request.server, user);

        const refreshTokenHash = await hashToken(tokens.refreshToken);

        const userAgent = request.headers['user-agent'] || 'unknown';
        const ipAddress = request.ip || 'unknown';

        sessionModel.create({
            user_id: user.id,
            refresh_token_hash: refreshTokenHash,
            user_agent: userAgent,
            ip_address: ipAddress,
            expires_at: tokens.refreshTokenExpiresAt.toISOString(),
        });

        userModel.setOnlineStatus(user.id, true);

        const acceptJson = request.headers.accept?.includes('application/json');

        if (acceptJson) {
            return reply.send(
                successResponse({
                    user: {
                        id: user.id,
                        email: user.email,
                        display_name: user.display_name,
                        avatar_url: user.avatar_url,
                        two_factor_enabled: user.two_factor_enabled === 1,
                    },
                    tokens: {
                        accessToken: tokens.accessToken,
                        refreshToken: tokens.refreshToken,
                        expiresAt: tokens.accessTokenExpiresAt.toISOString(),
                    },
                    isNewUser: !user.password_hash,
                })
            );
        }

        const frontendUrl = env.corsOrigin;
        const redirectUrl = `${frontendUrl}/auth/callback?access_token=${tokens.accessToken}&refresh_token=${tokens.refreshToken}`;

        return reply.redirect(redirectUrl);
    } catch (error) {
        request.log.error(error);

        const frontendUrl = env.corsOrigin;
        const errorMessage = error instanceof Error ? error.message : 'OAuth authentication failed';

        if (request.headers.accept?.includes('application/json')) {
            return reply.status(500).send(
                errorResponse(ErrorCodes.INTERNAL_ERROR, errorMessage)
            );
        }

        return reply.redirect(`${frontendUrl}/auth/error?message=${encodeURIComponent(errorMessage)}`);
    }
};

export const linkOAuth = async (
    request: FastifyRequest<{ Params: { provider: string } }>,
    reply: FastifyReply
): Promise<void> => {
    try {
        const userId = request.user.id;
        const provider = request.params.provider as OAuthProvider;

        if (provider !== '42') {
            return reply.status(400).send(
                errorResponse(ErrorCodes.VALIDATION_ERROR, 'Invalid OAuth provider')
            );
        }

        if (!isProviderConfigured(provider)) {
            return reply.status(400).send(
                errorResponse(ErrorCodes.VALIDATION_ERROR, `${provider} OAuth is not configured`)
            );
        }

        const user = userModel.findById(userId);
        if (user?.oauth_provider) {
            return reply.status(400).send(
                errorResponse(ErrorCodes.ALREADY_EXISTS, 'Account already has OAuth linked')
            );
        }

        const state = generateOAuthState();

        oauthStates.set(state, {
            provider,
            expiresAt: Date.now() + 10 * 60 * 1000,
            linkUserId: userId,
        });

        const authUrl = getAuthorizationUrl(provider, state);

        return reply.send(
            successResponse({
                authUrl,
                state,
            })
        );
    } catch (error) {
        request.log.error(error);
        return reply.status(500).send(
            errorResponse(ErrorCodes.INTERNAL_ERROR, 'Failed to initiate OAuth linking')
        );
    }
};

export const unlinkOAuth = async (
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

        if (!user.password_hash) {
            return reply.status(400).send(
                errorResponse(
                    ErrorCodes.VALIDATION_ERROR,
                    'Cannot unlink OAuth without a password set'
                )
            );
        }

        if (!user.oauth_provider) {
            return reply.status(400).send(
                errorResponse(ErrorCodes.VALIDATION_ERROR, 'No OAuth account linked')
            );
        }

        userModel.update(userId, {
            oauth_provider: undefined,
            oauth_id: undefined,
        });

        return reply.send(
            successResponse(null, 'OAuth account unlinked')
        );
    } catch (error) {
        request.log.error(error);
        return reply.status(500).send(
            errorResponse(ErrorCodes.INTERNAL_ERROR, 'Failed to unlink OAuth')
        );
    }
};
