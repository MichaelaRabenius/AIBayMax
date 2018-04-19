//#include <iostream>
//#include <vector>
//#include <deque>
//#include <string>
//#include <algorithm>
//#include <memory>
//#include <queue>
//
//using namespace std;
//
//struct Goal {
//	int array[3][3]{
//		{ 4,2,3 } ,
//		{ 6,5,1 },
//		{ 7,8,0 } };
//};
//
//struct Node{
//	Node(Matrix m, int depth, Node* parent, string move) : _state{ m }, _depth{ depth }, _parent{ parent }, _movement{move} {};
//
//	void setHeuristic() {
//		Goal goal;
//		h = h1(goal, _state);
//	}
//
//	//Node *_next = nullptr; //Node to nect -> breadth first
//	Node *_parent = nullptr;
//	Matrix _state;
//	int _depth;
//
//	float g, h;
//	float _cost;
//
//	string _movement = "";
//};
//
//int h1(Matrix goal, Matrix m){
//	int counter = 0;
//
//	for (int i = 0; i < 3; ++i) {
//		for (int j = 0; j < 3; ++j) {
//			if (m.array[i][j] != goal.array[i][j]) {
//				++counter;
//			}
//		}
//	}
//	return counter;
//}
//
//struct Matrix {
//	int array[3][3]{
//		{ 4,2,3 } ,
//		{ 6,5,1 },
//		{ 7,8,0 } };
//};
//
//void Successors(Node* n, deque<Node*>& NodeList) {
//
//	//generate successors
//	int row = 0, col = 0;
//	
//	for (int i = 0; i < 3; ++i) {
//		for (int j = 0; j < 3; ++j) {
//			
//			if (n->_state.array[i][j] == 0) {
//				row = i+1;
//				col = j+1;
//				break;
//			}
//		}
//	}
//
//	//Not row and col is with range [1 3]
//	if (row > 1) {
//		//Move up
//		Matrix m = n->_state;
//		std::swap(m.array[row - 1][col - 1], m.array[row - 2][col - 1]); //Swap values
//		Node* child = new Node(m, n->_depth + 1, n, n->_movement + "U");
//		child->g = n->g + 1;
//		NodeList.push_back(child);
//	}
//
//	if (row < 3) {
//		//Move down
//		Matrix m = n->_state;
//		std::swap(m.array[row - 1][col - 1], m.array[row][col - 1]); //Swap values
//		Node* child = new Node(m, n->_depth + 1, n, n->_movement + "B");
//		child->g = n->g + 1;
//		NodeList.push_back(child);
//	}
//
//	if (col > 1) {
//		//Move to the left
//		Matrix m = n->_state;
//		std::swap(m.array[row - 1][col - 1], m.array[row][col - 2]); //Swap values
//		Node* child = new Node(m, n->_depth + 1, n, n->_movement + "L");
//		child->g = n->g + 1;
//		NodeList.push_back(child);
//	}
//
//
//	if (col < 3) {
//		//Move to the right
//		Matrix m = n->_state;
//
//		//empty space <-> element to the right
//		std::swap(m.array[row - 1][col - 1], m.array[row-1][col]); //Swap values
//		Node* child = new Node(m, n->_depth + 1, n, n->_movement + "R");
//		child->g = n->g + 1;
//		NodeList.push_back(child);
//	}
//	
//	//Check the directions we can go in
//}
//
//string Astar(Matrix start, Goal goal) {
//	std::priority_queue<Node*> NodeList; //Open list
//	NodeList.push_back(new Node{ start, 0, nullptr , ""}); //Set the root of the tree and add it to the list
//	
//	// open / closed?
//
//	string solution{};
//	// pushback a move after every advancement
//	// push_backs each step (L,R,U,D) we make. 
//
//
//	while (true) {
//		if (NodeList.empty()) {
//			return nullptr;
//		}
//
//		//Take out first element
//		Node* first = NodeList.front();
//		NodeList.erase(NodeList.begin());
//
//		if (isGoal(goal, *first)) {
//			return "Solution found:" + first->_movement;
//		}
//		else {
//			Successors(first, NodeList);
//			NodeList = SortIn( NodeList);
//		}
//			
//
//	}
//}
//
//bool isGoal(Goal goal, Node n) {
//	for (int i = 0; i < 9; ++i) {
//		for (int j = 0; j < 9; ++j) {
//			if (n._state.array[i][j] != goal.array[i][j])
//				return false;
//		}
//	}
//	return true;
//}
//
//
//
//int main() {
//	
//	vector<Node*> tiles;
//
//	int Goal_state[3][3]{ 
//		{1,2,3} ,
//		{4,5,6}, 
//		{7,8,0} };
//
//
//}