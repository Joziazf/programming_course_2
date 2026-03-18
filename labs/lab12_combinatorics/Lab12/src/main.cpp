#include <iostream>
#include <vector> // умный, динамический и крутой массив, который сам управляет памятью
#include <cmath>

using namespace std;

void printBoard(const vector<vector<int>>& board, int k) {
    for (int i = 0; i < k; ++i, cout << endl)
        for (int j = 0; j < k; ++j) cout << (board[i][j] ? "Ф " : ". ");
    cout << endl;
}

void printBoard(const vector<int>& queens, int k) {
    for (int i = 0; i < k; ++i, cout << endl)
        for (int j = 0; j < k; ++j) cout <<(queens[i] == j ? "Ф " : ". ");
    cout << endl;
}

// Лобовое решение (работа с двумерным массивом)
bool isSafeLOB(const vector<vector<int>>& b, int r, int c, int k) {
    for (int i = 1; i <= r; ++i) { // крутая проверка в одном цикле
        if (b[r - i][c]) return false;
        if (c - i >= 0 && b[r - i][c - i]) return false;
        if (c + i < k && b[r - i][c + i]) return false;
    }
    return true;
}

void solutionLOB(vector<vector<int>>& board, int r, int k, int& count) {
    if (r == k) {
        count++;
        if (k<=6) printBoard(board, k);
        return;
    }
    for (int c = 0; c < k; ++c) {
        if (isSafeLOB(board , r, c, k)) {
            board[r][c] = 1;
            solutionLOB(board, r + 1, k, count);
            board[r][c] = 0;
        }
    }
}

// Чумовое решение(работа с одномерным массивом(вектор-массив))
bool isSafeCHUMA(const vector<int>& q, int r, int c) {
    for (int i = 0; i < r; ++i) // тут тоже крутая проверка
        if (q[i] == c || abs(q[i] - c) == r - i) return false;
    return true;
}

void solutionCHUMA(vector<int>& queens, int r, int k, int& count) {
    if (r == k) {
        count++;
        if (k<=6) printBoard(queens, k);
        return;
    }
    for (int c = 0; c < k; ++c) {
        if (isSafeCHUMA(queens, r, c)) {
            queens[r] = c;
            solutionCHUMA(queens, r + 1, k, count);
        }
    }
}


int main() {
    int k;
    cout << "Put a number: ";
    cin >> k;

    if (k <= 0) return 0;

    int countLOB = 0, countCHUMA = 0;
    vector<vector<int>> board(k, vector<int>(k, 0));
    vector<int> queens(k, 0);

    solutionLOB(board, 0, k, countLOB);

    solutionCHUMA(queens, 0, k, countCHUMA);

    cout << "LOB: " << countLOB << " CHUMA: " << countCHUMA << endl;

    return 0;
}