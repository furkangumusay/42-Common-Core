import { createWriteStream, unlinkSync, existsSync, mkdirSync } from 'fs';
import { join } from 'path';
import { pipeline } from 'stream/promises';
import { randomBytes } from 'crypto';
import { env } from '../config/env.js';

const ALLOWED_MIME_TYPES = [
    'image/jpeg',
    'image/png',
    'image/gif',
    'image/webp',
];

const MIME_TO_EXT: Record<string, string> = {
    'image/jpeg': '.jpg',
    'image/png': '.png',
    'image/gif': '.gif',
    'image/webp': '.webp',
};

export interface UploadResult {
    filename: string;
    path: string;
    url: string;
    size: number;
    mimeType: string;
}

export class UploadError extends Error {
    constructor(
        message: string,
        public code: string
    ) {
        super(message);
        this.name = 'UploadError';
    }
}

const ensureUploadDir = (subdir: string): string => {
    const baseDir = env.upload.dir.startsWith('/')
        ? env.upload.dir
        : join(process.cwd(), env.upload.dir);
    const uploadPath = join(baseDir, subdir);
    if (!existsSync(uploadPath)) {
        mkdirSync(uploadPath, { recursive: true });
    }
    return uploadPath;
};

const generateFilename = (userId: number, mimeType: string): string => {
    const ext = MIME_TO_EXT[mimeType] || '.jpg';
    const uniqueId = randomBytes(8).toString('hex');
    return `${userId}_${uniqueId}${ext}`;
};

export const validateUpload = (
    mimeType: string,
    fileSize: number
): void => {
    if (!ALLOWED_MIME_TYPES.includes(mimeType)) {
        throw new UploadError(
            `Invalid file type. Allowed types: ${ALLOWED_MIME_TYPES.join(', ')}`,
            'INVALID_FILE_TYPE'
        );
    }

    if (fileSize > env.upload.maxFileSize) {
        throw new UploadError(
            `File too large. Maximum size: ${env.upload.maxFileSize / 1024 / 1024}MB`,
            'FILE_TOO_LARGE'
        );
    }
};

export const saveAvatar = async (
    userId: number,
    fileStream: NodeJS.ReadableStream,
    mimeType: string,
    fileSize: number
): Promise<UploadResult> => {
    validateUpload(mimeType, fileSize);

    const uploadDir = ensureUploadDir('avatars');

    const filename = generateFilename(userId, mimeType);
    const filepath = join(uploadDir, filename);

    const writeStream = createWriteStream(filepath);

    try {
        await pipeline(fileStream, writeStream);
    } catch (error) {
        if (existsSync(filepath)) {
            unlinkSync(filepath);
        }
        throw new UploadError('Failed to save file', 'UPLOAD_FAILED');
    }

    return {
        filename,
        path: filepath,
        url: `/uploads/avatars/${filename}`,
        size: fileSize,
        mimeType,
    };
};

export const deleteAvatar = (filename: string): boolean => {
    if (!filename || filename === 'default-avatar.png') {
        return false;
    }

    if (filename.startsWith('http://') || filename.startsWith('https://')) {
        return false;
    }

    const baseDir = env.upload.dir.startsWith('/')
        ? env.upload.dir
        : join(process.cwd(), env.upload.dir);
    const filepath = join(baseDir, 'avatars', filename);

    if (existsSync(filepath)) {
        try {
            unlinkSync(filepath);
            return true;
        } catch {
            return false;
        }
    }

    return false;
};

export const getAvatarUrl = (filename: string): string => {
    if (!filename) {
        return '/uploads/avatars/default-avatar.png';
    }
    if (filename.startsWith('http://') || filename.startsWith('https://')) {
        return filename;
    }
    return `/uploads/avatars/${filename}`;
};
