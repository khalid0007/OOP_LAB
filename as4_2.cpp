#include<iostream>

using namespace std;

class complex
{
private:
    int rl;
    int im;

public:
    complex(int real, int imaginary = 0)
    {
        rl = real;
        im = imaginary;
    }

    complex operator+(complex a)
    {
        return complex(rl + a.rl, im + a.im);
    }

    complex operator-(complex a)
    {
        return complex(rl - a.rl, im - a.im);
    }

    complex operator*(complex a)
    {
        return complex(rl*a.rl - im*a.im, rl*a.im + im*a.rl);
    }

    friend ostream& operator<<(ostream& stream, complex a);
};

ostream& operator<<(ostream& stream, complex a)
{
    stream << a.rl << " + " << a.im << "i";

    return stream;
}

int main()
{
    cout << complex(12, 3) + complex(2) << endl;

    return 0;
}