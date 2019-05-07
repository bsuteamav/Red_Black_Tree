#pragma once

#include "Node.h"
#include "Rotations.h"

enum CASES {LL = 0, LR, RR, RL};

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
void performRotation(Node<T>*& addedNode){
    int rotationCase = calculateCase(addedNode);

    switch (rotationCase){
        case LL:
            LeftLeftCase_Rotations_Insertion(addedNode);
            break;
        case RL:
            RightLeftCase_Rotations_Insertion(addedNode);
            break;
        case LR:
            LeftRightCase_Rotations_Insertion(addedNode);
            break;
        case RR:
            RightRightCase_Rotations_Insertion(addedNode);
            break;
    }
}
