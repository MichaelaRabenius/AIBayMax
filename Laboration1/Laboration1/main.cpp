#include <iostream>
#include <vector>
#include <deque>
#include <string>

using namespace std;

struct Node{
	Node(Matrix m, int depth, Node* parent) : _state{ m }, _depth{depth}, _parent{ parent } {};

	//Node *_next = nullptr; //Node to nect -> breadth first
	Node *_parent = nullptr;
	Matrix _state;
	int _depth;

	float g, h;
	float _cost;

	string movement = "";
};

struct Matrix {
	int array[3][3]{
		{ 4,2,3 } ,
		{ 6,5,1 },
		{ 7,8,0 } };
};

void Successors(Node n) {

	//generate successors
	int row = 0, col = 0;
	
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			
			if (n._state.array[i][j] == 0) {
				row = i+1;
				col = j+1;
				break;
			}
		}
	}

	if (row > 1) {
		//Move up
		

	}


	if (row < 3) {
		//Move down
	}


	if (col > 1) {
		//Move to the left
	}


	if (col < 3) {
		//Move to the right
	}
	



	//Check the directions we can go in



}

string Astar(Matrix start, Matrix goal) {
	Node startNode{ start, 0, nullptr};
	
	deque<Node> NodeList;
	NodeList.push_back(startNode);

	
	// open / closed?

	string solution{};
	// pushback a move after every advancement
	// push_backs each step (L,R,U,D) we make. 


	while (true) {
		if (NodeList.empty()) {
			return nullptr;
		}

		//Take out first element
		Node first = NodeList.front();
		NodeList.erase(NodeList.begin());

		if (isGoal(goal, first)) {
			return "Solution found";
		}
		else {
			NodeList = SortIn(Successors(Node), NodeList);
		}
			

	}
}

bool isGoal(int goal[], Node n) {
	for (int i = 0; i < 9; ++i) {
		if (n._state[i] != goal[i])
			return false;
	}
	return true;
}



int main() {
	
	vector<Node*> tiles;

	int Goal_state[3][3]{ 
		{1,2,3} ,
		{4,5,6}, 
		{7,8,0} };


}