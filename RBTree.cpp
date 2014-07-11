#include "RBTree.h"

//export template<typename T> class RBtree;
/*template<typename T>
void RBTree<T>::something()
{
	std::cout << "this is something" << std::endl;
}*/

template<typename T>
void RBTree<T>::LeftRotation(T *pivot)
{
	RBNode *rchild = pivot->right;
	 pivot->right = rchild->left;

	 if (rchild->left != NULL)
		 rchild->left->parent = pivot;
	 rchild->parent = pivot->parent;
	 if (pivot->parent == NULL)
		 root = rchild;
	 else if (pivot == pivot->parent->left)
		 pivot->parent->left = rchild;
	 else
		 pivot->parent->right = rchild;

	 rchild->left  = pivot;
	 pivot->parent = rchild;
}

template<typename T>
void RBTree<T>::RightRotation(T *pivot)
{
	T *lchild = pivot->left;
	pivot->left = lchild->right;
	if (lchild->right != NULL)
		lchild->right->parent = pivot;
				    
	lchild->parent = pivot->parent;
	if (pivot->parent == NULL)
		root = lchild;
	else if (pivot == pivot->parent->left)
		pivot->parent->left = lchild;
	else
		pivot->parent->right = lchild;

	lchild->right = pivot;
	pivot->parent = lchild;
}

template<typename T>
void RBTree<T>::Insert(T *newNode)
{
	 T *pNode   = root;
	 T *parent  = NULL;
	
	while ( pNode != NULL) {
	    parent = pNode;
		if ( newNode->Prior(pNode) ) 
			pNode = pNode->left;
		else 
		    pNode = pNode->right;
		
	}
	if (parent == NULL) 
		root = newNode;
    else if (newNode->Prior(parent) )
		parent->left = newNode;
	else
		parent->right = newNode;

	newNode->parent = parent;

	InsertFixup(newNode);
}

template<typename T>
void RBTree<T>::InsertFixup(T *fixNode)
{
	 T *parent = fixNode->parent;
	 T *uncle  = NULL;
	
	while ( parent && parent->color == RED) {
		if ( !parent->parent )
			break; // if grandparent isnot exit break;
	    bool sideParent = 1; //default parent is leftson of grandparent
        if (parent == parent->parent->right)
			sideParent = 0;
		uncle = (sideParent) ? parent->parent->right : parent->parent->left;
		
		if (uncle && uncle->color == RED) { //case 1
		    parent->parent->color = RED;
			parent->color = BLACK;
			uncle->color = BLACK;

			fixNode = parent->parent;
		}
		else {
		    if (sideParent == 1 && fixNode == parent->right) {//case 2
			    fixNode = parent;
				LeftRotation(fixNode);
			}
			else if( sideParent == 0 && fixNode == parent->left) {
			    fixNode = parent;
				RightRotation(fixNode);
			}

			fixNode->parent->color = BLACK;
			fixNode->parent->parent->color = RED;

			if (sideParent == 1)
				RightRotation(fixNode->parent->parent);
			else
				LeftRotation(fixNode->parent->parent);
		}
		parent = fixNode->parent;
	}
	root->color = BLACK;
}


template<typename T>
void RBTree<T>::Delete(T *delNode)
{
	if (delNode == NULL) {
		return;
	}
	  EventNode *realDelNode = NULL;
	
	if (delNode->left == NULL || delNode->right == NULL)
		realDelNode = delNode;
	else
		realDelNode = Successor(delNode);
	
	  EventNode *son = (realDelNode->left != NULL) ? realDelNode->left : realDelNode->right;
	if (son)
		son->parent = realDelNode->parent;
	
	if (realDelNode->parent == NULL)
		root = son;
    else if (realDelNode == realDelNode->parent->left)
		realDelNode->parent->left = son;
	else
		realDelNode->parent->right = son;
												
	if (delNode != realDelNode)
		realDelNode->SwapKey(realDelNode);

	if (realDelNode->color == BLACK && son)
		DeleteFixup(son);
}

template<typename T>
void RBTree<T>::DeleteFixup(T* fixNode)
{
	while( fixNode != root && fixNode->color == BLACK ) {
	    bool sideFixNode = 1;
	      EventNode* parent = fixNode->parent;

	      EventNode* brother = sideFixNode? parent->right : parent->left;
	    if (brother->color == RED) { //brother is red  is case 1
		    brother->color = BLACK;
		    parent->color = RED;
		    
			if (sideFixNode == 1) {
			    LeftRotation(parent);
			    brother = parent->right;
		    }
		    else {
			    RightRotation(parent);
			    brother = parent->left;
		    }
        }
	
	    if ((!brother->left || brother->left->color_ == BLACK) && (!brother->right || brother->right->color_ == BLACK))  {  //case 2
		    brother->color = RED;
		    fixNode = parent;
	    }
        else {
		    if (sideFixNode && (!brother->right || brother->right->color == BLACK)) {   // case 3  fixNode is leftson of parent
			    brother->left->color = BLACK;
			    brother->color = RED;
			    RightRotation(brother);									
			    brother = parent->right;
		    }
	        if (sideFixNode && ( !brother->left || brother->left->color_ == BLACK)) { //case 3 fixNode is rightson of parent
			    brother->right->color = BLACK;
		 	    brother->color = RED;
			    LeftRotation(brother);
			    brother = parent->left;
		    }
		    brother->color = parent->color_;    // case 4
		    parent->color = BLACK;
		    
			if (sideFixNode) {
			   brother->right->color_ = BLACK;													
			   LeftRotation(parent); 
		    }
		    else {		
			   brother->left->color = BLACK;
			   RightRotation(parent);
		    }
		    fixNode = root;
	    }  
	}
	fixNode->color = BLACK;
}

template<typename T>
T* RBTree<T>::MinNode(T* keyNode)
{
	while (keyNode->left != NULL) 
		keyNode = keyNode->left;

    return keyNode;
}

template<typename T>
T* RBTree<T>::Successor(T *keyNode)
{
	if (keyNode->right != NULL)
	    return MinNode(keyNode->right);
			
	while (keyNode == keyNode->parent->right)
		keyNode = keyNode->parent;
				
	return keyNode->parent;
}

template<typename T>
void RBTree<T>::Inorder(T* root)
{
	if (root) {
	    Inorder(root->left);
	    root->Print();
	    Inorder(root->right);
	}
}