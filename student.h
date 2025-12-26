#ifndef STUDENT_H
#define STUDENT_H

typedef struct Student {
    int id;
    char name[100];
    struct Student *next;
} Student;

extern Student *student_head;

void load_students();
void save_students();
void add_student();
void display_students();
Student* find_student(int id);

#endif
