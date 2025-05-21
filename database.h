#ifndef DATABASE_H
#define DATABASE_H

#include <mysql/mysql.h>

MYSQL *dbconnect(void);
void fetch_book_details(MYSQL *conn);
void register_user(MYSQL *conn, char name[], char email[], int phone_number, char address[], char role);

#endif
