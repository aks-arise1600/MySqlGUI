#ifndef INSERTVALUE_H
#define INSERTVALUE_H
#include<insertline.h>
#include <QWidget>
#include <QLabel>
#include <QFont>
#include <QListWidgetItem>
#include <QSqlQuery>
#include <QHBoxLayout>
#include <QSqlError>
#include <QMap>

extern QStringList str_query;
extern QStringList typelist;

namespace Ui {
class InsertValue;
}

class InsertValue : public QWidget
{
    Q_OBJECT

public:
    explicit InsertValue(QWidget *parent = 0);
    ~InsertValue();
    void AddItems(QString,QString,int);
    QLabel *Label;
    QFont *font;
    InsertLine *Line;
    QListWidgetItem * item;
    QWidget *widget;
    QHBoxLayout *horizontal;
    int count;
public slots:
    void Insert_into();
signals:
    void textGet(QString);

private:
    Ui::InsertValue *ui;
};

#endif // INSERTVALUE_H
