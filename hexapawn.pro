QT       += core gui widgets

TARGET = hexapawn
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    src/main.cpp \
    src/MainWindow.cpp \
    src/BoardView.cpp \
    src/Game.cpp \
    src/Minimax.cpp \
    src/GameControls.cpp

HEADERS += \
    src/BoardView.hpp \
    src/Game.hpp \
    src/MainWindow.hpp \
    src/Minimax.hpp \
    src/GameControls.hpp

RESOURCES += res/res.qrc
