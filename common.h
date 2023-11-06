#ifndef COMMON_H
#define COMMON_H

#include <QDebug>
#include <QDateTime>





#define PRINT(func)      qDebug()<< QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss")+" "+func



#endif // COMMON_H
