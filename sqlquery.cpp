/**
* @file sqlquery.cpp
* @author Anil Kumar
* @date 15-11-2017
* @brief This sqlquery class, it's handle all SQL query as per clicked button.
*/


#include "sqlquery.h"
#include "ui_sqlquery.h"
extern QSqlDatabase db;

/**
 * @brief SqlQuery::SqlQuery
 * @param parent
 */
SqlQuery::SqlQuery(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SqlQuery)
{
    ui->setupUi(this);
    list.clear();
    ui->treeView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->treeView, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(onCustomContextMenu(const QPoint &)));
    connect(ui->treeView,SIGNAL(clicked(QModelIndex)),this,SLOT(On_Click_treeview(QModelIndex)));

    connect(ui->actionChange_Database,SIGNAL(triggered(bool)),SLOT(on_pushButton_changeDB_clicked()));
    connect(ui->actionQuit,SIGNAL(triggered(bool)),SLOT(sl_ExitClose()));
    connect(ui->actionAbout,SIGNAL(triggered(bool)),SLOT(sl_About()));

    ui->lineEdit_Query->installEventFilter(this);

    ui->tableView_QueryData->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    sl_TreeViewList();
    ui->pushButton_Upload->hide();
    connect(ui->pushButton_Exit,SIGNAL(clicked()),this,SLOT(sl_ExitClose()));
    connect(ui->pushButton_Clear,SIGNAL(clicked()),ui->lineEdit_Query,SLOT(clear()));
    ui->pushButton_Exit->setDefault(true);

    isExport=false;

}

/**
 * @brief SqlQuery::~SqlQuery
 */
SqlQuery::~SqlQuery()
{
    delete ui;
    delete Item;
    delete ItemMain;
    delete Model;
}

/**
 * @brief SqlQuery::sl_TreeViewList
 */
void SqlQuery::sl_TreeViewList()
{
    ui->lineEdit_Query->clear();
    int i=0;
    PRINT(__FUNCTION__)<<"in tree Database "<<db.databaseName();
    ui->label_selecteDB->setText(db.databaseName());
    QSqlQuery query0("use "+db.databaseName());
    query0.next();

    Model =new QStandardItemModel;
    ItemMain= new QStandardItem(db.databaseName()+"@"+db.hostName());
    Model->setHorizontalHeaderItem(0,ItemMain);
    ItemMain= new QStandardItem(db.databaseName());
    Model->setItem(0,ItemMain);

    QSqlQuery query1("show tables from "+db.databaseName());
    while(query1.next())
    {
        Item = new QStandardItem (query1.value(0).toString());
        ItemMain->appendRow(Item);
        i++;
    }
    if(i==0)
        ui->pushButton_Upload->show();
    else
        ui->pushButton_Upload->hide();
    ui->treeView->setModel(Model);
    ui->treeView->expandAll();
    ui->treeView->show();
}

/**
 * @brief SqlQuery::on_pushButton_Go_clicked
 */
void SqlQuery::on_pushButton_Go_clicked()
{
    ui->tableView_QueryData->repaint();

    ui->label_error->clear();
    strlist.clear();
    if(!ui->lineEdit_Query->text().isEmpty())
    {
        str_query=ui->lineEdit_Query->text();
        QSqlQuery Test_query;
        bool test_bool= Test_query.exec(str_query);
        if(test_bool)
        {
            int i=0;len=0;
            PRINT(__FUNCTION__)<<str_query<<str_query.length();
            int SpaceCount=0;
            while(i<str_query.length()-1)
            {
                if(str_query[i]==' ')
                    SpaceCount++;
                i++;
            }

            i=0;
            while(i<SpaceCount+1)
            {
                strlist<<str_query.split(" ").at(i);
                i++;
            }

            //PRINT(__FUNCTION__)<<"list"<<strlist;
            i=0;
            if(strlist.at(0)=="select" && strlist.at(1)=="*")
            {
                sl_SelectAll(strlist.at(3));
            }
            else if(strlist.at(0)=="select" && strlist.at(1)!="*")
            {
                int size;int col=1;
                for(int k=0;k<strlist.size();k++)
                {
                    QString strr=strlist.at(k);
                    if(strr.toLower()=="from")
                        size=k-1;
                }
                Model =new QStandardItemModel;
                while(size>0)
                {
                    QString str1=strlist.at(col);
                    //PRINT(__FUNCTION__)<<str1<<str1[str1.size()-1];
                    QString str2;
                    if(str1[str1.size()-1]==',')
                    {
                        int j=0;
                        while(j<str1.size()-1)
                        {
                            str2[j]=str1[j];
                            j++;
                        }
                        //PRINT(__FUNCTION__)<<"coma-word "<<str2;
                    }
                    else
                        str2=strlist.at(col);
                    //PRINT(__FUNCTION__)<<"str2 "<<str2;
                    Item = new QStandardItem (str2);
                    Model->setHorizontalHeaderItem(i,Item);
                    i++;
                    col++;
                    size--;
                }
                int totalColumn=i;
                i=0;
                QSqlQuery query2;
                bool ex = query2.exec(str_query);
                if(ex)
                {
                    while(query2.next())
                    {

                        for(int k=0;k<totalColumn;k++)
                        {
                            Item = new QStandardItem (query2.value(k).toString());
                            Model->setItem(i,k,Item);

                            ////////// * alternate color of rows  */////////////////
                            if(i%2==0)
                                Model->item(i,k)->setBackground(Qt::darkGray);
                            else
                                Model->item(i,k)->setBackground(Qt::lightGray);
                            ////////////////////////////////////////////////////////
                        }
                        i++;
                    }
                    ui->label_error->setText("<font color=green>Displayed  !!</font>");
                }
                else
                    ui->label_error->setText(query2.lastError().text());
                ui->tableView_QueryData->setModel(Model);
            }
            else
            {
                QString str=strlist.at(0);
                PRINT(__FUNCTION__)<<"keyword "<<str.toLower();
                if(str.toLower()=="update"||str.toLower()=="drop"||str.toLower()=="create"||str.toLower()=="delete"||str.toLower()=="insert")
                {
                    QSqlQuery query2;
                    bool ex = query2.exec(str_query);
                    if(!ex)
                    {
                        ui->label_error->setText(query2.lastError().text().split(";").at(0));
                        PRINT(__FUNCTION__)<<query2.lastError().text().split(";").at(0);
                    }
                    else
                    {
                        if(str.toLower()=="update")
                        {
                            ui->label_error->setText("<font color=green>Successfully updated !!</font>");
                            sl_SelectAll(strlist.at(1));
                        }
                        else if(str.toLower()=="drop")
                        {
                            ui->label_error->setText("<font color=green>Successfully droped !!</font>");
                            //sl_SelectAll(strlist.at(1));
                            sl_TreeViewList();
                        }
                        else if(str.toLower()=="create" && strlist.size()==3)
                        {
                            ui->label_error->setText("<font color=green>Successfully created database !!</font>");
                            //sl_SelectAll(strlist.at(1));
                            db.setDatabaseName(strlist.at(2));
                            sl_TreeViewList();
                        }
                        else if(str.toLower()=="delete")
                        {
                            ui->label_error->setText("<font color=green>deleted !!</font>");
                            sl_SelectAll(strlist.at(2));
                        }
                        else if(str.toLower()=="create" && QString(strlist.at(1)).toLower()=="table")
                        {
                            sl_TreeViewList();
                            ui->tableView_QueryData->setModel(nullptr);
                        }
                        else if(str.toLower()=="insert")
                        {
                            sl_SelectAll(strlist.at(2));
                        }
                    }
                }
            }
        }
        else
            ui->label_error->setText(Test_query.lastError().text());
    }
    else
        PRINT(__FUNCTION__)<<"Query not found !";

}

/**
 * @brief SqlQuery::On_Click_treeview
 * @param M_index
 */
void SqlQuery::On_Click_treeview(QModelIndex M_index)
{
    QVariant data = ui->treeView->model()->data(M_index);
    QString text = data.toString();
    //PRINT(__FUNCTION__)<< "Model Index "/*<<M_index */<<text;
    if(text!=db.databaseName())
    {
        ui->lineEdit_Query->setText("select * from "+text);
        sl_SelectAll(text);
    }
    else
    {
        ui->tableView_QueryData->setModel(nullptr);
        ui->lineEdit_Query->clear();
    }

}

/**
 * @brief SqlQuery::sl_ExitClose
 */
void SqlQuery::sl_ExitClose()
{
    db.close();
    this->close();
    MysqlLogin *MyLog= new MysqlLogin;
    MyLog->show();
}

void SqlQuery::sl_SelectAll(QString str)
{
    ui->label_Table->setText(str);
    list.clear();
    int i=0;
    Model =new QStandardItemModel;

    QSqlQuery query4("show columns from "+str);
    while(query4.next())
    {
        Item = new QStandardItem (query4.value(0).toString());
        Model->setHorizontalHeaderItem(i,Item);
        i++;
    }
    list.append("\n\n");
    int totalColumn=i;
    QSqlQuery query3("select * from "+str);
    i=0;
    while (query3.next())
    {
        for(int k=0;k<totalColumn;k++)
        {
            Item = new QStandardItem (query3.value(k).toString());
            Model->setItem(i,k,Item);

            ////////// * alternate color of rows  */////////////////
            if(i%2==0)
                Model->item(i,k)->setBackground(Qt::darkGray);
            else
                Model->item(i,k)->setBackground(Qt::lightGray);
            ////////////////////////////////////////////////////////
        }
        i++;
    }
    ui->tableView_QueryData->setModel(Model);
    //PRINT(__FUNCTION__)<<ui->treeView->size();
}

/**
 * @brief SqlQuery::on_pushButton_changeDB_clicked
 */
void SqlQuery::on_pushButton_changeDB_clicked()
{
    if(sdb)
        delete sdb;

    sdb=new DialogSelectDB(this);
    sdb->exec();
    sl_TreeViewList();
    ui->tableView_QueryData->setModel(nullptr);
    ui->label_selecteDB->setText(db.databaseName());
}

/**
 * @brief SqlQuery::sl_QueryLineEdit
 */
void SqlQuery::sl_QueryLineEdit()
{
    //PRINT(__FUNCTION__)<<"GO ";
    ui->pushButton_Go->setDefault(true);
    ui->pushButton_Exit->setDefault(false);
}

void SqlQuery::on_pushButton_Upload_clicked()
{
    //PRINT(__FUNCTION__)<<db.databaseName()<<db.userName()<<db.password();
    DialogUploadSQL *Upload_sql = new DialogUploadSQL(0,isExport);
    connect(Upload_sql,SIGNAL(refresh()),this,SLOT(sl_TreeViewList()));
    Upload_sql->show();
}

/**
 * @brief SqlQuery::onCustomContextMenu
 * @param point
 */
void SqlQuery::onCustomContextMenu(const QPoint &point)
{
    PRINT(__FUNCTION__)<<"right click";
    Mdl_Index = ui->treeView->indexAt(point);
    Table_Name.clear();
    Table_Name= ui->treeView->model()->data(Mdl_Index).toString();
    PRINT(__FUNCTION__)<<Mdl_Index<<Table_Name;

    QMenu *menu=new QMenu(this);
    if(db.databaseName()==Table_Name)
    {
        QAction *import= new QAction(QIcon(":/images/add.png"),tr("Import"),this);
        connect(import, &QAction::triggered, this, &SqlQuery::sl_Import_table);
        menu->addAction(import);

        QAction *_export= new QAction(QIcon(":/images/bottom.png"),tr("Export"),this);
        connect(_export, &QAction::triggered, this, &SqlQuery::sl_Export_table);
        menu->addAction(_export);
    }
    else
    {
        QAction *insert= new QAction(QIcon(":/images/add.png"),tr("Insert values"),this);
        connect(insert, &QAction::triggered, this, &SqlQuery::sl_Insert_table_values);
        menu->addAction(insert);

        QAction *browse= new QAction(QIcon(":/images/clear.png"),tr("Browse"),this);
        connect(browse, &QAction::triggered, this, &SqlQuery::sl_Browse_table);
        menu->addAction(browse);

        QAction *structure= new QAction(QIcon(":/images/settings.png"),tr("Structure"),this);
        connect(structure, &QAction::triggered, this, &SqlQuery::sl_Struct_table);
        menu->addAction(structure);

        QAction *sl_Drop_table= new QAction(QIcon(":/images/delete.png"),tr("Drop table"),this);
        connect(sl_Drop_table, &QAction::triggered, this, &SqlQuery::sl_Drop_table);
        menu->addAction(sl_Drop_table);
    }
    menu->popup(ui->treeView->viewport()->mapToGlobal(point));

}

/**
 * @brief SqlQuery::sl_Insert_table_values
 */
void SqlQuery::sl_Insert_table_values()
{
    this->setDisabled(true);
    PRINT(__FUNCTION__)<<"Table_Name "<<Table_Name<<Mdl_Index;
    if(ivalue)
        delete ivalue;

    ivalue = new InsertValue(0,Table_Name);
    connect(ivalue,SIGNAL(si_RefreshTable(QString)),SLOT(sl_SelectAll(QString)));

    ivalue->show();
    this->setEnabled(true);

}

/**
 * @brief SqlQuery::sl_Struct_table
 */
void SqlQuery::sl_Struct_table()
{
    PRINT(__FUNCTION__)<<"Table_Name "<<Table_Name;
    int i=0;
    Model =new QStandardItemModel;
    Model->setHorizontalHeaderItem(0,new QStandardItem("Field"));
    Model->setHorizontalHeaderItem(1,new QStandardItem("Type"));
    Model->setHorizontalHeaderItem(2,new QStandardItem("Null"));
    Model->setHorizontalHeaderItem(3,new QStandardItem("Key"));
    Model->setHorizontalHeaderItem(4,new QStandardItem("Default"));
    Model->setHorizontalHeaderItem(5,new QStandardItem("Extra"));

    QSqlQuery query4("show columns from "+Table_Name);
    while(query4.next())
    {
        for(int k=0;k<6;k++)
        {
            if(k==4 && query4.value(k).toString()=="")
            {
                Item = new QStandardItem ("NULL");
            }
            else
                Item = new QStandardItem (query4.value(k).toString());
            Model->setItem(i,k,Item);

            ////////// * alternate color of rows  */////////////////
            if(i%2==0)
                Model->item(i,k)->setBackground(Qt::darkGray);
            else
                Model->item(i,k)->setBackground(Qt::lightGray);
            ////////////////////////////////////////////////////////
        }
        i++;
    }
    ui->tableView_QueryData->setModel(Model);

}

/**
 * @brief SqlQuery::sl_Browse_table
 */
void SqlQuery::sl_Browse_table()
{
    PRINT(__FUNCTION__)<<"Table_Name "<<Table_Name;
    On_Click_treeview(Mdl_Index);
}

/**
 * @brief SqlQuery::sl_Drop_table
 */
void SqlQuery::sl_Drop_table()
{
     PRINT(__FUNCTION__)<<"Table_Name "<<Table_Name;
     QSqlQuery queryDROP;
     queryDROP.exec("drop table "+Table_Name);
     sl_TreeViewList();
     ui->tableView_QueryData->setModel(nullptr);
}

/**
 * @brief SqlQuery::sl_Import_table
 */
void SqlQuery::sl_Import_table()
{
    isExport=false;
    PRINT(__FUNCTION__)<<"Table_Name "<<Table_Name;
    on_pushButton_Upload_clicked();
}

/**
 * @brief SqlQuery::sl_Export_table
 */

void SqlQuery::sl_Export_table()
{
    isExport=true;
    PRINT(__FUNCTION__)<<"Table_Name "<<Table_Name;
    on_pushButton_Upload_clicked();
}

/**
 * @brief SqlQuery::sl_About
 */
void SqlQuery::sl_About()
{
    QMessageBox::information(this,"About us","<b>MySQL GUI</b><br>"
                                             "Version 1.1a<br>"
                                             "<br>Copyright 2022-2023 The anil-arise1600. All rights reserved.<br>"
                                             "<br>The program is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE WARRANTY OF DESIGN, "
                                             "MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE");
}

/**
 * @brief SqlQuery::eventFilter
 * @param obj
 * @param event
 * @return
 */
bool SqlQuery::eventFilter(QObject *obj, QEvent *event)
{
    //PRINT(__FUNCTION__)<<"event"<<obj;
    if(obj==ui->lineEdit_Query)
    {
        if (event->type() == QEvent::FocusIn)
        {
            ui->pushButton_Go->setDefault(true);
            ui->pushButton_Exit->setDefault(false);
            PRINT(__FUNCTION__) << "Default set Go";
        }
        else
        {
            ui->pushButton_Exit->setDefault(true);
            ui->pushButton_Go->setDefault(false);
        }
    }

}
