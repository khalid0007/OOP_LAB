#include<iostream>
#include<limits>
#include<iterator>

using namespace std;

class Array 
{
private:
    int sz;
    int* a;

public:
    Array(int size){
        sz = size;
        a = new int[sz];

        for(int i = 0; i < sz; i++) a[i] = 0;
    }

    Array(const Array& arr)
    {
        sz = arr.sz;
        a = new int[sz];

        for(int i = 0; i < sz; i++) a[i] = arr.a[i];
    }

    Array(int size, int arr[])
    {
        sz = size;
        a = new int[sz];

        for(int i = 0; i < sz; i++) a[i] = arr[i];
    }

    ~Array()
    {
        if(a != NULL) delete[] a;
    }

    int size()
    {
        return sz;
    }

    void operator=(const Array& original)
    {
        if(sz != original.sz){
            cout << "Invalid assignment between array of different size!!!\n";
            return;
        }

        for(int i = 0; i < sz; i++) a[i] = original.a[i];
    }

    Array operator+(const Array& original)
    {
        Array temp(*this);
        if(sz != original.sz){
            cout << "Invalid assignment between array of different size!!!\n";
            return temp;
        }

        for(int i = 0; i < sz; i++) temp.a[i] = a[i] + original.a[i];

        return temp;
    }
    Array& operator*(int multiplier)
    {
        for(int i = 0; i < sz; i++) a[i] *= multiplier;

        return (*this);
    }

    friend Array& operator*(int, Array&);

    int& operator[](int indx)
    {
        if(indx >= sz)
        {
            cout << "Index out of range!!!" << "\n";
            int* temp = new int;
            *temp = INT32_MAX;
            return *temp;
        }

        else return a[indx];
    }

    friend ostream& operator<<(ostream& stream,const Array& c);
};

Array& operator*(int multiplier, Array& multiplicant)
{
    for(int i = 0; i < multiplicant.sz; i++) multiplicant[i] *= multiplier;

    return multiplicant;
}


ostream& operator<<(ostream& stream,const Array& c)
{
    stream << "{";

    copy(c.a, c.a + c.sz - 1, ostream_iterator<int>(stream, ", "));

    stream << c.a[c.sz - 1] << "}";

    return stream;
}


int main()
{
    int arr[] = {1, 2, 3, 4, 5}; 
    Array a(5);
    Array c(5, arr);
    Array d(c);
    Array e = d + c;

    cout << a << endl;
    cout << c << endl;
    cout << d << endl;
    cout << e << endl;

    e*5;
    cout << e << endl;
    2*e;
    cout << e << endl;

    cout << d[2] << endl;    

    return 0;
}