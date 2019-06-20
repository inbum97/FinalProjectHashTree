#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>

#include "BinarySearchTree.h"
#include "Hash.h"
#include "List.h"

using namespace std;

// Type of BST
typedef BinarySearchTree TreeType;

// FUNCTIONS PROTOTYPE

/* Hash functions */
void insertHashManager(Hash& H);
void deleteHashManager(Hash& H);
void searchHashManager(Hash& H, void visit(Armors*));
void inputValid(string& returnItem);
void hashInput(string filename, Hash& H);
//void printTree(TreeType& bstp, TreeType& bsts);
void printHeader(string title);

/* reading file and building BST */
void fileInput(string filename, TreeType& bstp, TreeType& bsts, Hash & H);	// read data from txt file and insert to tree

																	/* menus & sub-menus */
void menu();
void searchSubmenu(TreeType& bstp, TreeType& bsts,Hash &);		// show search sub-menu when user choose to search
void listSubmenu(TreeType& bstp, TreeType& bst, Hash &);		// show list sub-menu when user choose to print list
void processChoice(TreeType& bstp, TreeType& bsts, Hash &);		// this will execute which menu options that the user choose
string inputKey();	// prompt user to enter key for menu & submenu

					/* insert and delete data from tree */
void insertToData(TreeType& bstp, TreeType& bsts,Hash &);	// ADD data
void delData(TreeType& bstp, TreeType& bsts, Hash &);		// DELETE data

													/* SEARCH data */
void searchBSTp(TreeType& bstp, TreeType& bsts, Hash &H);	// by primary key
void searchBSTs(TreeType& bstp, TreeType& bsts, Hash &H);	// by secondary key
void printLevel(int level, int space);

													/* print LIST functions */
void listByPriKey(TreeType& bstp, TreeType& bsts, Hash &H);			// print list, sorted by primary key
void listBySec(TreeType& bstp, TreeType& bsts, Hash &H);			
void breadthTraversal(TreeType& bstp, TreeType& bsts, Hash &H);		// print all armors codename with its type by breadth order
void preOrderTraversal(TreeType& bstp, TreeType& bsts, Hash &H);		// print all armors codename with its type by pre-order
void inOrderTraversal(TreeType& bstp, TreeType& bsts, Hash &H);		// print all armors codename with its type by in-order
void postOrderTraversal(TreeType& bstp, TreeType& bsts, Hash &H);	// print all armors codename with its type by post-order


															/* display function to pass to BST print function */

															//void display(Armors* item)
															//{
															//	cout << item << endl;
															//}

void display(Armors* a) {
	cout << "I am in display func\n";
	cout << a->getCodename() << " " << a->getYear() << endl;
	cout << "--------------------------------------------------------------------------" << endl;
	cout << a->getCodename() << ":" << a->getArmorType() << "\nMade by: " << a->getCreator() << " in " << a->getYear()
		<< "\nUsers: " << a->getUser() << ", appeared in: " << a->getMovie() << "\nCurrent Status: " << a->getStatus()
		<< "\nArmor Capabilities: " << a->getCap() << "\nWeapons: " << a->getWeapon()
		<< "\nPrecede: " << a->getPre() << "\tSucceed: " << a->getSuc();
	cout << "\n--------------------------------------------------------------------------" << endl;
}

/*****************************************************************
void displayCodenames(Armors* item):
display the armor codenames with its type
*****************************************************************/
void displayCodenames(Armors* item)
{
	cout  << item->getCodename() << " -" << item->getArmorType()<<endl;
}

/*****************************************************************
void displayTree(Armors* item, int level):
print tree with indent depending on the level
*****************************************************************/
void displayTree(Armors * A) {
	cout << A->getCodename() << ": " << A->getArmorType() << " created by - " << A->getCreator() << endl << endl;
}

/********************************************
This function prints out the level of node
********************************************/
void printLevel(int level, int space) {
	cout << setw(space) << "Level " << level << ". ";
}

int main()
{
	const char inputFileName[] = "armors.txt";

	TreeType bstP;
	TreeType bstS;
	Hash H(59);

	fileInput(inputFileName, bstP, bstS, H);

	menu();
	processChoice(bstP, bstS,H);

	/*hashInput(inputFileName, H);
	H.stat();
	insertHashManager(H);
	searchHashManager(H, display);
	deleteHashManager(H);
	H.printHash(display);*/

}

void insertHashManager(Hash& H) {
	string targetName = "";
	Armors* A = new Armors;
	Armors* A2 = new Armors;
	A2->setCodename("");

	cout << "\n Insert\n";
	cout << "=======\n";

	while (A2->getCodename() != "Q")
	{
		cout << endl << "Enter an armor name to insert (or Q for stop inserting):";
		getline(cin, targetName);
		A2->setCodename(targetName);
		cout << endl;
		if (A2->getCodename() != "Q")
		{
			if (H.searchHash(A2, A))
				cout << "Armor " << targetName << " is already in this Hash Table.";
			else {
				cout << "Enter the information of the Armor" << endl;
				A->setCodename(targetName);
				getline(cin, A);
				if (H.insertItem(A))
					cout << "\nInserted" << endl;
			}
		}
	}
	cout << endl;
	cout << "___________________END INSERT SECTION _____\n";
}

void deleteHashManager(Hash& H) {
	string targetName = "";
	int n = 0;

	cout << "\n Delete\n";
	cout << "=======\n";

	while (targetName != "Q")
	{
		cout << endl << "Enter an armor name for delete (or Q for stop searching): ";
		getline(cin, targetName);

		if (targetName != "Q")
		{
			if (H.deleteItem(targetName))
				cout << "Deleted\n";
			else
				cout << "Armor " << targetName << " was not found in this Hash Table." << endl;
		}
	}
	cout << "___________________END DELETE SECTION_____\n";
}

void searchHashManager(Hash& H, void visit(Armors*)) {
	string key = "";
	string sKey = "";
	Armors* A;
	Armors* A2;
	A = new Armors;
	A2 = new Armors;
	cout << "\n Search\n";
	cout << "=======\n";
	do
	{
		cout << "\nEnter a primary key for search (or Q for stop searching): ";
		getline(cin, key);
		if (!cin.good())
			inputValid(key);
		A2->setCodename(key);
		cout << endl;
		if (A2->getCodename() != "Q") {
			if (!H.searchHash(A2, A))
				cout << "Armor " << key << " was not found in this Hash Table.\n";
			else
				visit(A);
		}
	} while (key != "Q");

	cout << endl;
	cout << "___________________END SEARCH SECTION _____\n";

}

void inputValid(string& returnItem) {
	string val;
	do {
		cout << "Your input is invalid\n" << "Please input integer to search\n";
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		getline(cin, val);
	} while (!cin.good());
	returnItem = val;
}

//void hashInput(string filename, Hash& H)
//{
//	ifstream infile(filename);
//
//	string codename, type, creator, movie, curstat, precede, succeed, users, capbl, weap, space;
//	int year = 0;
//
//	if (!infile) {
//		cout << "Error happened to open the input file!" << endl;
//		exit(EXIT_FAILURE);
//	}
//
//	// READING THE FILE AND DECLARE TO RESPECTICE VARIABLE 
//	//======================================================
//
//	while (getline(infile, codename, ';'))
//	{
//		getline(infile, type, ';');
//		getline(infile, creator, ';');
//		infile >> year;
//		infile.ignore();
//		getline(infile, users, ';');
//		getline(infile, movie, ';');
//		getline(infile, curstat, ';');
//		getline(infile, capbl, ';');
//		getline(infile, weap, ';');
//		getline(infile, precede, ';');
//		getline(infile, succeed, ';');
//
//
//		Armors* armors;
//		armors = new Armors(codename, type, creator, year, users, movie, curstat, capbl, weap, precede, succeed);
//		H.insertItem(armors);
//		cout << "Inserted\n";
//		getline(infile, space);
//	}
//	infile.close();
//}

/**********************************************************************
BUILD BST
void fileInput(string filename, TreeType& bstp, TreeType& bsts):
this function will read data from txt file and insert the data
into the 2 BST (primary key & secondary key)
Input Parameter: the 2 BST to build BST
**********************************************************************/
void fileInput(string filename, TreeType& bstp, TreeType& bsts, Hash & H)
{
	ifstream infile(filename);

	string codename, type, creator, movie, curstat, precede, succeed, users, capbl, weap, space;
	int year = 0;

	if (!infile) {
		cout << "Error happened to open the input file!" << endl;
		exit(EXIT_FAILURE);
	}

	// READING THE FILE AND DECLARE TO RESPECTICE VARIABLE
	while (getline(infile, codename, ';'))
	{
		getline(infile, type, ';');
		getline(infile, creator, ';');
		infile >> year;
		infile.ignore();
		getline(infile, users, ';');
		getline(infile, movie, ';');
		getline(infile, curstat, ';');
		getline(infile, capbl, ';');
		getline(infile, weap, ';');
		getline(infile, precede, ';');
		getline(infile, succeed, ';');

		// TEST IF FILE IS READ PROPERLY
		/*
		cout << "======================================================" << endl;
		cout << "codename: " << codename << endl;
		cout << "type: " << type << endl;
		cout << "creator: " << creator << endl;
		cout << "year: " << year << endl;
		cout << "users: " << users << endl;
		cout << "movie: " << movie << endl;
		cout << "status: " << curstat << endl;
		cout << "capabilities: " << capbl << endl;
		cout << "weapons: " << weap << endl;
		cout << "precede: " << precede << endl;
		cout << "succeed: " << succeed << endl;
		cout << "======================================================" << endl << endl;
		*/

		// Building BST
		Armors* armors;
		armors = new Armors(codename, type, creator, year, users, movie, curstat, capbl, weap, precede, succeed);
		bstp.insert(armors);
		bsts.insertSec(armors);
		H.insertItem(armors);
		getline(infile, space);



	}
	infile.close();
	H.stat();
}

/**********************************************************************
void menu():
this will print the menu. layout of menu:

1 : (A) ADD
2 : (D) DELETE
3 : (S) SEARCH :
1 : (P)SEARCH by PRIMARY Key
2 : (S)SEARCH by SECONDARY Key
0 : Back to main menu
4 : (L) LIST :
1 : (U)LIST - Unsorted
2 : (P)LIST - Sorted by PRIMARY Key
3 : (S)LIST - Sorted by SECONDARY Key
4 : (T)LIST - as a TREE
5 : (0) LIST - Print LEVEL-ORDER
6 : (1) LIST - Print PRE-ORDER
7 : (2) LIST - Print IN-ORDER
8 : (3) LIST - Print POST-ORDER
0 : Basck to main menu
0 : Quit
**********************************************************************/
void menu()
{
	cout << "                        MENU                        \n";
	cout << "======================================================" << endl;
	cout << "1 : Add armor" << endl;
	cout << "2 : Delete armor" << endl;
	cout << "3 : Search" << endl;
	cout << "4 : Show list" << endl;
	cout << "5 : Delete the root" << endl;
	cout << "0 : Quit" << endl;
	cout << "------------------------------------------------------" << endl;
}

/**********************************************************************
void searchSubmenu(TreeType& bstp, TreeType& bsts):
when the user choose to search, a sub-menu will be printed so
the user can choose how they want to search it.
It will keep prompting user for the choice if input is invalid
Input Parameter: the 2 BST for recursion
**********************************************************************/
void searchSubmenu(TreeType& bstp, TreeType& bsts, Hash &H)
{
	int y = -1;
	cout << "Search by:" << endl;
	cout << "------------" << endl;
	cout << "1 : Primary Key " << endl;
	cout << "2 : Secondary Key " << endl;
	cout << "0 : Back to main menu " << endl;
	cout << "User choice: ";
	cin >> y;
	cin.ignore();
	cout << endl;

	switch (y)
	{
	case 1: // search by primary key function
		searchHashManager(H,display);
		menu();
		processChoice(bstp, bsts, H);
		break;
	case 2: // search by secondary key function
		searchBSTs(bstp,bsts,H);
		menu();
		processChoice(bstp, bsts, H);
		break;
	case 0: menu();
		processChoice(bstp,bsts,H);
		break;
	default:
		cout << "----------------" << endl;
		cout << " INPUT INVALID. " << endl;
		cout << "----------------" << endl;
		searchSubmenu(bstp,bsts,H);
	}
}

/**********************************************************************
void listSubmenu(TreeType& bstp, TreeType& bsts):
when the user choose to print list, a sub-menu will be printed so
the user can choose which order they want to see
It will keep prompting user for the choice if input is invalid
Input Parameter: the 2 BST for recursion
**********************************************************************/
void listSubmenu(TreeType& bstp, TreeType& bsts, Hash &H)
{
	int y = -1;
	cout << "List as:" << endl;
	cout << "------------" << endl;
	cout << "1 : Unsorted " << endl;
	cout << "2 : Primary Key " << endl;
	cout << "3 : Secondary Key " << endl;
	cout << "4 : Level-order " << endl;
	cout << "5 : Pre-order " << endl;
	cout << "6 : In-order " << endl;
	cout << "7 : Post-order " << endl;
	cout << "0 : Back to main menu " << endl;
	cout << "User choice: ";
	cin >> y;
	cin.ignore();
	cout << endl;

	switch (y)
	{
	case 1: // unsorted list
		H.printHash(displayCodenames);
		menu();
		processChoice(bstp, bsts, H);
		break;
	case 2: // lsit sorted by primary key
		listByPriKey(bstp, bsts,H);
		break;
	case 3: // list sorted by secondary key
		 listBySec(bstp, bsts,H); 
		break;
	case 4: // list printed as level-order
		breadthTraversal(bstp, bsts, H);
		break;
	case 5: // list printed as pre-order
		preOrderTraversal(bstp, bsts, H);
		break;
	case 6: // list printed as in-order
		inOrderTraversal(bstp, bsts, H);
		break;
	case 7://list printed as post - order 
		postOrderTraversal(bstp, bsts, H);
		break;
	case 0: menu();
		processChoice(bstp, bsts,H);
		break;
	default:
		cout << "--------------------" << endl;
		cout << "   INPUT INVALID.   " << endl;
		cout << "--------------------" << endl;
		listSubmenu(bstp, bsts,H);
	}

}


/**********************************************************************
void processChoice(TreeType& bstp, TreeType& bsts):
Prompt user to choose the menu and execute their choice.
It will keep prompting user if input is invalid

Input Parameter: the 2 BST for recursion
**********************************************************************/
void processChoice(TreeType& bstp, TreeType & bsts, Hash &H)
{
	int x = 0;
	cout << "User input: ";
	cin >> x;
	cin.ignore();
	cout << endl;

	switch (x)
	{
	case 1: // add function
		insertToData(bstp,bsts,H);
		break;
	case 2: // delete function
		delData(bstp,bsts,H);
		break;
	case 3:
		searchSubmenu(bstp,bsts,H);
		break;
	case 4:
		listSubmenu(bstp,bsts,H);
		break;
	case 5:
		bstp.deleteRoot();
		bsts.deleteRoot();
		menu();
		processChoice(bstp, bsts, H);
		break;
	case 0: cout << "Program ended" << endl;
		return ;
		//exit(EXIT_FAILURE);
	default:
		cout << "----------------" << endl;
		cout << " INPUT INVALID. " << endl;
		cout << "----------------" << endl;
		processChoice(bstp,bsts,H);
	}
}

/**********************************************************************
string inputKey():
Prompt user to input a string and return the string.
**********************************************************************/
string inputKey()
{
	string key;
	cout << "Input a key ('0' - main menu) : ";
	getline(cin, key);
	return key;
}

/**********************************************************************
ADD
void insertToTree(TreeType& bstp, TreeType& bsts):
When the user choose to add data, it will prompt the user
to input all the variable into an object and then insert it into
the 2 BST.
If the codename that the user input already exist, it will reject
the insertion and it will go back to main menu
Input Parameter: the 2 BST for insertion
**********************************************************************/
void insertToData(TreeType& bstp, TreeType& bsts, Hash & H)
{

		string targetName = "";
		Armors* A = new Armors;
		Armors* A2 = new Armors;
		A2->setCodename("");

		cout << "\n Insert\n";
		cout << "=======\n";

		while (A2->getCodename() != "Q")
		{
			cout << endl << "Enter an armor name to insert (or Q for stop inserting):";
			getline(cin, targetName);
			A2->setCodename(targetName);
			cout << endl;
			if (A2->getCodename() != "Q")
			{
				if (H.searchHash(A2, A)&& bstp.getEntry(A2, A))
					cout << "Armor " << targetName << " is already in this Hash Table.";
				else {
					cout << "Enter the information of the Armor" << endl;
					A->setCodename(targetName);
					getline(cin, A);
					if (H.insertItem(A) && bstp.insert(A) && bsts.insertSec(A))
						cout << "\nInserted" << endl;
				}
			}
		}
		cout << endl;
		cout << "___________________END INSERT SECTION _____\n";

		// Write to file
		ofstream outFile;
		outFile.open("armors.txt", ios::app);

		outFile << endl << A->getCodeName() << ';' << A->getArmorType() << ';' << A->getCreator() << ';' << A->getYear() << 
			";" << A->getUser() << ';' << A->getMovie() << ';' << A->getStatus() << ';' << A->getCap() << ";" << A->getWeapon()
			<< ";" << A->getPre() << ";" << A->getSuc() << ";";
		outFile.close();

	menu();
	processChoice(bstp, bsts,H);
}

/**********************************************************************
SEARCH by PRIMARY key
void searchBSTp(TreeType& bstp, TreeType& bsts):
When user choose to search by primary key, it will prompt
the user to enter the codename.
If it exist, it will print out the data.
if it's not it will show that it's not found.
When the user choose to add data, it will prompt the user
to input all the variable into an object and then insert it into
the 2 BST.
If the codename that the user input already exist, it will reject
the insertion and it will go back to main menu
Input Parameter: the 2 BST for recursion
**********************************************************************/
void searchBSTp(TreeType& bstp, TreeType& bsts, Hash &H)
{
	string key = "";

	Armors* A1;
	A1 = new Armors;
	Armors* A2;
	A2 = new Armors;
	A2->setCodename("");


	cout << "Search by PRIMARY key:" << endl;
	key = inputKey();
	A2->setCodename(key);
	if (A2->getCodename() != "0") {
		if (bstp.getEntry(A2, A1))
		{
			display(A1);
			searchBSTp(bstp,bsts,H);
		}
		else {
			cout << key << " not found." << endl;
			searchBSTp(bstp,bsts,H);
		}
	}
	else { cout << endl; menu(); processChoice(bstp,bsts,H); }



}

// Search for secondary key
void searchBSTs(TreeType& bstp, TreeType& bsts, Hash &H)
{
	string key = "";

	Armors* A1;
	A1 = new Armors;
	Armors* A2;
	A2 = new Armors;
	A2->setCodename("");


	cout << "Search by SECONDARY key:" << endl;
	key = inputKey();
	A2->setArmorType(key);
	if (A2->getArmorType() != "0") {
		if (bsts.getEntrySec(A2,A1, display))
		{
			// FOUND!
			//searchBSTs(bsts);
		}
		else {
			cout << "NOT FOUND." << endl;
			//searchBSTs(bst);
		}
	}
	else { menu(); processChoice(bstp,bsts,H); }


}


///**********************************************************************
// delData: 
//	delete data based on the codename that the user input.
// **********************************************************************/
void delData(TreeType& bstp, TreeType& bsts, Hash &H)
{
	string key = "";

	Armors* A1;
	A1 = new Armors;
	Armors* A2 = new Armors;

	cout << "Delete data: ";
	cout << "\n                             DELETE                                    \n";
	cout << "===========================================================================" << endl;
	bstp.inOrder(displayCodenames);
	cout << "---------------------------------------------------------------------------" << endl;

	key = inputKey();
	A1->setCodename(key);

	if (key == "0")
	{
		cout << endl;
		menu();
		processChoice(bstp, bsts,H);
	}
	H.searchHash(A1, A2);
	if (H.deleteItem(key) && bstp.remove(A1))
	{
		cout << key << " removed. \n\n";
		menu();
		processChoice(bstp, bsts,H);
	}
	else {
		cout << key << " doesn't exists." << endl;
		menu();
		processChoice(bstp, bsts,H);
	}
	
}



void listByPriKey(TreeType& bstp, TreeType& bsts, Hash &H)
{
	cout << "By PRIMARY Key:" << endl;
	cout << "---------------------------------------------------------------------------" << endl;
	bstp.inOrder(displayCodenames);
	cout << "---------------------------------------------------------------------------" << endl << endl;
	menu(); processChoice(bstp, bsts,H);
}

void listBySec(TreeType& bstp, TreeType& bsts, Hash &H)
{
	cout << "By SECONDARY Key:" << endl;
	cout << "---------------------------------------------------------------------------" << endl;
	bsts.inOrder(displayCodenames);
	cout << "---------------------------------------------------------------------------" << endl << endl;
	menu(); processChoice(bstp, bsts,H);
}

void breadthTraversal(TreeType& bstp, TreeType& bsts, Hash &H)
{
	cout << "LEVEL-ORDER:" << endl;
	cout << "---------------------------------------------------------------------------" << endl;
	printHeader("each level in PrimaryKey");
	bstp.printTree(displayCodenames,printLevel);
	cout << "---------------------------------------------------------------------------" << endl << endl;
	printHeader("each level in SecondaryKey");
	bsts.printTree(displayCodenames, printLevel);
	cout << "---------------------------------------------------------------------------" << endl << endl;

	menu(); processChoice(bstp, bsts,H);
}

void preOrderTraversal(TreeType& bstp, TreeType& bsts, Hash &H)
{
	cout << "PRE-ORDER:" << endl;
	cout << "---------------------------------------------------------------------------" << endl;
	bstp.preOrder(displayCodenames);
	cout << "---------------------------------------------------------------------------" << endl << endl;
	menu(); processChoice(bstp, bsts,H);
}

void inOrderTraversal(TreeType& bstp, TreeType& bsts, Hash &H)
{
	cout << "IN-ORDER:" << endl;
	cout << "---------------------------------------------------------------------------" << endl;
	bstp.inOrder(displayCodenames);
	cout << "---------------------------------------------------------------------------" << endl << endl;
	menu(); processChoice(bstp, bsts,H);
}

void postOrderTraversal(TreeType& bstp, TreeType& bsts, Hash &H)
{
	cout << "POST-ORDER:" << endl;
	cout << "---------------------------------------------------------------------------" << endl;
	bstp.postOrder(displayCodenames);
	cout << "---------------------------------------------------------------------------" << endl << endl;
	menu(); processChoice(bstp, bsts,H);
}

//Printing header for each traversal
void printHeader(string title) {
	cout << "\n\n***************Printing tree in " << title
		<< "***********************" << endl;
}

//
//void printTree(TreeType& bst)
//{
//	bst.printTree(displayTree);
//}
