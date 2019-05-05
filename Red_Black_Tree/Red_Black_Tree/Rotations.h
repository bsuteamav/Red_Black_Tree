#pragma once
#include "Node.h"

template<typename T>
void LeftLeftRotation(Node<T>*& addedNode);

template<typename T>
void LeftRightRotation(Node<T>*& addedNode);

template<typename T>
void RightRightRotation(Node<T>*& addedNode);

template<typename T>
void RightLeftRotation(Node<T>*& addedNode);



template<typename T>
inline void LeftLeftRotation(Node<T>*& addedNode)
{
	/* right son of parent becomes left son of grandparent;
	   grandparent becomes parent for right son of parent
	*/
	addedNode->parent->parent->left = addedNode->parent->right;
	addedNode->parent->right->parent = addedNode->parent->parent;
	
	// grandparent becomes right son of parent
	addedNode->parent->right = addedNode->parent->parent;

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

	//  G's parent = P
	addedNode->parent->right->parent = addedNode->parent;

	// swap colors of P and G
	addedNode->parent->color = BLACK;
	addedNode->parent->right->color = RED;
}

template<typename T>
inline void LeftRightRotation(Node<T>*& addedNode)
{
	/* P's right son = X's left son
	   X's left son's parent = P
	*/
	addedNode->parent->right = addedNode->left;
	addedNode->left->parent = addedNode->parent;

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
