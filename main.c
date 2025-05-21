#include <stdio.h>
#include "user.c"
#include "admin.c"
int login_menu();
void register_account();
int main(){

    int choice;
    choice=login_menu();
}

int login_menu() {
    printf("1. Login\n"
        "2. Register\n"
        "3. Exit\n");
    int choice;
    printf("Enter your choice: ");
    scanf("%d", &choice);
    if (choice == 2){register_account();}
}

//create account
struct user
{
    char role;
    char name[20];
    int age;
};
void register_account()
{
    struct user user;
    int role;
    printf("Enter your detail to create account.\n");
    printf("Enter your name: ");
    scanf("%s",user.name);
    printf("\n");
    printf("Enter your age: ");
    scanf("%d",&user.age);
    printf("\n");
    printf("1. Admin\n2. User \nEnter your role : ");
    scanf("%d",&role);
    if (role == 1){user.role = 'a';}
    else if (role == 2){user.role = 'u';}
}