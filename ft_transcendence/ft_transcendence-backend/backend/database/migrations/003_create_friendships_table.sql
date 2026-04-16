CREATE TABLE IF NOT EXISTS friendships (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    
    requester_id INTEGER NOT NULL,
    addressee_id INTEGER NOT NULL,
    
    status TEXT DEFAULT 'pending' CHECK(status IN ('pending', 'accepted', 'blocked')),
    
    created_at DATETIME DEFAULT CURRENT_TIMESTAMP,
    updated_at DATETIME DEFAULT CURRENT_TIMESTAMP,
    
    FOREIGN KEY (requester_id) REFERENCES users(id) ON DELETE CASCADE,
    FOREIGN KEY (addressee_id) REFERENCES users(id) ON DELETE CASCADE,
    
    UNIQUE(requester_id, addressee_id)
);

CREATE INDEX IF NOT EXISTS idx_friendships_requester ON friendships(requester_id);
CREATE INDEX IF NOT EXISTS idx_friendships_addressee ON friendships(addressee_id);
CREATE INDEX IF NOT EXISTS idx_friendships_status ON friendships(status);

CREATE TRIGGER IF NOT EXISTS update_friendships_timestamp 
AFTER UPDATE ON friendships
BEGIN
    UPDATE friendships SET updated_at = CURRENT_TIMESTAMP WHERE id = NEW.id;
END;
