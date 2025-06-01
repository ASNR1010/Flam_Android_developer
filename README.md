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
Source file : Q1.java, Q1.cpp 
[Explained with code comments]

## Time Complexity
**Worst-case:** `O(N!)`

- Each row tries `N` columns.
- With pruning through `isSafe()` checks, many invalid states are avoided.
- Still factorial in nature due to permutations of positions.

## Space Complexity
- `O(N^2)` for the board representation.
- `O(N)` for the recursion call stack.
- `O(N^2 × S)` for storing all solutions, where `S` is the number of valid solutions.




## Q.2 Problem Description

You are building a **module loader** for a large software system. Each module may depend on one or more other modules. Before loading, you must ensure that the **dependencies do not contain any circular dependency**, as that would lead to infinite loading loops.

## Input
- An integer `n` representing the number of modules labeled from `0` to `n - 1`.
- A list of edges `edges`, where each `edge[i] = {a, b}` means **module `a` depends on module `b`**.

## Output
- Return `true` if there is a **circular dependency**, otherwise `false`.

## Constraints
- `1 <= n <= 10^4`
- `0 <= edges.length <= 10^5`
- Dependencies form a **directed graph**
- **Self-dependencies** like `{a, a}` are valid and considered a **cycle**
- The graph can have **multiple disconnected components**

## Example 1:
Input:
n = 4
edges = {{0, 1}, {1, 2}, {2, 3}}

Explanation:
0 → 1 → 2 → 3 — no back edge found

Output:
false

## Example 2:
Input:
n = 4
edges = {{0, 1}, {1, 2}, {2, 0}}

Explanation:
0 → 1 → 2 → 0 — forms a cycle

Output:
true


---

## Algorithm Overview

This problem is solved using **graph traversal with cycle detection**:

- Build an **adjacency list** from the given dependency edges.
- Use **DFS** to explore each module's dependencies.
- Maintain a `visited[]` array to track states:
  - `0 = not visited`
  - `1 = currently visiting` (in recursion stack)
  - `2 = fully visited`
- If we revisit a node that's marked as `1` (i.e., already in the recursion stack), it means a **cycle** exists.
- Special case: **self-loop** (e.g. `{a, a}`) is also a cycle.

---

## Solution 
Source file : Q2.java, Q2.cpp 
[Explained with code comments]

## Time Complexity

- `O(N + E)` overall:
  - We perform a DFS traversal on each node once.
  - Each edge is considered once during traversal.

## Space Complexity

- `O(N)` for visited state tracking.
- `O(N + E)` for the adjacency list.
- `O(N)` for the recursion stack in the worst case (deepest DFS path).






