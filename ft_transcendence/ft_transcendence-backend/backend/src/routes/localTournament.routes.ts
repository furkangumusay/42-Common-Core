import { FastifyInstance } from 'fastify';
import {
    createLocalTournament,
    addGuestParticipant,
    addParticipant,
    startTournament,
    recordMatchResult,
    completeTournament,
    getTournamentMatches,
    getTournamentBracket,
    getTournamentParticipants,
} from '../controllers/localTournament.controller.js';
import { authenticate } from '../middleware/auth.middleware.js';

const tournamentIdParams = {
    type: 'object',
    properties: {
        id: { type: 'string' }
    },
    required: ['id']
} as const;

const matchIdParams = {
    type: 'object',
    properties: {
        matchId: { type: 'string' }
    },
    required: ['matchId']
} as const;

export const localTournamentRoutes = async (fastify: FastifyInstance): Promise<void> => {

    fastify.post(
        '/create',
        { preHandler: [authenticate] },
        createLocalTournament
    );

    // Start tournament with bracket data
    fastify.post<{ Params: { id: string } }>(
        '/:id/start',
        {
            preHandler: [authenticate],
            schema: { params: tournamentIdParams }
        },
        startTournament
    );

    fastify.post(
        '/add-participant',
        { preHandler: [authenticate] },
        addParticipant
    );

    fastify.post(
        '/add-guest',
        { preHandler: [authenticate] },
        addGuestParticipant
    );

    fastify.post<{ Params: { matchId: string } }>(
        '/match/:matchId/result',
        {
            preHandler: [authenticate],
            schema: { params: matchIdParams }
        },
        recordMatchResult
    );

    fastify.get<{ Params: { id: string } }>(
        '/:id/participants',
        { schema: { params: tournamentIdParams } },
        getTournamentParticipants
    );

    fastify.get<{ Params: { id: string } }>(
        '/:id/matches',
        { schema: { params: tournamentIdParams } },
        getTournamentMatches
    );

    fastify.get<{ Params: { id: string } }>(
        '/:id/bracket',
        { schema: { params: tournamentIdParams } },
        getTournamentBracket
    );

    fastify.post<{ Params: { id: string } }>(
        '/:id/complete',
        {
            preHandler: [authenticate],
            schema: { params: tournamentIdParams }
        },
        completeTournament
    );
};
