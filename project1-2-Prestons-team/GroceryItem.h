#pragma once
#include <string>
using namespace std;

class GroceryItem {
private:
	string _name;
	int _quantity;
	float _unitPrice;
	bool _taxable;

public:
	GroceryItem();
	GroceryItem(const string&, const int&, const float&, const bool&);

	string getName() const;
	void setName(const string&);
	int getQuantity() const;
	void setQuantity(const int&);
	float getUnitPrice() const;
	void setUnitPrice(const float&);
	bool isTaxable() const;
	void setTaxable(const bool&);
};


GroceryItem::GroceryItem()
{
	_name = " ";
	_quantity = 0;
	_unitPrice = 0.0;
	_taxable = true;

}

GroceryItem::GroceryItem(const string& grocName, const int& grocQuantity, const float& grocPrice, const bool& statement)
{
	_name = grocName;
	_quantity = grocQuantity;
	_unitPrice = grocPrice;
	_taxable = statement;
}

string GroceryItem::getName() const
{
	return _name;
}

void GroceryItem::setName(const string& grocName)
{
	_name = grocName;
}

int GroceryItem::getQuantity() const
{
	return _quantity;
}

void GroceryItem::setQuantity(const int& grocQuantity)
{
	_quantity = grocQuantity;
}

float GroceryItem::getUnitPrice() const
{
	return _unitPrice;
}

void GroceryItem::setUnitPrice(const float& grocPrice)
{
	_unitPrice = grocPrice;
}


bool GroceryItem::isTaxable() const
{
	return _taxable;
}

void GroceryItem::setTaxable(const bool& statement)
{
	_taxable = statement;
}
