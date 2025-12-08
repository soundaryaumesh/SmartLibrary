/* Smart Library Management System (single file)
   - Uses linked lists for books and students
   - Uses a simple issues linked list (acts like records/queue)
   - Stores data in CSV-like text files under ./data/
   - Simple fine calculation and top-3 popular books feature
   - Compile: gcc main.c -o smartlib
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 256
#define DATA_DIR "data/"

// ---------- STRUCTS ----------
typedef struct Book {
    int id;
    char title[100];
    char author[100];
    int quantity;
    int issued_count; // innovation: how many times issued
    struct Book *next;
} Book;

typedef struct Student {
    int id;
    char name[80];
    char dept[50];
    struct Student *next;
} Student;

typedef struct Issue {
    int book_id;
    int student_id;
    int issued_on_day; // simplified: integer day
    int due_days;      // e.g., 14 days
    struct Issue *next;
} Issue;

// ---------- HEADS ----------
Book *books_head = NULL;
Student *students_head = NULL;
Issue *issues_head = NULL;

// ---------- UTIL ----------
void flush_stdin() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

char *trim_newline(char *s) {
    char *p = strchr(s, '\n');
    if (p) *p = '\0';
    return s;
}

// ---------- BOOKS ----------
Book* create_book_node(int id, const char *title, const char *author, int qty, int issued_count) {
    Book *b = (Book*)malloc(sizeof(Book));
    b->id = id;
    strncpy(b->title, title, sizeof(b->title)-1); b->title[sizeof(b->title)-1]=0;
    strncpy(b->author, author, sizeof(b->author)-1); b->author[sizeof(b->author)-1]=0;
    b->quantity = qty;
    b->issued_count = issued_count;
    b->next = NULL;
    return b;
}

void add_book_interactive() {
    int id, qty;
    char title[100], author[100];
    printf("Enter book id (numeric): "); scanf("%d", &id); flush_stdin();
    printf("Enter title: "); fgets(title, sizeof(title), stdin); trim_newline(title);
    printf("Enter author: "); fgets(author, sizeof(author), stdin); trim_newline(author);
    printf("Enter quantity: "); scanf("%d", &qty); flush_stdin();

    // check duplicate id
    Book *p = books_head;
    while (p) { if (p->id == id) { printf("Book with id %d already exists.\n", id); return; } p = p->next; }

    Book *newb = create_book_node(id, title, author, qty, 0);
    newb->next = books_head;
    books_head = newb;
    printf("Book added.\n");
}

void display_books() {
    printf("\n--- Books ---\n");
    Book *p = books_head;
    if (!p) { printf("No books.\n"); return; }
    printf("ID\tTitle\tAuthor\tQty\tIssuedCount\n");
    while (p) {
        printf("%d\t%s\t%s\t%d\t%d\n", p->id, p->title, p->author, p->quantity, p->issued_count);
        p = p->next;
    }
}

// find book by id
Book* find_book(int id) {
    Book *p = books_head;
    while (p) { if (p->id == id) return p; p = p->next; }
    return NULL;
}

// ---------- STUDENTS ----------
Student* create_student_node(int id, const char *name, const char *dept) {
    Student *s = (Student*)malloc(sizeof(Student));
    s->id = id;
    strncpy(s->name, name, sizeof(s->name)-1); s->name[sizeof(s->name)-1]=0;
    strncpy(s->dept, dept, sizeof(s->dept)-1); s->dept[sizeof(s->dept)-1]=0;
    s->next = NULL;
    return s;
}

void add_student_interactive() {
    int id;
    char name[80], dept[50];
    printf("Enter student id: "); scanf("%d", &id); flush_stdin();
    printf("Enter name: "); fgets(name, sizeof(name), stdin); trim_newline(name);
    printf("Enter dept: "); fgets(dept, sizeof(dept), stdin); trim_newline(dept);

    Student *p = students_head;
    while (p) { if (p->id == id) { printf("Student with id %d already exists.\n", id); return; } p = p->next; }

    Student *ns = create_student_node(id, name, dept);
    ns->next = students_head;
    students_head = ns;
    printf("Student added.\n");
}

void display_students() {
    printf("\n--- Students ---\n");
    Student *p = students_head;
    if (!p) { printf("No students.\n"); return; }
    printf("ID\tName\tDept\n");
    while (p) {
        printf("%d\t%s\t%s\n", p->id, p->name, p->dept);
        p = p->next;
    }
}

Student* find_student(int id) {
    Student *p = students_head;
    while (p) { if (p->id == id) return p; p = p->next; }
    return NULL;
}

// ---------- ISSUES ----------
Issue* create_issue_node(int book_id, int student_id, int issued_on_day, int due_days) {
    Issue *it = (Issue*)malloc(sizeof(Issue));
    it->book_id = book_id;
    it->student_id = student_id;
    it->issued_on_day = issued_on_day;
    it->due_days = due_days;
    it->next = NULL;
    return it;
}

// issue a book
void issue_book_interactive() {
    int bid, sid;
    printf("Enter book id to issue: "); scanf("%d", &bid); flush_stdin();
    Book *b = find_book(bid);
    if (!b) { printf("Book not found.\n"); return; }
    if (b->quantity <= 0) { printf("No copies available.\n"); return; }

    printf("Enter student id: "); scanf("%d", &sid); flush_stdin();
    Student *s = find_student(sid);
    if (!s) { printf("Student not found. Add student first.\n"); return; }

    int today;
    printf("Enter 'today' as day number (e.g., 100 for day count): "); scanf("%d", &today); flush_stdin();
    int due = 14; // fixed due days
    Issue *it = create_issue_node(bid, sid, today, due);
    it->next = issues_head;
    issues_head = it;

    b->quantity -= 1;
    b->issued_count += 1; // innovation

    printf("Book issued to %s. Due in %d days.\n", s->name, due);
}

void display_issues() {
    printf("\n--- Issued Books ---\n");
    Issue *p = issues_head;
    if (!p) { printf("No issued records.\n"); return; }
    printf("BookID\tStudentID\tIssuedOn\tDueDays\n");
    while (p) {
        printf("%d\t%d\t\t%d\t\t%d\n", p->book_id, p->student_id, p->issued_on_day, p->due_days);
        p = p->next;
    }
}

// return a book
void return_book_interactive() {
    int bid, sid;
    printf("Enter returning book id: "); scanf("%d", &bid); flush_stdin();
    printf("Enter student id: "); scanf("%d", &sid); flush_stdin();
    Issue *p = issues_head, *prev = NULL;
    while (p) {
        if (p->book_id == bid && p->student_id == sid) break;
        prev = p; p = p->next;
    }
    if (!p) { printf("No matching issue record found.\n"); return; }

    int return_day;
    printf("Enter return day number: "); scanf("%d", &return_day); flush_stdin();
    int due_day = p->issued_on_day + p->due_days;
    int fine = 0;
    if (return_day > due_day) {
        fine = (return_day - due_day) * 2; // Rs2 per late day
    }

    // remove issue record from list
    if (prev == NULL) issues_head = p->next;
    else prev->next = p->next;

    // update book quantity
    Book *b = find_book(bid);
    if (b) b->quantity += 1;

    free(p);
    printf("Book returned. Fine = Rs %d\n", fine);
}

// ---------- FILE I/O ----------
void loadBooksFromFile() {
    char path[MAXLINE];
    snprintf(path, sizeof(path), DATA_DIR "books.txt");
    FILE *f = fopen(path, "r");
    if (!f) return;
    char line[MAXLINE];
    while (fgets(line, sizeof(line), f)) {
        trim_newline(line);
        if (strlen(line) == 0) continue;
        // format: id,title,author,quantity,issued_count
        int id, qty, issued_count;
        char title[100], author[100];
        char *tok = strtok(line, ",");
        if (!tok) continue;
        id = atoi(tok);
        tok = strtok(NULL, ","); if (!tok) continue; strncpy(title, tok, sizeof(title));
        tok = strtok(NULL, ","); if (!tok) continue; strncpy(author, tok, sizeof(author));
        tok = strtok(NULL, ","); if (!tok) continue; qty = atoi(tok);
        tok = strtok(NULL, ",");
        issued_count = tok ? atoi(tok) : 0;
        Book *b = create_book_node(id, title, author, qty, issued_count);
        b->next = books_head;
        books_head = b;
    }
    fclose(f);
}

void saveBooksToFile() {
    char path[MAXLINE];
    snprintf(path, sizeof(path), DATA_DIR "books.txt");
    FILE *f = fopen(path, "w");
    if (!f) { printf("Failed to open books file for writing. Create data/ directory.\n"); return; }
    Book *p = books_head;
    while (p) {
        // id,title,author,quantity,issued_count
        fprintf(f, "%d,%s,%s,%d,%d\n", p->id, p->title, p->author, p->quantity, p->issued_count);
        p = p->next;
    }
    fclose(f);
}

void loadStudentsFromFile() {
    char path[MAXLINE];
    snprintf(path, sizeof(path), DATA_DIR "students.txt");
    FILE *f = fopen(path, "r");
    if (!f) return;
    char line[MAXLINE];
    while (fgets(line, sizeof(line), f)) {
        trim_newline(line);
        if (strlen(line) == 0) continue;
        // format: id,name,dept
        int id;
        char name[80], dept[50];
        char *tok = strtok(line, ",");
        if (!tok) continue;
        id = atoi(tok);
        tok = strtok(NULL, ","); if (!tok) continue; strncpy(name, tok, sizeof(name));
        tok = strtok(NULL, ","); if (!tok) continue; strncpy(dept, tok, sizeof(dept));
        Student *s = create_student_node(id, name, dept);
        s->next = students_head;
        students_head = s;
    }
    fclose(f);
}

void saveStudentsToFile() {
    char path[MAXLINE];
    snprintf(path, sizeof(path), DATA_DIR "students.txt");
    FILE *f = fopen(path, "w");
    if (!f) { printf("Failed to open students file for writing.\n"); return; }
    Student *p = students_head;
    while (p) {
        fprintf(f, "%d,%s,%s\n", p->id, p->name, p->dept);
        p = p->next;
    }
    fclose(f);
}

void loadIssuesFromFile() {
    char path[MAXLINE];
    snprintf(path, sizeof(path), DATA_DIR "issues.txt");
    FILE *f = fopen(path, "r");
    if (!f) return;
    char line[MAXLINE];
    while (fgets(line, sizeof(line), f)) {
        trim_newline(line);
        if (strlen(line) == 0) continue;
        // format: book_id,student_id,issued_on_day,due_days
        int bid, sid, isd, due;
        char *tok = strtok(line, ",");
        if (!tok) continue; bid = atoi(tok);
        tok = strtok(NULL, ","); if (!tok) continue; sid = atoi(tok);
        tok = strtok(NULL, ","); if (!tok) continue; isd = atoi(tok);
        tok = strtok(NULL, ","); if (!tok) continue; due = atoi(tok);
        Issue *it = create_issue_node(bid, sid, isd, due);
        it->next = issues_head;
        issues_head = it;
    }
    fclose(f);
}

void saveIssuesToFile() {
    char path[MAXLINE];
    snprintf(path, sizeof(path), DATA_DIR "issues.txt");
    FILE *f = fopen(path, "w");
    if (!f) { printf("Failed to open issues file for writing.\n"); return; }
    Issue *p = issues_head;
    while (p) {
        fprintf(f, "%d,%d,%d,%d\n", p->book_id, p->student_id, p->issued_on_day, p->due_days);
        p = p->next;
    }
    fclose(f);
}

// ---------- REPORTS / INNOVATION ----------
void show_top3_popular_books() {
    // collect into array (simple approach)
    int n = 0;
    Book *p = books_head;
    while (p) { n++; p = p->next; }
    if (n == 0) { printf("No books.\n"); return; }
    Book **arr = (Book**)malloc(n * sizeof(Book*));
    int i = 0;
    p = books_head;
    while (p) { arr[i++] = p; p = p->next; }
    // sort by issued_count desc (simple bubble for small n)
    for (int a=0; a<n-1; a++) {
        for (int b=0; b<n-1-a; b++) {
            if (arr[b]->issued_count < arr[b+1]->issued_count) {
                Book *tmp = arr[b]; arr[b] = arr[b+1]; arr[b+1] = tmp;
            }
        }
    }
    printf("\nTop Popular Books:\n");
    int upto = n < 3 ? n : 3;
    for (int k=0; k<upto; k++) {
        printf("%d. %s (Issued %d times)\n", k+1, arr[k]->title, arr[k]->issued_count);
    }
    free(arr);
}

// ---------- MENU ----------
void show_menu() {
    printf("\n===== SMART LIBRARY =====\n");
    printf("1. Add Book\n");
    printf("2. Display Books\n");
    printf("3. Add Student\n");
    printf("4. Display Students\n");
    printf("5. Issue Book\n");
    printf("6. Return Book\n");
    printf("7. Display Issued Records\n");
    printf("8. Popular Books (Top 3)\n");
    printf("9. Save & Exit\n");
    printf("Enter choice: ");
}

// ---------- MAIN ----------
int main() {
    // Ensure data dir exists message (user must create data/)
    printf("Smart Library starting. Ensure folder '%s' exists and files (books.txt, students.txt, issues.txt) are placed or will be created.\n", DATA_DIR);

    // load data from files if present
    loadBooksFromFile();
    loadStudentsFromFile();
    loadIssuesFromFile();

    int choice;
    do {
        show_menu();
        if (scanf("%d", &choice) != 1) { flush_stdin(); choice = 0; }
        flush_stdin();
        switch (choice) {
            case 1: add_book_interactive(); break;
            case 2: display_books(); break;
            case 3: add_student_interactive(); break;
            case 4: display_students(); break;
            case 5: issue_book_interactive(); break;
            case 6: return_book_interactive(); break;
            case 7: display_issues(); break;
            case 8: show_top3_popular_books(); break;
            case 9:
                saveBooksToFile();
                saveStudentsToFile();
                saveIssuesToFile();
                printf("Saved. Exiting.\n");
                break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 9);

    // free memory (not strictly necessary for small program)
    // skipped for brevity

    return 0;
}
