/* =====================================================================================================
NAME OF FUNCTION:    CDatabaseManipulation::Connect
CREDIT:              Satish Jagtap
PURPOSE:             This function is used to connect MYSQL database.
PARAMETERS:          [IN] 1) TCHAR *ptchHost: Parameter passed as ptchHost may be either a host name or
                             an IP address. If host is NULL or the string "localhost", a connection to
                             the local host is assumed.
                             For Windows, the client connects using a shared-memory connection,if the
                             server has shared-memory connections enabled. Otherwise, TCP/IP is used.
                     [IN] 2) TCHAR *ptchUserID: Parameter passed as ptchUserID contains the user's
                             MySQL login ID.
                     [IN] 3) TCHAR *ptchDatabase: Parameter passed as ptchDatabase is the database
                             name. If ptchDatabase is not NULL, the connection sets the default
                             database to this value.
                     [IN] 4) TCHAR *ptchPassword: Parameter passed as ptchPassword contains the
                             password for user.
RETURN VALUE:        None
CALLS TO:            None
CALLED FROM:         None
Added date:          1 September, 2018
Updated date:
======================================================================================================*/


#include "mysqllogin.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MysqlLogin w;
    w.show();

    return a.exec();
}
