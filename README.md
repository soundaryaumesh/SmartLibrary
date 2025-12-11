# Smart Library Management System

## Team Members
- Member 1: Name
- Member 2: Name
- Member 3: Name (if applicable)

## Problem Statement
A mini library management system to manage books, students, and issued books using the C programming language.  
This system uses linked lists and a queue to store and manage data dynamically, ensuring smooth operations for issuing and returning books.

## Features
- Add and display books
- Add and display students
- Issue books to students (with quantity update)
- Return books (with quantity update)
- Display issued books queue
- Input validation for robust menu selection
- Optional: Save and load data using file handling (if implemented)

## Data Structures Used
- **Linked List:** To store books and students
- **Queue (Linked List):** To manage issued books in FIFO order

## How to Compile and Run

### Prerequisites:
- GCC compiler installed (TDM-GCC / MinGW-w64 / any C compiler)
- VS Code (or any text editor with terminal)

### Steps:
1. Open the project folder in VS Code.
2. Open `main.c`.
3. Open terminal in VS Code (`Ctrl + ~`).
4. Compile the program:
   ```bash
   gcc main.c -o SmartLibrary.exe
5.run the program
   ./SmartLibrary.exe
6. Use the menu to:
Add books/students
Issue/return books
Display lists and issued queue

Notes:
Enter valid integers for menu choices, book IDs, student IDs, and quantities.
Strings like book titles and student names can include spaces.
The program handles invalid inputs gracefully.
