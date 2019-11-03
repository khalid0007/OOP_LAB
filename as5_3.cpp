#include<iostream>
#include<string.h>

using namespace std;

class Employee{
protected:
    int id;
    char name[30];
    char designation[30];
    double basic;
public:
    // Employee(int i, char * name)
    virtual double generate_salary()
    {
        // Should be overridden
        return basic;
    }
};

class PEmp: public Employee{

public:
    PEmp(int i,const char* EmpName,const char* des, double base)
    {
        Employee::id = i;
        strcpy(Employee::name, EmpName);
        strcpy(Employee::designation, des);
        Employee::basic = base;
    }

    double generate_salary() override {
        double da = 0.8*Employee::basic;
        double hra = 0.3*Employee::basic;
        return (Employee::basic + da + hra);
    }
};

class CEmp: public Employee{
private:
    double allowance;
public:
    CEmp(int i,const char* EmpName,const char* des, double base, double allow)
    {
        Employee::id = i;
        strcpy(Employee::name, EmpName);
        strcpy(Employee::designation, des);
        Employee::basic = base;
        allowance = allow;
    }

    double generate_salary() override {
        return (Employee::basic + allowance);
    }
};

int main()
{
    PEmp* p1 = new PEmp(1, "Sandipan Saha", "Ass. Prof", 12000);
    CEmp* p2 = new CEmp(2, "Mrityunjoy Dey", "Ass. Prof", 8000, 8000);

    Employee* p = p1;

    cout << p->generate_salary() << endl;
    p = p2;

    cout << p->generate_salary() << endl;
    
    return 0;
}
