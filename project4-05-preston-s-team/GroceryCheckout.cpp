#include	<iostream>
#include <stdexcept>
#include	"GroceryCheckout.h"

using namespace std;

bool GroceryInventory::AddItem(const string& name, int quantity,
							   float price, bool taxable)
{

    if(FindItem(name) == NULL)
    {
        GroceryItem temp(name, quantity, price, taxable);
        Grocerystuff.insert(pair<string, GroceryItem>(name,temp));
        return true;
    }
    return false;

}

void GroceryInventory::CreateFromFile(const string& fileName)
{
    ifstream	file(fileName);
	string		name;
	float		price;
	int			quantity;
	bool		taxable;

	if (file.is_open())
	{
		while (true)
		{
			file >> name >> quantity >> price >> taxable;
			if (!file.fail())
			{
				AddItem(name, quantity, price, taxable);
			}
			else
			{
				break;
			}
         }
        file.close();
    }
	else
	{
        cout << "Could not open file " + fileName << endl;
    }

	return;
}

Receipt GroceryInventory::CreateReceipt(const string& fileName)
{
    ifstream input;
    Receipt obj;

	obj.subtotal_ = 0.0;
	obj.taxAmount_ = 0.0;
	obj.total_ = 0.0;


	input.open(fileName);

	std::string name;


	if (input.is_open())
	{
		while (input >> name)
		{
			if (Grocerystuff.find(name) != Grocerystuff.end())
			{
				ReceiptItem temp(name, Grocerystuff[name].price_);
				obj.item_.push_back(temp);
				--Grocerystuff[name].quantity_;
				obj.subtotal_ += Grocerystuff[name].price_;
				if (Grocerystuff[name].taxable_)
                {
                    obj.taxAmount_ += Grocerystuff[name].price_* (tax.taxAmount_);
                }
			else(cout << "Couldnt find the item\n");
		}
		obj.total_ = obj.subtotal_ + obj.taxAmount_;
	}

	return obj;

}
}

GroceryItem*	GroceryInventory::FindItem(const string& name)
{
	//	TO BE COMPLETED.
	for(navStatus = Grocerystuff.begin(); navStatus != Grocerystuff.end(); ++navStatus)
    {
        if(navStatus->first == name)
        {
            return &(navStatus->second);
        }
    }
    return NULL;
}

bool GroceryInventory::RemoveItem(const string& name)
{
	if(FindItem(name) != NULL)
    {
        Grocerystuff.erase(name);
        return &(navStatus->second);

    }

}

void GroceryInventory::SetTaxRate(float taxRate)
{
	tax.taxAmount_ = (taxRate/100);
}

size_t GroceryInventory::Size()
{
	return Grocerystuff.size();
}
