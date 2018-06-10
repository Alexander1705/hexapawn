#include "MainWindow.hpp"
#include "BoardView.hpp"
#include <QHBoxLayout>
#include "GameControls.hpp"

MainWindow::MainWindow() : QMainWindow(nullptr) {
    auto central = new QWidget();
    auto layout = new QHBoxLayout();

    auto boardView = new BoardView(this);
    auto gameControls = new GameControls(this);
    QObject::connect(gameControls, &GameControls::startClicked, boardView, &BoardView::restartGame);

    layout->addWidget(boardView);
    layout->addWidget(gameControls);
    central->setLayout(layout);

    setCentralWidget(central);
}
