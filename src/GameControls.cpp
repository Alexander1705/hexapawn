#include "GameControls.hpp"
#include <QVBoxLayout>
#include <QRadioButton>
#include <QPushButton>
#include <QGroupBox>
#include <QSpinBox>
#include <QFormLayout>

GameControls::GameControls(QWidget *parent) : QWidget(parent) {
    auto mainLayout = new QVBoxLayout();

    auto playerSideGroup = new QGroupBox("Player Color");
    auto playerSideLayout = new QVBoxLayout();
    auto whiteRadio = new QRadioButton("White");
    auto blackRadio = new QRadioButton("Black");
    whiteRadio->setChecked(true);
    playerSideLayout->addWidget(whiteRadio);
    playerSideLayout->addWidget(blackRadio);
    playerSideGroup->setLayout(playerSideLayout);

    auto complexitySpinBox = new QSpinBox();
    auto complexityLayout = new QFormLayout();
    complexityLayout->addRow("AI Complexity", complexitySpinBox);

    auto startButton = new QPushButton("Start");

    mainLayout->addWidget(playerSideGroup);
    mainLayout->addLayout(complexityLayout);
    mainLayout->addWidget(startButton);
    this->setLayout(mainLayout);

    QObject::connect(complexitySpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &GameControls::setComplexity);
    QObject::connect(whiteRadio, &QRadioButton::toggled, this, &GameControls::onWhitePlayerColorToggled);
    QObject::connect(startButton, &QPushButton::clicked, this, &GameControls::emitStart);
}

void GameControls::setComplexity(int complexity) {
    mComplexity = complexity;
}

void GameControls::setPlayerColor(Color playerColor) {
    mPlayerColor = playerColor;
}

void GameControls::emitStart() {
    emit startClicked(mComplexity, mPlayerColor);
}

void GameControls::onWhitePlayerColorToggled(bool isWhite) {
    if (isWhite) {
        mPlayerColor = Color::White;
    } else {
        mPlayerColor = Color::Black;
    }
}
