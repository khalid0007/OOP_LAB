#include<iostream>
#include<stdio.h>

using namespace std;

class Applicant
{
private:
    static int last_id;
    static int cnt;
    int id;
    char name[50];
    int mark;

public:
    void getData()
    {
        cout << "Enter Name: ";
        scanf("%[^\n]s", name);
        cin.get();
        cout << "Enter Mark: ";
        cin >> mark;
        id = ++(Applicant::last_id);
        (Applicant::cnt)++;
    }

    void disp() const
    {
        cout << "Application ID: " << id << endl;
        cout << "Name: " << name << endl;
        cout << "Mark: " << mark << endl;
    }

    static void PrintNumAppl()
    {
        cout << "Total applicants: " << Applicant::cnt << endl;
    }
};

// Intialise static member attributes:
int Applicant::last_id = 10000;
int Applicant::cnt = 0; 

int main()
{

    Applicant a;
    a.getData();
    a.disp();

    Applicant::PrintNumAppl();


    return 0;
}