/**
* @file sqlquery.h
* @author Anil Kumar
* @date 15-11-2017
* @brief This is header of SqlQuery class.
*/
#ifndef SQLQUERY_H
#define SQLQUERY_H

#include <QMainWindow>
#include <QObject>
#include <QSqlQuery>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QDebug>
#include <mysqllogin.h>
#include <QDialog>
#include <dialogselectdb.h>
#include <dialoguploadsql.h>
#include <insertvalue.h>

namespace Ui {
class SqlQuery;
}

class SqlQuery : public QMainWindow
{
    Q_OBJECT
    QString Table_Name; /**< Selected Table Name **/
public:
    explicit SqlQuery(QWidget *parent = 0);
    ~SqlQuery();
    QByteArray list;
    QString Column1,Column2,Column3,Column4,Tbl_name,Select,Star;
    int len;
    DialogSelectDB * sdb = 0; /**< Object of DialogSelectDB class **/
    QString str_query;
    QStringList strlist;
    QModelIndex Mdl_Index;
    InsertValue *ivalue = 0; /**< Object of InsertValue class **/

private slots:
    void sl_TreeViewList();
    void on_pushButton_Go_clicked();
    void On_Click_treeview(QModelIndex);
    void sl_ExitClose();
    void sl_SelectAll(QString);
    void on_pushButton_changeDB_clicked();
    void sl_QueryLineEdit();
    void on_pushButton_Upload_clicked();
    void onCustomContextMenu(const QPoint &);
    void sl_Insert_table_values();
    void sl_Struct_table();
    void sl_Browse_table();
    void sl_Drop_table();
    void sl_Import_table();
    void sl_Export_table();
    void sl_About();
private:
    Ui::SqlQuery *ui;
    QStandardItemModel *Model;
    QStandardItem *ItemMain;
    QStandardItem *Item;
    bool isExport;
    bool eventFilter(QObject *obj, QEvent *event);
};

#endif // SQLQUERY_H
