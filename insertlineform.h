/**
* @file InsertLineForm.h
* @author Anil Kumar
* @date 7-11-2023
* @brief This is header of InsertLineForm class.
*/

#ifndef INSERTLINEFORM_H
#define INSERTLINEFORM_H

#include <QWidget>
#include <common.h>
#include <QRegExpValidator>

namespace Ui {
class InsertLineForm;
}

class InsertLineForm : public QWidget
{
    Q_OBJECT

public:
    explicit InsertLineForm(QWidget *parent = 0,QString str = "na",QString TypId = "na", int size = 0);
    ~InsertLineForm();
    QString m_GetcNameValue();
    QString m_GetTypeValue();
private:
    Ui::InsertLineForm *ui;
};

#endif // INSERTLINEFORM_H
