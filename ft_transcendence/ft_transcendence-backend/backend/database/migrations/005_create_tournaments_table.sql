CREATE TABLE IF NOT EXISTS tournaments (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    
    name TEXT NOT NULL,
    description TEXT,
    
    status TEXT DEFAULT 'pending' CHECK(status IN ('pending', 'in_progress', 'completed', 'cancelled')),
    
    max_players INTEGER DEFAULT 8,
    current_round INTEGER DEFAULT 0,
    
    winner_id INTEGER,
    
    created_by INTEGER NOT NULL,
    
    created_at DATETIME DEFAULT CURRENT_TIMESTAMP,
    started_at DATETIME,
    ended_at DATETIME,
    
    FOREIGN KEY (winner_id) REFERENCES users(id) ON DELETE SET NULL,
    FOREIGN KEY (created_by) REFERENCES users(id) ON DELETE CASCADE
);

CREATE TABLE IF NOT EXISTS tournament_participants (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    tournament_id INTEGER NOT NULL,
    user_id INTEGER NOT NULL,
    
    alias TEXT,
    
    placement INTEGER,
    
    status TEXT DEFAULT 'registered' CHECK(status IN ('registered', 'playing', 'eliminated', 'winner')),
    
    joined_at DATETIME DEFAULT CURRENT_TIMESTAMP,
    
    FOREIGN KEY (tournament_id) REFERENCES tournaments(id) ON DELETE CASCADE,
    FOREIGN KEY (user_id) REFERENCES users(id) ON DELETE CASCADE,
    
    UNIQUE(tournament_id, user_id)
);

CREATE INDEX IF NOT EXISTS idx_tournaments_status ON tournaments(status);
CREATE INDEX IF NOT EXISTS idx_tournaments_created_by ON tournaments(created_by);
CREATE INDEX IF NOT EXISTS idx_tournament_participants_tournament ON tournament_participants(tournament_id);
CREATE INDEX IF NOT EXISTS idx_tournament_participants_user ON tournament_participants(user_id);
