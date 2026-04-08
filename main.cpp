#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

class Student {
public:
    int id;
    char name[50];
    float marks;

    void input() {
        cout << "Enter ID: ";
        cin >> id;
        cout << "Enter Name: ";
        cin.ignore();
        cin.getline(name, 50);
        cout << "Enter Marks: ";
        cin >> marks;
    }

    void display() const {
        cout << left << setw(10) << id
             << setw(20) << name
             << setw(10) << marks << endl;
    }
};

// Add Student
void addStudent() {
    Student s;
    ofstream file("students.dat", ios::binary | ios::app);

    s.input();
    file.write((char*)&s, sizeof(s));

    file.close();
    cout << "✅ Student added successfully!\n";
}

// Display All Students
void displayStudents() {
    Student s;
    ifstream file("students.dat", ios::binary);

    cout << "\n--- Student Records ---\n";
    cout << left << setw(10) << "ID"
         << setw(20) << "Name"
         << setw(10) << "Marks" << endl;

    while (file.read((char*)&s, sizeof(s))) {
        s.display();
    }

    file.close();
}

// Search Student
void searchStudent() {
    int id;
    Student s;
    bool found = false;

    cout << "Enter ID to search: ";
    cin >> id;

    ifstream file("students.dat", ios::binary);

    while (file.read((char*)&s, sizeof(s))) {
        if (s.id == id) {
            cout << "\nRecord Found:\n";
            s.display();
            found = true;
            break;
        }
    }

    if (!found)
        cout << "❌ Record not found.\n";

    file.close();
}

// Delete Student
void deleteStudent() {
    int id;
    Student s;
    bool found = false;

    cout << "Enter ID to delete: ";
    cin >> id;

    ifstream file("students.dat", ios::binary);
    ofstream temp("temp.dat", ios::binary);

    while (file.read((char*)&s, sizeof(s))) {
        if (s.id != id) {
            temp.write((char*)&s, sizeof(s));
        } else {
            found = true;
        }
    }

    file.close();
    temp.close();

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (found)
        cout << "✅ Record deleted.\n";
    else
        cout << "❌ Record not found.\n";
}

// Update Student
void updateStudent() {
    int id;
    Student s;
    bool found = false;

    cout << "Enter ID to update: ";
    cin >> id;

    fstream file("students.dat", ios::binary | ios::in | ios::out);

    while (file.read((char*)&s, sizeof(s))) {
        if (s.id == id) {
            cout << "Enter new details:\n";
            s.input();

            file.seekp(-sizeof(s), ios::cur);
            file.write((char*)&s, sizeof(s));

            found = true;
            break;
        }
    }

    file.close();

    if (found)
        cout << "✅ Record updated.\n";
    else
        cout << "❌ Record not found.\n";
}

// Main Menu
int main() {
    int choice;

    do {
        cout << "\n====== Student Management System ======\n";
        cout << "1. Add Student\n";
        cout << "2. Display Students\n";
        cout << "3. Search Student\n";
        cout << "4. Update Student\n";
        cout << "5. Delete Student\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }

    } while (choice != 6);

    return 0;
}