#include "sqlquery.h"
#include "ui_sqlquery.h"
extern QSqlDatabase db;
QString Table_Name;//="NULL";
bool Export;

SqlQuery::SqlQuery(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SqlQuery)
{
    ui->setupUi(this);
    list.clear();
    ui->treeView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->treeView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->treeView, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(onCustomContextMenu(const QPoint &)));

    //this->installEventFilter(ui->lineEdit_query);
    ui->lineEdit_query->installEventFilter(this);

    ui->tableView_QueryData->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    TreeViewList();
    ui->tableView_QueryData->setEditTriggers(0);
    ui->pushButton_Upload->hide();
    ui->tableView_QueryData->setStyleSheet("alternate-background-color: lightgrey;");
    connect(ui->pushButton_Exit,SIGNAL(clicked(bool)),this,SLOT(ExitClose()));
    connect(ui->pushButton_Clear,SIGNAL(clicked(bool)),ui->lineEdit_query,SLOT(clear()));
    ui->pushButton_Exit->setDefault(true);
    //connect(ui->lineEdit_query, SIGNAL(cursorPositionChanged(int,int)),this,SLOT(QueryLineEdit()));
    //ui->tableView_QueryData->horizontalHeader()->setStretchLastSection(true);
    //ui->tableView_QueryData->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    //ui->tableView_QueryData->horizontalHeader()->setMaximumSectionSize(50);
    Export=false;
}

SqlQuery::~SqlQuery()
{
    delete ui;
    delete Item;
    delete ItemMain;
    delete Model;
}

void SqlQuery::TreeViewList()
{
    int i=0;
    PRINT(__FUNCTION__)<<"in tree Database "<<db.databaseName();
    ui->label_selecteDB->setText(db.databaseName());
    QSqlQuery query0("use "+db.databaseName());
    query0.next();

    Model =new QStandardItemModel;
    ItemMain= new QStandardItem(db.databaseName()+"@"+db.hostName());
    Model->setHorizontalHeaderItem(0,ItemMain);
    ItemMain= new QStandardItem(db.databaseName());
    //ItemMain->setBackground(Qt::blue);
    Model->setItem(0,ItemMain);

    //    QSqlQuery query11("select count(*) from information_schema.tables where table_schema = database()");
    //    query11.next();
    //    PRINT(__FUNCTION__)<<query11.value(0).toInt();
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
    connect(ui->treeView,SIGNAL(clicked(QModelIndex)),this,SLOT(On_Click_treeview(QModelIndex)));
}

void SqlQuery::on_pushButton_Go_clicked()
{
    ui->tableView_QueryData->repaint();

//    QFont *font=new QFont;
//    font -> setFamily("Sans Serif");
//    font -> setPointSize(14);
//    font -> setBold(true);
//    //ui->tableView_QueryData->horizontalHeader ()->setFont (QFont::setFamily("Arial"));
//    ui->tableView_QueryData->horizontalHeader ()->setStyleSheet ("QheaderView {font-size: 14pt;color: blue;}");

    ui->label_error->clear();
    strlist.clear();
    if(!ui->lineEdit_query->text().isEmpty())
    {
        str_query=ui->lineEdit_query->text();
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
                SelectAll(strlist.at(3));
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
                            SelectAll(strlist.at(1));
                        }
                        else if(str.toLower()=="drop")
                        {
                            ui->label_error->setText("<font color=green>Successfully droped !!</font>");
                            //SelectAll(strlist.at(1));
                            TreeViewList();
                        }
                        else if(str.toLower()=="create" && strlist.size()==3)
                        {
                            ui->label_error->setText("<font color=green>Successfully created database !!</font>");
                            //SelectAll(strlist.at(1));
                            db.setDatabaseName(strlist.at(2));
                            TreeViewList();
                        }
                        else if(str.toLower()=="delete")
                        {
                            ui->label_error->setText("<font color=green>deleted !!</font>");
                            SelectAll(strlist.at(2));
                        }
                        else if(str.toLower()=="create" && QString(strlist.at(1)).toLower()=="table")
                        {
                            TreeViewList();
                            ui->tableView_QueryData->setModel(nullptr);
                        }
                        else if(str.toLower()=="insert")
                        {
                            SelectAll(strlist.at(2));
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

void SqlQuery::On_Click_treeview(QModelIndex M_index)
{
    QVariant data = ui->treeView->model()->data(M_index);
    QString text = data.toString();
    //PRINT(__FUNCTION__)<< "Model Index "/*<<M_index */<<text;
    if(text!=db.databaseName())
    {
        ui->lineEdit_query->setText("select * from "+text);
        SelectAll(text);
    }
    else
    {
        ui->tableView_QueryData->setModel(nullptr);
        ui->lineEdit_query->clear();
    }

}

void SqlQuery::ExitClose()
{
    db.close();
    this->close();
    MysqlLogin *MyLog= new MysqlLogin;
    MyLog->show();
}

void SqlQuery::SelectAll(QString str)
{
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

void SqlQuery::on_pushButton_changeDB_clicked()
{
    sdb=new DialogSelectDB;
    sdb->exec();
    TreeViewList();
    ui->tableView_QueryData->setModel(nullptr);
    ui->label_selecteDB->setText(db.databaseName());
}

void SqlQuery::QueryLineEdit()
{
    //PRINT(__FUNCTION__)<<"GO ";
    ui->pushButton_Go->setDefault(true);
    ui->pushButton_Exit->setDefault(false);
}

void SqlQuery::on_pushButton_Upload_clicked()
{
    //PRINT(__FUNCTION__)<<db.databaseName()<<db.userName()<<db.password();
    DialogUploadSQL *Upload_sql = new DialogUploadSQL;
    connect(Upload_sql,SIGNAL(refresh()),this,SLOT(TreeViewList()));
    Upload_sql->show();
}

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
        connect(import, &QAction::triggered, this, &SqlQuery::Import_table);
        menu->addAction(import);

        QAction *_export= new QAction(QIcon(":/images/bottom.png"),tr("Export"),this);
        connect(_export, &QAction::triggered, this, &SqlQuery::Export_table);
        menu->addAction(_export);
    }
    else
    {
        QAction *insert= new QAction(QIcon(":/images/add.png"),tr("Insert values"),this);
        connect(insert, &QAction::triggered, this, &SqlQuery::Insert_table_values);
        menu->addAction(insert);

        QAction *browse= new QAction(QIcon(":/images/clear.png"),tr("Browse"),this);
        connect(browse, &QAction::triggered, this, &SqlQuery::Browse_table);
        menu->addAction(browse);

        QAction *structure= new QAction(QIcon(":/images/settings.png"),tr("Structure"),this);
        connect(structure, &QAction::triggered, this, &SqlQuery::Struct_table);
        menu->addAction(structure);

        QAction *drop_table= new QAction(QIcon(":/images/delete.png"),tr("Drop table"),this);
        connect(drop_table, &QAction::triggered, this, &SqlQuery::Drop_table);
        menu->addAction(drop_table);
    }
    menu->popup(ui->treeView->viewport()->mapToGlobal(point));

}

void SqlQuery::Insert_table_values()
{
    this->setDisabled(true);
    PRINT(__FUNCTION__)<<"Insert_table_values()->Table_Name "<<Table_Name<<Mdl_Index;
    InsertValue *ivalue=new InsertValue;

//    foreach( QWidget* p_widget, qApp->topLevelWidgets() )
//    {
//        if ( QMainWindow* p_main_window = qobject_cast<QMainWindow*>( p_widget ) )
//        {
//            ivalue->setParent( p_main_window );
//        }
//    }

    ivalue->show();
    //On_Click_treeview(Mdl_Index);
    ui->tableView_QueryData->setModel(nullptr);
    SelectAll(Table_Name);
    this->setEnabled(true);

}

void SqlQuery::Struct_table()
{
    PRINT(__FUNCTION__)<<"Struct_table()->Table_Name "<<Table_Name;
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

void SqlQuery::Browse_table()
{
    PRINT(__FUNCTION__)<<"Browse_table()->Table_Name "<<Table_Name;
    On_Click_treeview(Mdl_Index);
}

void SqlQuery::Drop_table()
{
     PRINT(__FUNCTION__)<<"Drop_table()->Table_Name "<<Table_Name;
     QSqlQuery queryDROP;
     queryDROP.exec("drop table "+Table_Name);
     TreeViewList();
     ui->tableView_QueryData->setModel(nullptr);
}

void SqlQuery::Import_table()
{
    Export=false;
    PRINT(__FUNCTION__)<<"Import_table()->Table_Name "<<Table_Name;
    on_pushButton_Upload_clicked();
}

void SqlQuery::Export_table()
{
    Export=true;
    PRINT(__FUNCTION__)<<"Export_table()->Table_Name "<<Table_Name;
    on_pushButton_Upload_clicked();
}

bool SqlQuery::eventFilter(QObject *obj, QEvent *event)
{
    //PRINT(__FUNCTION__)<<"event"<<obj;
    if(obj==ui->lineEdit_query)
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
