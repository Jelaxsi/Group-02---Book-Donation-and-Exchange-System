#include <stdio.h>
int admin()
{
    int choice;
    printf("1. View all book requests"
           "2. Approve/Reject Request"
           "3. Create Book"
           "4. View Reports"
           "5. Remove Users"
           "6. Edit Book Details"
           "7. Logout");
    printf("Enter your choice: ");
    scanf("%d", &choice);
}