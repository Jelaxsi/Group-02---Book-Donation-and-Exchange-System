#ifndef DATABASE_H
#define DATABASE_H

#include <mysql/mysql.h>

MYSQL *dbconnect(void);
MYSQL_RES *fetch_book_details(MYSQL *conn);
void register_user(MYSQL *conn, char name[], char password[], char email[], int phone_number, char address[], char role);
char fetch_login_data(MYSQL *conn, char username[], char password[]);
void donate_books_db(MYSQL *conn, char username[], int book_id, int no_of_books);
void create_book_db(MYSQL *conn, char book_title[], char author[], char genre[], char language[]);

void book_req_db(MYSQL *conn, int book_id_req, int no_book_req, char username[]);

void fetch_user_details(MYSQL *conn);
void remove_users_db(MYSQL *conn, int user_id_rm);
int view_book_req_db(MYSQL *conn);
int view_book_req_db_user(MYSQL *conn);
void app_rej_req_db(MYSQL *conn, int receiver_id, int response);
#endif
