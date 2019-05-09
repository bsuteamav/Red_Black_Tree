#pragma once

#include "Node.h"
#include "Rotations_Insertion.h"

// INSERTION

template<typename T>
int calculateCase(Node<T>* addedNode){
    //if addedNode = left son
    if(addedNode == addedNode->parent->left){
        //if parent = left son
        if(addedNode->parent == addedNode->parent->parent->left)
            return 0;   //LeftLeftCase
        // if parent = right son
        else
            return 3;   //RightLeftCase
    }

    //if addedNode = right son
    else{
        //if parent = left son
        if(addedNode->parent == addedNode->parent->parent->left)
            return 1;   //LeftRightCase
            // if parent = right son
        else
            return 2;   //RightRightCase
    }
}

template <typename T>
bool performRotation(Node<T>*& addedNode){
	bool isChangeRoot;
    int rotationCase = calculateCase(addedNode);

    switch (rotationCase){
        case LL:
            isChangeRoot = LeftLeftCase_Rotations_Insertion(addedNode);
            break;
        case RL:
			isChangeRoot = RightLeftCase_Rotations_Insertion(addedNode);
            break;
        case LR:
			isChangeRoot = LeftRightCase_Rotations_Insertion(addedNode);
            break;
        case RR:
            isChangeRoot = RightRightCase_Rotations_Insertion(addedNode);
            break;
    }
	return isChangeRoot;
}
