#include<iostream>
#include<string>
#include<vector>

using namespace std;

#define MAX_SIZE 10

class Item
{
	int code, quantity;
	double rate;
	string name;
	public:
		void getData(int c = -1)
		{    
            if (c == -1) {cout << "Item code: "; cin >> code; getchar;}
            else code = c;
			cout << "Enter item name : ";
			getline(cin,name); 
			// getline(cin,name);
			cout << "Enter item rate : ";
			cin >> rate;
			cout << "Enter item quantity : ";
			cin >> quantity;
		}
	friend class Interface;
};

class Interface
{
private:
    int top;
    Item list[MAX_SIZE];

public:
    Interface()
    {
        top = -1;
    }

    int getPos(int codeItem)
    {
        if(top == -1)
            return -1;

        for(int i = 0; i <= top; i++)
        {
            if(list[i].code == codeItem) return i;
        }

        return -1;
    }

    void add_item()
    {
        int codeItem;
        cout << "Item code: "; cin >> codeItem; getchar();

        int pos = getPos(codeItem);

        if(pos != -1) 
        {
            cout << "Item already exists!!\n";
            return;
        }

        list[++top].getData(codeItem);
    }

    void change_rate()
    {
        int codeItem;
        cout << "Item code: "; cin >> codeItem; 

        int pos = getPos(codeItem);

        if(pos == -1)
        {
            cout << "Item don't exist in list\n";
            return;
        }

        int rt;
        cout << "Enter new rate: "; cin >> rt; 
        list[pos].rate = rt;

    }

    void issue_item()
    {
        int codeItem;
        cout << "Item code: "; cin >> codeItem; 
        int pos = getPos(codeItem);

        if(pos == -1)
        {
            cout << "Item don't exist in list\n";
            return;
        }

        int amnt;
        cout << "Amount to be issued: "; cin >> amnt;

        if(list[pos].quantity < amnt) {cout << "Too less quantity\n"; return;}
        else list[pos].quantity -= amnt;

    }

    void return_item()
    {
        int codeItem;
        cout << "Item code: "; cin >> codeItem;
        int pos = getPos(codeItem);

        if(pos == -1)
        {
            cout << "Item don't exist in list\n";
            return;
        }

        int amnt;
        cout << "Amount to be returned: "; cin >> amnt;

        list[pos].quantity += amnt;
    }

    void printQuantity()
    {
        int codeItem;
        cout << "Item code: "; cin >> codeItem;

        int pos = getPos(codeItem);

        if(pos == -1)
        {
            cout << "Item don't exist in list\n";
            return;
        }

        cout << "Quantity: " << list[pos].quantity << endl;
    }

    void printRate()
    {
        int codeItem;
        cout << "Item code: "; cin >> codeItem;

        int pos = getPos(codeItem);

        if(pos == -1)
        {
            cout << "Item don't exist in list\n";
            return;
        }

        cout << "Quantity: " << list[pos].rate << endl;
    }

};

int main(void)
{
	int ch, code;
	Interface obj;

	while(1)
	{
        // Clear screen:
        // For linux, unix, mac
        #if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
            system("clear");
        #endif

        // For win32 & win64
        #if defined(_WIN32) || defined(_WIN64)
            system("cls");
        #endif

        cout << "Press 1 to add an item\n";
        cout << "Press 2 to change rate of an item\n";
        cout << "Press 3 to issue an item\n";
        cout << "Press 4 to return an item\n";
        cout << "Press 5 to check available quantity of an item\n";
        cout << "Press 6 to check price of an item\n";
        cout << "Press 0 to exit\n";

		cout << "Enter your choice : ";
		cin >> ch;

		switch(ch)
		{
			case 1:
				obj.add_item();
				break;
			case 2:
				obj.change_rate();
				break;
			case 3:
				obj.issue_item();
				break;
			case 4:
				obj.return_item();
				break;
			case 5:
				obj.printQuantity();
				break;
			case 6:
				obj.printRate();
				break;
			case 0:
				exit(0);
			default:
				cout << "Invalid Choice !!! Please try again.\n";
		}


        cout << "Press enter to continue..."; getchar(); getchar();
	}
}