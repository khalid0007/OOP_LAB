#include<iostream>
using namespace std;

template <typename T>
class Array {
    T *ptr;
    int size;
public: 
    Array(int);
    void getdata();
    T maxm();
    T sum();
};

template <typename T>
Array<T>::Array(int s) {
    size = s;
    ptr = new T[size];
}

template <typename T>
void Array<T>::getdata() {
    cout << "Enter Array Elements : \n";
    for(int i = 0; i < size; i++) cin >> ptr[i];
}

template <typename T>
T Array<T>::maxm() {
    T res = ptr[0];
    for(int i = 1; i < size; i++) {
        if(res < ptr[i]) res = ptr[i];
    }
    return res;
}

template <typename T>
T Array<T>::sum() {
    T res = ptr[0];
    for(int i = 1; i < size; i++) res += ptr[i];
    return res;
}

int main() {
    Array<int> a(5);
    a.getdata();
    cout << a.maxm() << "\n";
    return 0;
}
