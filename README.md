# Smart Library Management System 📚  
**Course:** Data Structures Mini Project  
**Language:** C  
**Concepts Used:** Modular Programming, File Handling, Data Structures, Auto-Suggestion Logic

---

## 📌 Project Overview
The Smart Library Management System is a console-based application developed in C to efficiently manage library operations.  
It allows users to add books, search books, issue/return books, maintain records using files, and intelligently auto-suggest books based on the user’s first choice.

This project demonstrates:
✔ Practical application of Data Structures  
✔ Proper Modular Programming Structure  
✔ Persistent Data Storage using File Handling  
✔ Simple Recommendation System (Auto Suggestion)

---

## 🎯 Objectives
- To implement real-world problem solving using C
- To use **Modular Programming**
- To implement **File Handling** for permanent storage
- To demonstrate **efficient searching & data management**
- To add innovation using **Auto Suggest Feature**

---

## 🚀 Key Features
### 🔹 1. Add New Books
Stores books permanently using file handling.

### 🔹 2. Display All Books
Reads and prints all book records from file.

### 🔹 3. Search Books
Supports search by:
- Book Name  
- Author Name  
- Book ID  

### 🔹 4. Issue Book
Marks books as issued and stores issue details.

### 🔹 5. Return Book
Updates record back to available state.

### 🔹 6. Delete Book
Removes a record from file safely.

### 🔹 7. Auto Suggest Books (Innovation Feature ⭐)
When a user selects a book or category once,
the system **auto-suggests similar books** based on:
- Same Category / Genre
- Same Author
- Popular Books List in File

This enhances user experience similar to online libraries.

---

## 🏗️ Modular Programming Structure
The project strictly follows modular programming:
main.c → main menu + control
books.c → add, display, search
issue.c → issue & return handling
suggestion.c → auto suggest feature logic
filehandler.c → file read / write operations
library.h → function declarations + structures


Advantages:
✔ Code becomes readable  
✔ Easy debugging  
✔ Reusable modules  
✔ Professional project structure  

---

## 🗂️ Data Structures Used
struct Book {
int id;
char title[50];
char author[50];
char category[30];
int isIssued;
};


---

## 💾 File Handling
The project uses files for permanent storage:
books.txt → stores all books
issued.txt → stores issued book details
suggest.txt → stores user preference history


Operations included:
✔ Append  
✔ Update  
✔ Delete  
✔ Read / Write  
✔ Temporary File Replacement Method for Safe Delete  

---

## 🧠 Auto Suggestion Logic (Innovation Feature)
The system suggests books based on:

- If user selected a “Category”
  → Suggest books of same category
- If user selected a specific “Author”
  → Suggest books by same author
- If no match available
  → Suggest Top Popular Books from suggest.txt

---

## 🖥️ How to Run the Project
### ✔️ Step 1: Compile
gcc main.c books.c issue.c filehandler.c suggestion.c -o SmartLibrary

### ✔️ Step 2: Run
./SmartLibrary (Linux / Mac)
SmartLibrary.exe (Windows)

---

## 📂 Project Output (Expected)
- Clear menu-based interface
- Proper status messages
- Persistent stored data
- Auto Suggest display after user choice

---

## 📝 Assumptions
- User enters valid input
- Basic text environment
- Files exist or will auto-create

---

## 🔮 Future Enhancements
- GUI Version
- Student / Admin Login
- Due Date & Fine System
- Book Ratings

---

## ✅ Conclusion
This project successfully demonstrates:
✔ Modular Programming  
✔ File Handling  
✔ Data Structures Application  
✔ Innovation using Auto Suggest System  

It is suitable for **Mini Project**, **Internal Assessment**, and **Lab Submission**.

---

## 👩‍💻 Developer
Soundarya U,sneha S S, Spoorthi K S
BE – CSE  E sec
Smart Library Project

