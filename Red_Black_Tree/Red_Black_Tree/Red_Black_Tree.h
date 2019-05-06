#pragma once

#include <iostream>
#include "Node.h"
#include "Calculate.h"

using namespace std;

template<typename T>
class Red_Black_Tree {
private:
    Node<T>* root;

    void addNode(T data, Node<T>*& Tree);
    void show(Node<T>*& Tree);
    void balance(Node<T>*& Tree);
	void cleanup(Node<T>* tree); // for destructor
public:
    Red_Black_Tree();
    void addNode(T data);
    void show();
    ~Red_Black_Tree();
};

template <typename T>
Red_Black_Tree<T>::Red_Black_Tree() {
    root = nullptr;
}

template <typename T>
Red_Black_Tree<T>::~Red_Black_Tree() {
	cleanup(this->root);
}

template <typename T>
void Red_Black_Tree<T>::addNode(T data) {
    this->addNode(data, root);
}

template <typename T>
void Red_Black_Tree<T>::addNode(T data, Node<T> *&Tree) {
    //if tree is empty
    if(root == nullptr){
        root = new Node<T>;
        root->key = data;
        root->parent = nullptr;
        root->color = BLACK; //constantly for the root
        root->left = nullptr;
        root->right = nullptr;
        //new node is the root - don't need to do balance
    }
    else{
        //left subtree
        if(data < Tree->key){
            if(Tree->left != nullptr){
                addNode(data, Tree->left);
            }
            else{
                Tree->left = new Node<T>;
                Tree->left->key = data;
                Tree->left->parent = Tree;
                Tree->left->color = RED;
                Tree->left->left = nullptr;
                Tree->left->right = nullptr;

				// call balance function for X (tree's left son)
                balance(Tree->left);
            }
        }
        //right subtree
        else if(data > Tree->key){
            if(Tree->right != nullptr){
                addNode(data, Tree->right);
            }
            else{
                Tree->right = new Node<T>;
                Tree->right->key = data;
                Tree->right->parent = Tree;
                Tree->right->color = RED;
                Tree->right->left = nullptr;
                Tree->right->right = nullptr;

                balance(Tree->right);
            }
        }
    }
}

template <typename T>
void Red_Black_Tree<T>::balance(Node<T> *&Son) {
	if (Son == root) {
		Son->color = BLACK;
		return;
	}

    if(Son != root) {
        if (Son->parent->color != BLACK) {
            //if uncle is a Tree->parent->right
            if (Son->parent == Son->parent->parent->left) {
                //therefore uncle is a Son->parent->parent->right
                if (Son->parent->parent->right != nullptr) {
                    if (Son->parent->parent->right->color == RED) {
                        //case 3a) full

                        //Change color of parent and uncle as BLACK
                        Son->parent->color = BLACK;                 //change color of parent
                        Son->parent->parent->right->color = BLACK;  //change color of uncle

                        //color of grand parent as RED
                        Son->parent->parent->color = RED;

                        //Change x = x’s grandparent, repeat steps 2 and 3 for new x.
                        //new x = Son->parent->parent
                        balance(Son->parent->parent);

                    } 
					else if (Son->parent->parent->right->color == BLACK) {
                        //case 3b) rotations
                        performRotation(Son);
                    }
                }
                //uncle = nullptr
                else {
                    //case 3b) rotations
                    performRotation(Son);
                }
            }

            //if uncle is a Tree->parent->left
            else if (Son->parent == Son->parent->parent->right) {
                //therefore uncle is a Son->parent->parent->left
                if (Son->parent->parent->left != nullptr) {
                    if (Son->parent->parent->left->color == RED) {

                        //case 3a) full
                        //Change color of parent and uncle as BLACK
                        Son->parent->color = BLACK;                 //change color of parent
                        Son->parent->parent->left->color = BLACK;   //change color of uncle

                        //color of grand parent as RED
                        Son->parent->parent->color = RED;

                        //Change x = x’s grandparent, repeat steps 2 and 3 for new x.
                        //new x = Son->parent->parent
                        balance(Son->parent->parent);

                    } 
					else if (Son->parent->parent->right->color == BLACK) {
                        //case 3b) rotations
                        performRotation(Son);
                    }
                }
                //uncle = nullptr
                else {
                    //case 3b) rotations
					performRotation(Son);
                }
            }
        }
    }
}

template<typename T>
inline void Red_Black_Tree<T>::cleanup(Node<T>* tree)
{
	if (tree != nullptr) {
		cleanup(tree->left);
		cleanup(tree->right);
		delete tree;
	}
}

template <typename T>
void Red_Black_Tree<T>::show()
{
    this->show(this->root);
}

template <typename T>
void Red_Black_Tree<T>::show(Node<T>*& Tree) {
    if(Tree != nullptr){
        show(Tree->left);
        cout << Tree->key << " - " << Tree->color << " ";
        show(Tree->right);
    }
}