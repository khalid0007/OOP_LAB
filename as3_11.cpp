#include<iostream>
#include<stdint.h>
#include<string.h>
#include<stdio.h>


#define pause cout << "Press Enter to continue...\n"; getchar()

#define STDNT_LMT 100

int cnt = 0;

using namespace std;

class date
{
public:
    int day, month, year;

    date()
    {
        day = INT32_MIN;
        month = INT32_MIN;
        year = INT32_MIN;
    }

    date(int dd, int mm, int yy)
    {
        day = dd; month = mm; year = yy;
    }

    void show_date()
    {
        cout << day << "/" << month << "/" << year << endl;
    }
};


/*
ostream& operator<<(ostream &stream, date d)
{
    stream << d.day << "/" << d.month << "/" << d.year;

    return stream;
}*/

void operator>>(istream& stream, date& d)
{
    cout << "(dd mm yyyy) ";
    stream >> d.day >> d.month >> d.year;
}

class student_list;

class Student 
{
    friend class student_list;
private:
    int roll;
    int scores[5];
    char course[20];
    char name[50];
    date DOA;

    //static int count;

public:

    
    Student()
    {
        for(int i = 0; i < 5; i++)  scores[i] = INT32_MIN;
    }

    Student(char* Name_student, int Roll_student, char* Course_student, date DOA_student)
    {
        roll = Roll_student;
        DOA = DOA_student;

        int i;
        for(i = 0; i < 5; i++)  scores[i] = INT32_MIN;
        
        for(i = 0; i <= strlen(Name_student); i++) name[i] = Name_student[i];

        //name[i] = '\0';

        for(int i = 0; i <= strlen(Course_student); i++) course[i] = Course_student[i];

        //course[i] = '\0';
    }

    void show_data()
    {
        cout << "-----------------------------<Student_Info>-----------------------------\n";
        cout << "Name: " << name << endl;
        cout << "Roll: " << roll << endl;
        cout << "Course Name: " << course << endl;

        cout << "Date of Admission: ";
        DOA.show_date();    
    }

    void print_marksheet()
    {
        char subject_names[5][20] = {"Subject1", "Subject2", "Subject3", "Subject4", "Subject5"};

        cout << "-----------------------------<MarkSheet>-----------------------------\n";
        cout << "Name: " << name << endl;
        cout << "Roll: " << roll << endl;
        cout << "Course Name: " << course << endl;

        for(int i = 0; i < 5; i++)
            cout << subject_names[i] << "\t";
        
        cout << endl;
        
        for(int i = 0; i < 5; i++)
        {
            if(scores[i] == INT32_MIN) cout << "N/A" << "\t\t";
            else cout << scores[i] << "\t\t";
        }
        cout << endl;
    }

    update_marks(int marks[5])
    {
        for(int i = 0; i < 5; i++) scores[i] = marks[i];
    }
};

class student_list
{
private:
    int count;
    Student** list;

public:
    student_list()
    {
        count = 0;
        if((list = new Student*[STDNT_LMT]) == NULL) cerr << "malloc error\n";
        //memset(list, NULL, STDNT_LMT);
    }

    student_list(int estimate_size)
    {
        count = 0;

        if((list = new Student*[estimate_size]) == NULL) cerr << "malloc error\n";
        //memset(list, NULL, STDNT_LMT);
    }

    void append()
    {
        int Roll, dd, mm, yy;
        char Name[30], dept[20];
        date DOA;

        cout << "Enter roll: "; cin >> Roll;
        getchar();

        cout << "Enter name: ";
        scanf("%[^\n]s", Name);
        getchar();

        cout << "Enter course name: ";
        scanf("%[^\n]s", dept);
        getchar();

        cout << "Enter date of admission: ";
        cin >> DOA;

        list[count++] = new Student(Name, Roll, dept, DOA);
    }

    void enter_marks(int indx)
    {
        cout << "Enter marks: ";
        int m[5];

        for(int i = 0; i < 5; i++) cin >> m[i];

        (*list[indx]).update_marks(m);
    }

    Student& operator[](int n)
    {
        if(count > n + 1)
        {
            cerr << "Index out of range!!\n";
            exit(1);
        }

        return *list[n];
    }

    int size()
    {
        return count;
    }

    void update(int Roll)
    {
        for(int i = 0; i < count; i++)
        {
            if((*this)[i].roll == Roll)
            {
                enter_marks(i);
                return;
            }
        }

        cout << "Student data don't exist\n";
    }

    void info_print(int Roll)
    {
        for(int i = 0; i < count; i++)
        {
            if((*this)[i].roll == Roll)
            {
                (*this)[i].show_data();
                return;
            }
        }

        cout << "Student data don't exist\n";
    }


    void marksheet_print(int Roll)
    {
        for(int i = 0; i < count; i++)
        {
            if((*this)[i].roll == Roll)
            {
                (*this)[i].print_marksheet();
                return;
            }
        }

        cout << "Student data don't exist\n";
    }

    ~student_list()
    {
        delete list;
    }
};


bool menu(student_list& l)
{
    bool flag = true;
    
    system("cls");

    printf("---------------------<MENU>---------------------\n");
    printf("<1> Admission\n");
    printf("<2> Update marks\n");
    printf("<3> Show student_info\n");
    printf("<4> Print Marksheet\n");
    printf("<5> Print total admission\n");
    printf("<6> Exit menu\n");


    printf("\nEnter choice: ");
    int choice, roll; cin >> choice;

    switch(choice)
    {
        case 1:

            system("cls");

            l.append();
            break;

        case 2:
            system("cls");

            cout << "Enter roll: ";
            cin >> roll;
            l.update(roll);
            pause;
            break;

        case 3:

            system("cls");

            cout << "Enter roll: ";
            cin >> roll;
            l.info_print(roll);
            getchar();
            pause;
            break;
        case 4:

            system("cls");

            cout << "Enter roll: ";
            cin >> roll;
            l.marksheet_print(roll);
            getchar();
            pause;
            break;

        case 5:
            system("cls");

            cout << "Total admissions: " <<  l.size() << endl;
            getchar();
            pause;
            break;
        case 6:
            flag = false;
            break;
        default:
            cout << "Invalid OP-Code\n";
    }

    return flag;
}

int main()
{

    student_list a;

    while(menu(a));

    return 0;
}