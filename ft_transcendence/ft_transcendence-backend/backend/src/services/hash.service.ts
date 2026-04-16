import bcrypt from 'bcrypt';
import { env } from '../config/env.js';

export const hashPassword = async (password: string): Promise<string> => {
    return bcrypt.hash(password, env.bcryptSaltRounds);
};

export const verifyPassword = async (
    password: string,
    hash: string
): Promise<boolean> => {
    return bcrypt.compare(password, hash);
};

export const hashToken = async (token: string): Promise<string> => {
    return bcrypt.hash(token, 10);
};

export const verifyToken = async (
    token: string,
    hash: string
): Promise<boolean> => {
    return bcrypt.compare(token, hash);
};
