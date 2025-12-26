#include <stdio.h>
#include "book.h"
#include "student.h"
#include "issue.h"

int main(){
    load_books();
    load_students();
    load_issues();

    int ch;
    do{
        printf("\n===== SMART LIBRARY =====\n");
        printf("1. Add Book\n2. Display Books\n");
        printf("3. Add Student\n4. Display Students\n");
        printf("5. Issue Book\n6. Return Book\n");
        printf("7. Display Issued Queue\n8. Exit\n");
        printf("Enter Choice: ");
        scanf("%d",&ch);

        switch(ch){
            case 1: add_book(); break;
            case 2: display_books(); break;
            case 3: add_student(); break;
            case 4: display_students(); break;
            case 5: issue_book(); break;
            case 6: return_book(); break;
            case 7: display_issues(); break;
            case 8: printf("Exiting...\n"); break;
            default: printf("Invalid Choice\n");
        }
    }while(ch!=8);

    return 0;
}
