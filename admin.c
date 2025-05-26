#include <stdio.h>
#include <mysql/mysql.h>
#include "database.h"
#include "admin.h"
#include "user.h"
void admin(char username[])
{
    printf("\n\n\n\t\t\tHi👋 %s \n\t\tYou have logged in as Admin\n\n", username);
    printf("---------------------------------------------------------\n\n");
    while (1)
    {
        int choice;

        printf("1. View all Books \n"
               "2. Approve/Reject Request\n"
               "3. View all book requests\n"
               "4. Create Book\n"
               "5. View all Users\n"
               "6. Remove Users\n"
               "7. Logout\n\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        if (choice == 1)
        {

            view_all_books();
        }
        else if (choice == 2)
        {

            app_rej_req();
        }
        else if (choice == 3)
        {
            MYSQL *conn = dbconnect();
            if (conn == NULL)
            {
                fprintf(stderr, "Database connection failed.\n");
            }

            if (view_book_req_db(conn) == 1)
            {
            }
            else if (view_book_req_db(conn) == 0)
            {
                printf("\n\n\t No Request pending\n\n");
            }
        }
        else if (choice == 4)
        {
            create_book();
        }
        else if (choice == 5)
        {
            MYSQL *conn = dbconnect();
            if (conn == NULL)
            {
                fprintf(stderr, "Database connection failed.\n");
            }
            fetch_user_details(conn);
        }
        else if (choice == 6)
        {
            remove_users();
        }

        else if (choice == 7)
        {
            break;
        }
    }
}

void create_book()
{
    char Boot_title[255], author[255], genre[255], language[255];
    MYSQL *conn = dbconnect();
    if (conn == NULL)
    {
        fprintf(stderr, "Database connection failed.\n");
    }
    printf("\n\nEnter Book Details to add\n\n");
    printf("Book Title: ");
    scanf("%s", Boot_title);
    printf("\nAuthor: ");
    scanf("%s", author);
    printf("\nGenre: ");
    scanf("%s", genre);
    printf("\nLanguage: ");
    scanf("%s", language);
    create_book_db(conn, Boot_title, author, genre, language);
};

void remove_users()
{
    int user_id_rm;
    MYSQL *conn = dbconnect();
    if (conn == NULL)
    {
        fprintf(stderr, "Database connection failed.\n");
    }

    fetch_user_details(conn);
    printf("Enter user id of the user that u want to remove: ");
    scanf("%d", &user_id_rm);
    remove_users_db(conn, user_id_rm);
}

void app_rej_req()
{
    int receiver_id, response;
    MYSQL *conn = dbconnect();
    if (conn == NULL)
    {
        fprintf(stderr, "Database connection failed.\n");
    }

    if (view_book_req_db(conn) == 1)
    {
        printf("select the receiver id: ");
        scanf("%d", &receiver_id);
        printf("\n");
        printf("1. Approve Request\n");
        printf("2. Reject Request\n");
        printf("Enter your decision: ");
        scanf("%d", &response);

        app_rej_req_db(conn, receiver_id, response);
    }
    else if (view_book_req_db(conn) == 0)
    {
        printf("\n\n\t No Request pending\n\n");
    }
}