#include <iostream>
#include "login.h"
#include "QApplication"
int main(int argc,char* argv[]) {
    std::cout << "Hello, World!" << std::endl;
    QApplication *app=new QApplication(argc,argv);
    login * login1=new login(100,200);
    return app->exec();
}