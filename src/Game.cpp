#include "Game.hpp"
#include <QDebug>

Color opposite(Color color) {
    return (color == Color::White ? Color::Black : Color::White);
}

QString Move::toString() const {
    QString string;

    string += ('a' + from.x()) + QString::number(from.y() + 1);
    string += (isCapturing ? 'x' : '-');
    string += ('a' + to.x()) + QString::number(to.y() + 1);

    return string;
}

GameState::GameState() :mCurrentMoveColor(Color::White) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (i == 0) {
                mIsCaptured[i][j] = true;
                mCapturedColor[i][j] = Color::White;
            } else if (i == 2) {
                mIsCaptured[i][j] = true;
                mCapturedColor[i][j] = Color::Black;
            } else {
                mIsCaptured[i][j] = false;
            }
        }
    }
}

void GameState::apply(const Move& move) {
    if (!mIsCaptured[move.from.x()][move.from.y()]) {
        qCritical() << "Move from empty square";
    }

    if (mIsCaptured[move.to.x()][move.to.y()] && !move.isCapturing) {
        qCritical() << "Capturing empty square";
    }

    mIsCaptured[move.from.x()][move.from.y()] = false;
    mIsCaptured[move.to.x()][move.to.y()] = true;
    mCapturedColor[move.to.x()][move.to.y()] = mCapturedColor[move.from.x()][move.from.y()];
    mCurrentMoveColor = opposite(mCurrentMoveColor);
}

void GameState::rollback(const Move& move) {
    if (mIsCaptured[move.from.x()][move.from.y()]) {
        qCritical() << "Rollback error1";
    }

    if (!mIsCaptured[move.to.x()][move.to.y()]) {
        qCritical() << "Rollback error2";
    }

    mIsCaptured[move.from.x()][move.from.y()] = true;
    mCapturedColor[move.from.x()][move.from.y()] = mCapturedColor[move.to.x()][move.to.y()];

    if (!move.isCapturing) {
        mIsCaptured[move.to.x()][move.to.y()] = false;
    } else {
        mCapturedColor[move.to.x()][move.to.y()] = opposite(mCapturedColor[move.to.x()][move.to.y()]);
    }

    mCurrentMoveColor = opposite(mCurrentMoveColor);
}

QList<Move> GameState::possibleMoves() const {
    for (int i = 0; i < 3; ++i) {
        if (mIsCaptured[0][i] && mCapturedColor[0][i] == Color::Black) {
            return {};
        }

        if (mIsCaptured[2][i] && mCapturedColor[2][i] == Color::White) {
            return {};
        }
    }
    QList<Move> moves;

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (mCapturedColor[i][j] == mCurrentMoveColor) {
                moves += possibleMovesFrom(QPoint(i, j));
            }
        }
    }

    return moves;
}

QList<Move> GameState::possibleMovesFrom(const QPoint& source) const {
    for (int i = 0; i < 3; ++i) {
        if (mIsCaptured[0][i] && mCapturedColor[0][i] == Color::Black) {
            return {};
        }

        if (mIsCaptured[2][i] && mCapturedColor[2][i] == Color::White) {
            return {};
        }
    }

    if (!mIsCaptured[source.x()][source.y()] || mCapturedColor[source.x()][source.y()] != mCurrentMoveColor) {
        return {};
    }

    Color color = mCapturedColor[source.x()][source.y()];
    int forwardDir = (color == Color::White ? 1 : -1);

    QPoint forward(source.x() + forwardDir, source.y());
    QPoint left(source.x() + forwardDir, source.y() - 1);
    QPoint right(source.x() + forwardDir, source.y() + 1);

    if (forward.x() == -1 || forward.x() == 3) {
        return {};
    }

    QList<Move> moves;

    if (!mIsCaptured[forward.x()][forward.y()]) {
        moves += Move{source, false, forward};
    }

    if (left.y() != -1 && mIsCaptured[left.x()][left.y()] && mCapturedColor[left.x()][left.y()] != color) {
        moves += Move{source, true, left};
    }

    if (right.y() != 3 && mIsCaptured[right.x()][right.y()] && mCapturedColor[right.x()][right.y()] != color) {
        moves += Move{source, true, right};
    }

    return moves;
}

QList<QPoint> GameState::pawns(Color color) const {
    QList<QPoint> pawns;

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (mIsCaptured[i][j] && mCapturedColor[i][j] == color) {
                pawns += QPoint(i, j);
            }
        }
    }

    return pawns;
}

bool GameState::isCaptured(const QPoint& square) const {
    return mIsCaptured[square.x()][square.y()];
}

Color GameState::capturedByColor(const QPoint& square) const {
    return mCapturedColor[square.x()][square.y()];
}

Color GameState::currentMoveColor() const {
    return mCurrentMoveColor;
}
