#pragma once

#include <iostream>
#include "Node.h"

using namespace std;

template<typename T>
void LeftLeftRotation(Node<T>* addedNode);

template<typename T>
void LeftRightRotation(Node<T>* addedNode);

template<typename T>
void RightRightRotation(Node<T>* addedNode) {
    addedNode->parent->parent->right = addedNode->parent->left;
    addedNode->parent->left = addedNode->parent->parent;
    if(addedNode->parent->left->right != nullptr)
        addedNode->parent->left->right->parent = addedNode->parent->left;

    addedNode->parent->left->color = RED;
    addedNode->parent->color = BLACK;

    addedNode->parent->parent = addedNode->parent->left->parent;
    addedNode->parent->left->parent = addedNode->parent;

    if(addedNode->parent->parent->left == addedNode->parent->left)
        addedNode->parent->parent->left = addedNode->parent;

    else
        addedNode->parent->parent->right = addedNode->parent;
}

template<typename T>
void RightLeftRotation(Node<T>* addedNode){
    //first part
    addedNode->parent->left = addedNode->right;
    addedNode->right = addedNode->parent;
    addedNode->parent = addedNode->right->parent;
    addedNode->right->parent = addedNode;
    if (addedNode->right->left != nullptr)
        addedNode->right->left->parent = addedNode->right;
    addedNode->parent->right = addedNode;


    RightRightRotation(addedNode->right);
    //second part
    /*addedNode->parent->right = addedNode->left;
    addedNode->left->parent = addedNode->parent;

    addedNode->left = addedNode->parent;
    addedNode->color = BLACK;
    addedNode->parent->color = RED;
    addedNode->parent = addedNode->left->parent;
    addedNode->left->parent = addedNode;

    if(addedNode->left == addedNode->parent->left)
        addedNode->parent->left = addedNode;

    else
        addedNode->parent->right = addedNode;*/
}