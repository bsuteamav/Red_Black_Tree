#pragma once

#include "Node.h"
#include "Rotations_Deletion.h"

enum CASES { LL = 0, LR, RR, RL };

// DELETION

template<typename T>
int calculateCaseDeletion(Node<T>* currentNode) {
	// sibling S - right son
	if (currentNode->parent->left == currentNode) {
		// red child R - right son -> RR case deletion
		if (currentNode->parent->right->right != nullptr) {
			return RR;
		}
		// red child R - left son -> RL case deletion
		else {
			return RL;
		}
	}
	// sibling S - left son
	else {
		// red child R - right son-> LR case deletion
		if (currentNode->parent->right->right != nullptr) {
			return LR;
		}
		// red child R - left son -> LL case deletion
		else {
			return LL;
		}
	}
}

template<typename T>
bool performRotation_Deletion(Node<T>*& currentNode) {
	bool isChangeRoot;
	int rotationsCase = calculateCaseDeletion(currentNode);

	switch (rotationsCase) {
	case LL:
		isChangeRoot = LeftLeftCase_Rotations_Deletion(currentNode->parent->left->left);
		break;
	case LR:
		isChangeRoot = LeftRightCase_Rotations_Deletion(currentNode->parent->left->right);
		break;
	case RR:
		isChangeRoot = RightRightCase_Rotations_Deletion(currentNode->parent->right->right);
		break;
	case RL:
		isChangeRoot = RightLeftCase_Rotations_Deletion(currentNode->parent->right->left);
		break;
	}
	return isChangeRoot;
}
