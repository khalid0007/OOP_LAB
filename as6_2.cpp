#include<iostream>
#define __MAX_SIZE__ 100
using namespace std;

class Stu_List;
class student{
private:
    int roll;
    char name[40];
    int score;

public:
    student() {
        roll = -1;
        name = "Unknown";
        score = 0;
    }

    student(int roll_st, char* name_st, int marks_st) : roll(roll_st), score(marks_st) {strcpy(name, name_st);} 

    friend ostream& operator<<(ostream& stream, student a);
    friend istream& operator<<(istream& stream, student a);
    friend class Stu_List;
};

ostream& operator<<(ostream& stream, const student& a)
{
    stream << "\t\t Student Information\n";
    stream << "Name: " << name << "\n";
    stream << "Roll: " << roll << "\n";
    stream << "Score: " << score << "\n";
}

istream& operator<<(istream& stream, student& a)
{
    cout << "Enter Name: "; stream << a.name;
    cout << "Enter Roll: "; stream << a.roll;
    cout << "Enter Score: ";stream << a.score; 
}


class Stu_List{
private:
    int top;
    student list[__MAX_SIZE__];
public:
    Stu_List() : top(0) {}

    void insert()
    {
        cin >> list[top++];
    }

    void display(int indx)
    {
        int INDEX_OUT_OF_BOUND = 132532;
        try()
        {
            if(indx >= top || indx < 0)
            {
                throw INDEX_OUT_OF_BOUND;
            }

            else{
                cout << list[indx] << endl;
            }
        }

        catch(INDEX_OUT_OF_BOUND)
        {
            cout << "Index out of bound!!!\n";
        }
    }
    
};

int main()
{
    return 0;
}
