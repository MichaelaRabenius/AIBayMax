/**Cleaner version**/
#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

using State = int[3][3];

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
		{ 6, 4, 7 },
		{ 8, 5, 0 },
		{ 3, 2, 1 }
	};


	//Heuristics and cost
	int _g = 0; //Cost from all earlier moves
	int _h = 0; // the heuristic for the current node
	int _cost = 0; //The total cost of moving -> _g + _h;

	//String containing the movemennts uptil the current node
	//Each movement is added as a letter to the string
	string _movement = "";


	bool operator==(Node& const n2) {
		return _state == n2._state;
	}

	string makeKey() {
		string res = "";
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				res += to_string(_state[i][j]);
			}
		}
		//cout << res << endl;
		return res;
	}

};

struct Compare_Cost {
	bool operator()(Node const & n1, Node const & n2) {
		return n1._cost > n2._cost;
	}
};

//Checks if a nodes state matches the goal state.
bool Is_Goal(Node const & n) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (n._state[i][j] != goal[i][j])
				return false;
		}
	}
	return true;
}

//finds the index in the goal state
pair<int, int> Find_Index(int val) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (goal[i][j] == val){
				return pair<int, int>(i, j);
			}
				
		}
	}
}

//Calculate heuristic for one node. The heuristic is the sum of all tiles different
//from the goal board.
void Heuristic(Node & n) {

	//h1
	/*int counter = 0;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {

			if (n._state[i][j] != goal[i][j]) {
				++counter;
			}
		}
	}
	n._h = counter;*/
	//h2
	int dist = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			pair<int, int> goal_index = Find_Index(n._state[i][j]);
			
			int distX = abs(i - goal_index.first);
			int distY = abs(j - goal_index.second);
			dist = dist + distX + distY;	
		}
	}
	n._h = dist;
	



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
	set<string> closed_list;
	//closed_list.emplace(open_list.top()._state);

	while (!open_list.empty()) {
		//Retrieve the first node in the queue
		Node first = open_list.top();
		open_list.pop();
		closed_list.emplace(first.makeKey()); //the node has been visited
		
		if (Is_Goal(first)) {
			return first._movement;
		}
		else {
			//Generate children for the node;
			vector<Node> children = Gen_Successors(first);
			//cout << "-------------" << endl;
			for (auto s : children) {
				if (closed_list.find(s.makeKey()) != closed_list.end()) {
					continue;
				}
				Compute_Cost(s);
				open_list.push(s);
			}

			
		}
	}

	return "No solution found.";
}




int main() {
	cout << "Starting puzzle" << endl;
	Node start;


	priority_queue<Node, vector<Node>, Compare_Cost> open_list;
	open_list.push(start);

	vector<Node> c = Gen_Successors(start);

	string res = A_Star(start);
	cout << "Solution found. Number of steps: " << res.size()  << endl;
	cout << "Moves: " << res << endl;
	cout << "Puzzle complete.";

	int n;
	cin >> n;
}