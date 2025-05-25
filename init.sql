-- init.sql
CREATE DATABASE IF NOT EXISTS book_don_ex_system;
USE book_don_ex_system;

CREATE TABLE IF NOT EXISTS books (
  Book_id INT AUTO_INCREMENT PRIMARY KEY,
  Book_title VARCHAR(100),
  author VARCHAR(100),
  genre VARCHAR(100),
  language VARCHAR(100)
);

CREATE TABLE IF NOT EXISTS users (
  User_id INT AUTO_INCREMENT PRIMARY KEY,
  User_name  VARCHAR(100),
  password VARCHAR(100),
  email VARCHAR(100),
  phone_number int,
  address VARCHAR(300),
  registed_date DATETIME DEFAULT CURRENT_TIMESTAMP,
  role VARCHAR(1)
);

CREATE TABLE IF NOT EXISTS donation_details (
  donation_id INT AUTO_INCREMENT PRIMARY KEY,
  user_id  int,
  book_id int,
  no_of_books int ,
  donation_date DATETIME DEFAULT CURRENT_TIMESTAMP
  
);

CREATE TABLE IF NOT EXISTS receiver_details (
  receiver_id INT AUTO_INCREMENT PRIMARY KEY,
  user_id  int,
  book_id int,
  no_of_books int ,
  requested_date DATETIME DEFAULT CURRENT_TIMESTAMP,
  request_status VARCHAR(10) DEFAULT 'pending'
  
);

