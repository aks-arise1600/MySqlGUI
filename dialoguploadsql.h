#ifndef DIALOGUPLOADSQL_H
#define DIALOGUPLOADSQL_H

#include <QDialog>
#include <qfile.h>
#include <QFileDialog>
#include <QProcess>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QObject>
#include <QLabel>

namespace Ui {
class DialogUploadSQL;
}

class DialogUploadSQL : public QDialog
{
    Q_OBJECT

public:
    explicit DialogUploadSQL(QWidget *parent = 0);
    ~DialogUploadSQL();
    QString m_fileName;
    QLabel *file_sql;
signals:
    void refresh();

private slots:
    void on_pushButton_browse_clicked();
    void on_pushButton_Upload_clicked();

private:
    Ui::DialogUploadSQL *ui;
};

#endif // DIALOGUPLOADSQL_H
