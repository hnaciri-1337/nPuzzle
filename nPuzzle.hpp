#include "Node.hpp"

class nPuzzle {
private:
	int	n;
	int	heuristic;
	int algorithm;
	ll closedCount = 0;
	ll peakCount = 0;
	Node* finalNode;
	vector<vector<short>>	puzzle;
	vector<vector<short>>	goal;

	bool isValidMove(int x, int y) {
		if (x < 0 || x >= n || y < 0 || y >= n)
			return false;
		return true;
	}

	int countInversions(const std::vector<int> &list) {
		int nb_inversions = 0;

		for (size_t i = 0; i < list.size(); i++)
		{
			int a = list[i];
			for (size_t j = i + 1; j < list.size(); j++) {
				int b = list[j];
				if (a > b && a != 0 && b != 0)
					nb_inversions++;
			}
		}
		return nb_inversions;
	}

	int getPuzzleBlankFromBottom(const std::vector<int> &list) {
		for (size_t i = 0; i < list.size(); i++)
			if (list[i] == 0)
				return (i);
		return (0);
	}

	std::vector<int> convert_2d_to_1d(const std::vector<std::vector<short> > &a) {
		std::vector<int> b;

		for (size_t i = 0; i < a.size(); i++)
			for (size_t j = 0; j < a[i].size(); j++)
				b.push_back(a[i][j]);
		return b;
	}

	pair<int, int> findEmpty(vector<vector<short>>& puzzle) {
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				if (puzzle[i][j] == 0)
					return make_pair(i, j);
		return make_pair(-1, -1);
	}
	
	void createGoal() {
		goal.resize(n, vector<short>(n));
		int	x = 0, y = 0;
		int	dx = 1, dy = 0;
		int	dir = 0;
		int	cnt = 1;

		while (cnt < n * n) {
			goal[y][x] = cnt;
			if (dir == 0) {
				if (x + dx == n || goal[y + dy][x + dx] != 0) {
					dir = 1;
					dx = 0;
					dy = 1;
				}
			} else if (dir == 1) {
				if (y + dy == n || goal[y + dy][x + dx] != 0) {
					dir = 2;
					dx = -1;
					dy = 0;
				}
			} else if (dir == 2) {
				if (x + dx == -1 || goal[y + dy][x + dx] != 0) {
					dir = 3;
					dx = 0;
					dy = -1;
				}
			} else if (dir == 3) {
				if (y + dy == -1 || goal[y + dy][x + dx] != 0) {
					dir = 0;
					dx = 1;
					dy = 0;
				}
			}
			x += dx;
			y += dy;
			cnt++;
		}
		goal[y][x] = 0;
	}
	
	int getManhattanDistance(int val, int x, int y) {
		int	dist = 0;
		int	gx, gy;

		if (val == 0)
			return 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (goal[i][j] == val) {
					gx = j;
					gy = i;
					break;
				}
			}
		}
		dist = abs(x - gx) + abs(y - gy);
		return dist;
	}
	
	float getEuclideanDistance(int val, int x, int y) {
		float	dist = 0;
		int	gx, gy;

		if (val == 0)
			return 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (goal[i][j] == val) {
					gx = j;
					gy = i;
					break;
				}
			}
		}
		dist = sqrt(pow(x - gx, 2) + pow(y - gy, 2));
		return dist;
	}

	int getIfMisplaced(int val, int x, int y) {
		return (val == 0) ? 0 : (val != goal[y][x]);
	}

	float getHeuristic(vector<vector<short>> &puzzle) {
		float	res = 0;

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (heuristic == 1)
					res += getManhattanDistance(puzzle[i][j], j, i);
				else if (heuristic == 2)
					heuristic += getEuclideanDistance(puzzle[i][j], j, i);
				else if (heuristic == 3)
					res += getIfMisplaced(puzzle[i][j], j, i);
			}
		}
		return res;
	}

	void applyAStar() {
		set<string>	visited;
		priority_queue<Node*, vector<Node*>, CompareNodes> pq;

		peakCount = 0;
		closedCount = 0;
		visited.insert(hashVector(puzzle));
		pq.push(new Node(puzzle, nullptr, 0, getHeuristic(puzzle), algorithm));
		while (!pq.empty()) {
			Node* current = pq.top();
			pq.pop();

			peakCount = max(peakCount, (ll)pq.size());
			closedCount++;

			if (current->state == goal) {
				finalNode = current;
				return ;
			}
			pair<int, int> emptyPos = findEmpty(current->state);
			vector<pair<int, int>> moves;
	
			if (isValidMove(emptyPos.first - 1, emptyPos.second))
				moves.push_back(make_pair(emptyPos.first - 1, emptyPos.second));
			if (isValidMove(emptyPos.first + 1, emptyPos.first))
				moves.push_back(make_pair(emptyPos.first + 1, emptyPos.second));
			if (isValidMove(emptyPos.first, emptyPos.second - 1))
				moves.push_back(make_pair(emptyPos.first, emptyPos.second - 1));
			if (isValidMove(emptyPos.first, emptyPos.second + 1))
				moves.push_back(make_pair(emptyPos.first, emptyPos.second + 1));

			for (auto& dir : moves) {
				vector<vector<short>> newState = current->state;
				swap(newState[dir.first][dir.second], newState[emptyPos.first][emptyPos.second]);
				if (visited.count(hashVector(newState)) == 0) {
					Node* newNode = new Node(newState, current, current->g + 1, getHeuristic(newState), algorithm);
					pq.push(newNode);
					visited.insert(hashVector(newState));
				}
			}
		}
	}

public:
	nPuzzle() {
		algorithm = 1;
		heuristic = 1;
	}
	void readPuzzle(char *fileName) {
		ifstream file;

		file.open(fileName);
		if (!file.is_open())
			fatal_error("Error: file not found");
		file.ignore(numeric_limits<streamsize>::max(), '\n');
		file >> n;
		puzzle.resize(n, vector<short>(n));
		file >> puzzle;
		createGoal();
	}
	void readOptions() {
		cout << "We have a puzzle to solve. What algorithm should we use ?" << endl;
		cout << "1. A* algorithm (MANDATORY)" << endl;
		cout << "2. Greedy search (BONUS)" << endl;
		cout << "3. Uniform cost search (BONUS)" << endl;
		cout << "> ";
		cin >> algorithm;
		if (algorithm != 3) {
			cout << "Which heuristic should we use ?" << endl;
			cout << "1. Manhattan distance" << endl;
			cout << "2. Euclidean distance" << endl;
			cout << "3. Misplaced tiles" << endl;
			cout << "> ";
			cin >> heuristic;
		}
		if (heuristic < 1 or heuristic > 3 or algorithm < 1 or algorithm > 3)
			fatal_error("Error: invalid option");
	}
	void printSolution() {
		Node* current = finalNode;
		vector<Node*> path;


		while (current != nullptr) {
			path.push_back(current);
			current = current->parent;
		}
		for (int i = path.size() - 1; i >= 0; i--) {
			for (auto &line : path[i]->state)
				cout << line;
			cout << endl;
		}


		cout << "Complexity in time: " << closedCount << endl;
		cout << "Complexity in size: " << peakCount << endl;
		cout << "Moves: " << finalNode->g << endl;
	}
	bool isSolvable()
	{
		std::vector<int> initial_state = convert_2d_to_1d(puzzle);
		std::vector<int> end_state = convert_2d_to_1d(goal);
		int initial_state_inversions = countInversions(initial_state);
		int end_state_inversions = countInversions(end_state);
		int initial_state_puzzle_blank_from_bottom = getPuzzleBlankFromBottom(initial_state);
		int end_state_puzzle_blank_from_bottom = getPuzzleBlankFromBottom(end_state);
		
		if ((n % 2) != 0)
			return initial_state_inversions % 2 == end_state_inversions % 2;
		return (initial_state_puzzle_blank_from_bottom % 2 == end_state_puzzle_blank_from_bottom % 2) == (initial_state_inversions % 2 == end_state_inversions % 2);
	}
	void solvePuzzle() {
		applyAStar();
	}
};
