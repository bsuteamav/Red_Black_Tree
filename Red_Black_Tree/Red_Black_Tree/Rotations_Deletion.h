#pragma once
#include "Node.h"

using namespace std;

// DELETION; cases 1 - 4
template<typename T>
bool LeftLeftCase_Rotations_Deletion(Node<T>* sonOfSibling);

template<typename T>
bool LeftRightCase_Rotations_Deletion(Node<T>* sonOfSibling);

template<typename T>
bool RightRightCase_Rotations_Deletion(Node<T>* sonOfSibling);

template<typename T>
bool RightLeftCase_Rotations_Deletion(Node<T>* sonOfSibling);

template<typename T>
inline bool LeftLeftCase_Rotations_Deletion(Node<T>* sonOfSibling)
{
	return false;
}

template<typename T>
inline bool LeftRightCase_Rotations_Deletion(Node<T>* sonOfSibling)
{
	return false;
}

template<typename T>
inline bool RightRightCase_Rotations_Deletion(Node<T>* sonOfSibling)
{
	return false;
}

template<typename T>
inline bool RightLeftCase_Rotations_Deletion(Node<T>* sonOfSibling)
{
	return false;
}
