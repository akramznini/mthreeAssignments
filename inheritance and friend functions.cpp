#include <iostream>
#include <string>
using namespace std;

class Example {
private:
    int privateValue;
protected:
    int protectedValue;
public:
    int publicValue;
    Example() {
        privateValue = 10;
        protectedValue = 20;
        publicValue = 30;
    }
    friend void showValues(Example e);
};

void showValues(Example e) {
    cout << "Private: " << e.privateValue << endl;
    cout << "Protected: " << e.protectedValue << endl;
    cout << "Public: " << e.publicValue << endl;
}

class Base1 {
    int number;
public:
    Base1(int n) {
        number = n;
    }
    int getNumber() {
        return number;
    }
};

class Derived1 : public Base1 {
public:
    Derived1() : Base1(100) {
    }
};

class Base2 {
    int value;
public:
    Base2(int v) {
        value = v;
    }
    int getValue() {
        return value;
    }
};

class Base3 {
    string word;
public:
    Base3() {
        word = "default";
    }
    string getWord() {
        return word;
    }
};

class Derived2 : public Base2, public Base3 {
    string name;
public:
    Derived2(int v, string n) : Base2(v), Base3() {
        name = n;
    }
    void display() {
        cout << "Value: " << getValue() << ", Word: " << getWord() << ", Name: " << name << endl;
    }
};

int main() {
    Example ex;
    showValues(ex);

    Derived1 d1;
    cout << "Derived1 Base Number: " << d1.getNumber() << endl;

    Derived2 d2(42, "Alpha");
    d2.display();

    return 0;
}
