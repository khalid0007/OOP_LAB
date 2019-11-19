#include<iostream>
#include<map>
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

class Map {
    map<int , student> _map;
public:
    void insert(student s[] , int size);
    void display();
    void fetchScore(int);
};

void Map::insert(student s[] , int size) {
    for(int i = 0; i < size; i++) _map.insert({s[i].getRoll(), s[i]});
}

void Map::display() {
    for(auto itr:_map) {
        cout << "\n";
        itr.second.display();
    }
}

void Map::fetchScore(int r) {
    cout << "\nScore of Roll " << r << " is : " << _map[r].getScore() << "\n";
}

int main() {

    student s[2];
    for(int i = 0; i < 2; i++) s[i].getdata();
    Map M;
    M.insert(s , 2);
    M.display();

    return 0;
}
