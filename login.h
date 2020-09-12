//
// Created by kiana on 2/1/18.
//

#ifndef OTHELLO_LOGIN_H
#define OTHELLO_LOGIN_H

#include <QtWidgets>
#include <QWidget>
#include "game.h"
class login :public QWidget{
    Q_OBJECT
public:
    login(int,int);
private:
    QHBoxLayout *hLayout;
    QPushButton *button;
public slots:
    void start_game();
};
#endif //OTHELLO_LOGIN_H
