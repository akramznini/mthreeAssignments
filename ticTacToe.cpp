#include <iostream>
using namespace std;

char isGameOver(char board[]) {
    // Diagonals
    if (board[0] != '\0' and board[0] == board[4] and board[4] == board[8]) return board[0];
    if (board[2] != '\0' and board[2] == board[4] and board[4] == board[6]) return board[2];

    // Horizontals
    for (int i = 0; i < 3; i++) {
        int rowStart = i * 3;
        if (board[rowStart] != '\0' and board[rowStart] == board[rowStart + 1] and board[rowStart + 1] == board[rowStart + 2])
            return board[rowStart];
    }

    // Verticals
    for (int i = 0; i < 3; i++) {
        if (board[i] != '\0' and board[i] == board[i + 3] and board[i + 3] == board[i + 6])
            return board[i];
    }

    // Draw
    for (int i = 0; i < 9; i++) {
        if (board[i] == '\0') break;
        if (i == 8) return 'D';
    }

    return '\0';
}

int main() {
    cout << "Welcome to Tic Tac Toe!\n\n";
    char board[9] = {};
    bool isPlayer1 = true;

    while (!isGameOver(board)) {
        char symbol = isPlayer1 ? 'X' : 'O';

        for (int i = 0; i < 9; i++) {
            if (i % 3 == 0) cout << "\n";
            if (i % 3 == 1) cout << "|";
            cout << (board[i] == '\0' ? ' ' : board[i]);
            if (i % 3 == 1) cout << "|";
        }
        cout << "\n\nPlayer " << symbol << ", choose a box number (0–8): ";
        
        int box;
        cin >> box;
        if (box < 0 or box > 8 or board[box] != '\0') {
            cout << "Invalid move. Try again.\n";
            continue;
        }

        board[box] = symbol;
        isPlayer1 = !isPlayer1;
    }

    char result = isGameOver(board);
    if (result == 'D') cout << "\nIt's a draw!\n";
    else cout << "\nThe winner is: " << result << "\n";

    cin.get();
    return 0;
}