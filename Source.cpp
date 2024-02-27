/*
* Author: Nicholas Sessa
* Date: February 22, 2022
*
* Project 3
* FileName: Source.cpp
* 
* Input File: inventory.txt
* Output File: frequency.dat
*/

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <set>
#include "GroceryItem.h"

using namespace std;

void displayMenu();
void searchForItem();
void displayFrequencies();
void displayHistogram();
set<GroceryItem> readFile(string operation, string searchItemName);

const string menuText =
"1. Search for an item\n"
"2. Display all frequencies\n"
"3. Print histogram\n"
"4. Exit\n"
"Select choice: ";

string userInput;
int userChoice = 99;

const string inputFileName = "inventory.txt";
ifstream inFS;   // Input file stream
std::string fileItem;     // File data

const string outputFileName = "frequency.dat";
ofstream outFS;  // Output file stream

int main() {
	stringstream ss;

	// Failed conversion will throw ios_base::failure
	ss.exceptions(ios::failbit);

	while (userChoice != 4) {
		displayMenu();
		cin >> userInput;

		try {
			ss.str("");
			ss.clear();
			ss << userInput;
			ss >> userChoice;

			// Check for range of the choice
			if (userChoice < 1 || userChoice > 4) {
				throw runtime_error("Invalid choice!");
			}
			else {
				userChoice = stoi(userInput);
				// Search for item
				if (userChoice == 1) {
					searchForItem();
				}
				// Display all frequencies
				if (userChoice == 2) {
					displayFrequencies();
				}
				// Print histogram
				if (userChoice == 3) {
					displayHistogram();
				}
				system("PAUSE");
				displayMenu;
			}
		}
		catch (ios_base::failure& excpt) {
			// This is a type conversion error. User entered something other than an int.
			cout << "Invalid choice!" << endl;
			system("PAUSE");
			displayMenu();
		}
		catch (runtime_error& excpt) {
			// Prints the error message passed by throw statement
			cout << excpt.what() << endl;
			system("PAUSE");
			displayMenu();
		}
	}
	return 0;
}

// Display the menu
// @param value - none
// Returns - none
void displayMenu() {
	system("CLS");
	cout << menuText;
}

// Opens the input file
// @param value - none
// Returns - a number
static int openInFile() {
	// Open file
	inFS.open(inputFileName);

	if (!inFS.is_open()) {
		cout << "Could not open file " << inputFileName << "." << endl;
		return 1;
	}
	return 0;
}

// Closes the input file
// @param value - none
// Returns - a number
static int closeInFile() {
	if (!inFS.eof()) {
		cout << "Input failure before reaching end of file." << endl;
	}
	// Done with file, so close it
	inFS.close();
	return 0;
}

// Opens the output file
// @param value - none
// Returns - a number
static int openOutFile() {
	// Open file
	outFS.open(outputFileName);

	if (!outFS.is_open()) {
		cout << "Could not open file " << outputFileName << "." << endl;
		return 1;
	}
	return 0;
}

// Closes the output file
// @param value - none
// Returns - a number
static int closeOutFile() {
	// Done with file, so close
	outFS.close();
	return 0;
}

// This function reads the input file and writes an output file.
// It also has the ability to:
// 1. search for an item
// 2. list all the items and their quantity
// 3. print a histogram of all the items and their quantity
// @param value - string directing the operation to be performed
// @param value - string of the item to be searched
// Returns - a set of GroceryItem(s)
set<GroceryItem> readFile(string operation, string searchItemName) {
	openInFile();

	set<GroceryItem> items;
	GroceryItem* item;

	// Read the item names
	inFS >> fileItem;
	while (!inFS.fail()) {
		// Create GroceryItem pointer
		item = new GroceryItem(fileItem);

		auto existingItem = items.find(*item);
		if (existingItem != items.end()) {  // If item is found in the set then:
			// existingItem is a pointer to a GroceryItem
			
			// Copy off the existing name
			string newItemName = existingItem->getName();

			// Copy off the existing quantity
			int newItemQuantity = existingItem->getQuantity();

			// Erase the existing item from the set
			items.erase(existingItem);

			// Reassign the GroceryItem pointer to one with the existing name and quantity
			item = new GroceryItem(newItemName, newItemQuantity);
		}
		// Add to the quantity
		item->addItem();

		// insert the item into the set
		items.insert(*item);
	
		// get the next line
		inFS >> fileItem;
	}
	closeInFile();

	// Output the item data to a file
	openOutFile();
	for (GroceryItem item : items) {
		outFS << item.getName() << " " << item.getQuantity() << endl;
	}
	closeOutFile();

	return items;
}

// Function that drives the search code
// @param value - none
// Returns - none
void searchForItem() {
	string itemName = "";

	set<GroceryItem> items;

	cout << "Enter the item to search for: ";
	cin >> itemName;
	items = readFile("search", itemName);

	bool foundIt = false;
	for (GroceryItem item : items) {
		if (item.getName() == itemName) {
			cout << item.getName() << " " << item.getQuantity() << endl;
			foundIt = true;
		}
	}
	if (!foundIt) {
		cout << "Item not found." << endl;
	}
}

// Function that drives the code to display the frequencies (quantities) of the items
// @param value - none
// Returns - none
void displayFrequencies() {
	set<GroceryItem> items;
	string itemName = "";
	items = readFile("display", itemName);

	for (GroceryItem item : items) {
		cout << item.getName() << " " << item.getQuantity() << endl;
	}
}

// Function that drives the code to display the quantities in a histogram
// @param value - none
// Returns - none
void displayHistogram() {
	set<GroceryItem> items;
	string itemName = "";
	items = readFile("display", itemName);

	for (GroceryItem item : items) {
		cout << item.getName() << " ";
		for (int i = 0; i < item.getQuantity(); i++) {
			cout << "*";
		}
		cout << endl;
	}
}