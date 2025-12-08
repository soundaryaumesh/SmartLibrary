import os

DATA_DIR = "data/"

books = []
students = []
issues = []

def load_books():
    path = DATA_DIR + "books.txt"
    if not os.path.exists(path): return
    with open(path, 'r') as f:
        for line in f:
            line = line.strip()
            if not line: continue
            parts = line.split(',')
            if len(parts) >= 4:
                books.append({
                    'id': int(parts[0]),
                    'title': parts[1],
                    'author': parts[2],
                    'quantity': int(parts[3]),
                    'issued_count': int(parts[4]) if len(parts) > 4 else 0
                })

def save_books():
    with open(DATA_DIR + "books.txt", 'w') as f:
        for b in books:
            f.write(f"{b['id']},{b['title']},{b['author']},{b['quantity']},{b['issued_count']}\n")

def load_students():
    path = DATA_DIR + "students.txt"
    if not os.path.exists(path): return
    with open(path, 'r') as f:
        for line in f:
            line = line.strip()
            if not line: continue
            parts = line.split(',')
            if len(parts) >= 3:
                students.append({'id': int(parts[0]), 'name': parts[1], 'dept': parts[2]})

def save_students():
    with open(DATA_DIR + "students.txt", 'w') as f:
        for s in students:
            f.write(f"{s['id']},{s['name']},{s['dept']}\n")

def load_issues():
    path = DATA_DIR + "issues.txt"
    if not os.path.exists(path): return
    with open(path, 'r') as f:
        for line in f:
            line = line.strip()
            if not line: continue
            parts = line.split(',')
            if len(parts) >= 4:
                issues.append({
                    'book_id': int(parts[0]),
                    'student_id': int(parts[1]),
                    'issued_on_day': int(parts[2]),
                    'due_days': int(parts[3])
                })

def save_issues():
    with open(DATA_DIR + "issues.txt", 'w') as f:
        for i in issues:
            f.write(f"{i['book_id']},{i['student_id']},{i['issued_on_day']},{i['due_days']}\n")

def add_book():
    id = int(input("Enter book id: "))
    if any(b['id'] == id for b in books):
        print(f"Book with id {id} already exists.")
        return
    title = input("Enter title: ")
    author = input("Enter author: ")
    qty = int(input("Enter quantity: "))
    books.append({'id': id, 'title': title, 'author': author, 'quantity': qty, 'issued_count': 0})
    print("Book added.")

def display_books():
    print("\n--- Books ---")
    if not books:
        print("No books.")
        return
    print("ID\tTitle\tAuthor\tQty\tIssuedCount")
    for b in books:
        print(f"{b['id']}\t{b['title']}\t{b['author']}\t{b['quantity']}\t{b['issued_count']}")

def add_student():
    id = int(input("Enter student id: "))
    if any(s['id'] == id for s in students):
        print(f"Student with id {id} already exists.")
        return
    name = input("Enter name: ")
    dept = input("Enter dept: ")
    students.append({'id': id, 'name': name, 'dept': dept})
    print("Student added.")

def display_students():
    print("\n--- Students ---")
    if not students:
        print("No students.")
        return
    print("ID\tName\tDept")
    for s in students:
        print(f"{s['id']}\t{s['name']}\t{s['dept']}")

def issue_book():
    bid = int(input("Enter book id to issue: "))
    book = next((b for b in books if b['id'] == bid), None)
    if not book:
        print("Book not found.")
        return
    if book['quantity'] <= 0:
        print("No copies available.")
        return
    
    sid = int(input("Enter student id: "))
    student = next((s for s in students if s['id'] == sid), None)
    if not student:
        print("Student not found. Add student first.")
        return
    
    today = int(input("Enter 'today' as day number (e.g., 100): "))
    due = 14
    issues.append({'book_id': bid, 'student_id': sid, 'issued_on_day': today, 'due_days': due})
    book['quantity'] -= 1
    book['issued_count'] += 1
    print(f"Book issued to {student['name']}. Due in {due} days.")

def display_issues():
    print("\n--- Issued Books ---")
    if not issues:
        print("No issued records.")
        return
    print("BookID\tStudentID\tIssuedOn\tDueDays")
    for i in issues:
        print(f"{i['book_id']}\t{i['student_id']}\t\t{i['issued_on_day']}\t\t{i['due_days']}")

def return_book():
    bid = int(input("Enter returning book id: "))
    sid = int(input("Enter student id: "))
    issue = next((i for i in issues if i['book_id'] == bid and i['student_id'] == sid), None)
    if not issue:
        print("No matching issue record found.")
        return
    
    return_day = int(input("Enter return day number: "))
    due_day = issue['issued_on_day'] + issue['due_days']
    fine = max(0, (return_day - due_day) * 2)
    
    issues.remove(issue)
    book = next((b for b in books if b['id'] == bid), None)
    if book:
        book['quantity'] += 1
    
    print(f"Book returned. Fine = Rs {fine}")

def show_top3():
    if not books:
        print("No books.")
        return
    sorted_books = sorted(books, key=lambda b: b['issued_count'], reverse=True)
    print("\nTop Popular Books:")
    for i, b in enumerate(sorted_books[:3], 1):
        print(f"{i}. {b['title']} (Issued {b['issued_count']} times)")

def main():
    print(f"Smart Library starting. Ensure folder '{DATA_DIR}' exists.")
    load_books()
    load_students()
    load_issues()
    
    while True:
        print("\n===== SMART LIBRARY =====")
        print("1. Add Book")
        print("2. Display Books")
        print("3. Add Student")
        print("4. Display Students")
        print("5. Issue Book")
        print("6. Return Book")
        print("7. Display Issued Records")
        print("8. Popular Books (Top 3)")
        print("9. Save & Exit")
        
        try:
            choice = int(input("Enter choice: "))
            if choice == 1: add_book()
            elif choice == 2: display_books()
            elif choice == 3: add_student()
            elif choice == 4: display_students()
            elif choice == 5: issue_book()
            elif choice == 6: return_book()
            elif choice == 7: display_issues()
            elif choice == 8: show_top3()
            elif choice == 9:
                save_books()
                save_students()
                save_issues()
                print("Saved. Exiting.")
                break
            else: print("Invalid choice.")
        except:
            print("Invalid input.")

if __name__ == "__main__":
    main()
