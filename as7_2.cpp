#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

class student {
    int roll , score;
    string name;
public:
    student(string str = "" , int r = 0 , int sc = 0) {
        roll = r , score = sc , name = str;
    }
    void getdata();
    void display();
    int getScore() {return score;}
    int getRoll() {return roll;}
    string getName() {return name;}
};

void student::getdata() {
    cout << "Enter Name : ";
    cin >> name;
    cout << "Enter roll : ";
    cin >> roll;
    cout << "Enter score : ";
    cin >> score;
}

void student::display() {
    cout << "Name : " << name << "\n";
    cout << "Roll : " << roll << "\n";
    cout << "Score : " << score << "\n";
}

class stu_list {
    vector<student> vec;
public:
    void insert(student &);
    void display(int);
    void remove(int);
    void highestScore();
    void with_without_Substr(string);
    void removeRoll(int);
    void Sort();
    friend void Merge(stu_list & , stu_list &);
    void showList();
};

void stu_list::insert(student &s) {
    vec.push_back(s);
}

void stu_list::display(int idx) {
   try {
       if(idx >= vec.size() || idx < 0) throw(idx);
       else vec[idx].display();
   } 
   catch(...) {
       cout << "Out of Bounds\n";
       return;
   }
}

void stu_list::remove(int idx) {
    try {
        if(idx >= vec.size() || idx < 0) throw(idx);
        else vec.erase(vec.begin()+idx);
    }
    catch(...) {
        cout << "Out of Bounds\n";
        return;
    }
}

bool cmp(student s1 , student s2) {
    return s1.getScore() < s2.getScore();
}
void stu_list::highestScore() {
    student stu = *max_element(vec.begin() , vec.end() , cmp);
    cout << "Student with Highest Score : \n";
    stu.display();
}

void stu_list::with_without_Substr(string pat) {
    vector<student> with , without;
    for(int i = 0; i < vec.size(); i++) {
        auto found = vec[i].getName().find(pat);
        if(found != string::npos) with.push_back(vec[i]);
        else without.push_back(vec[i]);
    }
    cout << "Students with " << pat << " in their name : \n";
    for(int i = 0; i < with.size(); i++) {
        with[i].display();
        cout << "\n";
    }
    cout << "Students without " << pat << " in their name : \n";
    for(int i = 0; i < without.size(); i++) {
        without[i].display();
        cout << "\n";
    }
}

void stu_list::removeRoll(int r) {
    for(int i = 0; i < vec.size(); i++) {
        if(vec[i].getRoll() == r) {
            vec.erase(vec.begin()+i);
            break;
        }
    }
}


bool cmp1(student s1 , student s2) {
    return s1.getRoll() > s2.getRoll();
}
void stu_list::Sort() {
    sort(vec.begin() , vec.end() , cmp1);
}

void Merge(stu_list &L1 , stu_list &L2) {
    // Merge contents of L2 in L1
    copy(L2.vec.begin(), L2.vec.end(), back_inserter(L1.vec));
}

void stu_list::showList() {
    for(int i = 0; i < vec.size(); i++) {
        vec[i].display();
        cout << "\n";
    }
}

int main() {

    stu_list L1 , L2;
    char c;
    do {
        student s;
        s.getdata();
        L1.insert(s);
        cout << "Want to insert more data (y/n) ? ";
        cin >> c; 
    }while(c == 'y' || c == 'Y');

    do {
        student s;
        s.getdata();
        L2.insert(s);
        cout << "Want to insert more data (y/n) ? ";
        cin >> c; 
    }while(c == 'y' || c == 'Y');
    //Merge(L1 , L2);
    L1.Sort();
    L1.showList();
    
    return 0;
}
