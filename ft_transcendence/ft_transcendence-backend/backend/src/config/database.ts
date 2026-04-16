import Database from 'better-sqlite3';
import { existsSync, mkdirSync } from 'fs';
import { dirname } from 'path';
import { env } from './env.js';

let db: Database.Database | null = null;

export const getDatabase = (): Database.Database => {
    if (db) return db;

    const dbDir = dirname(env.databasePath);
    if (!existsSync(dbDir)) {
        mkdirSync(dbDir, { recursive: true });
    }


    db = new Database(env.databasePath, {
        verbose: env.isDevelopment ? console.log : undefined,
    });

    db.pragma('foreign_keys = ON');

    db.pragma('journal_mode = WAL');

    console.log(`Database connected: ${env.databasePath}`);

    return db;
};


export const closeDatabase = (): void => {
    if (db) {
        db.close();
        db = null;
    }
};


export const transaction = <T>(fn: () => T): T => {
    const database = getDatabase();
    return database.transaction(fn)();
};


export const isDatabaseConnected = (): boolean => {
    return db !== null && db.open;
};

export { Database };
