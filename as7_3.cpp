#include<iostream>
#include<queue>
using namespace std;

class student {
    int roll , score[5];
    string name;
public:
    student(string str = "" , int r = 0) {
        roll = r , name = str;
    }
    void getdata();
    void display();
    int getRoll() {return roll;}
    string getName() {return name;}
};

void student::getdata() {
    cout << "Enter Name : ";
    cin >> name;
    cout << "Enter roll : ";
    cin >> roll;
    cout << "Enter score in 5 subjects : ";
    for(int i = 0; i < 5; i++) cin >> score[i];
}

void student::display() {
    cout << "Name : " << name << "\n";
    cout << "Roll : " << roll << "\n";
    cout << "Score Card : \n";
    for(int i = 0; i < 5; i++) cout << "Subject" << i+1 << " : " << score[i] << "\n";
}

class MarkSheetDesk {
    queue<student> que;
public:
    void insert(student s[] , int size);
    void display();
};

void MarkSheetDesk::insert(student s[] , int size) {
    for(int i = 0; i < size; i++) que.push(s[i]);
}

void MarkSheetDesk::display() {
    while(!que.empty()) {
        cout << "\n";
        que.front().display();
        que.pop();
    }
}

int main() {

    student s[2];
    for(int i = 0; i < 2; i++) s[i].getdata();
    MarkSheetDesk D;
    D.insert(s , 2);
    D.display();

    return 0;
}
