#include <stdio.h>
#include <mysql/mysql.h>
#include "database.h"
#include <string.h>
#include "user_management.h"

struct user
{
    char role;
    char name[255];
    char password[255];
    char email[255];
    int phone_number;
    char address[255];
};
void register_account()
{
    struct user user;
    int role;
    printf("\n\nEnter your detail to create account.\n\n");
    printf("Enter your name: ");
    scanf(" %[^\n]s", user.name);
    printf("\n");
    printf("Create a password: ");
    scanf(" %[^\n]s", user.password);
    printf("\n");
    printf("Enter your email: ");
    scanf(" %[^\n]s", user.email);
    printf("\n");
    printf("Enter your phone number: ");
    scanf("%d", &user.phone_number);
    printf("\n");
    printf("Enter your address: ");
    scanf(" %[^\n]s", user.address);
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

    register_user(conn, user.name, user.password, user.email, user.phone_number, user.address, user.role);
}