/**
* @file MysqlLogin.cpp
* @author Anil Kumar
* @date 15-11-2017
* @brief This MysqlLogin class, it's responsible for MySQL connection.
*/
#include "MysqlLogin.h"
#include "ui_MysqlLogin.h"

/**
 * @brief MysqlLogin::MysqlLogin
 * This is a UI constructor of MysqlLogin with QWidget->QMainWindow as parent
 * @param parent QWidget
 */
MysqlLogin::MysqlLogin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MysqlLogin)
{
    ui->setupUi(this);
    ui->comboBox_datbase->hide();
    ui->label_datbase->hide();
    ui->label->hide();
    ui->label_2->hide();
    ui->label_3->hide();

    Connection=false;
    ui->pushButton_open->setDefault(true);
    //////////////************ to set QPushbutton in circle *///////////////////
    /*ui->pushButton_Clear->setFixedHeight(36);
    ui->pushButton_Clear->setFixedWidth(36);
    QRect *rect = new QRect(0,0,34,34);
    QRegion* region = new QRegion(*rect,QRegion::Ellipse);
    ui->pushButton_Clear->setMask(*region);
    ui->pushButton_Clear->show();*/
    ///////////////////////////////////////////////////////////////////////////

    dba = QSqlDatabase::addDatabase("QMYSQL");
    dba.setConnectOptions("MYSQL_OPT_RECONNECT=1");

}
/**
 * @brief MysqlLogin::~MysqlLogin
 * Destructor of MysqlLogin class
 */
MysqlLogin::~MysqlLogin()
{
    if(dba.isOpen())
        dba.close();
    else
        PRINT(__FUNCTION__) <<"Database is not opned.";
    delete ui;
}

/**
 * @brief MysqlLogin::HostName
 * Method to get Hostname from lineEdit_Host
 * @return string host name
 */
const QString MysqlLogin::HostName()
{
    if(ui->lineEdit_Host->text()=="")
        return "localhost";
    else
    return ui->lineEdit_Host->text();
}

/**
 * @brief MysqlLogin::UserName
 * Method to get User Name from lineEdit_UserName
 * @return string user name
 */
const QString MysqlLogin::UserName()
{
    return ui->lineEdit_UserName->text();
}

/**
 * @brief MysqlLogin::Password
 * Method to get User password from lineEdit_Password
 * @return string user password
 */
const QString MysqlLogin::Password()
{
    return ui->lineEdit_Password->text();

}

/**
 * @brief MysqlLogin::Database
 * Method to get selected database name from comboBox_datbase
 * @return string database name
 */
const QString MysqlLogin::Database()
{
    if(ui->comboBox_datbase->currentText()!="Select DB")
        return ui->comboBox_datbase->currentText();
    else
        return QString("NULL");
}

/**
 * @brief MysqlLogin::on_pushButton_Clear_clicked
 * Slot to clear all strings from Line Edit and Labels
 */
void MysqlLogin::on_pushButton_Clear_clicked()
{
    ui->lineEdit_Host->clear();
    ui->lineEdit_Password->clear();
    ui->lineEdit_UserName->clear();
    ui->label_Message->clear();
}

/**
 * @brief MysqlLogin::on_pushButton_open_clicked
 * Slot to initialise connection with mysql server
 */
void MysqlLogin::on_pushButton_open_clicked()
{
    ui->label_Message->clear();
    if(Connection==false)
    {
        if(!ui->lineEdit_UserName->text().isEmpty() && !ui->lineEdit_Password->text().isEmpty())
        {
            ui->label_Message->setText("Please wait ...");
            PRINT(__FUNCTION__)<<HostName();
            dba.setUserName(UserName());
            dba.setPassword(Password());
            dba.setHostName(HostName());
            //QTest::qSleep(20);
            if(dba.open())
            {
                ui->label_Message->setText("<font color=green>Database Connected</font>");
                PRINT(__FUNCTION__) <<"Database Successfully opened";
                QSqlQuery query1("SHOW DATABASES");
                ui->comboBox_datbase->addItem("Select DB");
                while(query1.next())
                {
                    ui->comboBox_datbase->addItem(query1.value(0).toString());
                }
                ui->comboBox_datbase->show();
                //ui->label_datbase->show();
                ui->pushButton_open->setText("Open");
                Connection=true;
                ui->pushButton_Clear->setDisabled(true);
            }
            else
            {
                ui->label_Message->setText("<font color=red>Database not Connected</font>");
                PRINT(__FUNCTION__) << "Database not opened" << dba.lastError();
                ui->label_Message->setText("<font color=red>username/password/host are mismatch.</font>");
                //QMessageBox::information(this,tr("Database Connection"),"<font color=red>Database Connection error due to username/password/host are mismatch.</font>");
            }
        }
        else
        {
            PRINT(__FUNCTION__)<<" empty";
            ui->label_Message->setText("<font color=red>username/password/host fields <br>should not be empty.</font>");
            //QMessageBox::warning(this,tr("Error Login"),"<font color=red>username/password/host fields should not be empty.</font>");
        }
    }
    else
    {
        if(Database()!="NULL")
        {
            dba.setDatabaseName(Database());
            ui->comboBox_datbase->hide();
            ui->label_datbase->hide();
            ui->pushButton_Clear->setEnabled(true);
            ui->pushButton_open->setText("Connect");
            Connection=false;
            DataQueryWindow *obj_queryQindow = new DataQueryWindow(0,&dba);
            connect(obj_queryQindow,SIGNAL(si_ShowLogin()),SLOT(sl_Show()));
            obj_queryQindow->show();
            PRINT(__FUNCTION__) <<"Database "<<Database()<<dba.databaseName();
            this->hide();
        }
        else
            ui->label_Message->setText("<font color=red>Database not selected</font>");
    }
}

void MysqlLogin::sl_Show()
{
    ui->lineEdit_Password->clear();
    ui->comboBox_datbase->setCurrentIndex(0);
    this->show();
}
