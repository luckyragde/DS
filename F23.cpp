#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Student {
private:
    int rollNumber;
    string name;
    string division;
    string address;

public:
    // Constructor
    Student() : rollNumber(0), name(""), division(""), address("") {}

    // Method to set student details
    void setDetails(int r, const string& n, const string& d, const string& a) {
        rollNumber = r;
        name = n;
        division = d;
        address = a;
    }

    // Method to display student details
    void display() const {
        cout << "Roll Number: " << rollNumber << endl;
        cout << "Name: " << name << endl;
        cout << "Division: " << division << endl;
        cout << "Address: " << address << endl;
    }

    // Method to get roll number
    int getRollNumber() const {
        return rollNumber;
    }

    // Method to save student details to a file
    void saveToFile(ofstream& outFile) const {
        outFile << rollNumber << endl;
        outFile << name << endl;
        outFile << division << endl;
        outFile << address << endl;
    }

    // Method to read student details from a file
    void readFromFile(ifstream& inFile) {
        inFile >> rollNumber;
        inFile.ignore(); // Ignore the newline character
        getline(inFile, name);
        getline(inFile, division);
        getline(inFile, address);
    }
};

void addStudent() {
    Student student;
    int rollNumber;
    string name, division, address;

    cout << "Enter Roll Number: ";
    cin >> rollNumber;
    cin.ignore(); // To ignore the newline character after the integer input
    cout << "Enter Name: ";
    getline(cin, name);
    cout << "Enter Division: ";
    getline(cin, division);
    cout << "Enter Address: ";
    getline(cin, address);

    student.setDetails(rollNumber, name, division, address);

    ofstream outFile("students.txt", ios::app);
    if (outFile.is_open()) {
        student.saveToFile(outFile);
        outFile.close();
        cout << "Student added successfully!" << endl;
    } else {
        cout << "Unable to open file." << endl;
    }
}

void deleteStudent() {
    int rollNumber;
    cout << "Enter Roll Number to delete: ";
    cin >> rollNumber;

    ifstream inFile("students.txt");
    ofstream outFile("temp.txt");
    bool found = false;
    Student student;

    if (inFile.is_open() && outFile.is_open()) {
        while (true) {
            student.readFromFile(inFile);
            if (inFile.eof()) break; // Break if end of file is reached

            if (student.getRollNumber() == rollNumber) {
                found = true;
                cout << "Deleting student: " << student.getRollNumber() << endl;
                continue; // Skip writing this student to the temp file
            }
            student.saveToFile(outFile);
        }
        inFile.close();
        outFile.close();

        remove("students.txt");
        rename("temp.txt", "students.txt");

        if (found) {
            cout << "Student deleted successfully!" << endl;
        } else {
            cout << "Student with Roll Number " << rollNumber << " not found." << endl;
        }
    } else {
        cout << "Unable to open file." << endl;
    }
}

void displayStudent() {
    int rollNumber;
    cout << "Enter Roll Number to display: ";
    cin >> rollNumber;

    ifstream inFile("students.txt");
    bool found = false;
    Student student;

    if (inFile.is_open()) {
        while (true) {
            student.readFromFile(inFile);
            if (inFile.eof()) break; // Break if end of file is reached

            if (student.getRollNumber() == rollNumber) {
                found = true;
                student.display();
                break;
            }
        }
        inFile.close();

        if (!found) {
            cout << "Student with Roll Number " << rollNumber << " not found." << endl;
        }
    } else {
        cout << "Unable to open file." << endl;
    }
}

int main() {
    int choice;
    do {
        cout << "\nStudent Information System" << endl;
        cout << "1. Add Student" << endl;
        cout << "2. Delete Student" << endl;
        cout << "3. Display Student" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                deleteStudent();
                break;
            case 3:
                displayStudent();
                break;
            case 4:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 4);

    return 0;
}