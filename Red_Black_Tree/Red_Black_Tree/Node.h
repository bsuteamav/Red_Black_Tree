#pragma once

enum COLORS { BLACK = 0, RED = 1 };

template <typename T>
struct Node {
	T key;
	Node<T>* previous;
	Node<T>* left;
	Node<T>* right;
	bool color;
	int height;
	int	depth;
};