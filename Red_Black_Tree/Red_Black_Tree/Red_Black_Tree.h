#pragma once

#include <iostream>
#include "Node.h"
#include "Calculate.h"
#include "swap.h"

using namespace std;

template<typename T>
class Red_Black_Tree {
private:
    Node<T>* root;

    void addNode(T data, Node<T>*& Tree);
    void show(Node<T>*& Tree);
	Node<T>* search(T data, Node<T>* Tree);
    void balance(Node<T>*& Tree);
	void cleanup(Node<T>* tree); // for destructor

	void leftRotate(Node<T>* x);
	void rightRotate(Node<T>* x);
	Node<T>* predecessor(Node<T>* x);
	Node<T>* BSTreplace(Node<T>* x);
	void fixDoubleBlack(Node<T>* x);
	void deleteNode(Node<T>* v);
	
public:
	int getHeight(Node<T>* x) const;
	Node<T>* getRoot() const;

public:
    Red_Black_Tree();
    void addNode(T data);
	void deleteNode(T data);
	Node<T>* search(T data);
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

template<typename T>
inline void Red_Black_Tree<T>::deleteNode(T data)
{
	if (root == nullptr) {
		// tree is empty
		return;
	}
	Node<T>* v = search(data, this->root);

	if (v->key != data) {
		cout << "There isn't node with this value:\n";
		return;
	}

	deleteNode(v);
}

template<typename T>
inline Node<T>* Red_Black_Tree<T>::search(T data)
{
	return this->search(data, this->root);
}

template <typename T>
void Red_Black_Tree<T>::addNode(T data, Node<T> *&Tree) {
    //if tree is empty
    if (root == nullptr) {
        root = new Node<T>;
        root->key = data;
        root->parent = nullptr;
        root->color = BLACK; //constantly for the root
        root->left = nullptr;
        root->right = nullptr;
        //new node is the root - don't need to do balance
    }
    else {
        //left subtree
        if (data < Tree->key) {
            if (Tree->left != nullptr) {
                addNode(data, Tree->left);
            }
            else {
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
        else if (data > Tree->key) {
            if (Tree->right != nullptr) {
                addNode(data, Tree->right);
            }
            else {
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
	bool isChangeRoot;
	if (Son == root) {
		Son->color = BLACK;
		return;
	}

    if (Son != root) {
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
						/*TRUE - no need to change root;
						FALSE - need to change root on addedNode->parent*/
                        isChangeRoot = performRotation(Son);
						if (!isChangeRoot) {
							root = Son->parent;
						}
                    }
                }
                //uncle = nullptr
                else {
                    //case 3b) rotations
					/*TRUE - no need to change root;
					FALSE - need to change root on addedNode->parent*/
					isChangeRoot = performRotation(Son);
					if (!isChangeRoot) {
						root = Son->parent;
					}
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
					else if (Son->parent->parent->left->color == BLACK) {
                        //case 3b) rotations
						/*TRUE - no need to change root;
						FALSE - need to change root on addedNode->parent*/
                        isChangeRoot = performRotation(Son);
						if (!isChangeRoot) {
							root = Son->parent;
						}
                    }
                }
                //uncle = nullptr
                else {
                    //case 3b) rotations
					/*TRUE - no need to change root;
					FALSE - need to change root on addedNode->parent*/
					isChangeRoot = performRotation(Son);
					if (!isChangeRoot) {
						root = Son->parent;
					}
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

template<typename T>
inline void Red_Black_Tree<T>::leftRotate(Node<T>* x)
{
	// new parent will be node's right child 
	Node<T>* nParent = x->right;

	// update root if current node is root 
	if (x == root)
		root = nParent;

	x->moveDown(nParent);

	// connect x with new parent's left element 
	x->right = nParent->left;
	// connect new parent's left element with node 
	// if it is not null 
	if (nParent->left != nullptr)
		nParent->left->parent = x;

	// connect new parent with x 
	nParent->left = x;
}

template<typename T>
inline void Red_Black_Tree<T>::rightRotate(Node<T>* x)
{
	// new parent will be node's left child 
	Node<T>* nParent = x->left;

	// update root if current node is root 
	if (x == root)
		root = nParent;

	x->moveDown(nParent);

	// connect x with new parent's right element 
	x->left = nParent->right;
	// connect new parent's right element with node 
	// if it is not null 
	if (nParent->right != nullptr)
		nParent->right->parent = x;

	// connect new parent with x 
	nParent->right = x;
}

template<typename T>
inline Node<T>* Red_Black_Tree<T>::predecessor(Node<T>* x)
{
	Node<T>* temp = x;
	while (temp->right != nullptr) {
		temp = temp->right;
	}
	return temp;
}

template<typename T>
inline Node<T>* Red_Black_Tree<T>::BSTreplace(Node<T>* x)
{
	// when node have 2 children 
	if (x->left != nullptr and x->right != nullptr)
		return predecessor(x->left);

	// when leaf 
	if (x->left == nullptr and x->right == nullptr)
		return nullptr;

	// when single child 
	if (x->left != nullptr)
		return x->left;
	else
		return x->right;
}

template<typename T>
inline void Red_Black_Tree<T>::fixDoubleBlack(Node<T>* x)
{
	if (x == root)
		// Reached root 
		return;

	Node<T>* sibling = x->sibling();
	Node<T>* parent = x->parent;
	if (sibling == nullptr) {
		// No sibiling, double black pushed up 
		fixDoubleBlack(parent);
	}
	else {
		if (sibling->color == RED) {
			// Sibling red 
			parent->color = RED;
			sibling->color = BLACK;
			if (sibling->isOnLeft()) {
				// left case 
				rightRotate(parent);
			}
			else {
				// right case 
				leftRotate(parent);
			}
			fixDoubleBlack(x);
		}
		else {
			// Sibling black 
			if (sibling->hasRedChild()) {
				// at least 1 red children 
				if (sibling->left != nullptr && sibling->left->color == RED) {
					if (sibling->isOnLeft()) {
						// left left 
						sibling->left->color = sibling->color;
						sibling->color = parent->color;
						rightRotate(parent);
					}
					else {
						// right left 
						sibling->left->color = parent->color;
						rightRotate(sibling);
						leftRotate(parent);
					}
				}
				else {
					if (sibling->isOnLeft()) {
						// left right 
						sibling->right->color = parent->color;
						leftRotate(sibling);
						rightRotate(parent);
					}
					else {
						// right right 
						sibling->right->color = sibling->color;
						sibling->color = parent->color;
						leftRotate(parent);
					}
				}
				parent->color = BLACK;
			}
			else {
				// 2 black children 
				sibling->color = RED;
				if (parent->color == BLACK)
					fixDoubleBlack(parent);
				else
					parent->color = BLACK;
			}
		}
	}
}

template<typename T>
inline void Red_Black_Tree<T>::deleteNode(Node<T>* v)
{
	Node<T>* u = BSTreplace(v);

	// True when u and v are both black 
	bool uvBlack = ((u == nullptr || u->color == BLACK) && (v->color == BLACK));
	Node<T>* parent = v->parent;

	if (u == nullptr) {
		// u is nullptr therefore v is leaf 
		if (v == root) {
			// v is root, making root null 
			root = nullptr;
		}
		else {
			if (uvBlack) {
				// u and v both black 
				// v is leaf, fix double black at v 
				fixDoubleBlack(v);
			}
			else {
				// u or v is red 
				if (v->sibling() != nullptr) {
					// sibling is not null, make it red" 
					v->sibling()->color = RED;
				}
			}

			// delete v from the tree 
			if (v->isOnLeft()) {
				parent->left = nullptr;
			}
			else {
				parent->right = nullptr;
			}
		}
		delete v;
		return;
	}

	if (v->left == nullptr || v->right == nullptr) {
		// v has 1 child 
		if (v == root) {
			// v is root, assign the value of u to v, and delete u 
			v->key = u->key;
			v->left = v->right = nullptr;
			delete u;
		}
		else {
			// Detach v from tree and move u up 
			if (v->isOnLeft()) {
				parent->left = u;
			}
			else {
				parent->right = u;
			}
			delete v;
			u->parent = parent;
			if (uvBlack) {
				// u and v both black, fix double black at u 
				fixDoubleBlack(u);
			}
			else {
				// u or v red, color u black 
				u->color = BLACK;
			}
		}
		return;
	}

	// v has 2 children, swap values with predecessor and recurse 
	swapValues(u, v);
	deleteNode(u);

}

template<typename T>
inline int Red_Black_Tree<T>::getHeight(Node<T>* x) const
{
	if (root == nullptr) {
		return 0;
	}

	// find the height of each subtree
	int lh = getHeight(x->left);
	int rh = getHeight(x->right);

	return 1 + max(lh, rh);
}

template<typename T>
inline Node<T>* Red_Black_Tree<T>::getRoot() const
{
	return this->root;
}



template <typename T>
void Red_Black_Tree<T>::show()
{
    this->show(this->root);
}

template <typename T>
void Red_Black_Tree<T>::show(Node<T>*& Tree) {
    if (Tree != nullptr) {
        show(Tree->left);
		cout << Tree->key;
		if (Tree->color == BLACK) {
			cout << " - BLACK\n";
		}
		else {
			cout << " - RED\n";
		}
        show(Tree->right);
    }
}

template<typename T>
inline Node<T>* Red_Black_Tree<T>::search(T data, Node<T>* Tree)
{
	// if data wasn't found
	if (Tree == nullptr) {
		return nullptr;
	}

	else {
		if (Tree->key == data) {
			return Tree;
		}
		// data < Tree->data
		else if (data < Tree->key) {
			if (Tree->left != nullptr) {
				return search(data, Tree->left);
			}
			else {
				return nullptr;
			}
		}

		// data > Tree->data
		else {
			if (Tree->right != nullptr) {
				return search(data, Tree->right);
			}
			else {
				return nullptr;
			}
		}
	}
}
