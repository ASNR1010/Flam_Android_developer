# Flam_Android_developer

Q.1 
# N-Queens Problem

![Java](https://img.shields.io/badge/language-Java-blue)
![Backtracking](https://img.shields.io/badge/algorithm-Backtracking-green)

## 🧩 Problem Description
The **N-Queens** puzzle involves placing N queens on an `N x N` chessboard so that no two queens threaten each other. A valid solution ensures that no two queens share the same row, column, or diagonal.

## 📥 Input
- An integer `n` where `1 <= n <= 9`, representing the size of the board and the number of queens.

## 📤 Output
- All **distinct** board configurations.
- `'Q'` denotes a queen, and `'.'` denotes an empty cell.

## 📘 Example
```java
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



