#include <iostream>
using namespace std;

int** mul(int** a, int** b, int r1, int c1, int c2) {
    int** res = new int*[r1];
    for (int i = 0; i < r1; i++) {
        res[i] = new int[c2];
        for (int j = 0; j < c2; j++) {
            res[i][j] = 0;
            for (int k = 0; k < c1; k++)
                res[i][j] += a[i][k] * b[k][j];
        }
    }
    return res;
}

int main() {
    int r1, c1, r2, c2;
    cout << "matrix A size (rows cols): ";
    cin >> r1 >> c1;
    cout << "matrix B size (rows cols): ";
    cin >> r2 >> c2;

    if (c1 != r2) {
        cout << "invalid sizes for multiplication";
        return 0;
    }

    int** a = new int*[r1];
    int** b = new int*[r2];
    for (int i = 0; i < r1; i++) a[i] = new int[c1];
    for (int i = 0; i < r2; i++) b[i] = new int[c2];

    cout << "matrix A:\n";
    for (int i = 0; i < r1; i++)
        for (int j = 0; j < c1; j++)
            cin >> a[i][j];

    cout << "matrix B:\n";
    for (int i = 0; i < r2; i++)
        for (int j = 0; j < c2; j++)
            cin >> b[i][j];

    int** res = mul(a, b, r1, c1, c2);

    cout << "A * B =\n";
    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c2; j++)
            cout << res[i][j] << " ";
        cout << "\n";
    }

    return 0;
}