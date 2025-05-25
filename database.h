#ifndef DATABASE_H
#define DATABASE_H

#include <mysql/mysql.h>

MYSQL *dbconnect(void);
MYSQL_RES *fetch_book_details(MYSQL *conn);
void register_user(MYSQL *conn, char name[], char password[], char email[], int phone_number, char address[], char role);
char fetch_login_data(MYSQL *conn, char username[], char password[]);
void donate_books_db(MYSQL *conn, char username[], int book_id, int no_of_books);

#endif
