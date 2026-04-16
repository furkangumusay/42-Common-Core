ALTER TABLE users ADD COLUMN is_ai INTEGER DEFAULT 0;

CREATE TABLE match_history_new (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    
    player1_id INTEGER NOT NULL,
    player2_id INTEGER NOT NULL,
    
    player1_score INTEGER NOT NULL DEFAULT 0,
    player2_score INTEGER NOT NULL DEFAULT 0,
    
    winner_id INTEGER,
    
    game_type TEXT DEFAULT 'pong' CHECK(game_type IN ('pong', 'tournament', 'ai', 'other')),
    
    tournament_id INTEGER,
    
    duration_seconds INTEGER,
    
    started_at DATETIME,
    ended_at DATETIME DEFAULT CURRENT_TIMESTAMP,
    
    FOREIGN KEY (player1_id) REFERENCES users(id) ON DELETE CASCADE,
    FOREIGN KEY (player2_id) REFERENCES users(id) ON DELETE CASCADE,
    FOREIGN KEY (winner_id) REFERENCES users(id) ON DELETE SET NULL
);

INSERT INTO match_history_new 
SELECT * FROM match_history;

DROP TABLE match_history;

ALTER TABLE match_history_new RENAME TO match_history;

CREATE INDEX IF NOT EXISTS idx_match_player1 ON match_history(player1_id);
CREATE INDEX IF NOT EXISTS idx_match_player2 ON match_history(player2_id);
CREATE INDEX IF NOT EXISTS idx_match_winner ON match_history(winner_id);
CREATE INDEX IF NOT EXISTS idx_match_game_type ON match_history(game_type);
CREATE INDEX IF NOT EXISTS idx_match_ended_at ON match_history(ended_at);

INSERT OR IGNORE INTO users (email, display_name, is_ai, password_hash, avatar_url)
VALUES ('ai-player@system.local', 'AI Player', 1, '', 'default-avatar.png');
