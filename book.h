#ifndef BOOK_H
#define BOOK_H

typedef struct Book {
    int id;
    char title[100];
    char author[100];
    char category[50];
    int quantity;
    struct Book *next;
} Book;

extern Book *book_head;

void load_books();
void save_books();
void add_book();
void display_books();
Book* find_book(int id);
void suggest_books(char category[]);

#endif
