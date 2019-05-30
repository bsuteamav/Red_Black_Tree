#pragma once
#include "Node.h"

using namespace std;

// DELETION; cases 1 - 4
template<typename T>
bool LeftLeftCase_Rotations_Deletion(Node<T>* sonOfSibling);

template<typename T>
bool LeftRightCase_Rotations_Deletion(Node<T>* sonOfSibling);

template<typename T>
bool RightRightCase_Rotations_Deletion(Node<T>* sonOfSibling);

template<typename T>
bool RightLeftCase_Rotations_Deletion(Node<T>* sonOfSibling);

template<typename T>
inline bool LeftLeftCase_Rotations_Deletion(Node<T>* sonOfSibling)
{
	// change color of sibling's right son
	sonOfSibling->color = BLACK;
	bool isChangeRoot = RightRotation(sonOfSibling);
	return isChangeRoot;
}

template<typename T>
inline bool LeftRightCase_Rotations_Deletion(Node<T>* sonOfSibling)
{
	// change color 
	sonOfSibling->right->color = BLACK;

	/* P's right son = X's left son
	   X's left son's parent = P
	*/
	sonOfSibling->parent->right = sonOfSibling->left;
	// X's left son != nullptr
	if (sonOfSibling->left != nullptr) {
		sonOfSibling->left->parent = sonOfSibling->parent;
	}

	/* X's left son = P
	   X's parent = G
	*/
	sonOfSibling->left = sonOfSibling->parent;
	sonOfSibling->parent = sonOfSibling->parent->parent;

	/* P's parent = X
	   G's left son = X
	*/
	sonOfSibling->left->parent = sonOfSibling;
	sonOfSibling->parent->left = sonOfSibling;

	// call LL case for P (X's left son)
	bool isChangeRoot = RightRotation(sonOfSibling->left);
	return isChangeRoot;
}

template<typename T>
inline bool RightRightCase_Rotations_Deletion(Node<T>* sonOfSibling)
{
	sonOfSibling->color = BLACK;
	bool isChangeRoot = LeftRotation(sonOfSibling);
	return isChangeRoot;
}

template<typename T>
inline bool RightLeftCase_Rotations_Deletion(Node<T>* sonOfSibling)
{
	// change color
	sonOfSibling->color = BLACK;
	// right rotate P
	sonOfSibling->parent->left = sonOfSibling->right;
	sonOfSibling->right = sonOfSibling->parent;
	sonOfSibling->parent = sonOfSibling->right->parent;
	sonOfSibling->right->parent = sonOfSibling;
	if (sonOfSibling->right->left != nullptr) {
		sonOfSibling->right->left->parent = sonOfSibling->right;
	}
	sonOfSibling->parent->right = sonOfSibling;

	// right right case for X's previous Parent (now X's right son = P)
	bool isChangeRoot = LeftRotation(sonOfSibling->right);
	return isChangeRoot;
}
