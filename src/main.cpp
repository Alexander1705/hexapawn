#include <QApplication>
#include <QDebug>
#include "MainWindow.hpp"
#include "Game.hpp"

int main(int argc, char** argv) {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
