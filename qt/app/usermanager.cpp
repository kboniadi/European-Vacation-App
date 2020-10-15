#include "usermanager.h"

// User and Password Section

void createUserTable() // QSqlDatabase &db
{
    QString create = "CREATE TABLE if not exists users ("
                     "ID integer,"
                     "username VARCHAR(20),"
                     "password VARCHAR(20));";
    QSqlQuery query;
    if(!query.exec(create))
    {
        qDebug() << "Error creating table";
    }
    return;
}

bool checkUserTable() // check if user table exists
{
    QString checkUser;
    checkUser = "SELECT name FROM sqlite_master where type='table' AND name='users';";
    QSqlQuery query;
    query.prepare(checkUser);
    if (query.exec()) // found
    {
        return query.next(); // return true if user table found, false if not
    }
    else // error check for table
    {
        qDebug() << query.lastError().text() << endl;
        return false;
    }
}

void addUser(int ID, QString username, QString password) // add user data into database
{
    QString addUser = "INSERT INTO users ("
                       "ID, username, password)"
                       "VALUES (:id, :uname , :pass);";
    QSqlQuery query;
    query.prepare(addUser);
    query.bindValue(":id", ID);
    query.bindValue(":uname", username);
    query.bindValue(":pass", password);
    //qDebug() << query.boundValue(":pass");
    if(!query.exec())
    {
        qDebug() << query.lastError().text() << endl;
        qDebug() << "Error adding " << username << " to users";
    }
    return;
}

bool checkPassword(QString uname, QString pass) // check if user table exists
{
    QString checkPassword;
    checkPassword = "SELECT username FROM users where username=:uname AND password=:pass;";
    QSqlQuery query;
    query.prepare(checkPassword);
    query.bindValue(":uname", uname);
    query.bindValue(":pass",pass);
    if (query.exec()) // found
    {
        return query.next(); // return true if user and password found, false if not match
    }
    else // error check for table
    {
        qDebug() << query.lastError().text() << endl;
        return false;
    }
}
