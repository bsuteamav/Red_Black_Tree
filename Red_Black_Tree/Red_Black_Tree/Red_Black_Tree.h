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
		root->left = nullptr;
		root->right = nullptr;
		root->color = BLACK; //constantly for the root
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
	            Tree->left->left = nullptr;
	            Tree->left->right = nullptr;
	            Tree->color = RED;
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
                Tree->right->left = nullptr;
                Tree->right->right = nullptr;
                Tree->color = RED;
            }
        }
	}
}

template<typename T>
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