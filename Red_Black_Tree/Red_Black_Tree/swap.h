#pragma once

#include "Node.h"

template<typename T>
void swapColors(Node<T>* x1, Node<T>* x2) {
	COLORS temp;
	temp = x1->color;
	x1->color = x2->color;
	x2->color = temp;
}

template<typename T>
void swapValues(Node<T>* u, Node<T>* v) {
	T temp;
	temp = u->key;
	u->key = v->key;
	v->key = temp;
}