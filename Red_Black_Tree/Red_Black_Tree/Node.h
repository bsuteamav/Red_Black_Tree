#pragma once

enum COLORS { BLACK = 0, RED = 1 };

template <typename T>
struct Node {
	T key;
	Node<T>* parent;
	Node<T>* left;
	Node<T>* right;
	bool color;
	int height;
	int	depth;
	bool isDoubleBlack = false;

	// returns pointer to uncle 
	Node<T>* uncle() {
		// If no parent or grandparent, then no uncle 
		if (parent == nullptr or parent->parent == nullptr)
			return nullptr;

		if (parent->isOnLeft())
			// uncle on right 
			return parent->parent->right;
		else
			// uncle on left 
			return parent->parent->left;
	}

	// check if node is left child of parent 
	bool isOnLeft() { return this == parent->left; }

	// returns pointer to sibling	
	Node<T>* sibling() {
		// sibling null if no parent 
		if (parent == nullptr)
			return nullptr;

		if (isOnLeft())
			return parent->right;

		return parent->left;
	}

	// moves node down and moves given node in its place 
	template<typename T>
	void moveDown(Node<T>* nParent) {
		if (parent != nullptr) {
			if (isOnLeft()) {
				parent->left = nParent;
			}
			else {
				parent->right = nParent;
			}
		}
		nParent->parent = parent;
		parent = nParent;
	}

	bool hasRedChild() {
		return (left != nullptr and left->color == RED) ||
			(right != nullptr and right->color == RED);
	}
};
