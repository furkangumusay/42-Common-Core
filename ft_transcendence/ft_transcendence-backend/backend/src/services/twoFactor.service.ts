import { randomInt } from 'crypto';

interface PendingCode {
    code: string;
    expiresAt: number;
    attempts: number;
}

const pendingCodes = new Map<string, PendingCode>();

setInterval(() => {
    const now = Date.now();
    for (const [key, data] of pendingCodes) {
        if (data.expiresAt < now) {
            pendingCodes.delete(key);
        }
    }
}, 60000);

export const generateVerificationCode = (): string => {
    return randomInt(100000, 999999).toString();
};

/**
 * Store a verification code for a given key (userId or email)
 * @param key - unique identifier (e.g. `2fa:${userId}` or `reset:${email}`)
 * @param code - 6-digit code
 * @param ttlMinutes - time to live in minutes (default 5)
 */
export const storeVerificationCode = (
    key: string,
    code: string,
    ttlMinutes: number = 5
): void => {
    pendingCodes.set(key, {
        code,
        expiresAt: Date.now() + ttlMinutes * 60 * 1000,
        attempts: 0,
    });
};

export const verifyCode = (key: string, code: string): boolean => {
    const pending = pendingCodes.get(key);

    if (!pending) {
        return false;
    }

    if (pending.expiresAt < Date.now()) {
        pendingCodes.delete(key);
        return false;
    }

    pending.attempts++;
    if (pending.attempts > 5) {
        pendingCodes.delete(key);
        return false;
    }

    if (pending.code === code) {
        pendingCodes.delete(key);
        return true;
    }

    return false;
};

export const hasValidCode = (key: string): boolean => {
    const pending = pendingCodes.get(key);
    if (!pending) return false;
    if (pending.expiresAt < Date.now()) {
        pendingCodes.delete(key);
        return false;
    }
    return true;
};

export const removeCode = (key: string): void => {
    pendingCodes.delete(key);
};
