#include "BoardView.hpp"
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#include "Minimax.hpp"

BoardView::BoardView(QWidget *parent) : QWidget(parent), m_isDragging(false) {
    this->setMinimumSize(160, 160);
}

void BoardView::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    QBrush whiteBrush(QColor(245, 222, 179), Qt::SolidPattern);
    QBrush blackBrush(QColor(139,  69,  19), Qt::SolidPattern);

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            painter.setBrush((i + j) % 2 == 0 ? whiteBrush : blackBrush);
            painter.drawRect(i * 50, j * 50, 50, 50);
        }
    }

    QImage whitePawnImg(":white_pawn.png");
    whitePawnImg = whitePawnImg.scaled(50, 50);
    for (const QPoint& pawn : m_gameState.pawns(Color::White)) {
        if (!m_isDragging || pawn != m_dragStartPosition) {
            painter.drawImage(pawn.x() * 50, pawn.y() * 50, whitePawnImg);
        }
    }

    QImage blackPawnImg(":black_pawn.png");
    blackPawnImg = blackPawnImg.scaled(50, 50);
    for (const QPoint& pawn : m_gameState.pawns(Color::Black)) {
        if (!m_isDragging || pawn != m_dragStartPosition) {
            painter.drawImage(pawn.x() * 50, pawn.y() * 50, blackPawnImg);
        }
    }

    if (m_isDragging) {
        painter.drawImage(m_dragCurrentPosition - QPoint(25, 25), (m_dragColor == Color::White ? whitePawnImg : blackPawnImg));

        QList<Move> possibleMoves = m_gameState.possibleMovesFrom(m_dragStartPosition);

        painter.setBrush(QBrush(QColor(127, 127, 127), Qt::Dense4Pattern));
        for (const Move& move : possibleMoves) {
            painter.drawRect(move.to.x() * 50, move.to.y() * 50, 50, 50);
        }
    }
}

void BoardView::mousePressEvent(QMouseEvent *event) {
    int x = event->pos().x() / 50;
    int y = event->pos().y() / 50;

    m_dragStartPosition = QPoint(x, y);

    if (m_gameState.isCaptured(m_dragStartPosition) && m_gameState.capturedByColor(m_dragStartPosition) == m_gameState.currentMoveColor()) {
        m_isDragging = true;
        m_dragColor = m_gameState.capturedByColor(m_dragStartPosition);
        m_dragCurrentPosition = event->pos();
        this->repaint();
    }
}

void BoardView::mouseMoveEvent(QMouseEvent* event) {
    if (m_isDragging) {
        m_dragCurrentPosition = event->pos();
        this->repaint();
    }
}

void BoardView::mouseReleaseEvent(QMouseEvent* event) {
    if (!m_isDragging) {
        return;
    }

    m_isDragging = false;

    int x = event->pos().x() / 50;
    int y = event->pos().y() / 50;

    QPoint releasePos(x, y);

    QList<Move> possibleMoves = m_gameState.possibleMovesFrom(m_dragStartPosition);

    for (const Move& move : possibleMoves) {
        if (move.to == releasePos) {
            m_gameState.apply(move);

            Minimax minimax(m_complexity);
            if (!m_gameState.possibleMoves().empty()) {
                Move m = minimax.getOptimalMove(m_gameState);
                m_gameState.apply(m);
            }
            break;
        }
    }

    this->repaint();
}

void BoardView::restartGame(int complexity, Color playerColor) {
    m_complexity = complexity;
    m_gameState = GameState();

    if (playerColor == Color::Black) {
        Minimax minimax(m_complexity);
        Move move = minimax.getOptimalMove(m_gameState);
        m_gameState.apply(move);
    }

    this->repaint();
}
