#pragma once
#include "Node.h"

using namespace std;

// DELETION; cases 1 - 4
template<typename T>
void LeftLeftCase_Rotations_Deletion(Node<T>* addedNode);

template<typename T>
void LeftRightCase_Rotations_Deletion(Node<T>* addedNode);

template<typename T>
void RightRightCase_Rotations_Deletion(Node<T>* addedNode);

template<typename T>
void RightLeftCase_Rotations_Deletion(Node<T>* addedNode);
