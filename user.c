#include <stdio.h>
#include "database.h"
#include <mysql/mysql.h>
int user()
{
    int choice;
    printf("1. View All Books"
           "2. Donate Books"
           "3. Request Book"
           "4. Search Book"
           "5. Track My Requests"
           "6. logout");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    MYSQL *conn = dbconnect();
    if (conn == NULL)
    {
        fprintf(stderr, "Database connection failed.\n");
    }
    if (choice == 1)
    {
        fetch_book_details(conn);
    }
}