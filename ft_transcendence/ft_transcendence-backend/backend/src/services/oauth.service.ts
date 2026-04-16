import { env } from '../config/env.js';

export type OAuthProvider = '42';

export interface OAuthProfile {
    provider: OAuthProvider;
    id: string;
    email: string;
    displayName: string;
    avatarUrl?: string;
}

interface OAuthTokenResponse {
    access_token: string;
    token_type: string;
    scope?: string;
    expires_in?: number;
}

interface FortyTwoUserInfo {
    id: number;
    email: string;
    login: string;
    displayname: string;
    image?: {
        link?: string;
        versions?: {
            medium?: string;
            small?: string;
        };
    };
}

export const isProviderConfigured = (provider: OAuthProvider): boolean => {
    if (provider === '42') {
        return !!(env.oauth.fortyTwo?.clientId && env.oauth.fortyTwo?.clientSecret);
    }
    return false;
};

export const getAuthorizationUrl = (provider: OAuthProvider, state: string): string => {
    if (provider === '42') {
        return buildFortyTwoAuthUrl(state);
    }
    throw new Error(`Unknown OAuth provider: ${provider}`);
};

const buildFortyTwoAuthUrl = (state: string): string => {
    const params = new URLSearchParams({
        client_id: env.oauth.fortyTwo?.clientId!,
        redirect_uri: env.oauth.fortyTwo?.callbackUrl!,
        response_type: 'code',
        scope: 'public',
        state,
    });
    return `https://api.intra.42.fr/oauth/authorize?${params}`;
};

export const handleOAuthCallback = async (
    provider: OAuthProvider,
    code: string
): Promise<OAuthProfile> => {
    if (provider === '42') {
        return handleFortyTwoCallback(code);
    }
    throw new Error(`Unknown OAuth provider: ${provider}`);
};

const handleFortyTwoCallback = async (code: string): Promise<OAuthProfile> => {
    const tokenResponse = await fetch('https://api.intra.42.fr/oauth/token', {
        method: 'POST',
        headers: { 'Content-Type': 'application/x-www-form-urlencoded' },
        body: new URLSearchParams({
            grant_type: 'authorization_code',
            client_id: env.oauth.fortyTwo?.clientId!,
            client_secret: env.oauth.fortyTwo?.clientSecret!,
            code,
            redirect_uri: env.oauth.fortyTwo?.callbackUrl!,
        }),
    });

    if (!tokenResponse.ok) {
        const error = await tokenResponse.text();
        throw new Error(`42 token exchange failed: ${error}`);
    }

    const tokens = (await tokenResponse.json()) as OAuthTokenResponse;

    const userResponse = await fetch('https://api.intra.42.fr/v2/me', {
        headers: { Authorization: `Bearer ${tokens.access_token}` },
    });

    if (!userResponse.ok) {
        throw new Error('Failed to fetch 42 user info');
    }

    const userInfo = (await userResponse.json()) as FortyTwoUserInfo;

    return {
        provider: '42',
        id: userInfo.id.toString(),
        email: userInfo.email,
        displayName: userInfo.displayname || userInfo.login,
        avatarUrl: userInfo.image?.versions?.medium || userInfo.image?.link,
    };
};

export const generateOAuthState = (): string => {
    const array = new Uint8Array(32);
    crypto.getRandomValues(array);
    return Array.from(array, (byte) => byte.toString(16).padStart(2, '0')).join('');
};
