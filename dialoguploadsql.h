/**
* @file DialogUploadSQL.h
* @author Anil Kumar
* @date 17-11-2017
* @brief This header of DialogUploadSQL class.
*/
#ifndef DIALOGUPLOADSQL_H
#define DIALOGUPLOADSQL_H

#include <QDialog>
#include <QFile>
#include <QFileDialog>
#include <QProcess>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QObject>
#include <QLabel>
#include <common.h>
#include <QDir>

namespace Ui {
class DialogUploadSQL;
}

class DialogUploadSQL : public QDialog
{
    Q_OBJECT

public:
    explicit DialogUploadSQL(QWidget *parent = 0, bool isexport = false);
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
    bool is_export;
};

#endif // DIALOGUPLOADSQL_H
