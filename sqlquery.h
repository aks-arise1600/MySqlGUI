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

extern QString Table_Name;
extern bool Export;
namespace Ui {
class SqlQuery;
}

class SqlQuery : public QMainWindow
{
    Q_OBJECT

public:
    explicit SqlQuery(QWidget *parent = 0);
    ~SqlQuery();
    QByteArray list;
    QString Column1,Column2,Column3,Column4,Tbl_name,Select,Star;
    int len;
    DialogSelectDB * sdb;
    QString str_query;
    QStringList strlist;
    QModelIndex Mdl_Index;

private slots:
    void TreeViewList();
    void on_pushButton_Go_clicked();
    void On_Click_treeview(QModelIndex);
    void ExitClose();
    void SelectAll(QString);
    void on_pushButton_changeDB_clicked();
    void QueryLineEdit();
    void on_pushButton_Upload_clicked();
    void onCustomContextMenu(const QPoint &);
    void Insert_table_values();
    void Struct_table();
    void Browse_table();
    void Drop_table();
    void Import_table();
    void Export_table();

private:
    Ui::SqlQuery *ui;
    QStandardItemModel *Model;
    QStandardItem *ItemMain;
    QStandardItem *Item;
    bool eventFilter(QObject *obj, QEvent *event);
};

#endif // SQLQUERY_H
