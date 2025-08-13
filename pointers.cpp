#include <iostream>
#include <string>
using namespace std;

class Student {
public:
    string name;
    int number;
    float marks;
    string specialization;

    void input() {
        cout << "Enter name: ";
        cin >> name;
        cout << "Enter number: ";
        cin >> number;
        cout << "Enter marks: ";
        cin >> marks;
        cout << "Enter specialization: ";
        cin >> specialization;
    }

    void display() {
        cout << "Name: " << name
             << ", Number: " << number
             << ", Marks: " << marks
             << ", Specialization: " << specialization << endl;
    }
};

int main() {
    int n;
    cout << "Enter number of students: ";
    cin >> n;

    Student** arr = new Student*[n];

    for (int i = 0; i < n; i++) {
        arr[i] = new Student;
        cout << "Student " << i + 1 << " details:" << endl;
        arr[i]->input();
    }

    cout << "\nStudent list:\n";
    for (int i = 0; i < n; i++) {
        arr[i]->display();
    }

    for (int i = 0; i < n; i++) {
        delete arr[i];
    }
    delete[] arr;

    return 0;
}
