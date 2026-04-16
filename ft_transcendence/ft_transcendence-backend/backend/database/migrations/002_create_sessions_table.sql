CREATE TABLE IF NOT EXISTS sessions (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    
    user_id INTEGER NOT NULL,
    
    refresh_token_hash TEXT UNIQUE NOT NULL,
    
    user_agent TEXT,
    ip_address TEXT,
    
    expires_at DATETIME NOT NULL,
    
    revoked INTEGER DEFAULT 0,
    revoked_at DATETIME,
    
    created_at DATETIME DEFAULT CURRENT_TIMESTAMP,
    
    FOREIGN KEY (user_id) REFERENCES users(id) ON DELETE CASCADE
);

CREATE INDEX IF NOT EXISTS idx_sessions_user_id ON sessions(user_id);
CREATE INDEX IF NOT EXISTS idx_sessions_token ON sessions(refresh_token_hash);
CREATE INDEX IF NOT EXISTS idx_sessions_expires ON sessions(expires_at);
