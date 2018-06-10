#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <QtCore>

enum class Color { White, Black };

struct Move {
    QPoint from;
    bool isCapturing;
    QPoint to;

    QString toString() const;
};

class GameState
{
private:
    Color mCurrentMoveColor;
    bool mIsCaptured[3][3];
    Color mCapturedColor[3][3];

public:
    GameState();

    void apply(const Move& move);
    void rollback(const Move& move);

    QList<Move> possibleMoves() const;
    QList<Move> possibleMovesFrom(const QPoint& square) const;

    QList<QPoint> pawns(Color color) const;

    bool isCaptured(const QPoint& square) const;
    Color capturedByColor(const QPoint& square) const;
    Color currentMoveColor() const;
};

#endif // GAMESTATE_HPP
