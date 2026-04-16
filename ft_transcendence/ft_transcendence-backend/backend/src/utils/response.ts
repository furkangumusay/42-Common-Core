export interface ApiResponse<T = unknown> {
    success: boolean;
    data?: T;
    message?: string;
    error?: ApiError;
}

export interface ApiError {
    code: string;
    message: string;
    details?: unknown;
}

export const successResponse = <T>(data: T, message?: string): ApiResponse<T> => ({
    success: true,
    data,
    message,
});

export const errorResponse = (code: string, message: string, details?: unknown): ApiResponse => ({
    success: false,
    error: {
        code,
        message,
        details,
    },
});

export const ErrorCodes = {
    UNAUTHORIZED: 'UNAUTHORIZED',
    FORBIDDEN: 'FORBIDDEN',
    INVALID_CREDENTIALS: 'INVALID_CREDENTIALS',
    TOKEN_EXPIRED: 'TOKEN_EXPIRED',
    TOKEN_INVALID: 'TOKEN_INVALID',
    TWO_FACTOR_REQUIRED: 'TWO_FACTOR_REQUIRED',
    TWO_FACTOR_INVALID: 'TWO_FACTOR_INVALID',

    VALIDATION_ERROR: 'VALIDATION_ERROR',
    INVALID_INPUT: 'INVALID_INPUT',

    NOT_FOUND: 'NOT_FOUND',
    ALREADY_EXISTS: 'ALREADY_EXISTS',
    CONFLICT: 'CONFLICT',

    RATE_LIMITED: 'RATE_LIMITED',

    INTERNAL_ERROR: 'INTERNAL_ERROR',
    DATABASE_ERROR: 'DATABASE_ERROR',
} as const;

export type ErrorCode = (typeof ErrorCodes)[keyof typeof ErrorCodes];
