#include "insertvalue.h"
#include "ui_insertvalue.h"
#define TINYINT 1
#define VARCHAR 2
#define INT 3
#define FLOAT 4


extern QString Table_Name;
QStringList str_query;
QStringList typelist;

InsertValue::InsertValue(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InsertValue)
{
    ui->setupUi(this);
    this->setWindowTitle("insert into "+Table_Name);
    this->setWindowFlags(Qt::WindowCloseButtonHint);
    connect(ui->pushButton_insert,SIGNAL(clicked()),this,SLOT(Insert_into()));
    count=0;
    QSqlQuery query1("show columns from "+Table_Name);
    while(query1.next())
    {
        QString Column_name=query1.value(0).toString();
        QString type_id;QString Limit;
        if(query1.value(1).toString()=="enum('N','Y')"||query1.value(1).toString()=="blob"||query1.value(1).toString()=="text"
                ||query1.value(1).toString()=="timestamp")
        {
            //qDebug()<<query1.value(1).toString();
            type_id=query1.value(1).toString();
            Limit="1";
        }
        else if(query1.value(1).toString().toLower()=="float")
        {
            type_id=query1.value(1).toString();
            Limit="10";
        }
        else
        {

            type_id=query1.value(1).toString().split("(").at(0);
            Limit=query1.value(1).toString().split(QRegularExpression("\\W+"), QString::SkipEmptyParts).at(1);
        }
        AddItems(Column_name,type_id,Limit.toInt());
        qDebug()<<Column_name<<"\t"<<type_id<<"\t"<<Limit;
    }
}

InsertValue::~InsertValue()
{
    delete ui;
}

void InsertValue::AddItems(QString str,QString TypId, int size)
{
    font = new QFont;
    font -> setFamily("Sans Serif");
    font -> setPointSize(12);
    font -> setBold(false);
    QSpacerItem *spacer_left, *spacer_right;
    spacer_left       = new QSpacerItem(1, 1, QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
    spacer_right      = new QSpacerItem(1, 1, QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);

    Label=new QLabel;
    Label->setFont(*font);
    Label->setText(str);

    Line=new InsertLine(str,TypId,size);
    Line-> setMinimumSize(QSize(210, 20));
    Line->setFont(*font);
    //Line->setStyleSheet("background-color:lightgrey; color:black;");

    connect(this,SIGNAL(textGet(QString)),Line,SLOT(getlineText(QString)));

    horizontal= new QHBoxLayout;
    item= new QListWidgetItem;

    horizontal->addWidget(Label);
    horizontal->addSpacerItem(spacer_left);
    horizontal->addSpacerItem(spacer_right);
    horizontal->addWidget(Line);
    horizontal->setAlignment(Label, Qt::AlignLeft);
    horizontal->setAlignment(Line, Qt::AlignRight);

    widget= new QWidget;
    widget->setObjectName(str);
    widget->setLayout(horizontal);
    item->setSizeHint(QSize(60, 30));
    ui->listWidget->insertItem((count++), item);
    ui->listWidget->setItemWidget(item, widget);
    ui->listWidget->setCurrentRow(ui->listWidget->count()-1);

}

void InsertValue::Insert_into()
{
    str_query.clear(); typelist.clear();
    for(int i=0;i<ui->listWidget->count();i++)
    {
        emit textGet(ui->listWidget->itemWidget(ui->listWidget->item(i))->objectName());
    }
    qDebug()<<"ColumnList"<<str_query<<" TypeList"<<typelist;
    QString strList;int j=0;
    strList = "insert into "+Table_Name+" values(";
    while(j<str_query.size())
    {
        qDebug()<<str_query.at(j)<<typelist.at(j);
        if(j!=str_query.size()-1)
        {
            if(typelist.at(j)=="varchar")
                strList+="'"+str_query.at(j)+"',";
            else if(typelist.at(j)=="int")
                strList+=str_query.at(j)+",";
            else if(typelist.at(j)=="tinyint")
                strList+=str_query.at(j)+",";
            else if(typelist.at(j)=="float")
                strList+=str_query.at(j)+",";
        }
        else
        {
            if(typelist.at(j)=="varchar")
                strList+="'"+str_query.at(j)+"');";
            else if(typelist.at(j)=="int")
                strList+=str_query.at(j)+");";
            else if(typelist.at(j)=="tinyint")
                strList+=str_query.at(j)+");";
            else if(typelist.at(j)=="float")
                strList+=str_query.at(j)+");";
        }
        j++;
    }
    qDebug()<<strList;
    QSqlQuery query2;
    bool ex=query2.exec(strList);
    if(!ex)
    {
        qDebug()<<query2.lastError().text();
        ui->label_status->setText(query2.lastError().text());
    }
    else
        this->close();
}
