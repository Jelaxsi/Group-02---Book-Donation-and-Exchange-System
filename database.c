#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    // Initialize
    conn = mysql_init(NULL);
    if (conn == NULL) {
        printf("mysql_init() failed\n");
        return 1;
    }

    // Connect to MySQL
    if (mysql_real_connect(conn, "localhost", "root", "3559", "user", 0, NULL, 0) == NULL) {
        fprintf(stderr, "mysql_real_connect() failed\nError: %s\n", mysql_error(conn));
        mysql_close(conn);
        return 1;
    }

    // Run Query
    if (mysql_query(conn, "SELECT * FROM books")) {
        fprintf(stderr, "SELECT failed. Error: %s\n", mysql_error(conn));
        mysql_close(conn);
        return 1;
    }

    // Store & Print Result
    res = mysql_store_result(conn);
    if (res == NULL) {
        fprintf(stderr, "mysql_store_result() failed\n");
        mysql_close(conn);
        return 1;
    }

    int num_fields = mysql_num_fields(res);
    while ((row = mysql_fetch_row(res))) {
        for (int i = 0; i < num_fields; i++) {
            printf("%s ", row[i] ? row[i] : "NULL");
        }
        printf("\n");
    }

    // Clean up
    mysql_free_result(res);
    mysql_close(conn);

    return 0;
}
