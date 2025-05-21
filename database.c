#include <stdio.h>                                                                                   
#include <stdlib.h>                                                                                  
#include <mysql/mysql.h>                                                                             

int main(void)                                                                                       
{                                                                                                    
  MYSQL *conn;                                                                                       

  if ((conn = mysql_init(NULL)) == NULL)                                                             
  {                                                                                                  
    fprintf(stderr, "Could not init DB\n");                                                 
    return EXIT_FAILURE;                                                                             
  }                                                                                                  
  if (mysql_real_connect(conn, "127.0.0.1", "root", "3559", "user", 0, NULL, 0) == NULL)             
  {                                                                                                  
    fprintf(stderr, "DB Connection Error\n");                                                        
    return EXIT_FAILURE;                                                                             
  } 
  
  

  if (mysql_query(conn, "INSERT INTO books VALUES (20,'Harry potter')") != 0)                   
  {                                                                                                  
    fprintf(stderr, "Query Failure\n");                                                              
    return EXIT_FAILURE;                                                                             
  }                                                                                                  
  
  
  mysql_close(conn);                                                                                 
  return EXIT_SUCCESS;                                                                               
}
