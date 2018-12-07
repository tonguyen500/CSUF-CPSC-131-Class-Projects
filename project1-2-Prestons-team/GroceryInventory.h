#pragma once
#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdexcept>
#include "GroceryItem.h"
using namespace std;

class GroceryInventory {
private:
	vector<GroceryItem> _inventory;
	float _taxRate;

public:
	GroceryInventory();      // constructor
	GroceryInventory(const float&);    // constructor


	GroceryItem& getEntry(const string&);
	void addEntry(const string&, const int&, const float&, const bool&);
	float getTaxRate() const;
	void setTaxRate(const float&);

	void createListFromFile(const string& filename);
	float calculateUnitRevenue() const;
	float calculateTaxRevenue() const;
	float calculateTotalRevenue() const;

	GroceryItem& operator[](const int&);
};

GroceryInventory::GroceryInventory()
{
	_taxRate = 0.0;

}

GroceryInventory::GroceryInventory(const float& invtaxrate)
{
	_taxRate = invtaxrate;
}


void GroceryInventory::addEntry(const string& grocName, const int& grocQuantity, const float& grocPrice, const bool& statement)
{
       GroceryItem temp(grocName, grocQuantity,grocPrice,statement);
       _inventory.push_back(temp);

}

GroceryItem& GroceryInventory::getEntry(const string& foo)
{
    for(size_t i = 0; i < _inventory.size();++i)
    {
        if(_inventory[i].getName() == foo )
        {
            return _inventory[i];

        }
    }
    throw invalid_argument("Invalid");
}

float GroceryInventory::getTaxRate() const
{
	return _taxRate;
}

void GroceryInventory::setTaxRate(const float& invtaxrate)
{
	_taxRate = invtaxrate;
}


float GroceryInventory::calculateUnitRevenue() const
{
	float total = 0.0f;

	for (int i = 0; i < _inventory.size(); ++i)
	{
		 total += ((float)_inventory[i].getUnitPrice() * (float)_inventory[i].getQuantity());

	}
	return total;
}

float GroceryInventory::calculateTaxRevenue() const
{
	float taxrev = 0.0;

	for (int i = 0; i < _inventory.size(); ++i)
	{
		if (_inventory[i].isTaxable() == true)
		{
		    taxrev += ( (_inventory[i].getQuantity() * _inventory[i].getUnitPrice()) * (getTaxRate()/100.f));

		}


	}
	  return taxrev;
}

float GroceryInventory::calculateTotalRevenue() const
{
	float totalrev = 0.0;
	for (int i = 0; i < _inventory.size(); ++i)
	{
		totalrev += (_inventory[i].getUnitPrice() * _inventory[i].getQuantity());
	}
			totalrev += calculateTaxRevenue();

	return totalrev;
}


void GroceryInventory::createListFromFile(const string& filename) {
	ifstream input_file(filename.c_str());

	if (input_file.is_open()) {
		cout << "Successfully opened file " << filename << endl;
		string name;
		int quantity;
		float unit_price;
		bool taxable;
		while (input_file >> name >> quantity >> unit_price >> taxable) {
			addEntry(name, quantity, unit_price, taxable);
		}
		input_file.close();
	}
	else {
		throw invalid_argument("Could not open file " + filename);
	}
}
