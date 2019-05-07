#pragma once

#include <iostream>
#include "Node.h"
#include "LeftAndRightRotations.h"

using namespace std;

// INSERTION; cases 1 - 4
template<typename T>
void LeftLeftCase_Rotations_Insertion(Node<T>* addedNode);

template<typename T>
void LeftRightCase_Rotations_Insertion(Node<T>* addedNode);

template<typename T>
void RightRightCase_Rotations_Insertion(Node<T>* addedNode);

template<typename T>
void RightLeftCase_Rotations_Insertion(Node<T>* addedNode);


template<typename T>
inline void LeftLeftCase_Rotations_Insertion(Node<T>* addedNode)
{
	RightRotation(addedNode);

	// swap colors of P and G
	addedNode->parent->color = BLACK;
	addedNode->parent->right->color = RED;
}

template<typename T>
inline void LeftRightCase_Rotations_Insertion(Node<T>* addedNode)
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
	LeftLeftCase_Rotations_Insertion(addedNode->left);
}

template<typename T>
void RightRightCase_Rotations_Insertion(Node<T>* addedNode) {
	LeftRotation(addedNode);

	addedNode->parent->color = BLACK;
	addedNode->parent->left->color = RED;
}

template<typename T>
void RightLeftCase_Rotations_Insertion(Node<T>* addedNode) {
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
	RightRightCase_Rotations_Insertion(addedNode->right);
}
