#include<iostream>
#include<string.h>
#include<iomanip>

using namespace std;


class Date{
public:
    int day, month, year;

    Date(int d, int m, int y) :day(d), month(m), year(y) {}
};

ostream& operator<<(ostream& stream, Date a)
{
    stream << "(";
    stream << setfill('0') << setw(2); 
    stream << a.day  << "/";
    stream << setfill('0') << setw(2); 
    stream << a.month;
    stream << "/" << a.year;
    stream << ")";

    return stream;
}

class player{
protected:
    char name[30];
    Date dob;
    int match_played;

public:
    player(char* n, Date d, int played) : dob(d), match_played(played) {strcpy(name, n);}

    virtual void show_details() {
        // Should be overridden 
    }
};

class batsman: virtual public player{
protected:
    double runs;
    double avarage;

public:
    batsman(char* n, Date d, int played, double run, double avr) : player(n, d, played), runs(run), avarage(avr) {}

    virtual void show_details()
    {
        cout << "Type: Batsman\n" << "Name: " << name << "\n";
        cout << "Date of birth: " << dob << "\n";  
        cout << "Match played: " << match_played << "\n";
        cout << "Total run scored: " << runs << "\n";
        cout << "Avarage score: " << avarage << "\n";
    }
};

class bowler: virtual public player{
protected:
    int wicket;
    double economy;

public:
    bowler(char* n, Date d, int played, int wicket, double economy) : player(n, d, played), wicket(wicket), economy(economy) {}
    
    virtual void show_details()
    {
        cout << "Type: Bowler\n" << "Name: " << name << "\n";
        cout << "Date of birth: " << dob << "\n";  
        cout << "Match played: " << match_played << "\n";
        cout << "Total wicket taken: " << wicket << "\n";
        cout << "Economy: " << economy << "\n";
    }
};

class all_rounder: public batsman, public bowler
{
public:
    all_rounder(char* n, Date d, int played, double run, double avr, int wick, double eco) : player(n,d,played), batsman(n,d,played, run, avr),
                                                bowler(n,d,played, wick, eco)
    {
        strcpy(name, n);
        dob = d;
        match_played = played;
        runs = run;
        avarage = avr;
        wicket = wick;
        economy = eco;
    }

    void show_details() override
    {
        cout << "Type: All Rounder\n" << "Name: " << name << "\n";
        cout << "Date of birth: " << dob << "\n";  
        cout << "Match played: " << match_played << "\n";
        cout << "Total run scored: " << runs << "\n";
        cout << "Avarage score: " << avarage << "\n";
        cout << "Total wicket taken: " << wicket << "\n";
        cout << "Economy: " << economy << "\n";
    }
};

int main()
{
    char name[30] = "Sachin Tendulkar";
    batsman a(name, Date(12, 3, 1980), 2000, 12534, 87.60);
    all_rounder b(name, Date(12, 3, 1980), 2000, 12534, 87.60, 100, 12.3);

    player* ptr;

    // ptr = &a;
    // ptr->show_details();
    ptr = &b;
    ptr->show_details();
    return 0;
}
