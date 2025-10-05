#include <iostream>
#include <vector>
using namespace std;

const int SIZE = 9;

class SudokuSolver {
private:
    vector<vector<int>> grid;

public:
    SudokuSolver() {
        grid = vector<vector<int>>(SIZE, vector<int>(SIZE, 0));
    }

    void inputGrid() {
        cout << "Enter the Sudoku puzzle (use 0 for empty cells):" << endl;
        for (int i = 0; i < SIZE; i++) {
            cout << "Row " << i + 1 << " (9 numbers separated by spaces): ";
            for (int j = 0; j < SIZE; j++) {
                cin >> grid[i][j];
            }
        }
    }

    void displayGrid() {
        cout << "\nSudoku Grid:" << endl;
        for (int i = 0; i < SIZE; i++) {
            if (i % 3 == 0 && i != 0) {
                cout << "------+-------+------" << endl;
            }
            for (int j = 0; j < SIZE; j++) {
                if (j % 3 == 0 && j != 0) {
                    cout << "| ";
                }
                if (grid[i][j] == 0) {
                    cout << ". ";
                } else {
                    cout << grid[i][j] << " ";
                }
            }
            cout << endl;
        }
    }

    bool isValid(int row, int col, int num) {
        // Check row
        for (int j = 0; j < SIZE; j++) {
            if (grid[row][j] == num) return false;
        }

        // Check column
        for (int i = 0; i < SIZE; i++) {
            if (grid[i][col] == num) return false;
        }

        // Check 3x3 box
        int startRow = row - row % 3;
        int startCol = col - col % 3;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (grid[i + startRow][j + startCol] == num) return false;
            }
        }

        return true;
    }

    bool findEmptyCell(int &row, int &col) {
        for (row = 0; row < SIZE; row++) {
            for (col = 0; col < SIZE; col++) {
                if (grid[row][col] == 0) return true;
            }
        }
        return false;
    }

    bool solveSudoku() {
        int row, col;

        // If no empty cell found, puzzle is solved
        if (!findEmptyCell(row, col)) return true;

        // Try numbers 1-9
        for (int num = 1; num <= 9; num++) {
            if (isValid(row, col, num)) {
                grid[row][col] = num;

                if (solveSudoku()) return true;

                // Backtrack
                grid[row][col] = 0;
            }
        }
        return false;
    }

    void solve() {
        cout << "\nSolving Sudoku..." << endl;
        
        if (solveSudoku()) {
            cout << "Sudoku solved successfully!" << endl;
            displayGrid();
        } else {
            cout << "No solution exists for this Sudoku puzzle!" << endl;
        }
    }
};

int main() {
    SudokuSolver solver;
    
    cout << "=== SUDOKU SOLVER ===" << endl;
    cout << "Automatically solves any valid Sudoku puzzle" << endl;
    
    solver.inputGrid();
    solver.displayGrid();
    solver.solve();

    return 0;
}