#pragma once

enum COLORS { BLACK = 0, RED = 1 };
enum ROTATE_CASES { LL = 0, LR, RR, RL };

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

	// check if node is left child of parent
	bool isOnLeft() { return this == parent->left; }

	// returns pointer to uncle
	Node<T>* uncle() {
		// if no parent or grandparent, then no uncle
		if (parent == nullptr || parent->parent == nullptr) {
			return nullptr;
		}
		if (parent->isOnLeft()) {
			// uncle is on right
			return parent->parent->right;
		}
		else {
			// uncle is on left
			return parent->parent->left;
		}
	}

	// returns pointer to sibling
	Node<T>* sibling() {
		// sibling null if no parent
		if (parent == nullptr) {
			return nullptr;
		}
		// this node is left son -> sibling is right son of parent
		if (isOnLeft()) {
			return parent->right;
		}
		else {
			return parent->left;
		}
	}
};
