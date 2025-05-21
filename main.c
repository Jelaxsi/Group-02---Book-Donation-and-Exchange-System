#include <stdio.h>
#include "user.h"
#include "user_management.h"

int login_menu();

int main()
{
    login_menu();
}

int login_menu()
{
    printf("1. Login\n"
           "2. Register\n"
           "3. Exit\n");
    int choice;
    printf("Enter your choice: ");
    scanf("%d", &choice);
    if (choice == 1)
    {
        user();
    }
    else if (choice == 2)
    {
        register_account();
    }
}
