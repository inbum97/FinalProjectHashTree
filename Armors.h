
#ifndef ARMOR_H
#define ARMOR_H
#include <string>
#include "BinarySearchTree.h"
#include <iostream>

using namespace std;
class Armors;

class Armors
{
private:
	string codename;	// Codename (name of armor) (unique key)
	string armorType;	// Type (amor type) (secondary key)
	string creator;	// Creator 
	int yearMade;	// Year Made - int (year of creation)
	string users;	// Users - vector of string (multiple users)
	string movieAppeared;	// movieAppeared - string (Name of the movies appeared)
	string currStats;	// Current Status (active, damaged, destroyed)
	string capabilities;	// Capabilities - vector of string (multiple capabilities)
	string weapons;	// Weapons - vector of string (multiple weapons)
	string precede;	// Precede - string (precede model)
	string succeed;	// Succeed - string (succeeding model)

public:
	// Constructors
	Armors()
	{
		codename = "";
		armorType = "";
		creator = "";
		yearMade = 0;
		users = "";
		movieAppeared = "";
		currStats = "";
		capabilities = "";
		weapons = "";
		precede = "";
		succeed = "";

	}
	// Getters
	string getCodeName() { return codename; }
	string getCodename() { return codename; }

	string getArmorType() { return armorType; }
	string getCreator() { return creator; }
	string getUser() { return users; }
	int getYear() { return yearMade; }
	string getMovie() { return movieAppeared; }
	string getStatus() { return currStats; }
	string getCap() { return capabilities; }
	string getWeapon() { return weapons; }
	string getPre() { return precede; }
	string getSuc() { return succeed; }




	//Overloaded Operator
	Armors(string coden, string type, string inventor, int yearmade,
		string user, string movieShown, string currStat, string capbl,
		string weap, string precedeModel, string succeedModel) : codename(coden),
		armorType(type),
		creator(inventor),
		yearMade(yearmade),
		users(user),
		movieAppeared(movieShown),
		currStats(currStat),
		capabilities(capbl),
		weapons(weap),
		precede(precedeModel),
		succeed(succeedModel) {};

	// Setters
	void setCodeName(string cn) { codename = cn; }
	void setCodename(string cn) { codename = cn; }

	void setArmorType(string at) { armorType = at; }
	//string getUnikey() { return codename; }
	// Other functions
	int intInputValid();
	int isIntGood(int a, Armors*);

	// Operator functions

	friend bool operator==(Armors& a1, Armors& a2) { return a1.codename == a2.codename; }
	friend istream& getline(istream& in, Armors *armor);

};


//Overloaded Operator
istream& getline(istream& in, Armors* armor) {
	//cout << "Enter the Codename: ";
	//getline(in, armor->codename);
	cout << "\nEnter the armor type: ";
	getline(in, armor->armorType);
	cout << "\nEnter the creater: ";
	getline(in, armor->creator);
	cout << "\nEnter the year made: ";
	in >> armor->yearMade;
	armor->yearMade = armor->isIntGood(armor->yearMade, armor);
	in.ignore();
	cout << "\nEnter the User : ";

	getline(in, armor->users);
	cout << "\nEnter the movie appeared in: ";

	getline(in, armor->movieAppeared);
	cout << "\nEnter the current status of the armor: ";

	getline(in, armor->currStats);
	cout << "\nEnter the capabilites of armor: ";

	getline(in, armor->capabilities);
	cout << "\nEnter the weapon: ";

	getline(in, armor->weapons);
	cout << "\nEnter the precede armor: ";

	getline(in, armor->precede);
	cout << "\nEnter the succeed armor: ";

	getline(in, armor->succeed);
	return in;
}

int Armors::intInputValid() {
	int a = 0;
	while (!cin.good()) {
		cout << "Input year is invalid.";
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout << endl << "Please input valid year: ";
		cin >> a;
	}
	return a;
}

int Armors::isIntGood(int a, Armors *A) {
	if (!cin.good())
		a = A->intInputValid();
	return a;
}




#endif#pragma once
