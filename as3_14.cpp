#include<iostream>
using namespace std;

enum TransactionType {credit, debit};

class Date
{
private:
    int dd, mm, yyyy;

public:
    Date()
    {
        dd = mm = yyyy = 0;
    }

    Date(int x, int y, int z) {
        dd = x;
        mm = y;
        yyyy = z;
    }

    void setDate(int x, int y, int z)
    {
        dd = x;
        mm = y;
        yyyy = z;
    }

    void getDate()
    {
        cout << "Enter date: (dd mm yyyy) ";
        cin >> dd >> mm >> yyyy;
    }

    void show() const {cout << "Date: " << dd << "/" << mm << "/" << yyyy << endl;}
};

class Balance;

class Transaction
{
private:
    int id;
    double amount;
    TransactionType t;
    Date dt;
public:
    void getData()
    {
        // 1 for debit
        // 0 for credit
        int temp;
        cout << "Account number: "; cin >> id;
        cout << "Amount: "; cin >> amount;
        cout << "Withdrawal (Y/N): "; cin >> temp;
        t = static_cast<TransactionType>(temp);
        dt.getDate();
    }

    friend class Balance;
};

class Balance {
private:
    int number;
    double balance;
    Date last_transaction;

public:
    Balance(int n, double d)
    {
        number = n;
        balance = d;
        // last_transaction(0, 0, 0);
    }

    void getData()
    {
        cout << "Enter accnt number: ";
        cin >> number;
        cout << "Enter balance: ";
        cin >> balance;
    }

    void update_balance(Transaction& tr)
    {
        if(tr.t == debit)
        {
            if(tr.amount > balance)
            {
                cout << "Transaction unsuccessful!!" << endl;
                return;
            }

            else
            {
                balance -= tr.amount;
                last_transaction = tr.dt;
                cout << "Rs. " << tr.amount << " successfully debited from account number " << number << endl;
                last_transaction.show();
            }
        }

        else
        {
                balance += tr.amount;
                last_transaction = tr.dt;
                cout << "Rs. " << tr.amount << " successfully credited to account number " << number << endl;
                last_transaction.show();
        }
    }


};

int main() {

    Balance a(100, 200);
    Transaction t;
    t.getData();
    a.update_balance(t);
    t.getData();
    a.update_balance(t);
    t.getData();
    a.update_balance(t);
}