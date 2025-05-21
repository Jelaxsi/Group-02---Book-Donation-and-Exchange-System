#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>


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

void fetch_book_details(MYSQL *conn)
{
  MYSQL_RES *res;
  MYSQL_ROW row;
  if (mysql_query(conn, "select * from books"))
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
  printf("Book ID\tBook Title\tAuthor\tGenre\tLanguage\n");

  // Fetch and print each row
  while ((row = mysql_fetch_row(res)))
  {
    for (int i = 0; i < mysql_num_fields(res); i++)
    {
      printf("%s\t", row[i] ? row[i] : "NULL");
    }
    printf("\n");
  }
}

void register_user(MYSQL *conn, char name[], char email[], int phone_number, char address[], char role)
{
  char query[1024];
  snprintf(query, sizeof(query), "insert into users (user_name,email,phone_number,address,role) values('%s','%s',%d,'%s','%c')", name, email, phone_number, address, role);
  if (mysql_query(conn, query) != 0)
  {
    fprintf(stderr, "Query Failure\n");
  }
}
