#pragma once

#include <iostream>
#include "Node.h"
#include "Calculate_Insertion.h"
#include "Calculate_Deletion.h"

using namespace std;

template<typename T>
class Red_Black_Tree {
private:
    Node<T>* root;

    void addNode(T data, Node<T>*& Tree);
	void deleteNode(T data, Node<T>*& Tree);
    void show(Node<T>*& Tree);
	Node<T>* search(T data, Node<T>* Tree);
    void balance(Node<T>*& Tree);
	void cleanup(Node<T>* tree); // for destructor
public:
    Red_Black_Tree();
    void addNode(T data);
	void deleteNode(T data);
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
	this->deleteNode(data, this->root);
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

template<typename T>
inline void Red_Black_Tree<T>::deleteNode(T data, Node<T>*& Tree)
{
	// look for the node to be deleted
	Node<T>* findedNode = search(data, Tree);

	// if there is no such node in the tree
	if (findedNode == nullptr) {
		return;
	}

	// node to be deleted was found;
	
	bool isFindedDoubleBlack = false; // needed when we need to delete black node
	Node<T>* nodeToDelete = nullptr; // node that we will really delete

	// case 1: finded node doesn't have children
	if (findedNode->left == nullptr && findedNode->right == nullptr) {
		// node is red -> simply delete it
		if (findedNode->color == RED) {
			// findedNode is left child
			if (findedNode->parent->left == findedNode) {
				findedNode->parent->left = nullptr;
			}
			// finded Node is right child
			else {
				findedNode->parent->right = nullptr;
			}
			delete findedNode;
		}
		// node is black -> we mark that we need to delete black node
		else {
			isFindedDoubleBlack = true;
			nodeToDelete = findedNode;
		}
	}

	// case 2: finded Node has only one child (in this case son is always red and node is always black, so we dont need to recolor)
	else if ((findedNode->left != nullptr && findedNode->right == nullptr) ||
		(findedNode->left == nullptr && findedNode->right != nullptr)) {
		// left son of findedNode != nullptr
		if (findedNode->left != nullptr) {

			// findedNode != root
			if (findedNode != this->root) {
				// finded node is left son
				if (findedNode->parent->left == findedNode) {
					findedNode->parent->left = findedNode->left;
				}
				// finded node is right son
				else {
					findedNode->parent->right = findedNode->left;
				}

				findedNode->left->parent = findedNode->parent;
				findedNode->left->color = BLACK;
				delete findedNode;
			}

			// finded node == root
			else {
				findedNode->key = findedNode->left->key;
				delete findedNode->left;
				findedNode->left = nullptr;
			}
		}
		// right son of findedNode != nullptr
		else {

			// findedNode != root
			if (findedNode != this->root) {
				// findedNode is left son
				if (findedNode->parent->left == findedNode) {
					findedNode->parent->left = findedNode->right;
				}
				// findedNode is right son
				else {
					findedNode->parent->right = findedNode->right;
				}

				findedNode->right->parent = findedNode->parent;
				findedNode->right->color = BLACK; // recolor
				delete findedNode;
			}
			// findedNode == root
			else {
				findedNode->key = findedNode->right->key;
				delete findedNode->right;
				findedNode->right = nullptr;
			}
		}
	}

	// case 3: finded Node has both children
	else {
		// we go to the left subtree and find the rightest elem
		nodeToDelete = findedNode->left;
		while (nodeToDelete->right) {
			nodeToDelete = nodeToDelete->right;
		}
		findedNode->key = nodeToDelete->key;

		// if node to delete has son -> son is left child and son's color = red
		if (nodeToDelete->left != nullptr) {
			// node to delete is root of left subtree
			if (findedNode->left == nodeToDelete) {
				findedNode->left = nodeToDelete->left; // left son of finded node = left son of node to delete
				nodeToDelete->left->parent = findedNode;
				nodeToDelete->left->color = BLACK; // recolor son of nodeToDelete in BLACK
				delete nodeToDelete;
			}
			// node to delete isn't root of left subtree
			else {
				nodeToDelete->parent->right = nodeToDelete->left; // left son of nodeToDelete becomes right son of nodeToDelete's parent
				nodeToDelete->left->parent = nodeToDelete->parent;
				nodeToDelete->left->color = BLACK;
				delete nodeToDelete;
			}
		}
		// if node to delete doesn't have son
		else {
			// if node to delete has RED color -> we simply delete it from tree
			if (nodeToDelete->color == RED) {
				nodeToDelete->parent->right = nullptr; // nodeToDelete was the rightest elem -> we need to make his parent's right = nullptr
				delete nodeToDelete;
			}
			// if node to delete has BLACK color -> we mark that we need to delete black node
			else {
				isFindedDoubleBlack = true;
			}
		}
	}

	// here cases when there is double black in tree
	if (isFindedDoubleBlack) {
		Node<T>* DoubleBlackLeaf = new Node<T>;
		bool isChangeRoot;

		// initialization of Double Black Leaf
		DoubleBlackLeaf->isDoubleBlack = true;
		DoubleBlackLeaf->left = nullptr;
		DoubleBlackLeaf->right = nullptr;
		DoubleBlackLeaf->parent = nodeToDelete->parent; // if we get in this IF, than nodeToDelete isn't nullptr
		// nodeToDelete is left son
		if (nodeToDelete->parent->left == nodeToDelete) {
			nodeToDelete->parent->left = DoubleBlackLeaf;
		}
		// nodeToDelete is right son
		else {
			nodeToDelete->parent->right = DoubleBlackLeaf;
		}
		delete nodeToDelete;
		nodeToDelete = nullptr;

		Node<T>* currentNode = DoubleBlackLeaf;

		// case 3.2 full
		while (currentNode->isDoubleBlack == true && currentNode != root) {

			// sibling is right son
			if (currentNode->parent->left == currentNode) {

				// case 3.2 a)

				// sibling is black and at least one of his children is red
				if (currentNode->parent->right->color == BLACK &&
					(currentNode->parent->right->right != nullptr ||
						currentNode->parent->right->left != nullptr)) {
					
					/*TRUE - no need to change root;
					FALSE - need to change root on addedNode->parent->parent*/
					isChangeRoot = performRotation_Deletion(currentNode);
					if (!isChangeRoot) {
						root = currentNode->parent->parent;
					}

					// if currentNode == DoubleBlack leaf -> we delete DoubleBlack leaf
					if (currentNode == DoubleBlackLeaf) {
						DoubleBlackLeaf->parent->left = nullptr;
						delete DoubleBlackLeaf;
						DoubleBlackLeaf = nullptr;
					}
					currentNode->isDoubleBlack = false; // we did rotation -> tree is balanced
				}

				// case 3.2 b)
				
				// sibling is black and both children are black
				else if (currentNode->parent->right->color == BLACK &&
					currentNode->parent->right->right == nullptr &&
					currentNode->parent->right->left == nullptr) {


					currentNode->parent->right->color = RED; // recoloring sibling
					currentNode->isDoubleBlack = false;

					// if parent was red, we didn't need to recur for parent, we just make it black
					if (currentNode->parent->color == RED) {
						currentNode->parent->color = BLACK;
						currentNode->isDoubleBlack = false;
					}
					// parent was black -> we recur for parent
					else {
						currentNode = currentNode->parent; // recur for currentNode->parent
						currentNode->isDoubleBlack = true;
					}

					// first recur -> we need to delete doubleBlack leaf
					if (DoubleBlackLeaf != nullptr) {
						currentNode->left = nullptr;
						delete DoubleBlackLeaf;
						DoubleBlackLeaf = nullptr;
					}

				}

				// case 3.2 c)

				// sibling is red
				else if (currentNode->parent->right->color == RED) {

					// TODO : finish this method

				}
			}

			// sibling is left son
			else {

				// case 3.2 a)

				// sibling is black and at least one of his children is red
				if (currentNode->parent->left->color == BLACK &&
					(currentNode->parent->left->left != nullptr ||
						currentNode->parent->left->right != nullptr)) {

					/*TRUE - no need to change root;
					FALSE - need to change root on addedNode->parent->parent*/
					isChangeRoot = performRotation_Deletion(currentNode);
					if (!isChangeRoot) {
						root = currentNode->parent->parent;
					}

					// if currentNode == DoubleBlack leaf -> we delete DoubleBlack leaf
					if (currentNode == DoubleBlackLeaf) {
						DoubleBlackLeaf->parent->right = nullptr;
						delete DoubleBlackLeaf;
					}
					currentNode->isDoubleBlack = false; // we did rotation -> tree is balanced

				}

				// case 3.2 b)

				// sibling is black and both children are black
				else if (currentNode->parent->left->color == BLACK &&
					currentNode->parent->left->right == nullptr &&
					currentNode->parent->left->left == nullptr) {

					currentNode->parent->left->color = RED; // recoloring sibling
					currentNode->isDoubleBlack = false;

					// if parent was red, we didn't need to recur for parent, we just make it black
					if (currentNode->parent->color == RED) {
						currentNode->parent->color = BLACK;
						currentNode->isDoubleBlack = false;
					}
					// parent was black -> we recur for parent
					else {
						currentNode = currentNode->parent; // recur for currentNode->parent
						currentNode->isDoubleBlack = true;
					}

					// first recur -> we need to delete doubleBlack leaf
					if (DoubleBlackLeaf != nullptr) {
						currentNode->right = nullptr;
						delete DoubleBlackLeaf;
						DoubleBlackLeaf = nullptr;
					}
				}

				// case 3.2 c)

				// sibling is red
				else if (currentNode->parent->left->color == RED) {

					// TODO: finish this method (sibling is left son)

				}
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
