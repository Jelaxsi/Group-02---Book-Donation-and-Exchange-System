#ifndef ADMIN_H
#define ADMIN_H

#include <mysql/mysql.h>

void admin(char username[]);

void create_book();
void remove_users();

void app_rej_req();

#endif
