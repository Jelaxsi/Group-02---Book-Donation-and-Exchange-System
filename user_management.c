#include <stdio.h>
#include <mysql/mysql.h>
#include "database.h"
#include <string.h>



// create account
struct user
{
    char role;
    char name[255];
    char email[255];
    int phone_number;
    char address[255];
};
void register_account()
{
    struct user user;
    int role;
    printf("Enter your detail to create account.\n");
    printf("Enter your name: ");
    scanf("%s", user.name);
    printf("\n");
    printf("Enter your email: ");
    scanf("%s", user.email);
    printf("\n");
    printf("Enter your phone number: ");
    scanf("%d", &user.phone_number);
    printf("\n");
    printf("Enter your address: ");
    getchar(); // flush newline from previous input
    fgets(user.address, sizeof(user.address), stdin);
    user.address[strcspn(user.address, "\n")] = 0;
    printf("\n");
    printf("1. Admin\n2. User \nEnter the number for your role : ");
    scanf("%d", &role);
    if (role == 1)
    {
        user.role = 'a';
    }
    else if (role == 2)
    {
        user.role = 'u';
    }

    MYSQL *conn = dbconnect();
    if (conn == NULL)
    {
        fprintf(stderr, "Database connection failed.\n");
    }

    register_user(conn, user.name, user.email, user.phone_number, user.address, user.role);
}