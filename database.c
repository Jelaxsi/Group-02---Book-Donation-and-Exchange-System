#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include "database.h"



MYSQL *dbconnect(void)
{
  MYSQL *conn = mysql_init(NULL);

  if ((conn = mysql_init(NULL)) == NULL)
  {
    fprintf(stderr, "Could not init DB\n");
    exit(EXIT_FAILURE);

    // return EXIT_FAILURE;
  }
  if (mysql_real_connect(conn, "127.0.0.1", "root", "3559", "book_don_ex_system", 0, NULL, 0) == NULL)
  {
    fprintf(stderr, "DB Connection Error\n");
    exit(EXIT_FAILURE);

    // return EXIT_FAILURE;
  }
  return conn;
}

//Return
char fetch_login_data(MYSQL *conn, char username[], char password[])
{
  MYSQL_RES *res;
  MYSQL_ROW row;

  /// select username,password from users where function value;

  char query[1024];
  snprintf(query, sizeof(query), "select role from users where user_name='%s' and password='%s';", username, password);
  mysql_query(conn, query);
  res = mysql_store_result(conn);
  if (res == NULL)
  {
    fprintf(stderr, "mysql_store_result() failed: %s\n", mysql_error(conn));
    return '\0';
  }

  row = mysql_fetch_row(res);
  if (row == NULL)
  {
    mysql_free_result(res);
    return '\0'; // no match found
  }
  printf("%s", row);
  char role = row[0][0]; // Get the first character of the role
  mysql_free_result(res);
  return role;
}

MYSQL_RES *fetch_book_details(MYSQL *conn)
{
  MYSQL_RES *res;
  MYSQL_ROW row;
  if (mysql_query(conn, "select * from books;") != 0)
  {
    fprintf(stderr, "SELECT query failed. Error: %s\n", mysql_error(conn));
  }
  res = mysql_store_result(conn);

  return res;
}

void register_user(MYSQL *conn, char name[], char password[], char email[], int phone_number, char address[], char role)
{
  char query[1024];
  snprintf(query, sizeof(query), "insert into users (user_name,password,email,phone_number,address,role) values('%s','%s','%s',%d,'%s','%c')", name, password, email, phone_number, address, role);
  if (mysql_query(conn, query))
  {
    fprintf(stderr, "Query Failure\n");
  }
  else
  {
    printf("\n\n\nYour account Created Successfuly.\n\n\n");
  }
}

// char username[30];

void donate_books_db(MYSQL *conn, char username[], int book_id, int no_of_books)
{
  MYSQL_RES *res;
  MYSQL_ROW row;
  int user_id;
  char query[1024];
  snprintf(query, sizeof(query), "select user_id from users where user_name='%s'", username);

  mysql_query(conn, query);
  res = mysql_store_result(conn);

  if (res == NULL)
  {
    fprintf(stderr, "mysql_store_result() failed: %s\n", mysql_error(conn));
  }

  row = mysql_fetch_row(res);
  if (row == NULL)
  {
    fprintf(stderr, "User not found.\n");
    mysql_free_result(res);
    // return;
  }
  user_id = atoi(row[0]);
  printf("userid = %d", user_id); // for testing
                                  // got user_id
  snprintf(query, sizeof(query), "insert into donation_details (user_id,book_id,no_of_books) values(%d,%d,%d)", user_id, book_id, no_of_books);
  printf("%s", query); // for testing
  if (mysql_query(conn, query))
  {
    fprintf(stderr, "Query Failure\n");
  }
  else
  {
    printf("\n\n\n Donated.\n\n\n");
  }
}


// Admin 