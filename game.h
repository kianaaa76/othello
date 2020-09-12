//
// Created by kiana on 2/1/18.
//

#ifndef OTHELLO_GAME_H
#define OTHELLO_GAME_H

#include <QWidget>
#include <QtWidgets>
#include <QtGui/QMouseEvent>
#include "result.h"
class game:public QWidget{
public:
    game(int,int);
    void mousePressEvent(QMouseEvent *ev);
private:
    int board[8][8];
    int score(int player);
    std::vector<QPoint>moves(int player);
    void cpu_move();
    void move(int,int,int);

protected:
    void paintEvent(QPaintEvent *);

};
#endif //OTHELLO_GAME_H
