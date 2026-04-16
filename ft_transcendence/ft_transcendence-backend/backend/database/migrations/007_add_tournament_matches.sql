ALTER TABLE tournaments ADD COLUMN is_local INTEGER DEFAULT 0;

CREATE TABLE tournament_participants_new (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    tournament_id INTEGER NOT NULL,
    user_id INTEGER,
    
    alias TEXT NOT NULL,
    
    placement INTEGER,
    
    status TEXT DEFAULT 'registered' CHECK(status IN ('registered', 'playing', 'eliminated', 'winner')),
    
    is_guest INTEGER DEFAULT 0,
    
    joined_at DATETIME DEFAULT CURRENT_TIMESTAMP,
    
    FOREIGN KEY (tournament_id) REFERENCES tournaments(id) ON DELETE CASCADE,
    FOREIGN KEY (user_id) REFERENCES users(id) ON DELETE CASCADE
);

INSERT INTO tournament_participants_new (id, tournament_id, user_id, alias, placement, status, is_guest, joined_at)
SELECT 
    tp.id, 
    tp.tournament_id, 
    tp.user_id, 
    COALESCE(tp.alias, u.display_name, 'Player ' || tp.id),
    tp.placement, 
    tp.status, 
    0,
    tp.joined_at
FROM tournament_participants tp
LEFT JOIN users u ON u.id = tp.user_id;

DROP TABLE tournament_participants;

ALTER TABLE tournament_participants_new RENAME TO tournament_participants;

CREATE INDEX IF NOT EXISTS idx_tournament_participants_tournament ON tournament_participants(tournament_id);
CREATE INDEX IF NOT EXISTS idx_tournament_participants_user ON tournament_participants(user_id);
CREATE INDEX IF NOT EXISTS idx_tournament_participants_alias ON tournament_participants(alias);

CREATE TABLE IF NOT EXISTS tournament_matches (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    tournament_id INTEGER NOT NULL,
    
    round INTEGER NOT NULL,
    match_order INTEGER NOT NULL,
    
    participant1_id INTEGER,
    participant2_id INTEGER,
    
    participant1_score INTEGER DEFAULT 0,
    participant2_score INTEGER DEFAULT 0,
    
    winner_participant_id INTEGER,
    
    status TEXT DEFAULT 'pending' CHECK(status IN ('pending', 'in_progress', 'completed', 'cancelled')),
    
    duration_seconds INTEGER,
    
    created_at DATETIME DEFAULT CURRENT_TIMESTAMP,
    started_at DATETIME,
    ended_at DATETIME,
    
    FOREIGN KEY (tournament_id) REFERENCES tournaments(id) ON DELETE CASCADE,
    FOREIGN KEY (participant1_id) REFERENCES tournament_participants(id) ON DELETE SET NULL,
    FOREIGN KEY (participant2_id) REFERENCES tournament_participants(id) ON DELETE SET NULL,
    FOREIGN KEY (winner_participant_id) REFERENCES tournament_participants(id) ON DELETE SET NULL,
    
    UNIQUE(tournament_id, round, match_order)
);

CREATE INDEX IF NOT EXISTS idx_tournament_matches_tournament ON tournament_matches(tournament_id);
CREATE INDEX IF NOT EXISTS idx_tournament_matches_round ON tournament_matches(tournament_id, round);
CREATE INDEX IF NOT EXISTS idx_tournament_matches_status ON tournament_matches(status);
CREATE INDEX IF NOT EXISTS idx_tournament_matches_participants ON tournament_matches(participant1_id, participant2_id);
