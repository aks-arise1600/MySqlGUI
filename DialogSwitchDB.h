/**
* @file DialogSwitchDB.h
* @author Anil Kumar
* @date 17-11-2017
* @brief This is header of DialogSwitchDB class.
*/
#ifndef DIALOGSWITCHDB_H
#define DIALOGSWITCHDB_H

#include <QDialog>
#include <QSqlQuery>
#include <common.h>

namespace Ui {
class DialogSwitchDB;
}

class DialogSwitchDB : public QDialog
{
    Q_OBJECT

public:
    explicit DialogSwitchDB(QWidget *parent = 0, QSqlDatabase *db_ = 0);
    ~DialogSwitchDB();

private slots:
    void on_pushButton_ok_clicked();
    void on_pushButton_Cancel_clicked();

signals:
    void si_ClosedSwitchDB(bool); // Status of is Switched or Not

private:
    Ui::DialogSwitchDB *ui;
    QSqlDatabase *dba;
};

#endif // DIALOGSWITCHDB_H
