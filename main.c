/* BASIC SMART LIBRARY MANAGEMENT SYSTEM
   - Uses Linked List for Books and Students
   - Uses Queue for Issued Books
   - Input and menu choice validation fixed
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ---------------------- STRUCTS ------------------------
typedef struct Book {
    int id;
    char title[100];
    char author[100];
    int quantity;
    struct Book *next;
} Book;

typedef struct Student {
    int id;
    char name[100];
    struct Student *next;
} Student;

typedef struct Issue {
    int book_id;
    int student_id;
    struct Issue *next;
} Issue;

// ---------------------- HEADS --------------------------
Book *book_head = NULL;
Student *student_head = NULL;
Issue *issue_front = NULL;
Issue *issue_rear = NULL;

// ---------------------- BOOK OPERATIONS ----------------
Book* create_book(int id, char *title, char *author, int qty) {
    Book *b = (Book*)malloc(sizeof(Book));
    if (!b) return NULL;
    b->id = id;
    strncpy(b->title, title, sizeof(b->title)-1);
    b->title[sizeof(b->title)-1] = '\0';
    strncpy(b->author, author, sizeof(b->author)-1);
    b->author[sizeof(b->author)-1] = '\0';
    b->quantity = qty;
    b->next = NULL;
    return b;
}

void add_book() {
    int id, qty;
    char title[100], author[100];

    printf("Enter Book ID: ");
    if (scanf("%d", &id) != 1) { 
        printf("Invalid input! Book ID must be a number.\n");
        while(getchar() != '\n');
        return;
    }
    while(getchar() != '\n');

    printf("Enter Title: ");
    scanf(" %[^\n]", title);

    printf("Enter Author: ");
    scanf(" %[^\n]", author);

    printf("Enter Quantity: ");
    if (scanf("%d", &qty) != 1 || qty < 0) {
        printf("Invalid quantity!\n");
        while(getchar() != '\n');
        return;
    }
    while(getchar() != '\n');

    // Check duplicate ID
    Book *temp = book_head;
    while (temp) {
        if (temp->id == id) {
            printf("Book ID already exists!\n");
            return;
        }
        temp = temp->next;
    }

    Book *b = create_book(id, title, author, qty);
    if (!b) {
        printf("Memory allocation failed!\n");
        return;
    }

    b->next = book_head;
    book_head = b;

    printf("Book added successfully!\n");
}

void display_books() {
    if (!book_head) {
        printf("No books available.\n");
        return;
    }

    Book *p = book_head;
    printf("\n--- BOOK LIST ---\n");
    while (p) {
        printf("ID: %d | Title: %s | Author: %s | Qty: %d\n",
               p->id, p->title, p->author, p->quantity);
        p = p->next;
    }
}

// ---------------------- STUDENT OPERATIONS -------------
Student* create_student(int id, char *name) {
    Student *s = (Student*)malloc(sizeof(Student));
    if (!s) return NULL;
    s->id = id;
    strncpy(s->name, name, sizeof(s->name)-1);
    s->name[sizeof(s->name)-1] = '\0';
    s->next = NULL;
    return s;
}

void add_student() {
    int id;
    char name[100];

    printf("Enter Student ID: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid input! Student ID must be a number.\n");
        while(getchar() != '\n');
        return;
    }
    while(getchar() != '\n');

    printf("Enter Name: ");
    scanf(" %[^\n]", name);

    // Check duplicate ID
    Student *temp = student_head;
    while (temp) {
        if (temp->id == id) {
            printf("Student ID already exists!\n");
            return;
        }
        temp = temp->next;
    }

    Student *s = create_student(id, name);
    if (!s) {
        printf("Memory allocation failed!\n");
        return;
    }

    s->next = student_head;
    student_head = s;

    printf("Student added successfully!\n");
}

void display_students() {
    if (!student_head) {
        printf("No students.\n");
        return;
    }

    Student *p = student_head;
    printf("\n--- STUDENT LIST ---\n");
    while (p) {
        printf("ID: %d | Name: %s\n", p->id, p->name);
        p = p->next;
    }
}

// ---------------------- ISSUE QUEUE --------------------
void enqueue_issue(int book_id, int student_id) {
    Issue *node = (Issue*)malloc(sizeof(Issue));
    if (!node) return;
    node->book_id = book_id;
    node->student_id = student_id;
    node->next = NULL;

    if (!issue_front) {
        issue_front = issue_rear = node;
    } else {
        issue_rear->next = node;
        issue_rear = node;
    }
}

void issue_book() {
    int bid, sid;

    printf("Enter Book ID to issue: ");
    if (scanf("%d", &bid) != 1) {
        printf("Invalid input!\n");
        while(getchar() != '\n');
        return;
    }
    while(getchar() != '\n');

    printf("Enter Student ID: ");
    if (scanf("%d", &sid) != 1) {
        printf("Invalid input!\n");
        while(getchar() != '\n');
        return;
    }
    while(getchar() != '\n');

    // check book exists
    Book *b = book_head;
    while (b && b->id != bid) b = b->next;
    if (!b) {
        printf("Book not found.\n");
        return;
    }
    if (b->quantity <= 0) {
        printf("Book not available.\n");
        return;
    }

    // check student exists
    Student *s = student_head;
    while (s && s->id != sid) s = s->next;
    if (!s) {
        printf("Student not found.\n");
        return;
    }

    enqueue_issue(bid, sid);
    b->quantity--;

    printf("Book issued successfully!\n");
}

void return_book() {
    if (!issue_front) {
        printf("No issued books to return.\n");
        return;
    }

    Issue *temp = issue_front;
    issue_front = issue_front->next;

    // update book qty
    Book *b = book_head;
    while (b && b->id != temp->book_id) b = b->next;
    if (b) b->quantity++;

    printf("Book returned successfully!\n");
    free(temp);

    if (!issue_front) issue_rear = NULL;
}

void display_issues() {
    if (!issue_front) {
        printf("No issued books.\n");
        return;
    }

    printf("\n--- ISSUE QUEUE ---\n");
    Issue *p = issue_front;
    while (p) {
        printf("BookID: %d -> StudentID: %d\n", p->book_id, p->student_id);
        p = p->next;
    }
}

// ---------------------- MENU ---------------------------
int main() {
    char input[10];
    int ch;

    do {
        printf("\n===== BASIC SMART LIBRARY =====\n");
        printf("1. Add Book\n");
        printf("2. Display Books\n");
        printf("3. Add Student\n");
        printf("4. Display Students\n");
        printf("5. Issue Book\n");
        printf("6. Return Book\n");
        printf("7. Display Issued Queue\n");
        printf("8. Exit\n");
        printf("Enter choice: ");

        scanf("%9s", input);          // read as string
        while(getchar() != '\n');     // clear buffer
        ch = atoi(input);              // convert to int

        switch (ch) {
            case 1: add_book(); break;
            case 2: display_books(); break;
            case 3: add_student(); break;
            case 4: display_students(); break;
            case 5: issue_book(); break;
            case 6: return_book(); break;
            case 7: display_issues(); break;
            case 8: printf("Exiting...\n"); break;
            default: printf("Invalid choice! Please enter 1-8.\n");
        }
    } while (ch != 8);

    return 0;
}


