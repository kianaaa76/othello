//
// Created by kiana on 2/1/18.
//

#ifndef OTHELLO_RESULT_H
#define OTHELLO_RESULT_H
#include <QtWidgets/QWidget>
#include <QtWidgets>
#include "login.h"
class result : public QWidget{
Q_OBJECT
public:
    result(int height, int width,int player_score,int CPU_score);

private:
    QHBoxLayout *t1;
    QHBoxLayout *t2;
    QVBoxLayout *Q;
    QLabel *player;
    QLabel *cpu;
    QLabel *board;
    QLabel *board2;
    QPushButton * btn;
public slots:
    void returnTologin();
};
#endif //OTHELLO_RESULT_H
