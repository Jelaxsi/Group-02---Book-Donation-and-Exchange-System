#include <stdio.h>
#include "user.h"
#include "user_management.h"
#include "database.h"
#include <mysql/mysql.h>
#include "admin.h"
int login_menu();

int main()
{
    login_menu();
}

int login_menu()
{
    char username[30];
    char password[30];
    int choice;
    printf("\n\n\t\tWelcome to Book Donation and Exchange System 📔📚📖\n\n");
    while (1)
    {
        printf("1. Login\n"
               "2. Register\n"
               "3. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1)
        {
            printf("\nEnter your login credintials\n");
            printf("Enter the username: ");
            scanf("%s", username);
            printf("Enter your password: ");
            scanf("%s", password);
            MYSQL *conn = dbconnect();
            if (conn == NULL)
            {
                fprintf(stderr, "Database Connection failes,\n");
            }
            char user_role = fetch_login_data(conn, username, password);
            if (user_role == '\0')
            {
                printf("Invalid username or password.\n");
                mysql_close(conn);
                continue;
            }
            if (user_role == 'a')
            {
                admin(username);
            }
            else if (user_role == 'u')
            {
                user(username);
            }
        }
        else if (choice == 2)
        {
            register_account();
        }
        else if (choice == 3)
        {
            printf("\n\n\nThanks for using Books donation and exchange system\n\n");
            printf("\t\tta-ta Bye! Bye! 👋👋\n\n");
            break;
        }
        else
        {
            printf("\n\n\nWrong option \n");
            printf("Enter a valid option\n\n");
            // break;
        }
    }
}
