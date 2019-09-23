#include<iostream>
#include<string.h>

using namespace std;
class String
{

private:
    char* str;

public:
    String()
    {
        str = new char[1];
        str[0] = '\0';
    }

    String(const char* s)
    {
        str = new char[strlen(s) + 1];
        strcpy(str, s);
    }


    String(char* s)
    {
        str = new char[strlen(s) + 1];
        strcpy(str, s);
    }


    String(const String& s)
    {
		str = new char[strlen(s.str) + 1];
        strcpy(str, s.str); 
    }

    ~String()
    {

        if(str != NULL) delete[] str;
    }

    int size()
    {
        return strlen(str);
    }

    void operator=(String& b)
    {

        if(str != NULL) delete[] str;

		str = new char[strlen(b.str) + 1];

		strcpy(str, b.str);
    }

    String operator+(const String& b)
    {
        int final_length = strlen(str) + strlen(b.str) + 1;

        char appndstr[final_length + 1];
		strcpy(appndstr, str);
        strcat(appndstr, b.str);

		return String(appndstr);
    }

    bool operator==(const String& b)
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

	String a("hello ");
	String b("world!");

	cout << a + b << endl;



}
