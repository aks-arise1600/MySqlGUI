/**
* @file InsertValue.h
* @author Anil Kumar
* @date 15-11-2017
* @brief This is header of InsertValue class.
*/
#ifndef INSERTVALUE_H
#define INSERTVALUE_H
#include <QWidget>
#include <QListWidgetItem>
#include <QSqlQuery>
#include <QSqlError>
#include <common.h>
#include <QList>
#include <InsertLineForm.h>

namespace Ui {
class InsertValue;
}

class InsertValue : public QWidget
{
    Q_OBJECT

public:
    explicit InsertValue(QWidget *parent = 0, QString tblName = "NA");
    ~InsertValue();
    void AddItems(QString,QString,int);
public slots:
    void sl_Insert_into();
signals:
    void si_RefreshTable(QString,QStringList);
private:
    Ui::InsertValue *ui;
    QString strTableName; /**< Selected Table Name **/
    QList<InsertLineForm*> listInputs; /**< list of InsertLineForm class object **/
};

#endif // INSERTVALUE_H
