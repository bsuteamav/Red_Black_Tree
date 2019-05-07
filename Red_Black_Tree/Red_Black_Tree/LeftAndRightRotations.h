#pragma once
#include "Node.h"

using namespace std;

/* bool: 
	TRUE - no need to change root;
	FALSE - need to change root on addedNode->parent
*/

template<typename T>
bool LeftRotation(Node<T>* addedNode);

template<typename T>
bool RightRotation(Node<T>* addedNode);



// every Right Right Case without changing colors
template<typename T>
inline bool LeftRotation(Node<T>* addedNode)
{
	addedNode->parent->parent->right = addedNode->parent->left;
	addedNode->parent->left = addedNode->parent->parent;
	if (addedNode->parent->left->right != nullptr) {
		addedNode->parent->left->right->parent = addedNode->parent->left;
	}

	addedNode->parent->parent = addedNode->parent->left->parent;
	addedNode->parent->left->parent = addedNode->parent;

	// GP is not nullptr
	if (addedNode->parent->parent != nullptr) {

		// GP's left son is G
		if (addedNode->parent->parent->left == addedNode->parent->left) {
			addedNode->parent->parent->left = addedNode->parent;
		}

		// GP's right son is G
		else {
			addedNode->parent->parent->right = addedNode->parent;
		}

		// TRUE - no need to change root;
		return true;
	}

	// GP is nullptr -> we change root
	else {
		// FALSE - need to change root on addedNode->parent
		return false;
	}
}

// every Left Left Case without changing colors
template<typename T>
inline bool RightRotation(Node<T>* addedNode)
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

	// GP is nullptr -> we change root
	if (addedNode->parent->parent == nullptr) {
		return false;
	}
	return true;
}
