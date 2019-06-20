#pragma once
#ifndef _BINARY_NODE
#define _BINARY_NODE
#include "Armors.h"
class BinaryNode
{
private:
	Armors * armor;         // Data portion
	BinaryNode* leftPtr;		// Pointer to left child
	BinaryNode* rightPtr;		// Pointer to right child

public:
	// constructors
	BinaryNode(Armors* anItem) { armor = anItem; leftPtr = nullptr; rightPtr = nullptr; }
	BinaryNode(Armors* anItem,
		BinaryNode* left,
		BinaryNode* right) {
		armor = anItem; leftPtr = left; rightPtr = right;
	}
	// accessors
	void setItem(Armors* anItem) { armor = anItem; }
	void setLeftPtr(BinaryNode* left) { leftPtr = left; }
	void setRightPtr(BinaryNode* right) { rightPtr = right; }
	// mutators
	Armors* getItem() { return armor; }
	BinaryNode* getLeftPtr() const { return leftPtr; }
	BinaryNode* getRightPtr() const { return rightPtr; }

	bool isLeaf() const { return (leftPtr == 0 && rightPtr == 0); }
};

#endif 