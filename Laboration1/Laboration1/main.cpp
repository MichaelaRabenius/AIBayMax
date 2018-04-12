#include <iostream>
#include <vector>

using namespace std;

struct Node{
	Node(int arr[], Node* next, Node* parent) : _state{ arr }, _next{next}, _parent{ parent } {};

	Node *_next = nullptr; //Node to nect -> breadth first
	Node *_parent = nullptr;
	int* _state;
	float _cost;
};

void Successors(Node n) {

}

String Astar(int start[], int goal[]) {
	Node startNode{ start };
	
	vector<Node> NodeList;
	NodeList.push_back(startNode);

	while (true) {
		if (NodeList.empty()) {
			return "No solutions found.";
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

	int Goal_state[]{ 1,2,3,4,5,6,7,8,0 };


}