/**Cleaner version**/
#include <iostream>
#include <string>
#include <queue>
#include <vector>
using namespace std;

//The goal state. Global to ease access for now.
const int goal[3][3]{
	{1, 2, 3},
	{4, 5, 6},
	{7, 8, 0}
};

//Struct to represent a board
struct Node
{
	//The current state of the puzzle board.
	int _state[3][3]{
		{ 1, 2, 3 },
	{ 0, 5, 4 },
	{ 7, 8, 6 }
	};

	//Heuristics and cost
	float _g; //Cost from all earlier moves
	float _h; // the heuristic for the current node
	float _cost; //The total cost of moving -> _g + _h;

	//String containing the movemennts uptil the current node
	//Each movement is added as a letter to the string
	string _movement = "";


};

struct Compare_Cost {
	bool operator()(Node const & n1, Node const & n2) {
		return n1._cost < n2._cost;
	}
};

//Checks if a nodes state matches the goal state.
bool Is_Goal(Node const & n) {
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			if (n._state[i][j] != goal[i][j])
				return false;
		}
	}
	return true;
}

//Calculate heuristic for one node. The heuristic is the sum of all tiles different
//from the goal board.
void Heuristic(Node & n) {
	int counter = 0;

	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {

			if (n._state[i][j] != goal[i][j]) {
				++counter;
			}
		}
	}

	n._h = counter;
}

void Compute_Cost(Node & n) {
	n._cost = n._g + n._h;
}

vector<Node> Gen_Successors(Node & n) {

	vector<Node> children;

	//generate successors
	int row = 0, col = 0;

	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {

			if (n._state[i][j] == 0) {
				row = i;
				col = j;
				break;
			}
		}
	}

	//Move up
	if (row > 0) {
		Node child = n;
		std::swap(child._state[row][col], child._state[row - 1][col]);
		child._movement += "U";
		++child._g;
		Heuristic(child);
		children.push_back(child);
	}

	//Move down
	if (row < 2) {
		Node child = n;
		std::swap(child._state[row][col], child._state[row + 1][col]);
		child._movement += "D";
		++child._g;
		Heuristic(child);
		children.push_back(child);
	}

	//Move to the left
	if (col > 0) {
		Node child = n;
		std::swap(child._state[row][col], child._state[row][col - 1]);
		child._movement += "L";
		++child._g;
		Heuristic(child);
		children.push_back(child);
	}

	//Move to the right
	if (col < 2) {
		Node child = n;
		std::swap(child._state[row][col], child._state[row][col + 1]);
		child._movement += "R";
		++child._g;
		Heuristic(child);
		children.push_back(child);
	}
	return children;
}


string A_Star(Node start) {

	//Instantiate the open list
	priority_queue<Node, vector<Node>, Compare_Cost> open_list;
	open_list.push(start);

	//Instantiate the closed list
	//priority_queue<Node, vector<Node>, Compare_Cost> closed_list;

	while (!open_list.empty()) {
		//Retrieve the first node in the queue
		Node first = open_list.top();
		open_list.pop();

		if (Is_Goal(first)) {
			return "Solution found: " + first._movement;
		}
		else {
			//Generate children for the node;
			vector<Node> children = Gen_Successors(first);

			for (auto c : children) {
				Heuristic(c);
				Compute_Cost(c);
				open_list.push(c);

			}
		}
	}

	return "No solution found.";
}




//int main() {
//	Node start;
//	string res = A_Star(start);
//	cout << res;
//	
//	int n;
//	cin >> n;
//}