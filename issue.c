#include <stdio.h>
#include <stdlib.h>
#include "book.h"
#include "student.h"
#include "issue.h"

typedef struct Issue {
    int book_id;
    int student_id;
    struct Issue *next;
} Issue;

Issue *front=NULL,*rear=NULL;

void load_issues(){
    FILE *fp=fopen("issues.txt","r");
    if(!fp) return;

    int bid,sid;
    while(fscanf(fp,"%d|%d\n",&bid,&sid)==2){
        Issue *n=(Issue*)malloc(sizeof(Issue));
        n->book_id=bid;
        n->student_id=sid;
        n->next=NULL;

        if(!front) front=rear=n;
        else { rear->next=n; rear=n; }
    }
    fclose(fp);
}

void save_issues(){
    FILE *fp=fopen("issues.txt","w");
    Issue *p=front;
    while(p){
        fprintf(fp,"%d|%d\n",p->book_id,p->student_id);
        p=p->next;
    }
    fclose(fp);
}

void issue_book(){
    int bid,sid;
    printf("Enter Book ID: ");
    scanf("%d",&bid);
    printf("Enter Student ID: ");
    scanf("%d",&sid);

    Book *b=find_book(bid);
    if(!b || b->quantity<=0){
        printf("Book Not Available!\n");
        return;
    }

    if(!find_student(sid)){
        printf("Student Not Found!\n");
        return;
    }

    Issue *n=(Issue*)malloc(sizeof(Issue));
    n->book_id=bid;
    n->student_id=sid;
    n->next=NULL;

    if(!front) front=rear=n;
    else rear->next=n,rear=n;

    b->quantity--;
    save_books();
    save_issues();

    printf("Book Issued Successfully!\n");

    // AUTO SUGGEST FEATURE
    suggest_books(b->category);
}

void return_book(){
    if(!front){
        printf("No Issued Books!\n");
        return;
    }

    Issue *t=front;
    front=front->next;

    Book *b=find_book(t->book_id);
    if(b) b->quantity++;

    free(t);
    save_books();
    save_issues();

    printf("Book Returned Successfully!\n");
}

void display_issues(){
    if(!front){
        printf("No Issued Books\n");
        return;
    }

    Issue *p=front;
    printf("\n--- ISSUE QUEUE ---\n");
    while(p){
        printf("Book %d -> Student %d\n",p->book_id,p->student_id);
        p=p->next;
    }
}
