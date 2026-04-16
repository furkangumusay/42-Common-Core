import { getDatabase } from '../config/database.js';

export type TournamentStatus = 'pending' | 'in_progress' | 'completed' | 'cancelled';

export type ParticipantStatus = 'registered' | 'playing' | 'eliminated' | 'winner';

export interface Tournament {
    id: number;
    name: string;
    description: string | null;
    status: TournamentStatus;
    max_players: number;
    current_round: number;
    winner_id: number | null;
    created_by: number;
    is_local: number;
    created_at: string;
    started_at: string | null;
    ended_at: string | null;
}

export interface TournamentParticipant {
    id: number;
    tournament_id: number;
    user_id: number | null;
    alias: string;
    placement: number | null;
    status: ParticipantStatus;
    is_guest: number;
    joined_at: string;
}

export interface TournamentWithCreator extends Tournament {
    creator_display_name: string;
    creator_avatar_url: string;
    participant_count: number;
}

export interface CreateTournamentInput {
    name: string;
    description?: string;
    max_players?: number;
    created_by: number;
    is_local?: boolean;
}

export type TournamentMatchStatus = 'pending' | 'in_progress' | 'completed' | 'cancelled';

export interface TournamentMatch {
    id: number;
    tournament_id: number;
    round: number;
    match_order: number;
    participant1_id: number | null;
    participant2_id: number | null;
    participant1_score: number;
    participant2_score: number;
    winner_participant_id: number | null;
    status: TournamentMatchStatus;
    duration_seconds: number | null;
    created_at: string;
    started_at: string | null;
    ended_at: string | null;
}

export interface CreateTournamentMatchInput {
    tournament_id: number;
    round: number;
    match_order: number;
    participant1_id?: number;
    participant2_id?: number;
}

export interface TournamentMatchWithParticipants extends TournamentMatch {
    participant1_alias: string | null;
    participant1_user_id: number | null;
    participant2_alias: string | null;
    participant2_user_id: number | null;
    winner_alias: string | null;
}

export class TournamentModel {
    private db = getDatabase();

    create(input: CreateTournamentInput): Tournament {
        const stmt = this.db.prepare(`
            INSERT INTO tournaments (name, description, max_players, created_by, is_local)
            VALUES (?, ?, ?, ?, ?)
        `);

        const result = stmt.run(
            input.name,
            input.description ?? null,
            input.max_players ?? 8,
            input.created_by,
            input.is_local ? 1 : 0
        );

        return this.findById(result.lastInsertRowid as number)!;
    }

    findById(id: number): Tournament | undefined {
        return this.db
            .prepare('SELECT * FROM tournaments WHERE id = ?')
            .get(id) as Tournament | undefined;
    }

    getWithCreator(id: number): TournamentWithCreator | undefined {
        return this.db
            .prepare(`
                SELECT 
                    t.*,
                    u.display_name as creator_display_name,
                    u.avatar_url as creator_avatar_url,
                    (SELECT COUNT(*) FROM tournament_participants WHERE tournament_id = t.id) as participant_count
                FROM tournaments t
                JOIN users u ON u.id = t.created_by
                WHERE t.id = ?
            `)
            .get(id) as TournamentWithCreator | undefined;
    }

    getAll(limit = 20, offset = 0, status?: TournamentStatus): TournamentWithCreator[] {
        let query = `
            SELECT 
                t.*,
                u.display_name as creator_display_name,
                u.avatar_url as creator_avatar_url,
                (SELECT COUNT(*) FROM tournament_participants WHERE tournament_id = t.id) as participant_count
            FROM tournaments t
            JOIN users u ON u.id = t.created_by
        `;

        const params: (string | number)[] = [];

        if (status) {
            query += ' WHERE t.status = ?';
            params.push(status);
        }

        query += ' ORDER BY t.created_at DESC LIMIT ? OFFSET ?';
        params.push(limit, offset);

        return this.db.prepare(query).all(...params) as TournamentWithCreator[];
    }

    updateStatus(id: number, status: TournamentStatus): boolean {
        const updates: { status: TournamentStatus; started_at?: string; ended_at?: string } = {
            status,
        };

        if (status === 'in_progress') {
            updates.started_at = new Date().toISOString();
        } else if (status === 'completed' || status === 'cancelled') {
            updates.ended_at = new Date().toISOString();
        }

        let query = 'UPDATE tournaments SET status = ?';
        const params: (string | number)[] = [status];

        if (updates.started_at) {
            query += ', started_at = ?';
            params.push(updates.started_at);
        }
        if (updates.ended_at) {
            query += ', ended_at = ?';
            params.push(updates.ended_at);
        }

        query += ' WHERE id = ?';
        params.push(id);

        const result = this.db.prepare(query).run(...params);
        return result.changes > 0;
    }

    setWinner(id: number, winnerId: number): boolean {
        const result = this.db
            .prepare('UPDATE tournaments SET winner_id = ?, status = ?, ended_at = ? WHERE id = ?')
            .run(winnerId, 'completed', new Date().toISOString(), id);
        return result.changes > 0;
    }

    advanceRound(id: number): boolean {
        const result = this.db
            .prepare('UPDATE tournaments SET current_round = current_round + 1 WHERE id = ?')
            .run(id);
        return result.changes > 0;
    }

    delete(id: number): boolean {
        const result = this.db.prepare('DELETE FROM tournaments WHERE id = ?').run(id);
        return result.changes > 0;
    }

    addParticipant(tournamentId: number, userId: number, alias: string): TournamentParticipant {
        const stmt = this.db.prepare(`
            INSERT INTO tournament_participants (tournament_id, user_id, alias, is_guest)
            VALUES (?, ?, ?, 0)
        `);

        const result = stmt.run(tournamentId, userId, alias);
        return this.getParticipant(result.lastInsertRowid as number)!;
    }

    addGuestParticipant(tournamentId: number, alias: string): TournamentParticipant {
        const stmt = this.db.prepare(`
            INSERT INTO tournament_participants (tournament_id, user_id, alias, is_guest)
            VALUES (?, NULL, ?, 1)
        `);

        const result = stmt.run(tournamentId, alias);
        return this.getParticipant(result.lastInsertRowid as number)!;
    }

    getParticipant(id: number): TournamentParticipant | undefined {
        return this.db
            .prepare('SELECT * FROM tournament_participants WHERE id = ?')
            .get(id) as TournamentParticipant | undefined;
    }

    getParticipants(tournamentId: number): (TournamentParticipant & {
        display_name: string | null;
        avatar_url: string | null;
    })[] {
        return this.db
            .prepare(`
                SELECT 
                    tp.*,
                    u.display_name,
                    u.avatar_url
                FROM tournament_participants tp
                LEFT JOIN users u ON u.id = tp.user_id
                WHERE tp.tournament_id = ?
                ORDER BY tp.placement ASC NULLS LAST, tp.joined_at ASC
            `)
            .all(tournamentId) as (TournamentParticipant & {
                display_name: string | null;
                avatar_url: string | null;
            })[];
    }
  
    updateParticipantStatus(
        tournamentId: number,
        userId: number,
        status: ParticipantStatus,
        placement?: number
    ): boolean {
        let query = 'UPDATE tournament_participants SET status = ?';
        const params: (string | number)[] = [status];

        if (placement !== undefined) {
            query += ', placement = ?';
            params.push(placement);
        }

        query += ' WHERE tournament_id = ? AND user_id = ?';
        params.push(tournamentId, userId);

        const result = this.db.prepare(query).run(...params);
        return result.changes > 0;
    }

    updateParticipantStatusById(
        participantId: number,
        status: ParticipantStatus,
        placement?: number
    ): boolean {
        let query = 'UPDATE tournament_participants SET status = ?';
        const params: (string | number)[] = [status];

        if (placement !== undefined) {
            query += ', placement = ?';
            params.push(placement);
        }

        query += ' WHERE id = ?';
        params.push(participantId);

        const result = this.db.prepare(query).run(...params);
        return result.changes > 0;
    }

    removeParticipant(tournamentId: number, userId: number): boolean {
        const result = this.db
            .prepare('DELETE FROM tournament_participants WHERE tournament_id = ? AND user_id = ?')
            .run(tournamentId, userId);
        return result.changes > 0;
    }

    isParticipant(tournamentId: number, userId: number): boolean {
        const result = this.db
            .prepare('SELECT 1 FROM tournament_participants WHERE tournament_id = ? AND user_id = ?')
            .get(tournamentId, userId);
        return !!result;
    }

    getParticipantCount(tournamentId: number): number {
        const result = this.db
            .prepare('SELECT COUNT(*) as count FROM tournament_participants WHERE tournament_id = ?')
            .get(tournamentId) as { count: number };
        return result.count;
    }

    getUserTournaments(userId: number, limit = 10): TournamentWithCreator[] {
        return this.db
            .prepare(`
                SELECT 
                    t.*,
                    u.display_name as creator_display_name,
                    u.avatar_url as creator_avatar_url,
                    (SELECT COUNT(*) FROM tournament_participants WHERE tournament_id = t.id) as participant_count
                FROM tournaments t
                JOIN users u ON u.id = t.created_by
                JOIN tournament_participants tp ON tp.tournament_id = t.id
                WHERE tp.user_id = ?
                ORDER BY t.created_at DESC
                LIMIT ?
            `)
            .all(userId, limit) as TournamentWithCreator[];
    }

    createMatch(input: CreateTournamentMatchInput): TournamentMatch {
        const stmt = this.db.prepare(`
            INSERT INTO tournament_matches (tournament_id, round, match_order, participant1_id, participant2_id)
            VALUES (?, ?, ?, ?, ?)
        `);

        const result = stmt.run(
            input.tournament_id,
            input.round,
            input.match_order,
            input.participant1_id ?? null,
            input.participant2_id ?? null
        );

        return this.getMatch(result.lastInsertRowid as number)!;
    }

    getMatch(id: number): TournamentMatch | undefined {
        return this.db
            .prepare('SELECT * FROM tournament_matches WHERE id = ?')
            .get(id) as TournamentMatch | undefined;
    }

    getMatchWithParticipants(id: number): TournamentMatchWithParticipants | undefined {
        return this.db
            .prepare(`
                SELECT 
                    tm.*,
                    p1.alias as participant1_alias,
                    p1.user_id as participant1_user_id,
                    p2.alias as participant2_alias,
                    p2.user_id as participant2_user_id,
                    pw.alias as winner_alias
                FROM tournament_matches tm
                LEFT JOIN tournament_participants p1 ON p1.id = tm.participant1_id
                LEFT JOIN tournament_participants p2 ON p2.id = tm.participant2_id
                LEFT JOIN tournament_participants pw ON pw.id = tm.winner_participant_id
                WHERE tm.id = ?
            `)
            .get(id) as TournamentMatchWithParticipants | undefined;
    }

    getMatchesByTournament(tournamentId: number): TournamentMatchWithParticipants[] {
        return this.db
            .prepare(`
                SELECT 
                    tm.*,
                    p1.alias as participant1_alias,
                    p1.user_id as participant1_user_id,
                    p2.alias as participant2_alias,
                    p2.user_id as participant2_user_id,
                    pw.alias as winner_alias
                FROM tournament_matches tm
                LEFT JOIN tournament_participants p1 ON p1.id = tm.participant1_id
                LEFT JOIN tournament_participants p2 ON p2.id = tm.participant2_id
                LEFT JOIN tournament_participants pw ON pw.id = tm.winner_participant_id
                WHERE tm.tournament_id = ?
                ORDER BY tm.round ASC, tm.match_order ASC
            `)
            .all(tournamentId) as TournamentMatchWithParticipants[];
    }

    getMatchesByRound(tournamentId: number, round: number): TournamentMatchWithParticipants[] {
        return this.db
            .prepare(`
                SELECT 
                    tm.*,
                    p1.alias as participant1_alias,
                    p1.user_id as participant1_user_id,
                    p2.alias as participant2_alias,
                    p2.user_id as participant2_user_id,
                    pw.alias as winner_alias
                FROM tournament_matches tm
                LEFT JOIN tournament_participants p1 ON p1.id = tm.participant1_id
                LEFT JOIN tournament_participants p2 ON p2.id = tm.participant2_id
                LEFT JOIN tournament_participants pw ON pw.id = tm.winner_participant_id
                WHERE tm.tournament_id = ? AND tm.round = ?
                ORDER BY tm.match_order ASC
            `)
            .all(tournamentId, round) as TournamentMatchWithParticipants[];
    }

    updateMatchResult(
        matchId: number,
        participant1Score: number,
        participant2Score: number,
        winnerParticipantId: number,
        durationSeconds?: number
    ): boolean {
        const result = this.db
            .prepare(`
                UPDATE tournament_matches 
                SET participant1_score = ?,
                    participant2_score = ?,
                    winner_participant_id = ?,
                    duration_seconds = ?,
                    status = 'completed',
                    ended_at = CURRENT_TIMESTAMP
                WHERE id = ?
            `)
            .run(
                participant1Score,
                participant2Score,
                winnerParticipantId,
                durationSeconds ?? null,
                matchId
            );
        return result.changes > 0;
    }

    startMatch(matchId: number): boolean {
        const result = this.db
            .prepare(`
                UPDATE tournament_matches 
                SET status = 'in_progress',
                    started_at = CURRENT_TIMESTAMP
                WHERE id = ? AND status = 'pending'
            `)
            .run(matchId);
        return result.changes > 0;
    }

    setMatchParticipant(
        matchId: number,
        position: 1 | 2,
        participantId: number
    ): boolean {
        const column = position === 1 ? 'participant1_id' : 'participant2_id';
        const result = this.db
            .prepare(`UPDATE tournament_matches SET ${column} = ? WHERE id = ?`)
            .run(participantId, matchId);
        return result.changes > 0;
    }

    isAliasUnique(tournamentId: number, alias: string): boolean {
        const result = this.db
            .prepare('SELECT 1 FROM tournament_participants WHERE tournament_id = ? AND alias = ?')
            .get(tournamentId, alias);
        return result === undefined;
    }

    getParticipantByAlias(tournamentId: number, alias: string): TournamentParticipant | undefined {
        return this.db
            .prepare('SELECT * FROM tournament_participants WHERE tournament_id = ? AND alias = ?')
            .get(tournamentId, alias) as TournamentParticipant | undefined;
    }
}

export const tournamentModel = new TournamentModel();
