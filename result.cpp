//
// Created by kiana on 2/1/18.
//

#include "result.h"
result::result(int height, int width, int player_score, int CPU_score) {
    QRect rec = QApplication::desktop() -> screenGeometry();
    this -> setGeometry(rec.width() / 2 - width / 2, rec.height() / 2 - height / 2, width, height);
    Q=new QVBoxLayout;
    t1=new QHBoxLayout;
    t2=new QHBoxLayout;
    player=new QLabel("your score: ");
    cpu=new QLabel("CPU Score: ");
    board=new QLabel;
    board2=new QLabel;
    btn=new QPushButton("return login");
    if(player_score>CPU_score)
    {
        board->setText("you won");
    }
    if(player_score==CPU_score)
    {
        board->setText("Draw");
    }
    if(player_score<CPU_score)
    {
        board->setText("you lose");
    }
    std::string str="result: "+std::to_string(player_score);
    str=str+" - ";
    str=str+std::to_string(CPU_score);
    board2->setText(QString::fromStdString(str));
    t1->addWidget(player);
    t1->addWidget(board);
    t2->addWidget(cpu);
    t2->addWidget(board2);
    Q->addLayout(t1);
    Q->addLayout(t2);
    Q->addWidget(btn);
    connect(btn,SIGNAL(clicked(bool)),this,SLOT(returnTologin()));
    setLayout(Q);
    show();
}
void result::returnTologin()  {
    this->deleteLater();
    login *a=new login(100,200);
}
