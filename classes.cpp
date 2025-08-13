#include <iostream>
#include <cmath>
using namespace std;

class Shape {
protected:
    double val1;
    double val2;
public:
    void get_data(double a, double b) {
        val1 = a;
        val2 = b;
    }
    virtual void display_area() {
    }
};

class Triangle : public Shape {
public:
    void display_area() override {
        cout << "Area of Triangle: " << 0.5 * val1 * val2 << endl;
    }
};

class Rectangle : public Shape {
public:
    void display_area() override {
        cout << "Area of Rectangle: " << val1 * val2 << endl;
    }
};

class Circle : public Shape {
public:
    void get_data(double r, double dummy = 0) {
        val1 = r;
        val2 = 0;
    }
    void display_area() override {
        cout << "Area of Circle: " << 3.14159 * val1 * val1 << endl;
    }
};

int main() {
    Shape* shapePtr;
    int choice;
    double a, b;

    cout << "1. Triangle\n2. Rectangle\n3. Circle\nEnter choice: ";
    cin >> choice;

    if (choice == 1) {
        Triangle t;
        cout << "Enter base and height: ";
        cin >> a >> b;
        t.get_data(a, b);
        shapePtr = &t;
        shapePtr->display_area();
    }
    else if (choice == 2) {
        Rectangle r;
        cout << "Enter length and width: ";
        cin >> a >> b;
        r.get_data(a, b);
        shapePtr = &r;
        shapePtr->display_area();
    }
    else if (choice == 3) {
        Circle c;
        cout << "Enter radius: ";
        cin >> a;
        c.get_data(a);
        shapePtr = &c;
        shapePtr->display_area();
    }
    else {
        cout << "Invalid choice" << endl;
    }

    return 0;
}
