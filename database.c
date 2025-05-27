#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include "database.h"
#include <string.h>

MYSQL *dbconnect(void)
{
  MYSQL *conn = mysql_init(NULL);

  if ((conn = mysql_init(NULL)) == NULL)
  {
    fprintf(stderr, "Could not init DB\n");
    exit(EXIT_FAILURE);

    // return EXIT_FAILURE;
  }
  if (mysql_real_connect(conn, "127.0.0.1", "root", "SEUSL", "book_don_ex_system", 0, NULL, 0) == NULL)
  {
    fprintf(stderr, "DB Connection Error\n");
    exit(EXIT_FAILURE);

    // return EXIT_FAILURE;
  }
  return conn;
}

// Return
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
    printf("Duplicate Entry");
  }
  else
  {
    printf("\n\n\nYour account Created Successfuly.\n\n\n");
  }
}

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
  // got user_id
  snprintf(query, sizeof(query), "insert into donation_details (user_id,book_id,no_of_books) values(%d,%d,%d)", user_id, book_id, no_of_books);
  if (mysql_query(conn, query))
  {
    fprintf(stderr, "Query Failure\n");
  }
  else
  {
    printf("\n\n\n Donated.\n\n\n");
  }
}

void book_req_db(MYSQL *conn, int no_book_req, int book_id_req, char username[])
{
  // checking for available amount of books

  int amount_have = 0;
  int amount_gone = 0;
  int amount_left;
  MYSQL_RES *res;
  MYSQL_ROW row;
  char query[1024];
  snprintf(query, sizeof(query), "select no_of_books from donation_details where book_id='%d'", book_id_req);
  if (mysql_query(conn, query) != 0)
  {
    fprintf(stderr, "SELECT query failed. Error: %s\n", mysql_error(conn));
  }
  res = mysql_store_result(conn);
  while ((row = mysql_fetch_row(res)))
  {
    amount_have += atoi(row[0]);
  }

  // MYSQL_RES *res;
  // MYSQL_ROW row;
  snprintf(query, sizeof(query), "select no_of_books from receiver_details where book_id=%d and request_status='approved'", book_id_req);
  if (mysql_query(conn, query) != 0)
  {
    fprintf(stderr, "SELECT query failed. Error: %s\n", mysql_error(conn));
  }
  res = mysql_store_result(conn);
  while ((row = mysql_fetch_row(res)))
  {
    amount_gone += atoi(row[0]);
  }
  amount_left = amount_have - amount_gone;

  if (amount_left <= 0)
  {
    printf("\n\nThere is no more books left to Donate😕\n\n");
  }
  else if (amount_left < no_book_req)
  {
    printf("only %d books left on this title\n your request cannot be completed \ninsufficient books left 😕\n\n", amount_left);
  }
  else
  {

    // sending book request (insert to table )
    int user_id;
    snprintf(query, sizeof(query), "select user_id from users where user_name='%s'", username);

    if (mysql_query(conn, query) != 0)
    {
      fprintf(stderr, "SELECT query failed. Error: %s\n", mysql_error(conn));
    }
    res = mysql_store_result(conn);
    if (res == NULL)
    {
      fprintf(stderr, "mysql_store_result() failed. Error: %s\n", mysql_error(conn));
    }
    row = mysql_fetch_row(res);
    if (row == NULL)
    {
      fprintf(stderr, "User not found.\n");
      mysql_free_result(res);
    }
    user_id = atoi(row[0]);

    snprintf(query, sizeof(query), "insert into receiver_details(book_id,user_id,no_of_books) values('%d','%d','%d')", book_id_req, user_id, no_book_req);

    if (mysql_query(conn, query) != 0)
    {
      fprintf(stderr, "SELECT query failed. Error: %s\n", mysql_error(conn));
    }
    else
    {
      printf("\n\tYour request has benn sent to the admin for the approval. ☺️\n\n\n ");
    }
  }
}

int view_book_req_db_user(MYSQL *conn)
{
  MYSQL_RES *res;
  MYSQL_ROW row;
  if (mysql_query(conn, "select receiver_id,user_name,Book_title,no_of_books,requested_date,request_status from receiver_details inner join books on receiver_details.book_id=books.book_id inner join users on users.user_id=receiver_details.user_id where request_status='pending'") != 0)
  {
    fprintf(stderr, "SELECT query failed. Error: %s\n", mysql_error(conn));
  }
  res = mysql_store_result(conn);

  if (res == NULL)
  {
    fprintf(stderr, "mysql_store_result() failed. Error: %s\n", mysql_error(conn));
    mysql_close(conn);
    exit(EXIT_FAILURE);
  }

  row = mysql_fetch_row(res);
  if (row)
  {

    printf("Receiver ID\tUser Name\tBook Title\t Number of Requsted Books\tDate Requested\tRequest Status\n");
    mysql_data_seek(res, 0);
    while ((row = mysql_fetch_row(res)))
    {
      for (int i = 0; i < mysql_num_fields(res); i++)
      {
        printf("%s\t", row[i] ? row[i] : "NULL");
      }
      printf("\n");
    }
    return 1;
  }
  else
  {
    return 0;
  }
}

// Admin

void create_book_db(MYSQL *conn, char book_title[], char author[], char genre[], char language[])
{
  char query[200];
  snprintf(query, sizeof(query), "insert into books(book_title,author,genre,language) values('%s','%s','%s','%s')", book_title, author, genre, language);
  if (mysql_query(conn, query))
  {
    fprintf(stderr, "Query Failure\n");
  }
  else
  {
    printf("\n\n\n Book added successfully.\n\n\n");
  }
}

void fetch_user_details(MYSQL *conn)
{
  MYSQL_RES *res;
  MYSQL_ROW row;
  if (mysql_query(conn, "select * from users;") != 0)
  {
    fprintf(stderr, "SELECT query failed. Error: %s\n", mysql_error(conn));
  }
  res = mysql_store_result(conn);

  if (res == NULL)
  {
    fprintf(stderr, "mysql_store_result() failed. Error: %s\n", mysql_error(conn));
    mysql_close(conn);
    exit(EXIT_FAILURE);
  }

  printf("User ID\tUser Name\tPassword\tEmail\tPhone Number\tAddress\tRegistered_date\tRole\n");

  while ((row = mysql_fetch_row(res)))
  {
    for (int i = 0; i < mysql_num_fields(res); i++)
    {
      if (i == 2 & *row[2] == 'a')
      {
        printf("Admin\t");
      }
      else if (i == 2 & *row[2] == 'u')
      {
        printf("User\t");
      }
      else
      {
        printf("%s\t", row[i] ? row[i] : "NULL");
      }
    }
    printf("\n");
  }
  printf("\n\n");
}

void remove_users_db(MYSQL *conn, int user_id_rm)
{
  char query[225];
  // snprintf(query, sizeof(query), "delete from donation_details where user_id=%d", user_id_rm);
  // if (mysql_query(conn, query))
  // {
  //   fprintf(stderr, "Query Failure\n");
  // }

  // snprintf(query, sizeof(query), "delete from receiver_details where user_id=%d", user_id_rm);
  // if (mysql_query(conn, query))
  // {
  //   fprintf(stderr, "Query Failure\n");
  // }

  snprintf(query, sizeof(query), "delete from users where user_id=%d", user_id_rm);
  if (mysql_query(conn, query))
  {
    fprintf(stderr, "Query Failure\n");
  }

  else
  {
    printf("\n\n\n User removed successfully.\n\n\n");
  }
}

int view_book_req_db(MYSQL *conn)
{
  MYSQL_RES *res;
  MYSQL_ROW row;
  if (mysql_query(conn, "select receiver_id,user_name,Book_title,no_of_books,requested_date from receiver_details inner join books on receiver_details.book_id=books.book_id inner join users on users.user_id=receiver_details.user_id where request_status='pending'") != 0)
  {
    fprintf(stderr, "SELECT query failed. Error: %s\n", mysql_error(conn));
  }
  res = mysql_store_result(conn);

  if (res == NULL)
  {
    fprintf(stderr, "mysql_store_result() failed. Error: %s\n", mysql_error(conn));
    mysql_close(conn);
    exit(EXIT_FAILURE);
  }

  row = mysql_fetch_row(res);
  if (row)
  {

    printf("Receiver ID\tUser Name\tBook Title\t Number of Requsted Books\tDate Requested\n");
    mysql_data_seek(res, 0);
    while ((row = mysql_fetch_row(res)))
    {
      for (int i = 0; i < mysql_num_fields(res); i++)
      {
        printf("%s\t", row[i] ? row[i] : "NULL");
      }
      printf("\n");
    }
    return 1;
  }
  else
  {
    return 0;
  }
}

void app_rej_req_db(MYSQL *conn, int receiver_id, int response)
{
  char response_char[16];
  if (response == 1)
  {
    strcpy(response_char, "Approved");
  }
  else if (response == 2)
  {
    strcpy(response_char, "rejected");
  }
  MYSQL_RES *res;
  MYSQL_ROW row;
  char query[1024];
  snprintf(query, sizeof(query), "update receiver_details set request_status='%s' where receiver_id=%d", response_char, receiver_id);

  if (mysql_query(conn, query) != 0)
  {
    fprintf(stderr, "SELECT query failed. Error: %s\n", mysql_error(conn));
  }
  else
  {
    printf("\n\n\tStatus Updated Successfully ☺️\n\n\n");
  }
}
