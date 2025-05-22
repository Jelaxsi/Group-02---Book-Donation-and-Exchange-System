# Group-02---Book-Donation-and-Exchange-System
The **Book Donation and Exchange system** is a c-based console application designed to Facilitate the donation and exchange of the books among the users. 
This system aim specifically to promote resources sharing, reduce book waste, and create a community-driven book circulation platform

##Database Tables
### 1. 'Books'
Stores details about the books available for donation.
| Field       | Type           | Key | Extra           |
|-------------|----------------|-----|-----------------|
| Book_id     | int            | PRI | auto_increment  |
| Book_title  | varchar(255)   |     |                 |
| author      | varchar(255)   |     |                 |
| genre       | varchar(255)   |     |                 |
| language    | varchar(255)   |     |                 |

### 2. 'Donation Details'
Tracks the donation of books by the user 
|Field         | Type           | Key | Default           |
|-----------   |----------------|-----|-------------------|
|Book_id       | int            | MUL | Null              |
|User_id       | int            | MUL | Null              |
|Donation_id   | int            | PRI | Null              |
|no_of_books   | int            |     | Null              |
|Donation_date | int            |     | Current_Timestamp |

### 3. 'Users'
Stores user information including donors and general user
| Field            | Type          | Key  | Extra           |
|------------------|--------------|-----|-------------------|
| user_id          | int          | PRI | auto_increment    |
| user_name        | varchar(255) |     |                   |
| Password         | int          |     |                   |
| email            | varchar(255) | UNI |                   |
| phone_number     | int          |     |                   |
| address          | varchar(255) |     |                   |
| Registered_date  | datetime     |     | CURRENT_TIMESTAMP |
| role             | varchar(1)   |     |                   |

### 4. 'Recevier Details'
Logs the receving of books by receipients

| Field            | Type         | Key | Default           |
|------------------|--------------|-----|-------------------|
| Book_id          | int          | MUL | NULL              |
| user_id          | int          | MUL | NULL              |
| Receiver_id      | int          | PRI | NULL              |
| no_of_books      | int          |     | NULL              |
| Received_date    | datetime     |     | CURRENT_TIMESTAMP |
----

















## Notes ##
*All datetime fields (donation_date,Registered_date,Received_date) are set to default  to the current timestamp.
*Primary keys are clearly defined for each table uniquely identify records.
*foreign key relationships are impiled (ex:- Book_id and User_id appear in multiple tables) 

## USAGE ##
1. Track Books available for donation.
2. Record who donates and who receives the books
3. Maintain a registry of all users in SQL.




