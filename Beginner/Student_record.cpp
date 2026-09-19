#include <iostream>
#include <string>
using namespace std;

const int MAX = 100;

// Student Class
class Student {
public:
    int roll;
    string Name;
    string Course;
    int Marks;
};

// Array to store student records
Student students[MAX];

// Number of students
int total = 0;


// Check if the Roll Number already exists
bool check(int roll)
{
    for (int i = 0; i < total; i++) {
        if (students[i].roll == roll)
            return true;
    }

    return false;
}


// Function to insert a student record
void Insert_Record(int roll, string Name,
                   string Course, int Marks)
{
    // Check if record already exists
    if (check(roll)) {
        cout << "Student with this record already exists\n";
        return;
    }

    // Check if array is full
    if (total >= MAX) {
        cout << "Student record is full\n";
        return;
    }

    // Add student to the array
    students[total].roll = roll;
    students[total].Name = Name;
    students[total].Course = Course;
    students[total].Marks = Marks;

    total++;

    cout << "Record Inserted Successfully\n";
}


// Function to search a student record
void Search_Record(int roll)
{
    for (int i = 0; i < total; i++) {

        if (students[i].roll == roll) {

            cout << "\nRoll Number\t"
                 << students[i].roll << endl;

            cout << "Name\t\t"
                 << students[i].Name << endl;

            cout << "Course\t\t"
                 << students[i].Course << endl;

            cout << "Marks\t\t"
                 << students[i].Marks << endl;

            return;
        }
    }

    cout << "No such Record Available\n";
}


// Function to delete a student record
void Delete_Record(int roll)
{
    int position = -1;

    // Find the student
    for (int i = 0; i < total; i++) {

        if (students[i].roll == roll) {
            position = i;
            break;
        }
    }

    // Student not found
    if (position == -1) {
        cout << "Record does not Exist\n";
        return;
    }

    // Shift all records after the deleted student
    for (int i = position; i < total - 1; i++) {
        students[i] = students[i + 1];
    }

    total--;

    cout << "Record Deleted Successfully\n";
}


// Function to display all student records
void Show_Record()
{
    if (total == 0) {
        cout << "No Record Available\n";
        return;
    }

    cout << "\nRoll\tName\tCourse\tMarks\n";
    cout << "-----------------------------------\n";

    for (int i = 0; i < total; i++) {

        cout << students[i].roll << "\t"
             << students[i].Name << "\t"
             << students[i].Course << "\t"
             << students[i].Marks << endl;
    }
}


// Driver code
int main()
{
    string Name, Course;
    int Roll, Marks;

    // Menu-driven program
    while (true) {

        cout << "\n\t\tWelcome to Student Record "
                "Management System\n\n";

        cout << "\tPress\n";
        cout << "\t1 to create a new Record\n";
        cout << "\t2 to delete a student record\n";
        cout << "\t3 to Search a Student Record\n";
        cout << "\t4 to view all students record\n";
        cout << "\t5 to Exit\n";

        cout << "\nEnter your Choice: ";

        int Choice;
        cin >> Choice;

        if (Choice == 1) {

            cout << "Enter Name of Student: ";
            cin >> Name;

            cout << "Enter Roll Number of Student: ";
            cin >> Roll;

            cout << "Enter Course of Student: ";
            cin >> Course;

            cout << "Enter Total Marks of Student: ";
            cin >> Marks;

            Insert_Record(Roll, Name, Course, Marks);
        }

        else if (Choice == 2) {

            cout << "Enter Roll Number of Student "
                    "whose record is to be deleted: ";

            cin >> Roll;

            Delete_Record(Roll);
        }

        else if (Choice == 3) {

            cout << "Enter Roll Number of Student "
                    "whose record you want to Search: ";

            cin >> Roll;

            Search_Record(Roll);
        }

        else if (Choice == 4) {

            Show_Record();
        }

        else if (Choice == 5) {

            cout << "Program Exited\n";
            break;
        }

        else {

            cout << "Invalid Choice. Try Again\n";
        }
    }

    return 0;
}
