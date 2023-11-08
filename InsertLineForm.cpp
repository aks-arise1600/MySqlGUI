/**
* @file InsertLineForm.cpp
* @author Anil Kumar
* @date 7-11-2023
* @brief This InsertLineForm class, It's UI of table column name and its value.
*/
#include "InsertLineForm.h"
#include "ui_InsertLineForm.h"

/**
 * @brief InsertLineForm::InsertLineForm
 * @param parent
 * @param str
 * @param typ
 * @param limit
 */
InsertLineForm::InsertLineForm(QWidget *parent,QString str,QString typ, int limit) :
    QWidget(parent),
    ui(new Ui::InsertLineForm)
{
    ui->setupUi(this);

    ui->label_Tag->setText(str);
//    str_type = typ;

    if(typ.toLower()=="varchar"||typ.toLower()=="char")
    {
        QRegExp rx("([A-Za-z0-9@. -/:]){"+QString::number(limit)+"}");
        ui->lineEdit_Value->setValidator(new QRegExpValidator(rx, this));
         ui->lineEdit_Value->setPlaceholderText("Max. Char("+QString::number(limit)+")");

    }
    else if(typ.toLower()=="int")
    {
        QRegExp rx("([0-9]){"+QString::number(limit)+"}");
         ui->lineEdit_Value->setValidator(new QRegExpValidator(rx, this));
         ui->lineEdit_Value->setPlaceholderText("Max. int("+QString::number(limit)+")");

    }
    else if(typ.toLower()=="tinyint")
    {
        QRegExp rx("([0-9]){1}");
         ui->lineEdit_Value->setValidator(new QRegExpValidator(rx, this));
         ui->lineEdit_Value->setPlaceholderText("Max. tinyint("+QString::number(limit)+")");

    }
    else if(typ.toLower()=="float")
    {
        QRegExp rx("([0-9.]){"+QString::number(limit)+"}");
         ui->lineEdit_Value->setValidator(new QRegExpValidator(rx, this));
         ui->lineEdit_Value->setPlaceholderText("Max. float("+QString::number(limit)+")");

    }
    else if(typ=="enum('N','Y')")
    {
        QRegExp rx("([NnYy]){"+QString::number(limit)+"}");
         ui->lineEdit_Value->setValidator(new QRegExpValidator(rx, this));
         ui->lineEdit_Value->setPlaceholderText("Only (Y/N)("+QString::number(limit)+")");

    }
    else if(typ.toLower()=="timestamp")
    {
        QRegExp rx("([0-9]){"+QString::number(limit)+"}");
         ui->lineEdit_Value->setValidator(new QRegExpValidator(rx, this));
         ui->lineEdit_Value->setPlaceholderText("Max. timestamp("+QString::number(limit)+")");

    }
    else if(typ.toLower()=="smallint")
    {
        QRegExp rx("([0-9]){"+QString::number(limit)+"}");
         ui->lineEdit_Value->setValidator(new QRegExpValidator(rx, this));
         ui->lineEdit_Value->setPlaceholderText("Max. smallint("+QString::number(limit)+")");

    }
    else if(typ.toLower()=="bigint")
    {
        QRegExp rx("([0-9]){"+QString::number(limit)+"}");
         ui->lineEdit_Value->setValidator(new QRegExpValidator(rx, this));
         ui->lineEdit_Value->setPlaceholderText("Max. bigint("+QString::number(limit)+")");

    }

}

/**
 * @brief InsertLineForm::~InsertLineForm
 */
InsertLineForm::~InsertLineForm()
{
    delete ui;
}

/**
 * @brief InsertLineForm::m_GetcNameValue
 * @return
 */
QString InsertLineForm::m_GetcNameValue()
{
    return ui->label_Tag->text();
}

/**
 * @brief InsertLineForm::m_GetTypeValue
 * @return
 */
QString InsertLineForm::m_GetTypeValue()
{
    if(ui->lineEdit_Value->text().size())
        return ui->lineEdit_Value->text();
    else
        return "0";
}
