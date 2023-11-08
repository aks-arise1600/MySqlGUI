/**
* @file common.h
* @author Anil Kumar
* @date 7-11-2023
* @brief This is common header for all classes.
*/
#ifndef COMMON_H
#define COMMON_H

#include <QDebug>
#include <QDateTime>
#include <QMessageBox>




#define PRINT(func)      qDebug()<< QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss")+" "+func



#endif // COMMON_H
