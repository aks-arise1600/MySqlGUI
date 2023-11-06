#include "dialogselectdb.h"
#include "ui_dialogselectdb.h"
extern QSqlDatabase db;


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

DialogSelectDB::~DialogSelectDB()
{
    delete ui;
}

void DialogSelectDB::on_pushButton_ok_clicked()
{
    db.setDatabaseName(ui->comboBox->currentText());
    this->close();
}
