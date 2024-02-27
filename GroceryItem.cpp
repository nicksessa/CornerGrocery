#include "GroceryItem.h"
#pragma once
#include <string>

// Getter to get the name
// @param value - none
// Returns - the name
std::string GroceryItem::getName() const {
	return m_name;
}

// Getter to get the quantity
// @param value - none
// Returns - the quantity
int GroceryItem::getQuantity() const {
	return m_quantity;
}

// Overload the less than symbol to be used for sorting items in a set
// @param value - Address of a GroceryItem object
// Returns - true of false
bool GroceryItem::operator<(const GroceryItem& other) const {
	return m_name.compare(other.getName()) < 0;
}

// Constructor to set the initial values
// @param value - the address of the name
// @returns - null
GroceryItem::GroceryItem(std::string& name) {
	m_name = name;
	m_quantity = 0;
};

// Constructor to set the initial values
// @param value - the name
// @param value - the quantity
// @returns - null
GroceryItem::GroceryItem(std::string& name, int quantity) {
	m_name = name;
	m_quantity = quantity;
};

// Add one to the quantity
// @param value - none
// Returns - none
void GroceryItem::addItem() {
	m_quantity++;
}

// Subtract one from the quantity
// @param value - none
// Returns - none
void GroceryItem::removeItem() {
	m_quantity--;
}