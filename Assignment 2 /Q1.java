import java.util.*;

public class NQueensSolver {

    // solves the n-queens problem and returns all valid board configurations
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
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter the value of n (1 to 9): ");
        int n = sc.nextInt();

        if (n < 1 || n > 9) {
            System.out.println("Invalid input. n must be between 1 and 9.");
            return;
        }

        NQueensSolver solver = new NQueensSolver();
        List<List<String>> solutions = solver.solveNQueens(n);

        System.out.println("Total solutions: " + solutions.size());
        for (List<String> sol : solutions) {
            for (String row : sol) {
                System.out.println(row);
            }
            System.out.println();
        }
    }
}
