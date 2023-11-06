#ifndef INSERTLINE_H
#define INSERTLINE_H
#include <QLineEdit>
#include <QDebug>
#include <QRegExp>
#include <QRegExpValidator>

class InsertLine: public QLineEdit
{
    Q_OBJECT
public:
    InsertLine(QString id,QString typ,int limit);
    QString lineid;
    QString typeID;
public slots:
    void getlineText(QString);
};

#endif // INSERTLINE_H
