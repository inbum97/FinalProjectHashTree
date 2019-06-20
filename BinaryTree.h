#ifndef _BINARY_TREE
#define _BINARY_TREE

#include "BinaryNode.h"
#include "Queue.h"

class BinaryTree
{
protected:
	BinaryNode * rootPtr;		// ptr to root node
	int count;							// number of nodes in tree

public:
	// "admin" functions
	BinaryTree() { rootPtr = 0; count = 0; }
	BinaryTree(const BinaryTree* tree) { }
	virtual ~BinaryTree() { }

	// common functions for all binary trees
	bool isEmpty() const { return count == 0; }
	int size() const { return count; }
	//	void clear()			{destroyTree(rootPtr); rootPtr = 0; count = 0;}
	void preOrder(void visit(Armors*)) const { _preorder(visit, rootPtr); }
	void inOrder(void visit(Armors*)) const { _inorder(visit, rootPtr); }
	void postOrder(void visit(Armors*)) const { _postorder(visit, rootPtr); }
	void printTree(void visit(Armors*), void disLev(int, int)) { _printTree(visit, disLev, rootPtr, 1, 6); }
	void _breadthF(void visit(Armors*)) const;
	// abstract functions to be implemented by derived class
	virtual bool insert(Armors* newData) = 0;
	virtual bool remove(Armors * data) = 0;
	virtual bool getEntry(Armors * anEntry, Armors *& returnedItem) const = 0;

	// search for the smallest
	// void findSmall(void visit(ItemType&)) { _findSmall(visit,rootPtr); }
	// // search for the largest
	// void findLarge(void visit(ItemType &)) { _findLarge(visit, rootPtr); }

private:
	// delete all nodes from the tree
	// void destroyTree(BinaryNode<ItemType>* nodePtr);
	// internal traverse
	void _preorder(void visit(Armors*), BinaryNode* nodePtr) const;
	void _inorder(void visit(Armors*), BinaryNode* nodePtr) const;
	void _postorder(void visit(Armors*), BinaryNode* nodePtr) const;
	//Mirror of preorder traversal
	void _printTree(void visit(Armors*), void displayLev(int, int), BinaryNode* nodePtr, int level, int space);
	//finding smallest node in the tree and print
	// void _findSmall(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
	//finding the largest node in the tree and print
	// void _findLarge(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;

};

/**********************************************
_findSmall: Find the smallest item in the node
then print the item when found
*********************************************/
// template<class ItemType>
// void BinaryTree<ItemType>::_findSmall(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const {
// 	if (nodePtr->getLeftPtr() != NULL) {
// 		_findSmall(visit,nodePtr->getLeftPtr());
// 	}
// 	else {
// 		ItemType item = nodePtr->getItem();
// 		visit(item);
// 	}
// }
/***********************************************
_findLarge: Find the largest item in the node
then print the item when it found
*********************************************/
// template<class ItemType>
// void BinaryTree<ItemType>::_findLarge(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const {
// 	if (nodePtr->getRightPtr() != NULL) {
// 		_findLarge(visit,nodePtr->getRightPtr());
// 	}
// 	else {
// 		ItemType item = nodePtr->getItem();
// 		visit(item);
// 	}
// }

/**********************************************
_printTree: Prints every nodes in the tree
in mirror of preorder
********************************************/
void BinaryTree::_printTree(void visit(Armors*), void disLev(int, int), BinaryNode* nodePtr, int level, int space)
{
	if (nodePtr != nullptr)
	{
		Armors* item = nodePtr->getItem();
		disLev(level, space);
		visit(item);
		_printTree(visit, disLev, nodePtr->getRightPtr(), level + 1, space + 6);
		_printTree(visit, disLev, nodePtr->getLeftPtr(), level + 1, space + 6);
	}
}


/**************************************************************
destroyTree: Deleting every node of the tree by
deleting the updated root of the tree until the tree is empty
*************************************************************/
// template<class ItemType>
// void BinaryTree<ItemType>::destroyTree(BinaryNode<ItemType>* nodePtr)
// {
// 	if (nodePtr = 0)
// 		cout << "Tree is destroyed\n";
// 	else {
// 		if (nodePtr->getLeftPtr != NULL)
// 			destroyTree(nodePtr->getLeftPtr)
// 			if (nodePtr->getRightPtr != NULL)
// 				destroyTree(nodePtr->getRightPtr)
// 	}
// 		delete nodePtr;
// }  

/***********************************************
_breadthF: Print the tree in breadth first order
using queue
**********************************************/
void BinaryTree::_breadthF(void visit(Armors*)) const
{
	Queue<BinaryNode*> qIn;
	BinaryNode* pCur;
	if (this->rootPtr == NULL)
		return;
	qIn.enqueue(this->rootPtr);
	while (!qIn.isEmpty()) {
		qIn.dequeue(pCur);
		Armors* item = pCur->getItem();
		visit(item);
		//visit(pCur->getItem());
		if (pCur->getLeftPtr() != NULL) {
			qIn.enqueue(pCur->getLeftPtr());

		}
		if (pCur->getRightPtr() != NULL) {
			qIn.enqueue(pCur->getRightPtr());
		}
	}

}

/**********************************************
_preorder: print the tree in preorder
using recursive method
********************************************/
void BinaryTree::_preorder(void visit(Armors*), BinaryNode* nodePtr) const
{
	//cout << count << endl;
	if (nodePtr != nullptr)
	{
		Armors* item = nodePtr->getItem();
		visit(item);
		_preorder(visit, nodePtr->getLeftPtr());
		_preorder(visit, nodePtr->getRightPtr());
	}
}

/*******************************************
_inOrder: print the tree in inorder order
using recursive method
*****************************************/
void BinaryTree::_inorder(void visit(Armors*), BinaryNode* nodePtr) const
{
	if (nodePtr != 0)
	{
		Armors* item = nodePtr->getItem();
		_inorder(visit, nodePtr->getLeftPtr());
		visit(item);
		_inorder(visit, nodePtr->getRightPtr());
	}
}

/**********************************************
_postorder: print the tree in postorder
using recursive method
***********************************************/
void BinaryTree::_postorder(void visit(Armors*), BinaryNode* nodePtr) const
{
	if (nodePtr != 0)
	{
		Armors* item = nodePtr->getItem();
		_postorder(visit, nodePtr->getLeftPtr());
		_postorder(visit, nodePtr->getRightPtr());
		visit(item);
	}
}


#endif
