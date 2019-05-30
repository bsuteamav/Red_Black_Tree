#include <iostream>
#include "Red_Black_Tree.h"
#include "Node.h"

using namespace std;


int main() {
	Red_Black_Tree<int> tree;
	//tree.addNode(50);
	//tree.addNode(40);
	//tree.addNode(70);
	//tree.addNode(30);
	//tree.addNode(35);
	//tree.addNode(100);
	//tree.addNode(150);
	//tree.addNode(80);
	//tree.addNode(130);
	//tree.addNode(200);
	//tree.addNode(60);
	//tree.addNode(10);
	//tree.addNode(45);
	//tree.addNode(155);
	//tree.addNode(160);
	//tree.addNode(5);
	//tree.addNode(250);
	//tree.addNode(4);
	//tree.addNode(3);
	//tree.addNode(2);
	//tree.addNode(58);
	//tree.addNode(59);
	

	// Left rotation (with root change)
	tree.addNode(50);
	tree.addNode(40);
	tree.addNode(70);
	tree.addNode(60);
	tree.addNode(80);
	tree.addNode(65);
	tree.addNode(68);
	tree.addNode(69);

	tree.addNode(64);

	tree.show();

	cout << "\n\nTree after deleting 40:\n";
	tree.deleteNode(40);
	tree.show();


	system("pause");
	return 0;
}
