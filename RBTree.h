#pragma once
#include <iostream>
#include "RBNode.h"

template <typename T>
class RBTree
{
public:
	RBTree(void):root(NULL) {};
	void LeftRotation(T *pivot);
	void RightRotation(T *pivot);
	void Insert(T *newNode);
	void InsertFixup(T *fixNode);
	void something(){std::cout <<"something" << std::endl;getchar();};
	T *MinNode(T *subTree);
	T *Successor(T *curNode);

	void Delete(T *delNode);
	void DeleteFixup(T *fixNode);

	void InorderTrave();
	void PreorderTrave();
	~RBTree(void){};
private:
	void Inorder(T* root);
	T *root;
};

