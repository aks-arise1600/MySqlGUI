/**
* @file DialogSelectDB.cpp
* @author Anil Kumar
* @date 17-11-2017
* @brief This DialogSelectDB class, It's responsible for select or change database.
*/
#include "DialogSelectDB.h"
#include "ui_DialogSelectDB.h"

/**
 * @brief DialogSelectDB::DialogSelectDB
 * @param parent
 * @param db_
 */
DialogSelectDB::DialogSelectDB(QWidget *parent, QSqlDatabase *db_) :
    QDialog(parent),
    ui(new Ui::DialogSelectDB)
{
    ui->setupUi(this);
    dba = db_;
    QSqlQuery query1("SHOW DATABASES");
    while(query1.next())
        ui->comboBox->addItem(query1.value(0).toString());

}

/**
 * @brief DialogSelectDB::~DialogSelectDB
 */
DialogSelectDB::~DialogSelectDB()
{
    delete ui;
}

/**
 * @brief DialogSelectDB::on_pushButton_ok_clicked
 */
void DialogSelectDB::on_pushButton_ok_clicked()
{
    dba->setDatabaseName(ui->comboBox->currentText());
    this->close();
}
