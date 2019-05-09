#pragma once

enum COLORS { BLACK = 0, RED = 1 };
enum ROTATE_CASES { LL = 0, LR, RR, RL };

template <typename T>
struct Node {
	T key;
	Node<T>* parent;
	Node<T>* left;
	Node<T>* right;
	bool color;
	int height;
	int	depth;
	bool isDoubleBlack = false;
};
