#include <iostream>;
#include <utility>;
#include <map>;
#include <vector>;
#include <algorithm>;
#include <queue>;
#include <math.h> 
#include <string> 

struct Board_state {
	std::map<int, int> board;

	std::map<int, int> goal_board = {
		{1, 1},
		{2, 2},
		{3, 3},
		{4, 4},
		{5, 5},
		{6, 6},
		{7, 7},
		{8, 8},
		{9, 0}
	};

	int depth = 0;
	std::vector<std::pair<int, int>> moves; // To store solution path

	// Initial state of board
	Board_state() {
		board.insert({ 1, 6 });
		board.insert({ 2, 4 });
		board.insert({ 3, 7 });
		board.insert({ 4, 8 });
		board.insert({ 5, 5 });
		board.insert({ 6, 0 });
		board.insert({ 7, 3 });
		board.insert({ 8, 2 });
		board.insert({ 9, 1 });
	}

	// Copy constructor
	Board_state(const Board_state& board_rhs) {
		board = board_rhs.board;
		depth = board_rhs.depth + 1;
		moves.reserve(moves.size() + 1);
		moves = board_rhs.moves;
	}

	// For printing
	friend std::ostream& operator<<(std::ostream& os, const Board_state& b) {
		for (int i = 1; i < 10; i++) {
			os << b.board.find(i)->second << " "; // To get value from key
		}
		return os;
	}

	bool operator==(const Board_state& b_rhs) {
		return this->board == b_rhs.board;
	}

	// Creates the available child states from a parent state
	std::vector<Board_state*> check_available_moves() {
		// Get key of value 0
		int position_of_zero;
		for (int i = 1; i < 10; i++) {
			if (board.find(i)->second == 0) {
				position_of_zero = board.find(i)->first;
			}
		}

		std::vector<Board_state*> available_child_states;

		// Copy parent, then swap
		Board_state* swap_left = new Board_state(*this);
		Board_state* swap_up = new Board_state(*this);
		Board_state* swap_right = new Board_state(*this);
		Board_state* swap_down = new Board_state(*this);

		// Define moves as a swap with the empty tile, store node path for solution printing
		switch (position_of_zero) {
		case 1:
			std::swap(swap_right->board.at(1), swap_right->board.at(2));
			swap_right->moves.push_back({ swap_right->board.find(1)->second, 2 });
			available_child_states.push_back(swap_right);

			std::swap(swap_down->board.at(1), swap_down->board.at(4));
			swap_down->moves.push_back({ swap_down->board.find(1)->second, 3 });
			available_child_states.push_back(swap_down);
			break;
		case 2:
			std::swap(swap_left->board.at(2), swap_left->board.at(1));
			swap_left->moves.push_back({ swap_left->board.find(2)->second, 0 });
			available_child_states.push_back(swap_left);

			std::swap(swap_right->board.at(2), swap_right->board.at(3));
			swap_right->moves.push_back({ swap_right->board.find(2)->second, 2 });
			available_child_states.push_back(swap_right);

			std::swap(swap_down->board.at(2), swap_down->board.at(5));
			swap_down->moves.push_back({ swap_down->board.find(2)->second, 3 });
			available_child_states.push_back(swap_down);
			break;
		case 3:
			std::swap(swap_left->board.at(3), swap_left->board.at(2));
			swap_left->moves.push_back({ swap_left->board.find(3)->second, 0 });
			available_child_states.push_back(swap_left);

			std::swap(swap_down->board.at(3), swap_down->board.at(6));
			swap_down->moves.push_back({ swap_down->board.find(3)->second, 3 });
			available_child_states.push_back(swap_down);
			break;
		case 4:
			std::swap(swap_up->board.at(4), swap_up->board.at(1));
			swap_up->moves.push_back({ swap_up->board.find(4)->second, 1 });
			available_child_states.push_back(swap_up);

			std::swap(swap_right->board.at(4), swap_right->board.at(5));
			swap_right->moves.push_back({ swap_right->board.find(4)->second, 2 });
			available_child_states.push_back(swap_right);

			std::swap(swap_down->board.at(4), swap_down->board.at(7));
			swap_down->moves.push_back({ swap_down->board.find(4)->second, 3 });
			available_child_states.push_back(swap_down);
			break;
		case 5:
			std::swap(swap_left->board.at(5), swap_left->board.at(4));
			swap_left->moves.push_back({ swap_left->board.find(5)->second, 0 });
			available_child_states.push_back(swap_left);

			std::swap(swap_up->board.at(5), swap_up->board.at(2));
			swap_up->moves.push_back({ swap_up->board.find(5)->second, 1 });
			available_child_states.push_back(swap_up);

			std::swap(swap_right->board.at(5), swap_right->board.at(6));
			swap_right->moves.push_back({ swap_right->board.find(5)->second, 2 });
			available_child_states.push_back(swap_right);

			std::swap(swap_down->board.at(5), swap_down->board.at(8));
			swap_down->moves.push_back({ swap_down->board.find(5)->second, 3 });
			available_child_states.push_back(swap_down);
			break;
		case 6:
			std::swap(swap_left->board.at(6), swap_left->board.at(5));
			swap_left->moves.push_back({ swap_left->board.find(6)->second, 0 });
			available_child_states.push_back(swap_left);

			std::swap(swap_up->board.at(6), swap_up->board.at(3));
			swap_up->moves.push_back({ swap_up->board.find(6)->second, 1 });
			available_child_states.push_back(swap_up);

			std::swap(swap_down->board.at(6), swap_down->board.at(9));
			swap_down->moves.push_back({ swap_down->board.find(6)->second, 3 });
			available_child_states.push_back(swap_down);
			break;
		case 7:
			std::swap(swap_up->board.at(7), swap_up->board.at(4));
			swap_up->moves.push_back({ swap_up->board.find(7)->second, 1 });
			available_child_states.push_back(swap_up);

			std::swap(swap_right->board.at(7), swap_right->board.at(8));
			swap_right->moves.push_back({ swap_right->board.find(7)->second, 2 });
			available_child_states.push_back(swap_right);
			break;
		case 8:
			std::swap(swap_left->board.at(8), swap_left->board.at(7));
			swap_left->moves.push_back({ swap_left->board.find(8)->second, 0 });
			available_child_states.push_back(swap_left);

			std::swap(swap_up->board.at(8), swap_up->board.at(5));
			swap_up->moves.push_back({ swap_up->board.find(8)->second, 1 });
			available_child_states.push_back(swap_up);

			std::swap(swap_right->board.at(8), swap_right->board.at(9));
			swap_right->moves.push_back({ swap_right->board.find(8)->second, 2 });
			available_child_states.push_back(swap_right);
			break;
		case 9:
			std::swap(swap_left->board.at(9), swap_left->board.at(8));
			swap_left->moves.push_back({ swap_left->board.find(9)->second, 0 });
			available_child_states.push_back(swap_left);

			std::swap(swap_up->board.at(9), swap_up->board.at(6));
			swap_up->moves.push_back({ swap_up->board.find(9)->second, 1 });
			available_child_states.push_back(swap_up);
			break;
		}

		return available_child_states;
	}

	// First heuristic function
	int h1() {
		int nr_misplaced_tiles = 0;
		for (int i = 1; i < 10; i++) {
			if (board.find(i)->second != 0) {
				if (board.find(i)->second != goal_board.find(i)->second) {
					nr_misplaced_tiles++;
				}
			}
		}
		return nr_misplaced_tiles;
	}

	int h2() {
		int manhattan_distance = 0;
		// For each tile on the board
		for (int i = 1; i < 10; i++) {
			// Are the values on a tile are different from the goal state? Empty tile cannot be misplaced
			if (board.find(i)->second != goal_board.find(i)->second && board.find(i)->second != 0) {
				int value_on_board = board.find(i)->second;
				int position_on_board = board.find(i)->first;

				int position_on_goal_board;
				for (auto it = goal_board.begin(); it != goal_board.end(); ++it) {
					if (it->second == value_on_board) {
						position_on_goal_board = it->first;
					}
				}

				int x_board;

				if (position_on_board % 3 == 0) {
					x_board = 3;
				}
				else if (position_on_board % 3 == 2) {
					x_board = 2;
				}
				else {
					x_board = 1;
				}

				int y_board;

				if (position_on_board <= 3) {
					y_board = 1;
				}
				else if (position_on_board > 3 && position_on_board <= 6) {
					y_board = 2;
				}
				else if (position_on_board > 6) {
					y_board = 3;
				}

				int x_goal;

				if (position_on_goal_board % 3 == 0) {
					x_goal = 3;
				}
				else if (position_on_goal_board % 3 == 2) {
					x_goal = 2;
				}
				else {
					x_goal = 1;
				}

				int y_goal;

				if (position_on_goal_board <= 3) {
					y_goal = 1;
				}
				else if (position_on_goal_board > 3 && position_on_goal_board <= 6) {
					y_goal = 2;
				}
				else if (position_on_goal_board > 6) {
					y_goal = 3;
				}

				// Sum for all values
				manhattan_distance += abs(x_board - x_goal) + abs(y_board - y_goal);
			}
		}
		return manhattan_distance;
	}

	// Testing other heuristics

	int h3() {
		return (h1() + h2()) / 2;
	}

	int h4() {
		return 2 * h1();
	}

	int h5() {
		return std::max(h1(), h2());
	}

	// First total cost function, using nr of misplaced tiles as heuristic
	int f1() {
		return h1() + depth;
	}

	// Second total cost function, using Manhattan distance
	int f2() {
		return h2() + depth;
	}


	// Total cost functions for other heuristics
	int f3() {
		return h3() + depth;
	}

	int f4() {
		return h4() + depth;
	}

	int f5() {
		return h5() + depth;
	}
};

// Because top acesses the highest element, the sorting needs to be reversed
struct compare_boards {
	bool operator() (Board_state* a, Board_state* b) {
		return a->f5() > b->f5();
	}
};

// Used for storing and searching for boards in the closed list
std::string board_to_string(Board_state* b) {
	std::string s = "";
	for (int i = 1; i < 10; i++) {
		s += std::to_string(b->board.find(i)->second);
	}
	return s;
}

int main() {
	Board_state b = Board_state();

	std::map<std::string, Board_state*> closed_list;
	std::priority_queue < Board_state*, std::vector<Board_state*>, compare_boards> open_list;

	Board_state* start = new Board_state();
	open_list.push(start);

	// While the goal state is not in the first position of the open list, continue
	while (open_list.top()->board != open_list.top()->goal_board) {
		std::vector<Board_state*> child_states = open_list.top()->check_available_moves();

		// Expand
		std::for_each(child_states.begin(), child_states.end(), [&](Board_state* child) {
			bool add_child = true;

			// Duplicate check
			if (closed_list.count(board_to_string(child)) > 0) {
				add_child = false;
			}

			if (add_child) {
				open_list.push(child);
			}
		});

		// Store expanded nodes
		Board_state* tmp = open_list.top();
		open_list.pop();
		closed_list.insert({ board_to_string(tmp), tmp });

		std::cout << open_list.top()->h5() << " ";
	}

	std::cout << "\n" << "Success!" << "\n";

	// Print list of moves for solution
	for (int i = 0; i < open_list.top()->moves.size(); i++) {

		std::string move_direction;
		switch (open_list.top()->moves[i].second) {
		case 0:
			move_direction = "right";
			break;
		case 1:
			move_direction = "down";
			break;
		case 2:
			move_direction = "left";
			break;
		case 3:
			move_direction = "up";
			break;
		}

		std::cout << "Move " << open_list.top()->moves[i].first << " " << move_direction << "\n";
	}

	return 0;
}