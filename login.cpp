//
// Created by kiana on 2/1/18.
//
#include "login.h"
login::login(int height, int width) {
    QRect rec = QApplication::desktop()->screenGeometry();
    this->setGeometry(rec.width() / 2 - width / 2, rec.height() / 2 - height / 2, width, height);
    button =new QPushButton("start game");
    hLayout =new QHBoxLayout;
    hLayout->addWidget(button);
    setLayout(hLayout);
    connect(button,SIGNAL(clicked(bool)),this,SLOT(start_game()));
    show();
}
void login::start_game() {
    this->deleteLater();
    game * game1=new game(800,1600);
}

