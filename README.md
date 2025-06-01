# Flam_Android_developer



## Q.1 Problem Description
The **N-Queens** puzzle involves placing N queens on an `N x N` chessboard so that no two queens threaten each other. A valid solution ensures that no two queens share the same row, column, or diagonal.

## Input
- An integer `n` where `1 <= n <= 9`, representing the size of the board and the number of queens.

## Output
- All **distinct** board configurations.
- `'Q'` denotes a queen, and `'.'` denotes an empty cell.

## Example
Input: n = 4

Output:
[
  [".Q..",
   "...Q",
   "Q...",
   "..Q."],

  ["..Q.",
   "Q...",
   "...Q",
   ".Q.."]
]

## Algorithm Overview
This problem is solved using **recursive backtracking**:

- Try placing a queen in each column of the current row.
- Check if the placement is safe:
  - No other queens in the same column.
  - No queens on upper-left and upper-right diagonals.
- If safe, move to the next row.
- If the end is reached, save the board configuration.
- Backtrack and try the next column.

## Solution 
Q1.java


## ⏱️ Time Complexity
**Worst-case:** `O(N!)`

- Each row tries `N` columns.
- With pruning through `isSafe()` checks, many invalid states are avoided.
- Still factorial in nature due to permutations of positions.

## 🧠 Space Complexity
- `O(N^2)` for the board representation.
- `O(N)` for the recursion call stack.
- `O(N^2 × S)` for storing all solutions, where `S` is the number of valid solutions.



