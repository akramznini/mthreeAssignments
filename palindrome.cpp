#include <iostream>
using namespace std;

int main() {
    int number, original, reversed = 0;
    cin >> number;

    original = number;

    while (number > 0) {
        int digit = number % 10;           
        reversed = reversed * 10 + digit;  
        number /= 10;                     
    }

    if (original == reversed) {
        cout << "The number is a palindrome\n";
    } else {
        cout << "The number is not a palindrome\n";
    }

    return 0;
}