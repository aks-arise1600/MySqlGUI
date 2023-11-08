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
#include <QSqlDatabase>
#include <QObject>
#include <QSqlQuery>
#include <DataQueryWindow.h>
#include <QTest>

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
    void sl_Show();
private:
    Ui::MysqlLogin *ui; /**< object of  MysqlLogin UI page**/
    QSqlDatabase dba;
protected:
    //bool eventFilter(QObject* obj, QEvent* event) ;
};

#endif // MYSQLLOGIN_H
