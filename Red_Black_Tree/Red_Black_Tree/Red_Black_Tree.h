#pragma once

#include <iostream>
#include "Node.h"

using namespace std;

template<typename T>
class Red_Black_Tree {
private:
	Node<T>* root;

	void addNode(T data, Node<T>*& Tree);
    void show(Node<T>*& Tree);
    void balance(Node<T>*& Tree);

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
    root = nullptr;
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
        //nullLeaves
        root->left = new Node<T>; //nullLeaf (color and parent)
        root->left->color = BLACK;
        root->left->parent = root;
        root->right = new Node<T>; //nullLeaf (color and parent)
        root->right->color = BLACK;
        root->right->parent = root;
		//new node is the root - needn't to do balance
	}
	else{
	    //left branch
	    if(data < Tree->key){
	        if(Tree->left != nullptr){
	            addNode(data, Tree->left);
	        }
	        else{
	            Tree->left = new Node<T>;
	            Tree->left->key = data;
	            Tree->left->parent = Tree;
	            Tree->left->color = RED;
                //nullLeaves
                Tree->left->left = new Node<T>;
                Tree->left->left->color = BLACK;
                Tree->left->left->parent = Tree->left;
                Tree->left->right = new Node<T>;
                Tree->left->right->color = BLACK;
                Tree->left->right->parent = Tree->left;

	            if(Tree->color != BLACK) {   //if color of x’s parent is not BLACK
                    balance(Tree);           //balance for a new node(left son)
                }
	        }
	    }
	    //right branch
        else if(data > Tree->key){
            if(Tree->right != nullptr){
                addNode(data, Tree->right);
            }
            else{
                Tree->right = new Node<T>;
                Tree->right->key = data;
                Tree->right->parent = Tree;
                Tree->right->color = RED;
                //nullLeaves
                Tree->right->left = new Node<T>;
                Tree->right->left->color = BLACK;
                Tree->right->left->parent = Tree->right;
                Tree->right->right = new Node<T>;
                Tree->right->right->color = BLACK;
                Tree->right->right->parent = Tree->right;

                if(Tree->color != BLACK) {  //if color of x’s parent is not BLACK
                    balance(Tree);          //balance for a new node(right son)
                }
            }
        }
	}
}

template <typename T>
void Red_Black_Tree<T>::balance(Node<T> *&Tree) {   //Tree is a parent of the new node!


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
        cout << Tree->key << " - " << Tree->color << " ";   //color for a test
        show(Tree->right);
    }
}