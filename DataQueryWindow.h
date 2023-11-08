/**
* @file DataQueryWindow.h
* @author Anil Kumar
* @date 15-11-2017
* @brief This is header of DataQueryWindow class.
*/
#ifndef DATAQUERYWINDOW_H
#define DATAQUERYWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QSqlQuery>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QDebug>
#include <QDialog>
#include <DialogSelectDB.h>
#include <DialogUploadSQL.h>
#include <InsertValue.h>

namespace Ui {
class DataQueryWindow;
}

class DataQueryWindow : public QMainWindow
{
    Q_OBJECT
    QString Table_Name; /**< Selected Table Name **/
public:
    explicit DataQueryWindow(QWidget *parent = 0, QSqlDatabase *db_ = 0);
    ~DataQueryWindow();
    QByteArray list;
    DialogSelectDB * sdb = 0; /**< Object of DialogSelectDB class **/
    QString str_query;
    QStringList strlist;
    QModelIndex Mdl_Index;
    InsertValue *ivalue = 0; /**< Object of InsertValue class **/

signals:
    void si_ShowLogin();

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
    Ui::DataQueryWindow *ui; /**< pointer object of DataQueryWindow UI page **/
    QStandardItemModel *Model; /**< pointer object of QStandardItemModel **/
    QStandardItem *ItemMain; /**< pointer object of QStandardItem **/
    QStandardItem *Item; /**< pointer object of QStandardItem **/
    bool isExport;
    QSqlDatabase *dba; /**< pointer object of QSqlDatabase **/
    bool eventFilter(QObject *obj, QEvent *event);
};

#endif // DATAQUERYQINDOW_H
