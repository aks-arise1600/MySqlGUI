/**
* @file DialogSwitchDB.cpp
* @author Anil Kumar
* @date 17-11-2017
* @brief This DialogSwitchDB class, It's responsible for select or change database.
*/
#include "DialogSwitchDB.h"
#include "ui_DialogSwitchDB.h"

/**
 * @brief DialogSwitchDB::DialogSwitchDB
 * @param parent
 * @param db_
 */
DialogSwitchDB::DialogSwitchDB(QWidget *parent, QSqlDatabase *db_) :
    QDialog(parent),
    ui(new Ui::DialogSwitchDB)
{
    ui->setupUi(this);
    dba = db_;
    QSqlQuery query1("SHOW DATABASES");
    while(query1.next())
        ui->comboBox->addItem(query1.value(0).toString());

}

/**
 * @brief DialogSwitchDB::~DialogSwitchDB
 */
DialogSwitchDB::~DialogSwitchDB()
{
    delete ui;
}

/**
 * @brief DialogSwitchDB::on_pushButton_ok_clicked
 */
void DialogSwitchDB::on_pushButton_ok_clicked()
{
    dba->setDatabaseName(ui->comboBox->currentText());
    emit si_ClosedSwitchDB(true);
    this->close();
}

void DialogSwitchDB::on_pushButton_Cancel_clicked()
{
    emit si_ClosedSwitchDB(false);
    this->close();
}
