/**
* @file main.cpp
* @author Anil Kumar
* @date 15-11-2017
* @brief This main class
*/
#include <MysqlLogin.h>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MysqlLogin w;
    w.show();

    return a.exec();
}
