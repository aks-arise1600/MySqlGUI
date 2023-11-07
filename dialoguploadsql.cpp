/**
* @file DialogUploadSQL.cpp
* @author Anil Kumar
* @date 17-11-2017
* @brief This DialogUploadSQL class, It's responsible for import and export data of select database.
*/
#include "dialoguploadsql.h"
#include "ui_dialoguploadsql.h"
extern QSqlDatabase db;

/**
 * @brief DialogUploadSQL::DialogUploadSQL
 * @param parent
 * @param isexport
 */
DialogUploadSQL::DialogUploadSQL(QWidget *parent, bool isexport) :
    QDialog(parent),
    ui(new Ui::DialogUploadSQL)
{
    ui->setupUi(this);
    is_export = isexport;
    m_fileName="";
    if(is_export)
    {
        //ui->pushButton_browse->hide();
        file_sql=new QLabel(db.databaseName()+".sql");
        file_sql->setTextInteractionFlags(Qt::TextEditorInteraction);
        ui->horizontalLayout->addWidget(file_sql);
        ui->pushButton_Upload->setText("Export");
    }
}

/**
 * @brief DialogUploadSQL::~DialogUploadSQL
 */
DialogUploadSQL::~DialogUploadSQL()
{
    delete ui;
}

/**
 * @brief DialogUploadSQL::on_pushButton_browse_clicked
 */
void DialogUploadSQL::on_pushButton_browse_clicked()
{
    if(is_export)
    {
        m_fileName= QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                      QDir::homePath(),
                                                      QFileDialog::ShowDirsOnly
                                                      | QFileDialog::DontResolveSymlinks);
    }
    else
        m_fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::homePath(),tr("( *.sql)"));
    ui->lineEdit->setText(m_fileName);
}

/**
 * @brief DialogUploadSQL::on_pushButton_Upload_clicked
 */
void DialogUploadSQL::on_pushButton_Upload_clicked()
{
    ui->label_status->clear();
    ui->label_status->setText("Please wait..... ");
    PRINT(__FUNCTION__)<<db.databaseName()<<db.userName()<<db.password()<<m_fileName;

    if(ui->lineEdit->text()!="")
    {
        if(is_export)
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
        if(is_export)
            ui->label_status->setText("<font color =red>folder not selected !!</font>");
        else
            ui->label_status->setText("<font color =red>Not sql file founded !!</font>");
    }
}
