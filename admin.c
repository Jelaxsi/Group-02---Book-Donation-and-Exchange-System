#include <stdio.h>
int admin()
{
    int choice;
    printf("1. View all book requests"
        "2. Approve/Reject Request"
        "3. Manage Book Inventory"
        "4. View Reports"
        "5. Manage Users"
        "6. Logout");
    printf("Enter your choice: ");
    scanf("%d", &choice);
}