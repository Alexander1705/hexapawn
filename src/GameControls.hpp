#ifndef GAMECONTROLS_HPP
#define GAMECONTROLS_HPP

#include <QWidget>
#include "Game.hpp"

class GameControls : public QWidget {
    Q_OBJECT

private:
    int mComplexity;
    Color mPlayerColor;

public:
    explicit GameControls(QWidget *parent = nullptr);

signals:
    void startClicked(int complexity, Color playerColor);

private slots:
    void setComplexity(int complexity);
    void setPlayerColor(Color playerColor);

private slots:
    void emitStart();
    void onWhitePlayerColorToggled(bool isWhite);
};

#endif // GAMECONTROLS_HPP
