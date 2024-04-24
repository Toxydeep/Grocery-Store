// C++ Program to implement Online shopping management
// system
#include <bits/stdc++.h>

using namespace std;
using namespace std::this_thread;
using namespace std::chrono;

// map data structure to store category-model as key and
// their price as value
map<string, map<string, double> > items;

// map data structure to store category-model in integer
// form as key and their model selected by the customer as
// value
map<pair<int, int>, string> names;

// a function to fill the product data into the data
// structure
void fillItems()
{
	items["FRUITS"]["Banana"] = 150;
	items["FRUITS"]["Mango"] = 120;
	items["FRUITS"]["Apple"] = 100;
	items["VEGETABLES"]["Tomato"] = 40;
	items["VEGETABLES"]["Onions"] = 35;
	items["VEGETABLES"]["Potato"] = 25;
	items["DAIRYPRODUCTS"]["Biscuit"] = 100;
	items["DAIRYPRODUCTS"]["Milk"] = 50;
	items["DAIRYPRODUCTS"]["Eggs"] = 15;
	items["DAIRYPRODUCTS"]["Butter"] = 53;

	// by default, category 1 is fruits, category 2 is
	// vegetables and category 3 is dairyproducts
	/// similarly, 1,2,3 in the second part of the key
	/// represent their model
	names[{ 1, 1 }] = "Banana";
	names[{ 1, 2 }] = "Mango";
	names[{ 1, 3 }] = "Apple";

	names[{ 2, 1 }] = "Tomato";
	names[{ 2, 2 }] = "Onions";
	names[{ 2, 3 }] = "Potato";

	names[{ 3, 1 }] = "Biscuit";
	names[{ 3, 2 }] = "Milk";
	names[{ 3, 3 }] = "Eggs";
	names[{ 3, 4 }] = "Butter";
}

// class customer to represent a real world entity, in our
// case - a customer
class customer {
	// map data strucute to store category-model as key and
	// their quantity selected by the customer as value
	map<string, map<string, int> > selected_items;

	// name of the customer. Here more data can be collected
	// from customer like phone number etc, but here we have
	// only collected name as an example
	string name;

public:
	// constructor
	customer()
	{
		cout << "Enter your name: ";
		string customer_name;
		getline(cin, customer_name);
		name = customer_name;
		cout << "HI ";
		for (int i = 0; i < customer_name.length(); i++) {
			cout << char(toupper(customer_name[i]));
		}
		cout << "\n\n\n";
	}

	// function to insert item in the data structure alloted
	// to customer
	void addToCart(string a, string b)
	{
		selected_items[a][b]++;
	}

	// function to print the bill during check-out
	void printBill()
	{
		int total_amount = 0;
		cout << "Category\t"
			<< "Item\t"
			<< "Quantity\t"
			<< "Cost\n";

		// iterators to traverse over respective maps
		map<string, map<string, int> >::iterator itr;
		map<string, int>::iterator ptr;
		for (itr = selected_items.begin();
			itr != selected_items.end(); itr++) {
			for (ptr = itr->second.begin();
				ptr != itr->second.end(); ptr++) {
				string category = itr->first;
				string model = ptr->first;
				int quantity = ptr->second;
				int temp
					= quantity * items[category][model];
				cout << category << "\t\t" << model << "\t"
					<< quantity << "\t\t" << temp << endl;
				total_amount += temp;
			}
		}

		cout << "-------------------------------"
			<< "-------------\n";
		cout << "Total amount:			 \t\t"
			<< total_amount << endl;
		cout << "-------------------------------"
			<< "-------------\n";
		cout << "*THANK YOU && HAPPY"
			<< " ONLINE SHOPPING*";
	}
};

// class shop to represent a real world entity - in our case
// a shop
class shop {

public:
	shop() {}

	virtual void show()
	{
		// this will be overridden
	}
	virtual void select(customer& obj)
	{
		// this will be overridden
	}

	void showMenu()
	{
		cout << "				 Menu\n";
		cout << " -----------------------------------------"
				"\n";
		cout << "1.FRUITS\n2.VEGETABLES\n3"
			<< ".DAIRY PRODUCTS\n4.Checkout\n\n";
		cout << " -----------------------------------------"
				"\n";
	}
};

// class Fruits inheriting properties from class shop
class FRUITS : public shop {
public:
	void show()
	{
		cout << "- - - - - - - - - - -"
			<< " - -\nItem Cost\n";
		int cnt = 1;
		for (auto& it : items["FRUITS"]) {
			cout << cnt++ << ". " << it.first << " --- Rs."
				<< it.second << "/-\n";
		}

		cout << "- - - - - - - - - - - - -\n\n";
	}

	void select(customer& obj)
	{
		cout << "These are the Grocery categories we "
				"have....\n";
		int num;
		cout << "Enter your selection\n";
		cin >> num;
		if (num < 1 || num > 3) {
			cout << "Wrong Input\n";
			return;
		}
		cout << "\n\nPURCHASE SUCCESSFULL!! ";
		cout << names[{ 1, num }]
			<< " IS ADDED TO THE CART\n\n";
		obj.addToCart("", names[{ 1, num }]);
	}
};

// class VEGETABLES inheriting properties from class shop
class VEGETABLES : public shop {
public:
	void show()
	{
		cout << "- - - - - - - - - - -"
			<< " - -\nItem Cost\n";
		int cnt = 1;
		for (auto& it : items["VEGETABLES"]) {
			cout << cnt++ << ". " << it.first << " --- Rs."
				<< it.second << "/-\n";
		}
		cout << "- - - - - - - - - - - - -\n";
	}
	void select(customer& obj)
	{
		cout << "These are the VEGETABLES categories we "
				"have....\n";
		int num;
		cout << "Enter your selection\n";
		cin >> num;
		if (num < 1 || num > 3) {
			cout << "Wrong Input\n";
			return;
		}
		cout << "\n\nPURCHASE SUCCESSFULL!! ";
		cout << names[{ 2, num }]
			<< " IS ADDED TO THE CART\n\n";
		obj.addToCart("VEGETABLES", names[{ 2, num }]);
	}
};

// class DAIRY PRODUCTS inheriting properties from class shop
class DAIRYPRODUCTS : public shop {
public:
	void show()
	{
		cout << "- - - - - - - - - - "
			<< " - -\nItem	 Cost\n";
		int cnt = 1;
		for (auto& it : items["DAIRYPRODUCTS"]) {
			cout << cnt++ << ". " << it.first << " --- Rs."
				<< it.second << "/-\n";
		}
		cout << "- - - - - - - - - - - - -\n";
	}
	void select(customer& obj)
	{
		cout << "These are the DAIRY PRODUCTS categories we "
				"have....\n";
		int num;
		cout << "Enter your selection\n";
		cin >> num;
		if (num < 1 || num > 4) {
			cout << "Wrong Input\n";
			return;
		}
		cout << "\n\nPURCHASE SUCCESSFULL!! ";
		cout << names[{ 3, num }]
			<< " IS ADDED TO THE CART\n\n";
		obj.addToCart("DAIRYPRODUCTS", names[{ 3, num }]);
	}
};

int main()
{
	// filling the hardcoded shop items in the data
	// structure
	fillItems();
	cout << "WELCOME TO OUR SHOP. WE ARE DELIGHTED THAT "
			"YOU ARE HERE. HOW CAN WE HELP YOU? WE DEAL IN "
			"GROCERY PRODUCTS.\n";
	customer c;
	shop* s;

	while (1) {

		s->showMenu();
		cout
			<< "Please select an option to proceed "
			"further. If you choose to checkout, "
			"shopping will end and bill will be "
			"generated for the items bought so far...\n";
		int val;
		cin >> val;

		if (val == 1) {
			 FRUITS mb;
			s = &mb;
			s->show();
			s->select(c);
		}
		else if (val == 2) {
			VEGETABLES lp;
			s = &lp;
			s->show();
			s->select(c);
		}
		else if (val == 3) {
			DAIRYPRODUCTS cs;
			s = &cs;
			s->show();
			s->select(c);
		}
		else if (val == 4) {
			c.printBill();
			break;
		}
		else {
			cout << "Wrong Input. If you want to checkout, "
					"you can press 4\n\n";
		}
		cout << "REDIRECTING TO THE MAIN MENU.....\n\n";

		// a function call to add a deliberate delay
		sleep_until(system_clock::now() + seconds(3));

		// clear screen
		system("cls");
	}

	return 0;
}
