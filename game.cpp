//
// Created by kiana on 2/1/18.
//
#include <iostream>
#include "game.h"
game::game(int height, int width) {
    QRect rec = QApplication::desktop()->screenGeometry();
    this->setGeometry(rec.width() / 2 - width / 2, rec.height() / 2 - height / 2, width, height);
    setStyleSheet("background-color: pink");
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            board[i][j]=0;
        }
    }
    board[3][3]=1;
    board[4][4]=1;
    board[3][4]=2;
    board[4][3]=2;
    show();
}
void game::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    QPen p;
    p.setWidth(4);
    p.setColor(Qt::white);
    painter.setPen(p);
    QFont font;
    font.setPixelSize(32);
    painter.setFont(font);
    painter.drawText(50,400,"white");
    std::string str=std::to_string(score(1));
    painter.drawText(50,450,QString::fromStdString(str));
    p.setColor(Qt::black);
    painter.setPen(p);
    str=std::to_string(score(2));
    painter.drawText(1500,450,QString::fromStdString(str));
    painter.drawText(1500,400,QString("black"));
    for(int i=0;i<9;i++)
    {
        p.setColor(Qt::black);
        p.setWidth(3);
        painter.setPen(p);
        painter.drawLine(100*i+400,0,100*i+400,800); //v
        painter.drawLine(400,100*i,1200,100*i); //h
    }
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            if(board[i][j]==1)
            {
                QPen pen=painter.pen();
                pen.setWidth(4);
                pen.setColor(Qt::white);
                painter.setPen(pen);
                painter.setBrush(Qt::white);
                painter.drawEllipse(i*100+50-40+400,j*100+50-40,80,80);
            }

            if(board[i][j]==2)
            {
                QPen pen=painter.pen();
                pen.setWidth(4);
                pen.setColor(Qt::black);
                painter.setPen(pen);
                painter.setBrush(Qt::black);
                painter.drawEllipse(i*100+50-40+400,j*100+50-40,80,80);
            }

        }
    }
    std::vector<QPoint> ss=moves(1);
    for(int i=0;i<ss.size();i++)
    {
        int x=ss[i].x();
        int y=ss[i].y();
        QPen pen=painter.pen();
        pen.setWidth(4);
        pen.setColor(Qt::green);
        painter.setPen(pen);
        painter.setBrush(Qt::green);
        painter.drawEllipse(x*100+50-10+400,y*100+50-10,20,20);
    }

}
void game::move(int x,int y,int player)
{
    board[x][y]=player;
    QPoint cordinations[8];
    cordinations[0]=QPoint(-1,-1);
    cordinations[1]=QPoint(-1,0);
    cordinations[2]=QPoint(-1,1);
    cordinations[3]=QPoint(0,-1);
    cordinations[4]=QPoint(0,1);
    cordinations[5]=QPoint(1,-1);
    cordinations[6]=QPoint(1,0);
    cordinations[7]=QPoint(1,1);
    std::vector<QPoint> reverses;
    for(int k=0;k<8;k++)
    {
        int cx=x+cordinations[k].x();
        int cy=y+cordinations[k].y();
        for(int l=0;cx<8 && cy<8 && cx>=0 && cy>=0;l++)
        {
            if(board[cx][cy]==0)
            {
                break;
            }
            if(board[cx][cy]==player)
            {
                if(l) {
                    reverses.push_back(cordinations[k]);
                }
                break;
            }
            cx=cx+cordinations[k].x();
            cy=cy+cordinations[k].y();
        }
    }
    for(int i=0;i<reverses.size();i++)
    {
        std::cout<<"all"<<player<<std::endl;
        int cx=x+reverses[i].x();
        int cy=y+reverses[i].y();
        while(cx>=0 && cy>=0 && cx<8 && cy<8 && board[cx][cy]!=player)
        {
            board[cx][cy]=player;
            cx=cx+reverses[i].x();
            cy=cy+reverses[i].y();
        }

    }

}
void game::mousePressEvent(QMouseEvent *ev) {
    if(ev->buttons() == Qt::LeftButton)
    {
        std::cout<<"fuck"<<std::endl;
        std::vector<QPoint> ss=moves(1);
        if(ss.size()==0 && moves(2).size()) {
            std::cout<<"ignored\n";
            cpu_move();
            update();
            return;
        }

        const QPoint p = ev->pos();
        int x=(p.x()-400)/100;
        int y=(p.y())/100;
        std::cout<<x<<","<<y<<std::endl;
        if(x>=8 || x<0 || y>=8 || y<0)
            return;
        for(int i=0;i<ss.size();i++)
        {
            if(ss[i].x()==x && ss[i].y()==y)
            {
                move(x,y,1);
                cpu_move();
                update();
                break;
            }
        }
        if(ss.size()==0 && moves(2).size()==0)
        {
            this->deleteLater();
            result *a=new result(200,320,score(1),score(2));
            return;
        }
    }
}
void game::cpu_move() {
    std::vector<QPoint> cmoves=moves(2);
    if(cmoves.size())
    {
        move(cmoves[0].x(),cmoves[0].y(),2);
    }
}
int game::score(int player) {
    int res=0;
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            if(board[i][j]==player)
                res++;
        }
    }
    return res;
}
std::vector<QPoint> game::moves(int player) {
    std::vector<QPoint> res;
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            if(board[i][j])
                continue;
            QPoint temp(i,j);
            bool ch=0;
            int cx,cy,l;
            l=0;
            cx=temp.x()+1;
            cy=temp.y()+1;
            while(!ch && cx>=0 && cy>=0 && cx<8 && cy<8)
            {
                if(board[cx][cy]==0)
                {
                    break;
                }
                if(board[cx][cy]==player)
                {
                    if(l) {
                        res.push_back(temp);
                        ch=1;
                    }
                    break;
                }
                cx=cx+1;
                cy=cy+1;
                l++;
            }
            l=0;
            cx=temp.x()+1;
            cy=temp.y();
            while(!ch && cx>=0 && cy>=0 && cx<8 && cy<8)
            {
                if(board[cx][cy]==0)
                {
                    break;
                }
                if(board[cx][cy]==player)
                {
                    if(l) {
                        res.push_back(temp);
                        ch=1;
                    }
                    break;
                }
                cx=cx+1;
                cy=cy;
                l++;
            }
            l=0;
            cx=temp.x()+1;
            cy=temp.y()-1;
            while(!ch && cx>=0 && cy>=0 && cx<8 && cy<8)
            {
                if(board[cx][cy]==0)
                {
                    break;
                }
                if(board[cx][cy]==player)
                {
                    if(l) {
                        res.push_back(temp);
                        ch=1;
                    }
                    break;
                }
                cx=cx+1;
                cy=cy-1;
                l++;
            }
            l=0;
            cx=temp.x();
            cy=temp.y()+1;
            while(!ch && cx>=0 && cy>=0 && cx<8 && cy<8)
            {
                if(board[cx][cy]==0)
                {
                    break;
                }
                if(board[cx][cy]==player)
                {
                    if(l) {
                        res.push_back(temp);
                        ch=1;
                    }
                    break;
                }
                cx=cx;
                cy=cy+1;
                l++;
            }
            l=0;
            cx=temp.x();
            cy=temp.y()-1;
            while(!ch && cx>=0 && cy>=0 && cx<8 && cy<8)
            {
                if(board[cx][cy]==0)
                {
                    break;
                }
                if(board[cx][cy]==player)
                {
                    if(l) {
                        res.push_back(temp);
                        ch=1;
                    }
                    break;
                }
                cx=cx;
                cy=cy-1;
                l++;
            }
            l=0;
            cx=temp.x()-1;
            cy=temp.y()+1;
            while(!ch && cx>=0 && cy>=0 && cx<8 && cy<8)
            {
                if(board[cx][cy]==0)
                {
                    break;
                }
                if(board[cx][cy]==player)
                {
                    if(l) {
                        res.push_back(temp);
                        ch=1;
                    }
                    break;
                }
                cx=cx-1;
                cy=cy+1;
                l++;
            }
            l=0;
            cx=temp.x()-1;
            cy=temp.y();
            while(!ch && cx>=0 && cy>=0 && cx<8 && cy<8)
            {
                if(board[cx][cy]==0)
                {
                    break;
                }
                if(board[cx][cy]==player)
                {
                    if(l) {
                        res.push_back(temp);
                        ch=1;
                    }
                    break;
                }
                cx=cx-1;
                cy=cy;
                l++;
            }
            l=0;
            cx=temp.x()-1;
            cy=temp.y()-1;
            while(!ch && cx>=0 && cy>=0 && cx<8 && cy<8)
            {
                if(board[cx][cy]==0)
                {
                    break;
                }
                if(board[cx][cy]==player)
                {
                    if(l) {
                        res.push_back(temp);
                        ch=1;
                    }
                    break;
                }
                cx=cx-1;
                cy=cy-1;
                l++;
            }

        }
    }
    return res;
}