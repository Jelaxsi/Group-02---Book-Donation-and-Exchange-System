#include <stdio.h>
#include "user.h"
#include "user_management.h"
#include "database.h"
#include <mysql/mysql.h>

int login_menu();

int main()
{
    login_menu();
}

int login_menu()
{
    char username[30];
    char password[30];
    while (1)
    {
        printf("1. Login\n"
               "2. Register\n"
               "3. Exit\n");
        int choice;
        printf("Enter your choice: ");
        scanf("%d", &choice);
        while (1)
        {

            if (choice == 1)
            {
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
                    printf("addmin");
                }
                else if (user_role == 'u')
                {
                    user();
                }
            }
            else if (choice == 2)
            {
                register_account();
                break;
            }
        }
    }
}
