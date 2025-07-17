#include <iostream>
using namespace std;

int main() {
    int start, end;
    cin >> start >> end;
    
    if (start >= end) {
        cout << "Invalid input: start must be less than end.\n";
        return 1;
    }

    while (start < end) {
        if (start < 2) {
            start++;
            continue;
        }

        bool isPrime = true;
        int i = 2;
        while (i * i <= start) {
            if (start % i == 0) {
                isPrime = false;
                break;
            }
            i++;
        }

        if (isPrime) {
            cout << start << " ";
        }

        start++;
    }

    cout << "\n";
    return 0;
}