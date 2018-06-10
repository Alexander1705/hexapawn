#include "Minimax.hpp"

Minimax::Minimax(int complexity) : mComplexity(complexity) {}


Move Minimax::getOptimalMove(GameState& gameState) {
    int bestScore;

    bool isMaximizing = gameState.currentMoveColor() == Color::White;
    if (isMaximizing) {
        bestScore = INT_MIN;
    } else {
        bestScore = INT_MAX;
    }

    Move bestMove = gameState.possibleMoves().first();

    for (const Move& move : gameState.possibleMoves()) {
        gameState.apply(move);
        int score = minimax(gameState, mComplexity, INT_MIN, INT_MAX);

        if ((isMaximizing && score > bestScore) || (!isMaximizing && score < bestScore)) {
            bestScore = score;
            bestMove = move;
        }

        gameState.rollback(move);
    }

    return bestMove;
}

int Minimax::minimax(GameState& gameState, int depth, int alpha, int beta) {
    if (depth == 0) {
        return heuristic(gameState);
    }

    bool isMaximizing = gameState.currentMoveColor() == Color::White;

    for (const Move& move : gameState.possibleMoves()) {
        gameState.apply(move);
        int score = minimax(gameState, depth - 1, alpha, beta);
        gameState.rollback(move);

        if (isMaximizing) {
            alpha = std::max(alpha, score);
        } else {
            beta = std::min(beta, score);
        }

        if (alpha >= beta) {
            break;
        }
    }

    return isMaximizing ? alpha : beta;
}

int Minimax::heuristic(GameState& gameState) {
    int score = 0;

    for (const QPoint& pawn : gameState.pawns(Color::White)) {
        score += (1 << (pawn.x() + 1)) - 1;
    }

    for (const QPoint& pawn : gameState.pawns(Color::Black)) {
        score -= (1 << (3 - pawn.x())) - 1;
    }

    return score;
}
