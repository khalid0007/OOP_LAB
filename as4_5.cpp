#include<iostream>
#include<string.h>

using namespace std;

class String
{
private:
    char* str;
    int* refcnt;

public:
    String()
    {
        str = new char[1];
        str[0] = '\0';
        refcnt = new int;
        *refcnt = 1;
    }

    String(const char* s)
    {
        str = new char[strlen(s) + 1];
        strcpy(str, s);

        refcnt = new int;
        *refcnt = 1;
    }


    String(char* s)
    {
        str = new char[strlen(s) + 1];
        strcpy(str, s);

        refcnt = new int;
        *refcnt = 1;

    }


    String(const String& s)
    {
        refcnt = s.refcnt;
        (*refcnt)++;

        str = s.str; 
    }

    ~String()
    {
        (*refcnt)--;
        cout << "String reference deleted!!" << endl;

        if(*refcnt == 0)
        {
            if(str != NULL) delete[] str;
            if(refcnt != NULL) delete refcnt;
            cout << "Memory deallocated!!" << endl;
        }
    }

    int size()
    {
        return strlen(str);
    }

    void operator=(String& b)
    {
        // Clear the current reference
        (*refcnt)--;

        if(*refcnt == 0)
        {
            if(str != NULL) delete[] str;
            if(refcnt != NULL) delete refcnt;
        }

        str = b.str;
        refcnt = b.refcnt;

        (*refcnt)++;
    }

    String& operator+(String b)
    {
        int final_length = strlen(str) + strlen(b.str) + 1;

        char x[final_length]; 

        strcpy(x, str);
        strcat(x, b.str);
        String* temp = new String(x);
        return (*temp); 
    }

    bool operator==(String& b)
    {
        if(strlen(str) != strlen(b.str)) return false;

        for(int i = 0; str[i]; i++)
            if(str[i] != b.str[i]) return false;

        return true;
    }

    bool operator<(String& s)
    {
        int i;
        for(i = 0; str[i] && s.str[i]; i++)
        {
            if(str[i] < s.str[i]) return true;
            else if(str[i] > s.str[i]) return false;
        }

        return (str[i] < s.str[i]);
    }

    bool operator>(String& s)
    {
        int i;
        for(i = 0; str[i] && s.str[i]; i++)
        {
            if(str[i] > s.str[i]) return true;
            else if (str[i] < s.str[i]) return false;
        }

        return (str[i] > s.str[i]);
    }

    bool operator<=(String& s)
    {
        int i;
        for(i = 0; str[i] && s.str[i]; i++)
        {
            if(str[i] < s.str[i]) return true;
            else if(str[i] > s.str[i]) return false;
        }

        return (str[i] <= s.str[i]);
    }

    bool operator>=(String& b)
    {
        int i;        
        for(i = 0; str[i] && b.str[i]; i++)
        {
            if(str[i] > b.str[i]) return true;
            else if (str[i] < b.str[i]) return false;
        }

        return (str[i] >= b.str[i]);
    }

    friend ostream& operator<<(ostream& stream,const String& a);
};

ostream& operator<<(ostream& stream,const String& a)
{
    stream << a.str;

    return stream;
}

int main()
{
    String a("hello");
    String b("hello ");

    String c = b + a;

    cout << c << endl;

    cout << (a == b) << endl;
    cout << (a < b) << endl;
    cout << (a > b) << endl;
    cout << (a >= b) << endl;
    cout << (a <= b) << endl;

    return 0;
}