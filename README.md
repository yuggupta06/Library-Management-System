# 📚 Library Management System

A simple and efficient console-based **Library Management System** written in C++ using **object-oriented programming** and **file handling**. This system allows users to **sign up**, **issue**, **return**, and **view** books. It also includes admin functionalities and implements **data persistence** using `books.txt` and `users.txt`.

---

## 🚀 Features

- 👤 **User Management**
  - Sign up and login
  - Store user credentials and issued books
  - Username validation and duplication checks
  - Fine notification for overdue books

- 📖 **Book Management**
  - Store and read books from `books.txt`
  - Check availability
  - Issue and return books
  - Store issue dates and status persistently

- 🛠️ **Admin Access**
  - Access via a predefined username/password (e.g., `Yug/7017`)
  - Extended capabilities can be added for managing the system

- 🗃️ **File-Based Persistence**
  - All user and book data is stored and updated in `users.txt` and `books.txt`
  - Temporary files are used for safe overwrite (`temp.txt`)

---

## 🧱 Code Structure

| File | Description |
|------|-------------|
| `library_management.cpp` | Main file containing the flow for login/signup and user tasks |
| `book_class.h` | Book class with methods for issuing/returning books and file updates |
| `user_class.h` | User class for managing user accounts and book interactions |
| `books.txt` | Stores all book data (id, name, author, status) |
| `users.txt` | Stores user data and their issued book IDs |
| `library_management.exe` | Precompiled executable (for Windows) |


