#include <iostream>
using namespace std;

const int N = 9;
const int UNASSIGNED = 0;

// Helper function to print the Sudoku grid
void printGrid(int grid[N][N]) {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            cout << grid[row][col] << " ";
        }
        cout << endl;
    }
}

// Helper function to check if a value can be placed in a given cell
bool isSafe(int grid[N][N], int row, int col, int num) {
    // Check if num is already in the row
    for (int c = 0; c < N; c++) {
        if (grid[row][c] == num) {
            return false;
        }
    }
    // Check if num is already in the column
    for (int r = 0; r < N; r++) {
        if (grid[r][col] == num) {
            return false;
        }
    }
    // Check if num is already in the 3x3 box
    int boxRow = row - row % 3;
    int boxCol = col - col % 3;
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {
            if (grid[boxRow + r][boxCol + c] == num) {
                return false;
            }
        }
    }
    // If num can be placed in the cell
    return true;
}

// Backtracking function to solve the Sudoku puzzle
bool solveSudoku(int grid[N][N]) {
    int row, col;
    bool emptyCellFound = false;
    // Find an unassigned cell
    for (row = 0; row < N; row++) {
        for (col = 0; col < N; col++) {
            if (grid[row][col] == UNASSIGNED) {
                emptyCellFound = true;
                break;
            }
        }
        if (emptyCellFound) {
            break;
        }
    }
    // If no unassigned cell is found, the puzzle is solved
    if (!emptyCellFound) {
        return true;
    }
    // Try each possible value in the unassigned cell
    for (int num = 1; num <= 9; num++) {
        if (isSafe(grid, row, col, num)) {
            grid[row][col] = num;
            // Recursively solve the puzzle
            if (solveSudoku(grid)) {
                return true;
            }
            // If the recursive call fails, backtrack and try another value
            grid[row][col] = UNASSIGNED;
        }
    }
    // If no value can be placed in the cell, the puzzle cannot be solved
    return false;
}

int main() {
    int grid[N][N] = {
        { 0, 0, 0, 0, 7, 0, 3, 0, 0 },
        { 0, 4, 8, 0, 5, 0, 7, 0, 0 },
        { 3, 0, 0, 0, 0, 6, 0, 0, 8 },
        { 0, 1, 0, 2, 0, 0, 5, 0, 0 },
        { 7, 0, 0, 0, 6, 0, 0, 0, 2 },
        { 0, 0, 9, 0, 0, 0, 0, 3, 0 },
        { 1, 0, 0, 3, 0, 0, 0, 0, 7 },
        { 0, 0, 4, 0, 2, 0, 8, 9, 0 },
        { 0, 0, 5, 0, 4, 0, 0, 0, 0 }
    };

    cout << "Original Grid: " << endl;
    printGrid(grid);
    cout << endl;
    if (solveSudoku(grid)) {
        cout << "Solved Grid: " << endl;
        printGrid(grid);
    } else {
        cout << "No solution exists" << endl;
    }

    std::cout << "Press any key to exit." << std::endl;
    getchar(); // Wait for user to press a key
    return 0;

}
