#include <iostream>
#include <vector>

const int N = 9;

// Function to check if it's safe to place the digit at the given position
bool isSafe(auto& grid, int row, int col, int num) {
    // Check if the number exists in the current row and column
    for (int i = 0; i < N; ++i) {
        if (grid[row][i] == num || grid[i][col] == num) {
            return false;
        }
    }

    // Check if the number exists in the 3x3 subgrid
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (grid[i + startRow][j + startCol] == num) {
                return false;
            }
        }
    }

    return true;
}

// Function to find an empty cell in the grid
bool findEmptyLocation(std::vector<std::vector<int>>& grid, int& row, int& col) {
    for (row = 0; row < N; ++row) {
        for (col = 0; col < N; ++col) {
            if (grid[row][col] == 0) {
                return true; // Empty cell found
            }
        }
    }
    return false; // No empty cell found
}

// Backtracking function to solve the Sudoku puzzle
bool solveSudoku(std::vector<std::vector<int>>& grid) {
    int row, col;

    // If no empty cell is found, the puzzle is solved
    if (!findEmptyLocation(grid, row, col)) {
        return true;
    }

    // Try placing a digit from 1 to 9
    for (int num = 1; num <= 9; ++num) {
        if (isSafe(grid, row, col, num)) {
            // Place the digit
            grid[row][col] = num;

            // Recursively solve the rest of the puzzle
            if (solveSudoku(grid)) {
                return true; // Puzzle solved successfully
            }

            // If placing the current digit leads to an invalid solution, backtrack
            grid[row][col] = 0;
        }
    }

    return false; // No valid digit found for the current cell
}

// Function to display the Sudoku grid
void displayGrid(const std::vector<std::vector<int>>& grid) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            std::cout << grid[i][j] << " ";
        }
        std::cout << "\n";
    }
}

int main() {
    std::vector<std::vector<int>> sudokuGrid = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    if (solveSudoku(sudokuGrid)) {
        std::cout << "Sudoku puzzle solved:\n";
        displayGrid(sudokuGrid);
    } else {
        std::cout << "No solution exists for the given Sudoku puzzle.\n";
    }

    return 0;
}