/**
* @file InsertValue.cpp
* @author Anil Kumar
* @date 15-11-2017
* @brief This InsertValue class, It has insert data fields and inserting data in DB.
*/

#include "InsertValue.h"
#include "ui_InsertValue.h"
#define TINYINT 1
#define VARCHAR 2
#define INT 3
#define FLOAT 4

/**
 * @brief InsertValue::InsertValue
 * @param parent
 * @param tblName
 */
InsertValue::InsertValue(QWidget *parent, QString tblName) :
    QWidget(parent),
    ui(new Ui::InsertValue)
{
    ui->setupUi(this);
    strTableName = tblName;
    this->setWindowTitle("insert into "+strTableName);
    this->setWindowFlags(Qt::WindowCloseButtonHint);
    connect(ui->pushButton_insert,SIGNAL(clicked()),this,SLOT(sl_Insert_into()));
    QSqlQuery query1("show columns from "+strTableName);
    while(query1.next())
    {
        QString Column_name=query1.value(0).toString();
        QString type_id;QString Limit;
        PRINT(__FUNCTION__)<<query1.value(1).toString();
        if(query1.value(1).toString()=="enum('N','Y')"||query1.value(1).toString()=="blob"||query1.value(1).toString()=="text"
                ||query1.value(1).toString()=="timestamp" || query1.value(1).toString()=="json")
        {
            //PRINT(__FUNCTION__)<<query1.value(1).toString();
            type_id=query1.value(1).toString();
            Limit="1";
        }
        else if(query1.value(1).toString().toLower()=="float" || query1.value(1).toString().toLower()=="int"
                || query1.value(1).toString().toLower()=="bigint")
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
        PRINT(__FUNCTION__)<<Column_name<<"\t"<<type_id<<"\t"<<Limit;
    }
}

/**
 * @brief InsertValue::~InsertValue
 */
InsertValue::~InsertValue()
{
    delete ui;
}

/**
 * @brief InsertValue::AddItems
 * @param str
 * @param TypId
 * @param size
 */
void InsertValue::AddItems(QString str,QString TypId, int size)
{

    InsertLineForm * iLineForm = new InsertLineForm(0,str,TypId,size);
    listInputs << iLineForm;
    QListWidgetItem *item  = new QListWidgetItem();
    item-> setSizeHint(iLineForm->minimumSizeHint());
    ui->listWidget->addItem(item);
    ui->listWidget->setItemWidget(item, iLineForm);

}

/**
 * @brief InsertValue::sl_Insert_into
 */
void InsertValue::sl_Insert_into()
{
    QString Columns, Vlues;
    foreach (InsertLineForm *input, listInputs) {
        Columns+="`"+input->m_GetcNameValue()+"`,";
        Vlues+="'"+input->m_GetTypeValue()+"',";
    }
//    PRINT(__FUNCTION__)<<"ColumnList"<<Columns<<" Vlues"<<Vlues;

    // ** INSERT INTO `tbl_NAME`(`COL_1`, `COL_2`, `COL_3`, `COL_4`) VALUES ([value-1],[value-2],[value-3],[value-4])
    QString strList = "insert into "+strTableName;
    strList+=" ("+Columns.mid(0,Columns.size()-1)+") values ("+Vlues.mid(0,Vlues.size()-1)+");";

    PRINT(__FUNCTION__)<<strList;
    QSqlQuery query2;
    bool ex=query2.exec(strList);
    if(!ex)
    {
        PRINT(__FUNCTION__)<<query2.lastError().text();
        ui->label_status->setText(query2.lastError().text());
    }
    else
        this->close();

    emit si_RefreshTable(strTableName);
}
