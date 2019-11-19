#include<iostream>
#include<queue>
using namespace std;

class student {
    int roll , score;
    string name;
public:
    student(string str = "" , int r = 0 , int sc = 0) {
        roll = r , name = str , score = sc;
    }
    void getdata();
    void display();
    int getRoll() {return roll;}
    int getScore() {return score;}
    string getName() {return name;}
    friend bool operator < (const student &s1 , const student &s2);
};

void student::getdata() {
    cout << "Enter Name : ";
    cin >> name;
    cout << "Enter roll : ";
    cin >> roll;
    cout << "Enter Score : ";
    cin >> score;
}

void student::display() {
    cout << "Name : " << name << "\n";
    cout << "Roll : " << roll << "\n";
    cout << "Score : " << score << "\n";
}

bool operator < (const student &s1 , const student &s2) {
    return s1.score < s2.score;
}

class Container {
    priority_queue<student> que;
public:
    void insert(student s[] , int size);
    void display();
};

void Container::insert(student s[] , int size) {
    for(int i = 0; i < size; i++) que.push(s[i]);
}

void Container::display() {
    while(!que.empty()) {
        cout << "\n";
        student s = que.top();
        s.display();
        que.pop();
    }
}

int main() {

    student s[2];
    for(int i = 0; i < 2; i++) s[i].getdata();
    Container D;
    D.insert(s , 2);
    D.display();

    return 0;
}
