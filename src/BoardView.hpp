#ifndef BOARDVIEW_HPP
#define BOARDVIEW_HPP

#include <QWidget>
#include <QPaintEvent>
#include <QMouseEvent>
#include "Game.hpp"

class BoardView : public QWidget {
    Q_OBJECT

private:
    GameState m_gameState;
    int m_complexity;

    bool m_isDragging = false;
    QPoint m_dragStartPosition;
    QPoint m_dragCurrentPosition;
    Color m_dragColor;

public:
    explicit BoardView(QWidget *parent = nullptr);

private:
    void paintEvent(QPaintEvent* event) override;

    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

public slots:
    void restartGame(int complexity, Color playerColor);
};

#endif // BOARDVIEW_HPP
