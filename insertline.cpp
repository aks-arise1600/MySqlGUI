#include "insertline.h"
extern QStringList str_query;
extern QStringList typelist;

InsertLine::InsertLine(QString id,QString typ,int limit)
{
    lineid=id;
    typeID=typ;
    if(typ.toLower()=="varchar"||typ.toLower()=="char")
    {
        QRegExp rx("([A-Za-z0-9@.]){"+QString::number(limit)+"}");
        this->setValidator(new QRegExpValidator(rx, this));
        this->setPlaceholderText("Max. Char("+QString::number(limit)+")");

    }
    else if(typ.toLower()=="int")
    {
        QRegExp rx("([0-9]){"+QString::number(limit)+"}");
        this->setValidator(new QRegExpValidator(rx, this));
        this->setPlaceholderText("Max. int("+QString::number(limit)+")");

    }
    else if(typ.toLower()=="tinyint")
    {
        QRegExp rx("([0-9]){1}");
        this->setValidator(new QRegExpValidator(rx, this));
        this->setPlaceholderText("Max. tinyint("+QString::number(limit)+")");

    }
    else if(typ.toLower()=="float")
    {
        QRegExp rx("([0-9.]){"+QString::number(limit)+"}");
        this->setValidator(new QRegExpValidator(rx, this));
        this->setPlaceholderText("Max. float("+QString::number(limit)+")");

    }
    else if(typ=="enum('N','Y')")
    {
        QRegExp rx("([NnYy]){"+QString::number(limit)+"}");
        this->setValidator(new QRegExpValidator(rx, this));
        this->setPlaceholderText("Only (Y/N)("+QString::number(limit)+")");

    }
    else if(typ.toLower()=="timestamp")
    {
        QRegExp rx("([0-9]){"+QString::number(limit)+"}");
        this->setValidator(new QRegExpValidator(rx, this));
        this->setPlaceholderText("Max. timestamp("+QString::number(limit)+")");

    }
    else if(typ.toLower()=="smallint")
    {
        QRegExp rx("([0-9]){"+QString::number(limit)+"}");
        this->setValidator(new QRegExpValidator(rx, this));
        this->setPlaceholderText("Max. smallint("+QString::number(limit)+")");

    }
    else if(typ.toLower()=="bigint")
    {
        QRegExp rx("([0-9]){"+QString::number(limit)+"}");
        this->setValidator(new QRegExpValidator(rx, this));
        this->setPlaceholderText("Max. bigint("+QString::number(limit)+")");

    }

}

void InsertLine::getlineText(QString str)
{
    if(lineid==str)
    {
        if(this->text()!="")
        {
            str_query.append(this->text());
            //qDebug()<<this->text()<<this->typeID;
        }
        else
        {
            str_query.append("NULL");
            //qDebug()<<"NULL"<<this->typeID;

        }
        typelist.append(this->typeID);
    }
    else
    {

    }

}
