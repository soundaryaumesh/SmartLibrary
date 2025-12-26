#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "book.h"

Book *book_head = NULL;

Book* create_book(int id, char *title, char *author, char *cat, int qty) {
    Book *b = (Book*)malloc(sizeof(Book));
    b->id=id;
    strcpy(b->title,title);
    strcpy(b->author,author);
    strcpy(b->category,cat);
    b->quantity=qty;
    b->next=NULL;
    return b;
}

void load_books() {
    FILE *fp=fopen("books.txt","r");
    if(!fp) return;

    int id,qty;
    char title[100], author[100], cat[50];

    while(fscanf(fp,"%d|%[^|]|%[^|]|%[^|]|%d\n",
           &id,title,author,cat,&qty)==5)
    {
        Book *b=create_book(id,title,author,cat,qty);
        b->next=book_head;
        book_head=b;
    }
    fclose(fp);
}

void save_books() {
    FILE *fp=fopen("books.txt","w");
    Book *p=book_head;
    while(p){
        fprintf(fp,"%d|%s|%s|%s|%d\n",
                p->id,p->title,p->author,p->category,p->quantity);
        p=p->next;
    }
    fclose(fp);
}

Book* find_book(int id){
    Book *p=book_head;
    while(p){
        if(p->id==id) return p;
        p=p->next;
    }
    return NULL;
}

void add_book(){
    int id,qty;
    char title[100],author[100],cat[50];

    printf("Enter Book ID: ");
    scanf("%d",&id);
    getchar();

    printf("Enter Title: ");
    scanf("%[^\n]",title);
    getchar();

    printf("Enter Author: ");
    scanf("%[^\n]",author);
    getchar();

    printf("Enter Category (Science/Novel/Tech/etc): ");
    scanf("%[^\n]",cat);
    getchar();

    printf("Enter Quantity: ");
    scanf("%d",&qty);

    Book *b=create_book(id,title,author,cat,qty);
    b->next=book_head;
    book_head=b;

    save_books();
    printf("Book Added Successfully!\n");
}

void display_books(){
    if(!book_head){
        printf("No Books Available\n");
        return;
    }
    Book *p=book_head;
    printf("\n--- BOOK LIST ---\n");
    while(p){
        printf("ID:%d  %s  by %s  [%s] Qty:%d\n",
               p->id,p->title,p->author,p->category,p->quantity);
        p=p->next;
    }
}

void suggest_books(char category[]){
    printf("\n📚 Suggested Books in Category: %s\n",category);
    Book *p=book_head;
    int found=0;
    while(p){
        if(strcmp(p->category,category)==0){
            printf("-> %s by %s (ID:%d)\n",p->title,p->author,p->id);
            found=1;
        }
        p=p->next;
    }
    if(!found) printf("No suggestions available.\n");
}
