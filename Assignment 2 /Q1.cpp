#include <iostream>
#include <vector>
#include <string>

using namespace std;

class NQueensSolver {
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> solutions; // list to store all the valid solutions
        vector<string> board(n, string(n, '.')); // initialize a 2D board as vector of strings

        // call the backtracking function starting from the first row
        backtrack(solutions, board, 0, n);

        return solutions;
    }

private:
    // backtracking function to try placing queens row by row
    void backtrack(vector<vector<string>>& solutions, vector<string>& board, int row, int n) {
        // base case: if all queens are placed successfully
        if (row == n) {
            solutions.push_back(board);
            return;
        }

        // try placing a queen in every column of the current row
        for (int col = 0; col < n; ++col) {
            if (isSafe(board, row, col, n)) {
                board[row][col] = 'Q'; // place queen
                backtrack(solutions, board, row + 1, n); // go to next row
                board[row][col] = '.'; // backtrack: remove queen
            }
        }
    }

    // function to check if it's safe to place a queen at board[row][col]
    bool isSafe(const vector<string>& board, int row, int col, int n) {
        // check same column in previous rows
        for (int i = 0; i < row; ++i) {
            if (board[i][col] == 'Q') return false;
        }

        // check upper left diagonal
        for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; --i, --j) {
            if (board[i][j] == 'Q') return false;
        }

        // check upper right diagonal
        for (int i = row - 1, j = col + 1; i >= 0 && j < n; --i, ++j) {
            if (board[i][j] == 'Q') return false;
        }

        return true; // it's safe to place the queen
    }
};

int main() {
    NQueensSolver solver;

    int n;
    cout << "Enter the value of n: ";
    cin >> n;

    vector<vector<string>> solutions = solver.solveNQueens(n);

    // print all solutions
    for (const auto& sol : solutions) {
        for (const auto& row : sol) {
            cout << row << endl;
        }
        cout << endl;
    }

    return 0;
}
