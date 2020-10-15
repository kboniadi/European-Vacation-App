#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <QtSql> // for password manager

// for password manager
void createUserTable(); // create user table
bool checkUserTable(); // check if user table exists
void addUser(int ID, QString username, QString password); // add user into user table
bool checkPassword(QString uname, QString pass); // check if user table exists

#endif // USERMANAGER_H
