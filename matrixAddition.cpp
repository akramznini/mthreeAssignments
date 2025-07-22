#include <iostream>
using namespace std;

int** add(int** a, int** b, int r, int c) {
    int** res = new int*[r];
    for (int i = 0; i < r; i++) {
        res[i] = new int[c];
        for (int j = 0; j < c; j++)
            res[i][j] = a[i][j] + b[i][j];
    }
    return res;
}

int main() {
    int r, c;
    cout << "Entrer rows and cols: ";
    cin >> r >> c;

    int** a = new int*[r];
    int** b = new int*[r];
    for (int i = 0; i < r; i++) {
        a[i] = new int[c];
        b[i] = new int[c];
    }

    cout << "matrix A:\n";
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
            cin >> a[i][j];

    cout << "matrix B:\n";
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
            cin >> b[i][j];

    int** res = add(a, b, r, c);
    cout << "A + B =\n";
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++)
            cout << res[i][j] << " ";
        cout << "\n";
    }

    return 0;
}