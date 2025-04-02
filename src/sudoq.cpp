#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <vector>

using namespace std;

#define N 9

class Sudoku {
private:
	int grid[81] = {0};
	const char* border = "  +-----------+-----------+-----------+";

public:
	Sudoku() {
		srand(time(0));
	}

	bool isSafe(int row, int col, int num) {
		for (int x = 0; x < N; x++) {
			if (grid[row * N + x] == num || grid[x * N + col] == num)
				return false;
		}
		
		int startRow = row - row % 3, startCol = col - col % 3;
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				if (grid[(startRow + i) * N + (startCol + j)] == num)
					return false;
					
		return true;
	}

	bool fillGrid(int row, int col) {
		if (row == N - 1 && col == N) return true;
		if (col == N) { row++; col = 0; }
		if (grid[row * N + col] != 0) return fillGrid(row, col + 1);

		vector<int> nums {1,2,3,4,5,6,7,8,9};
		random_shuffle(nums.begin(), nums.end());

		for (int num : nums) {
			if (isSafe(row, col, num)) {
				grid[row * N + col] = num;
				if (fillGrid(row, col + 1)) return true;
				grid[row * N + col] = 0;
			}
		}
		return false;
	}

	bool hasUniqueSolution(int tempGrid[81]) {
		int count = 0;
		function<bool(int, int)> solver = [&](int row, int col) {
			if (row == N) return ++count == 2;
			if (col == N) return solver(row + 1, 0);
			if (tempGrid[row * N + col] != 0) return solver(row, col + 1);

			vector<int> nums {1,2,3,4,5,6,7,8,9};
			random_shuffle(nums.begin(), nums.end());

			for (int num : nums) {
				if (isSafe(row, col, num)) {
					tempGrid[row * N + col] = num;
					if (solver(row, col + 1)) return true;
					tempGrid[row * N + col] = 0;
				}
			}
			return false;
		};
		return !solver(0, 0);
	}

	void removeNumbers(int difficulty) {
		int minRemove = 30 + (difficulty - 1) * 5;
		int maxRemove = 40 + (difficulty - 1) * 5;
		int numToRemove = minRemove + rand() % (maxRemove - minRemove + 1);

		vector<int> indices(81);
		for (int i = 0; i < 81; i++) indices[i] = i;
		random_shuffle(indices.begin(), indices.end());

		for (int index : indices) {
			if (numToRemove == 0) break;
			int backup = grid[index];
			grid[index] = 0;
			
			int tempGrid[81];
			copy(begin(grid), end(grid), begin(tempGrid));
			if (!hasUniqueSolution(tempGrid)) {
				grid[index] = backup;
			} else {
				numToRemove--;
			}
		}
	}

	void generate(int difficulty) {
		fillGrid(0, 0);
		removeNumbers(difficulty);
	}

	void printGrid() {
		cout << border << "\n";
		for (int i = 0; i < N; i++) {
			cout << "  |  ";
			for (int j = 0; j < N; j++) {
				cout << (grid[i * N + j] ? to_string(grid[i * N + j]) : ".") << "  ";
				if ((j + 1) % 3 == 0) cout << "|  ";
			}
			cout << "\n";
			if ((i + 1) % 3 == 0) cout << border << "\n";
		}
	}
};

int main() {
	Sudoku sudoku;
	int difficulty;
	cout << "Enter difficulty (1-10): ";
	cin >> difficulty;
	difficulty = max(1, min(10, difficulty));

	sudoku.generate(difficulty);
	sudoku.printGrid();

	return 0;
}
