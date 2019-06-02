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
	tree.addNode(7);
	tree.addNode(3);
	tree.addNode(18);
	tree.addNode(10);
	tree.addNode(22);
	tree.addNode(8);
	tree.addNode(11);
	tree.addNode(26);
	tree.addNode(2);
	tree.addNode(6);
	tree.addNode(13);

	cout << "Tree before deleting:\n";
	tree.show();

	cout << "\nDeleting 18:\n";
	tree.deleteNode(18);
	tree.show();

	cout << "\n\nDeleting 11\n";
	tree.deleteNode(11);
	tree.show();

	cout << "\n\nDeleting 3:\n";
	tree.deleteNode(3);
	tree.show();

	cout << "\n\nDeleting 10:\n";
	tree.deleteNode(10);
	tree.show();

	cout << "\n\nDeleting 22:\n";
	tree.deleteNode(22);
	tree.show();

	cout << "\n\nDeleting 13:\n";
	tree.deleteNode(13);
	tree.show();

	system("pause");
	return 0;
}
