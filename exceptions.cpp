#include <iostream>
#include <string>
using namespace std;

class LowerLengthOfChars : public exception {
public:
    const char* what() const noexcept override {
        return "Name is too short (must be between 10 and 30 characters).";
    }
};

class HigherLengthOfChars : public exception {
public:
    const char* what() const noexcept override {
        return "Name is too long (must be between 10 and 30 characters).";
    }
};

class UnderAgeException : public exception {
public:
    const char* what() const noexcept override {
        return "Age is too low (must be between 15 and 22).";
    }
};

class OverAgeException : public exception {
public:
    const char* what() const noexcept override {
        return "Age is too high (must be between 15 and 22).";
    }
};

class Student {
    string name;
    int age;
public:
    void input() {
        cout << "Enter student name: ";
        getline(cin, name);
        cout << "Enter age: ";
        cin >> age;
        if (name.length() < 10) throw LowerLengthOfChars();
        if (name.length() > 30) throw HigherLengthOfChars();
        if (age < 15) throw UnderAgeException();
        if (age > 22) throw OverAgeException();
    }
    void display() {
        cout << "Name: " << name << ", Age: " << age << endl;
    }
};

int main() {
    Student s;
    try {
        s.input();
        s.display();
    }
    catch (exception& e) {
        cout << "Error: " << e.what() << endl;
    }
    return 0;
}
