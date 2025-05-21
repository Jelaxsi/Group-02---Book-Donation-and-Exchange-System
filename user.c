#include <stdio.h>

int user() {
    int choice;
    printf("1. Donate"
        "2. View Book Inventory"
        "3. Request a Book"
        "4. Track My Requests"
        "5. logout");
    printf ("Enter your choice: ");
    scanf("%d", &choice);
}