import Fastify, { FastifyInstance } from 'fastify';
import { afterAll, beforeAll, beforeEach } from 'vitest';
import Database from 'better-sqlite3';
import { join } from 'path';
import { existsSync, unlinkSync, readFileSync, readdirSync } from 'fs';

const TEST_DB_PATH = join(process.cwd(), 'test.db');

let testDb: Database.Database | null = null;

export const createTestDatabase = (): Database.Database => {
    if (existsSync(TEST_DB_PATH)) {
        unlinkSync(TEST_DB_PATH);
    }

    const db = new Database(TEST_DB_PATH);
    db.pragma('journal_mode = WAL');
    db.pragma('foreign_keys = ON');

    const migrationsDir = join(process.cwd(), 'database', 'migrations');
    const migrationFiles = readdirSync(migrationsDir)
        .filter((f) => f.endsWith('.sql'))
        .sort();

    for (const file of migrationFiles) {
        const sql = readFileSync(join(migrationsDir, file), 'utf-8');
        db.exec(sql);
    }

    testDb = db;
    return db;
};

export const getTestDatabase = (): Database.Database => {
    if (!testDb) {
        throw new Error('Test database not initialized. Call createTestDatabase first.');
    }
    return testDb;
};

export const closeTestDatabase = (): void => {
    if (testDb) {
        testDb.close();
        testDb = null;
    }
    if (existsSync(TEST_DB_PATH)) {
        unlinkSync(TEST_DB_PATH);
    }
};

export const clearTestDatabase = (): void => {
    const db = getTestDatabase();

    db.pragma('foreign_keys = OFF');

    const tables = db.prepare(`
        SELECT name FROM sqlite_master 
        WHERE type='table' AND name NOT LIKE 'sqlite_%'
    `).all() as { name: string }[];

    for (const { name } of tables) {
        db.exec(`DELETE FROM ${name}`);
    }

    db.pragma('foreign_keys = ON');
};

export const createTestServer = async (): Promise<FastifyInstance> => {
    const server = Fastify({
        logger: false,
    });

    return server;
};

export const createTestUser = (overrides: Partial<TestUser> = {}): TestUser => ({
    email: `test${Date.now()}@example.com`,
    password: 'TestPassword123!',
    displayName: `TestUser${Date.now()}`,
    ...overrides,
});

export interface TestUser {
    email: string;
    password: string;
    displayName: string;
}

export const randomString = (length = 8): string => {
    const chars = 'abcdefghijklmnopqrstuvwxyz0123456789';
    let result = '';
    for (let i = 0; i < length; i++) {
        result += chars.charAt(Math.floor(Math.random() * chars.length));
    }
    return result;
};

export const wait = (ms: number): Promise<void> =>
    new Promise(resolve => setTimeout(resolve, ms));
