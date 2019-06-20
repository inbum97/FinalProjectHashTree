#pragma once
#ifndef Hash_H
#define Hash_H

#include <iostream>
#include "List.h"
#include "Armors.h"
#include <cmath>

using namespace std;

class Hash {
private:
	//number of buckets
	int numBucket;
	List* table;
	int collision;
	double LF;
public:
	//constructor
	Hash();
	//overloaded constructor
	Hash(int);
	//Destructor
	~Hash();
	//basic hash functions
	bool insertItem(Armors* A);
	bool deleteItem(string);
	bool searchHash(Armors*, Armors*&);
	int hashFunction(string);
	int badHashFunc(string);
	void printHash(void visit(Armors*));
	void printBuckList(int, void visit(Armors*));
	void stat();
	//Setter
	void setCol(int a) { collision = a; }
	void setLF(double a) { LF = a; }
	//getter
	int getCol() { return collision; }
	double getLF() { return LF; }
};

//print by bucket number
void Hash::printBuckList(int index, void visit(Armors*)) {
	if (table[index].getCount() > 0)
		table[index].displayList(visit);
	else
		cout << "There is no item in the " << index << " bucket";
}


//print unsorted 
void Hash::printHash(void visit(Armors*)) {
	for (int i = 0; i < numBucket; i++) {
			cout << "Bucket number " << i << ": ";
			table[i].displayList(visit);
	}

}

void Hash::stat() {
	int collision = 0;
	int numItem = 0;
	double loadFactor = 0.0;
	for (int i = 0; i < numBucket; i++) {
		if (table[i].getCount() > 1) {
			collision += table[i].getCount() - 1;
		}
	}
	for (int i = 0; i < numBucket; i++) {

		numItem += table[i].getCount();

	}
	setCol(collision);
	cout << "Collision: " << collision << endl;
	loadFactor = ((numItem - collision) * 100 / numBucket);
	setLF(loadFactor);
	cout << "Load Facotr " << loadFactor << "%" << endl;

}
//Overloaded Constructor
Hash::Hash(int b) {
	this->numBucket = b;
	table = new List[numBucket];
	cout << "Hash array of " << b << " number of index created\n";
}

bool Hash::searchHash(Armors * A, Armors * &returnItem) {
	bool found = false;
	int index = hashFunction(A->getCodename());

	if (table[index].searchListP(A, returnItem)) {
		found = true;
	}
	return found;
}

//Inserting an item into the hash table
bool Hash::insertItem(Armors * A) {
	bool found = false;
	int index = hashFunction(A->getCodename());
	if (table[index].insertNode(A)) {
		found = true;
		cout << A->getCodename() << " has been inserted\n\n";
	}
	return found;
}

//what should be the parameter
bool Hash::deleteItem(string target) {
	bool found = false;
	int index = hashFunction(target);
	if (table[index].deleteNode(target)) {
		found = true;
	}
	return found;
}

int Hash::hashFunction(string unikey) {
	int sum = 0;
	int len = unikey.size();
	for (int i = 0; i < len; i++) {
		sum += unikey[i];
	}
	int key = (7 * sum + 19) % numBucket;
	return key;
}

int Hash::badHashFunc(string unikey) {
	int sum = 0;
	int len = unikey.size();
	for (int i = 0; i < len; i++) {
		sum += unikey[i];
	}
	int key = sum % 4;
	return key;
}

Hash::~Hash() {
	for (int i = 0; i < numBucket; i++) {
		if (table[i].getCount() > 0) {
			table[i].~List();
		}
	}
}




#endif Hash-H