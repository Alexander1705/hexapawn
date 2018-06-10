#ifndef COMPUTERPLAYER_HPP
#define COMPUTERPLAYER_HPP

#include "Game.hpp"

class Minimax {
private:
    int mComplexity;

public:
    explicit Minimax(int complexity);
    Move getOptimalMove(GameState& gameState);

public slots:
    void setComplexity(int complexity);

private:
    int minimax(GameState& gameState, int depth);
    int heuristic(GameState& gameState);
};

#endif // COMPUTERPLAYER_HPP
