#include <stdio.h>
#include "database.h"
#include <mysql/mysql.h>
#include "user.h"
#include <stdlib.h>

void user(char username[])
{
    printf("\n\n\n\t\t\tHi👋 %s \n\t\tYou have logged in as User\n\n", username);
    printf("---------------------------------------------------------\n\n");

    while (1)
    {

        int choice;
        printf("1. View All Books\n"
               "2. Donate Books\n"
               "3. Request Book\n"
               "4. Track My Requests\n"
               "5. logout\n\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1)
        {
            view_all_books();
        }

        else if (choice == 2)
        {
            donate_books(username);
        }
        else if (choice == 3)
        {
            request_book(username);
        }
        else if (choice == 4)
        {
            MYSQL *conn = dbconnect();
            if (conn == NULL)
            {
                fprintf(stderr, "Database connection failed.\n");
            }

            if (view_book_req_db_user(conn) == 1)
            {
            }
            else if (view_book_req_db_user(conn) == 0)
            {
                printf("\n\n\t No Request pending\n\n");
            }
        }
        else if (choice == 5)
        {
            printf("You have been Logged out of the system! \n\n");
            break;
        }
    }
}

void view_all_books()
{
    MYSQL_ROW row;
    MYSQL *conn = dbconnect();
    if (conn == NULL)
    {
        fprintf(stderr, "Database connection failed.\n");
    }

    MYSQL_RES *res = fetch_book_details(conn);
    if (res == NULL)
    {
        fprintf(stderr, "mysql_store_result() failed. Error: %s\n", mysql_error(conn));
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }
    row = mysql_fetch_row(res);
    if (row)
    {
    printf("Book ID\tBook Title\tAuthor\tGenre\tLanguage\n");
    mysql_data_seek(res, 0);
    while ((row = mysql_fetch_row(res)))
    {
        for (int i = 0; i < mysql_num_fields(res); i++)
        {
            // printf("printing line of books");

            printf("%s",row[i] ? row[i] : "NULL");
            printf("\t");
        }
        printf("\n");
    }
    }
    else
    {
        printf("\t\t\n\nThere are No Book Available.😕\n");
    }
    printf("\n\n");
}

int book_id;
int no_of_books;
void donate_books(char username[])
{

    MYSQL *conn = dbconnect();
    if (conn == NULL)
    {
        fprintf(stderr, "Database connection failed.\n");
    }
    view_all_books();
    printf("Select a book from this list to donate!\n\n\n");
    printf("Enter a book id to Donate: ");
    scanf("%d", &book_id);

    printf("\n");
    printf("Enter the amount books you want to donate: ");
    scanf("%d", &no_of_books);
    donate_books_db(conn, username, book_id, no_of_books);
}

void request_book(char username[])
{
    MYSQL *conn = dbconnect();
    if (conn == NULL)
    {
        fprintf(stderr, "Database connection failed.\n");
    }
    view_all_books();
    printf("\nSelect the book📚 to be requested\n");
    int no_book_req;
    int book_id_req;
    printf("\n\nEnter the Book id of the book: ");
    scanf("%d", &book_id_req);
    printf("\n\nEnter the amount of book that you want: ");
    scanf("%d", &no_book_req);
    book_req_db(conn, no_book_req, book_id_req, username);
}
