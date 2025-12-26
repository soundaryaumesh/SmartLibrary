#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"

Student *student_head=NULL;

Student* create_student(int id,char *name){
    Student *s=(Student*)malloc(sizeof(Student));
    s->id=id;
    strcpy(s->name,name);
    s->next=NULL;
    return s;
}

void load_students(){
    FILE *fp=fopen("students.txt","r");
    if(!fp) return;

    int id;
    char name[100];

    while(fscanf(fp,"%d|%[^\n]\n",&id,name)==2){
        Student *s=create_student(id,name);
        s->next=student_head;
        student_head=s;
    }
    fclose(fp);
}

void save_students(){
    FILE *fp=fopen("students.txt","w");
    Student *p=student_head;
    while(p){
        fprintf(fp,"%d|%s\n",p->id,p->name);
        p=p->next;
    }
    fclose(fp);
}

Student* find_student(int id){
    Student *p=student_head;
    while(p){
        if(p->id==id) return p;
        p=p->next;
    }
    return NULL;
}

void add_student(){
    int id;
    char name[100];

    printf("Enter Student ID: ");
    scanf("%d",&id);
    getchar();

    printf("Enter Name: ");
    scanf("%[^\n]",name);

    Student *s=create_student(id,name);
    s->next=student_head;
    student_head=s;

    save_students();
    printf("Student Added Successfully!\n");
}

void display_students(){
    Student *p=student_head;
    if(!p){
        printf("No Students\n");
        return;
    }

    printf("\n--- STUDENT LIST ---\n");
    while(p){
        printf("ID:%d  Name:%s\n",p->id,p->name);
        p=p->next;
    }
}
