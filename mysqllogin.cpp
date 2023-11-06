#include "mysqllogin.h"
#include "ui_mysqllogin.h"
extern QSqlDatabase db= QSqlDatabase::addDatabase("QMYSQL");

MysqlLogin::MysqlLogin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MysqlLogin)
{
    ui->setupUi(this);
    ui->comboBox_datbase->setStyleSheet("QComboBox { combobox-popup: 0; }");
    ui->comboBox_datbase->setMaxVisibleItems(5);
    ui->comboBox_datbase->hide();
    ui->label_datbase->hide();
    ui->label->hide();
    ui->label_2->hide();
    ui->label_3->hide();
    ui->lineEdit_UserName->setPlaceholderText("User Name");
    ui->lineEdit_Password->setPlaceholderText("Password");
    ui->lineEdit_Password->setEchoMode(QLineEdit::Password);
    ui->lineEdit_Host->setPlaceholderText("Host Name(default:localhost)");
    Connection=false;
    ui->pushButton_open->setDefault(true);
    //ui->comboBox_datbase->setStyleSheet("combobox-popup: 5;");
    //////////////************ to set QPushbutton in circle *///////////////////
    /*ui->pushButton_Clear->setFixedHeight(36);
    ui->pushButton_Clear->setFixedWidth(36);
    QRect *rect = new QRect(0,0,34,34);
    QRegion* region = new QRegion(*rect,QRegion::Ellipse);
    ui->pushButton_Clear->setMask(*region);
    ui->pushButton_Clear->show();*/
    ///////////////////////////////////////////////////////////////////////////

}

MysqlLogin::~MysqlLogin()
{
    delete ui;
}

const QString MysqlLogin::HostName()
{
    if(ui->lineEdit_Host->text()=="")
        return "localhost";
    else
    return ui->lineEdit_Host->text();
}

const QString MysqlLogin::UserName()
{
    return ui->lineEdit_UserName->text();
}

const QString MysqlLogin::Password()
{
    return ui->lineEdit_Password->text();

}

const QString MysqlLogin::Database()
{
    if(ui->comboBox_datbase->currentText()!="Select DB")
        return ui->comboBox_datbase->currentText();
    else
        return QString("NULL");
}

void MysqlLogin::on_pushButton_Clear_clicked()
{
    ui->lineEdit_Host->clear();
    ui->lineEdit_Password->clear();
    ui->lineEdit_UserName->clear();
    ui->label_Message->clear();
}

void MysqlLogin::on_pushButton_open_clicked()
{
    ui->label_Message->clear();
    if(Connection==false)
    {
        if(!ui->lineEdit_UserName->text().isEmpty()&&!ui->lineEdit_Password->text().isEmpty())
        {
            ui->label_Message->setText("Please wait ...");
            PRINT(__FUNCTION__)<<" not empty"<<HostName();
            db.setUserName(UserName());
            db.setPassword(Password());
            db.setHostName(HostName());
            //QTest::qSleep(20);
            if(db.open())
            {
                ui->label_Message->setText("<font color=green>Database Connected</font>");
                PRINT(__FUNCTION__) <<" Database Successfully opened";
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
                PRINT(__FUNCTION__) << "Database not opened";
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
            db.setDatabaseName(Database());
            ui->comboBox_datbase->hide();
            ui->label_datbase->hide();
            ui->pushButton_Clear->setEnabled(true);
            ui->pushButton_open->setText("Connect");
            Connection=false;
            SqlQuery *sql = new SqlQuery;
            sql->show();
            PRINT(__FUNCTION__) <<"Database "<<Database()<<db.databaseName();
            this->close();
        }
        else
            ui->label_Message->setText("<font color=red>Database not selected</font>");
    }
}
