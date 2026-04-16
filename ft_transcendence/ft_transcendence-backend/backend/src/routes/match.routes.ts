import { FastifyInstance } from 'fastify';
import { CreateMatchInput } from '../models/match.model.js';
import { matchController } from '../controllers/match.controller.js';
import { authenticate } from '../middleware/auth.middleware.js';

export async function matchRoutes(fastify: FastifyInstance) {

    fastify.post<{ Body: CreateMatchInput }>(
        '/',
        { preHandler: [authenticate] },
        matchController.createMatch.bind(matchController)
    );

    fastify.get('/:id', matchController.getMatch.bind(matchController));
    fastify.get('/', matchController.getMatches.bind(matchController));
}
