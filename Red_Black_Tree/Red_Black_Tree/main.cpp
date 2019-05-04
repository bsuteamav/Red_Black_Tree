#include <iostream>
#include "Red_Black_Tree.h"
#include "Node.h"

using namespace std;


int main() {
	Red_Black_Tree<int> tree;
	tree.addNode(50);
	//tree.addNode(40);
	//tree.addNode(30);
	tree.addNode(60);
	//tree.addNode(80);
	tree.show();

	system("pause");
	return 0;
}