/**
* @file DialogSelectDB.cpp
* @author Anil Kumar
* @date 17-11-2017
* @brief This DialogSelectDB class, It's responsible for select or change database.
*/
#include "dialogselectdb.h"
#include "ui_dialogselectdb.h"
extern QSqlDatabase db;

/**
 * @brief DialogSelectDB::DialogSelectDB
 * @param parent
 */
DialogSelectDB::DialogSelectDB(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSelectDB)
{
    ui->setupUi(this);
    QSqlQuery query1("SHOW DATABASES");
    while(query1.next())
    {
        ui->comboBox->addItem(query1.value(0).toString());
    }
    ui->comboBox->setStyleSheet("QComboBox { combobox-popup: 0; }");
    ui->comboBox->setMaxVisibleItems(5);

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
    db.setDatabaseName(ui->comboBox->currentText());
    this->close();
}
