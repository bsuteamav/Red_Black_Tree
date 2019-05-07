#pragma once

#include <iostream>
#include "Node.h"

using namespace std;

template<typename T>
void LeftLeftRotation(Node<T>* addedNode);

template<typename T>
void LeftRightRotation(Node<T>* addedNode);

template<typename T>
void RightRightRotation(Node<T>* addedNode);

template<typename T>
void RightLeftRotation(Node<T>* addedNode);



template<typename T>
inline void LeftLeftRotation(Node<T>* addedNode)
{
	/* right son of parent becomes left son of grandparent;
	   grandparent becomes parent for right son of parent
	*/
	addedNode->parent->parent->left = addedNode->parent->right;
	if (addedNode->parent->right != nullptr) {
		addedNode->parent->right->parent = addedNode->parent->parent;
	}

	// grandparent becomes right son of parent
	addedNode->parent->right = addedNode->parent->parent;

	// GP is not nullptr
	if (addedNode->parent->parent != nullptr) {
		// GP's left son is G
		if (addedNode->parent->parent->parent->left == addedNode->parent->parent) {
			// P's parent = GP; GP's left son = P
			addedNode->parent->parent = addedNode->parent->parent->parent;
			addedNode->parent->parent->parent->left = addedNode->parent;
		}
		// GP's right son is G
		else {
			// P's parent = GP; GP's right son = P
			addedNode->parent->parent = addedNode->parent->parent->parent;
			addedNode->parent->parent->parent->right = addedNode->parent;
		}
	}
	// GP is nullptr
	else {
		addedNode->parent->parent = nullptr;
	}

	//  G's parent = P
	addedNode->parent->right->parent = addedNode->parent;

	// swap colors of P and G
	addedNode->parent->color = BLACK;
	addedNode->parent->right->color = RED;
}

template<typename T>
inline void LeftRightRotation(Node<T>* addedNode)
{
	/* P's right son = X's left son
	   X's left son's parent = P
	*/
	addedNode->parent->right = addedNode->left;
	// X's left son != nullptr
	if (addedNode->left != nullptr) {
		addedNode->left->parent = addedNode->parent;
	}

	/* X's left son = P
	   X's parent = G
	*/
	addedNode->left = addedNode->parent;
	addedNode->parent = addedNode->parent->parent;

	/* P's parent = X
	   G's left son = X
	*/
	addedNode->left->parent = addedNode;
	addedNode->parent->left = addedNode;

	// call LL case for P (X's left son)
	LeftLeftRotation(addedNode->left);
}

template<typename T>
void RightRightRotation(Node<T>* addedNode) {
	addedNode->parent->parent->right = addedNode->parent->left;
	addedNode->parent->left = addedNode->parent->parent;
	if (addedNode->parent->left->right != nullptr) {
		addedNode->parent->left->right->parent = addedNode->parent->left;
	}

	addedNode->parent->left->color = RED;
	addedNode->parent->color = BLACK;

	addedNode->parent->parent = addedNode->parent->left->parent;
	addedNode->parent->left->parent = addedNode->parent;

	if (addedNode->parent->parent->left == addedNode->parent->left) {
		addedNode->parent->parent->left = addedNode->parent;
	}

	else {
		addedNode->parent->parent->right = addedNode->parent;
	}
}

template<typename T>
void RightLeftRotation(Node<T>* addedNode) {
	// right rotate P
	addedNode->parent->left = addedNode->right;
	addedNode->right = addedNode->parent;
	addedNode->parent = addedNode->right->parent;
	addedNode->right->parent = addedNode;
	if (addedNode->right->left != nullptr) {
		addedNode->right->left->parent = addedNode->right;
	}
	addedNode->parent->right = addedNode;

	// right right case for X's previous Parent (now X's right son = P)
	RightRightRotation(addedNode->right);
}
