/**
* @file MysqlLogin.h
* @author Anil Kumar
* @date 15-11-2017
* @brief This is header of MysqlLogin class.
*/
#ifndef MYSQLLOGIN_H
#define MYSQLLOGIN_H

#include <QMainWindow>
#include <QDebug>
#include <QMessageBox>
#include <QtSql/QSqlDatabase>
#include <QObject>
#include <QSqlQuery>
#include <sqlquery.h>
#include <QTest>

extern QString dataBA;

namespace Ui {
class MysqlLogin;
}

class MysqlLogin : public QMainWindow
{
    Q_OBJECT

public:
    explicit MysqlLogin(QWidget *parent = 0);
    ~MysqlLogin();
    const QString HostName();
    const QString UserName();
    const QString Password();
    const QString Database();
    bool Connection;

private slots:
    void on_pushButton_Clear_clicked();

    void on_pushButton_open_clicked();

private:
    Ui::MysqlLogin *ui;
protected:
    //bool eventFilter(QObject* obj, QEvent* event) ;
};

#endif // MYSQLLOGIN_H
