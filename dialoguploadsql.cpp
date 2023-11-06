#include "dialoguploadsql.h"
#include "ui_dialoguploadsql.h"
extern QSqlDatabase db;
extern bool Export;

DialogUploadSQL::DialogUploadSQL(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogUploadSQL)
{
    ui->setupUi(this);
    m_fileName="";
    if(Export)
    {
        //ui->pushButton_browse->hide();
        file_sql=new QLabel(db.databaseName()+".sql");
        file_sql->setTextInteractionFlags(Qt::TextEditorInteraction);
        ui->horizontalLayout->addWidget(file_sql);
        ui->pushButton_Upload->setText("Export");
    }
}

DialogUploadSQL::~DialogUploadSQL()
{
    delete ui;
}

void DialogUploadSQL::on_pushButton_browse_clicked()
{
    if(Export)
    {
        m_fileName= QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                      "/home",
                                                      QFileDialog::ShowDirsOnly
                                                      | QFileDialog::DontResolveSymlinks);
    }
    else
        m_fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "/home",tr("( *.sql)"));
    ui->lineEdit->setText(m_fileName);
}

void DialogUploadSQL::on_pushButton_Upload_clicked()
{
    ui->label_status->clear();
    ui->label_status->setText("Please wait..... ");
    PRINT(__FUNCTION__)<<db.databaseName()<<db.userName()<<db.password()<<m_fileName;

    if(ui->lineEdit->text()!="")
    {
        if(Export)
        {
            PRINT(__FUNCTION__)<<"Exporting to "<<ui->lineEdit->text()<<"/"<<file_sql->text();
            ui->label_status->setText("Please wait..... ");

            QString lCommand("mysqldump -u"+db.userName()+" -p"+db.password()+" "+db.databaseName()+">" +m_fileName+"/"+file_sql->text());
            system(lCommand.toStdString().c_str());
            PRINT(__FUNCTION__)<<"Exported successfully";
            emit refresh();
            this->close();
        }
        else
        {
            QString lCommand("mysql -u"+db.userName()+" -p"+db.password()+" "+db.databaseName()+" -e \"source " + m_fileName + "\"");
            system(lCommand.toStdString().c_str());
            PRINT(__FUNCTION__)<<"Imported successfully";
            emit refresh();
            this->close();
            /////////////////  by reading each line /////////////////////////////////////////////
            /*QFile Query_string(m_fileName);
            int i=0;

            if (Query_string.open(QIODevice::ReadOnly))
            {
                QByteArray query_line;
                QTextStream in(&Query_string);
                while (!in.atEnd())
                {
                    query_line.clear();
                    query_line.append( in.readLine());

                    if(query_line=="")
                    {

                    }
                    else if(query_line[0]=='/' && query_line[1]=='*')
                    {

                    }
                    else
                    {
                        QSqlQuery query;
                        QString str=query_line;
                        bool ex=query.exec(str);
                        if(!ex)
                        {
                            PRINT(__FUNCTION__)<<query_line<<query.lastError().text();
                            i++;
                        }
                    }
                }
            }
            if(i==0)
            {
                ui->label_status->setText("<font color =green>Uploaded !!</font>");
                emit refresh();
                this->close();
            }
            else
                ui->label_status->setText("<font color =red>Not Uploaded Successfully !!</font>");*/
            ////////////////////////////////////////////////////////////////////////////////////////////////
        }
    }
    else
    {
        if(Export)
            ui->label_status->setText("<font color =red>folder not selected !!</font>");
        else
            ui->label_status->setText("<font color =red>Not sql file founded !!</font>");
    }
}
