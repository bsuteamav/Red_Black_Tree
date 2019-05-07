#pragma once
#include "Node.h"

using namespace std;

template<typename T>
void LeftRotation(Node<T>* addedNode);

template<typename T>
void RightRotation(Node<T>* addedNode);



// every Right Right Case without changing colors
template<typename T>
inline void LeftRotation(Node<T>* addedNode)
{
	addedNode->parent->parent->right = addedNode->parent->left;
	addedNode->parent->left = addedNode->parent->parent;
	if (addedNode->parent->left->right != nullptr) {
		addedNode->parent->left->right->parent = addedNode->parent->left;
	}

	addedNode->parent->parent = addedNode->parent->left->parent;
	addedNode->parent->left->parent = addedNode->parent;

	if (addedNode->parent->parent->left == addedNode->parent->left) {
		addedNode->parent->parent->left = addedNode->parent;
	}

	else {
		addedNode->parent->parent->right = addedNode->parent;
	}
}


// every Left Left Case without changing colors
template<typename T>
inline void RightRotation(Node<T>* addedNode)
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
	if (addedNode->parent->parent->parent != nullptr) {
		// GP's left son is G
		if (addedNode->parent->parent->parent->left == addedNode->parent->parent) {
			// P's parent = GP; GP's left son = P
			addedNode->parent->parent = addedNode->parent->parent->parent;
			addedNode->parent->parent->left = addedNode->parent;
		}
		// GP's right son is G
		else {
			// P's parent = GP; GP's right son = P
			addedNode->parent->parent = addedNode->parent->parent->parent;
			addedNode->parent->parent->right = addedNode->parent;
		}
	}
	// GP is nullptr
	else {
		addedNode->parent->parent = nullptr;
	}

	//  G's parent = P
	addedNode->parent->right->parent = addedNode->parent;
}


