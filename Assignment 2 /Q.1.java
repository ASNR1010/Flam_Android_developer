import java.util.*;

public class NQueensSolver {

    public List<List<String>> solveNQueens(int n) {
        List<List<String>> solutions = new ArrayList<>(); // list to store all the valid solutions
        char[][] board = new char[n][n]; // initialize a 2D board

        // fill the board with '.'
        for (char[] row : board) {
            Arrays.fill(row, '.');
        }

        // call the backtracking function starting from the first row
        backtrack(solutions, board, 0, n);

        return solutions;
    }

    // backtracking function to try placing queens row by row
    private void backtrack(List<List<String>> solutions, char[][] board, int row, int n) {
        // base case: if all queens are placed successfully
        if (row == n) {
            solutions.add(construct(board));
            return;
        }

        // try placing a queen in every column of the current row
        for (int col = 0; col < n; col++) {
            if (isSafe(board, row, col, n)) {
                board[row][col] = 'Q'; // place queen
                backtrack(solutions, board, row + 1, n); // go to next row
                board[row][col] = '.'; // backtrack: remove queen
            }
        }
    }

    // function to check if it's safe to place a queen at board[row][col]
    private boolean isSafe(char[][] board, int row, int col, int n) {
        // check same column in previous rows
        for (int i = 0; i < row; i++) {
            if (board[i][col] == 'Q') return false;
        }

        // check upper left diagonal
        for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
            if (board[i][j] == 'Q') return false;
        }

        // check upper right diagonal
        for (int i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++) {
            if (board[i][j] == 'Q') return false;
        }

        return true; // it's safe to place the queen
    }

    // convert the board into a list of strings for storing the solution
    private List<String> construct(char[][] board) {
        List<String> result = new ArrayList<>();
        for (char[] row : board) {
            result.add(new String(row)); // convert each row into a string
        }
        return result;
    }

    // main method to run and test the solution
    public static void main(String[] args) {
        NQueensSolver solver = new NQueensSolver();

        int n = 4; // example input
        List<List<String>> solutions = solver.solveNQueens(n);

        // print all solutions
        for (List<String> sol : solutions) {
            for (String row : sol) {
                System.out.println(row);
            }
            System.out.println();
        }
    }
}
