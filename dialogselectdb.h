/**
* @file DialogSelectDB.h
* @author Anil Kumar
* @date 17-11-2017
* @brief This is header of DialogSelectDB class.
*/
#ifndef DIALOGSELECTDB_H
#define DIALOGSELECTDB_H

#include <QDialog>
#include <QSqlQuery>

namespace Ui {
class DialogSelectDB;
}

class DialogSelectDB : public QDialog
{
    Q_OBJECT

public:
    explicit DialogSelectDB(QWidget *parent = 0);
    ~DialogSelectDB();

private slots:
    void on_pushButton_ok_clicked();

private:
    Ui::DialogSelectDB *ui;
};

#endif // DIALOGSELECTDB_H
