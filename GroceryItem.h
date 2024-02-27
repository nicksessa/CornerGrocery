#pragma once
#ifndef GroceryItem_h
#define GroceryItem_h
#include <string>

class GroceryItem {
public:
	GroceryItem(std::string& name);
	GroceryItem(std::string& name, int quantity);

	std::string getName() const;
	int getQuantity() const;

	void addItem();
	void removeItem();

	bool operator<(const GroceryItem& other) const;

private:
	std::string m_name;
	int m_quantity = 0;
};

#endif