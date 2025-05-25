#include <stdio.h>
#include <mysql/mysql.h>
#include "database.h"
#include "admin.h"
#include "user.h"
void admin(char username[])
{
    while (1)
    {
        int choice;
        printf("1. View all book requests"
               "2. Approve/Reject Request"
               "3. View all Books"
               "4. Create Book"
               "5. View Reports"
               "6. Remove Users"
               "7. Edit Book Details"
               "8. Logout");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        if (choice == 1)
        {
        }
        else if (choice == 2)
        {
        }
        else if (choice == 3)
        {
            view_all_books();
        }
        else if (choice == 4)
        {
        }
        else if (choice == 5)
        {
        }
        else if (choice == 6)
        {
        }
        else if (choice == 7)
        {
        }
        else if (choice == 8)
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
    printf("Book Title: \n\n");
    scanf("%s", Boot_title);
    printf("\nAuthor: \n");
    scanf("%s", author);
    printf("\nGenre: \n");
    scanf("%s", genre);
    printf("\nLanguage: \n");
    scanf("%s", language);
    
};
