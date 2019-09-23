#include<iostream>
#include<limits>
#include<iterator>

#define MAX_SIZE 1000

using namespace std;

class Account
{
private:
    int accnt_number; // Unique accnt number
    int blnc; // Balance

public:
    Account()
    {
        accnt_number = INT32_MIN;
        blnc = INT32_MIN;
    }

    Account(int number,int balance)
    {
        accnt_number = number; 
        blnc = balance;
    }
    ~Account()
    {
        if(accnt_number != INT32_MAX) cout << "Account closed!!" << endl;
    }

    void set(int number,int balance = 0)
    {
        accnt_number = number; 
        blnc = balance;
    }

    void set_balance(int balance)
    {
        blnc = balance;
    }

    void debit(int amnt)
    {
        if(amnt > blnc)
        {
            cout << "Too less money to debit!!\n";
            return;
        }

        blnc -= amnt;
        cout << "Rs." << amnt << " debited from account number: " << accnt_number << endl;
    }

    void credit(int amnt)
    {
        blnc += amnt;
        cout << "Rs." << amnt << " credited from account number: " << accnt_number << endl;
    }

    friend ostream& operator<<(ostream& stream, Account& a);
};

ostream& operator<<(ostream& stream, Account& a)
{
    stream << "Account Number: " << a.accnt_number << endl << "Net Balance: " << a.blnc << endl;

    return stream;
}

class AccountList
{
    Account list[MAX_SIZE];
    int top;
public:
    AccountList()
    {
        top = -1;
    }

    add(int number, int balance = 0)
    {
        list[++top].set(number, balance);
        cout << "New account added!!" << endl;
    }

    friend ostream& operator<<(ostream& stream, AccountList& a);

};

ostream& operator<<(ostream& stream, AccountList& a)
{
    stream << "Account List: \n";
    for(int i = 0; i <= a.top; i++)
    {
        stream << "------------------------------<" << i + 1 << ">------------------------------\n" << a.list[i];
    }

    return stream;
}

int main()
{

    AccountList a;

    a.add(1, 100);
    a.add(2, 1000);

    cout << a;

    return 0;
}