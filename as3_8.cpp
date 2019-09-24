#include<iostream>
#include<string.h>
#include<stdio.h>

using namespace std;

class TIME
{
private:
    int hr;
    int min;
    int sec;

public:
    TIME()
    {
        hr = 0; min = 0; sec = 0;
    }

    TIME(int hour, int minute, int second)
    {
        hr = hour;
        min = minute;
        sec = second;
    }

    TIME(char *time)
    {
        // Length of time string
        int len = strlen(time);

        
        hr = (time[0] - '0')*10 + (time[1] - '0');
        min = (time[3] - '0')*10 + (time[4] - '0');
        sec = (time[6] - '0')*10 + (time[7] - '0');

        if(time[len - 1] == 'M' && time[len - 2] == 'P') hr = (hr + 12)%24;

        // Normalising
        hr = hr + min/60;
        min = (min % 60) + sec/60;
        sec = (sec%60);
    }

    TIME(const char *time)
    {
        // Length of time string
        int len = strlen(time);

        
        hr = (time[0] - '0')*10 + (time[1] - '0');
        min = (time[3] - '0')*10 + (time[4] - '0');
        sec = (time[6] - '0')*10 + (time[7] - '0');

        if(time[len - 1] == 'M' && time[len - 2] == 'P') hr = (hr + 12)%24;

        // Normalising
        hr = hr + min/60;
        min = (min % 60) + sec/60;
        sec = (sec%60);
    }

    void getTime()
    {
        char time[15];

        cout << "Enter time: ";
        scanf("%[^\n]s", time);
        cin.get();

        // Length of time string
        int len = strlen(time);

        
        hr = (time[0] - '0')*10 + (time[1] - '0');
        min = (time[3] - '0')*10 + (time[4] - '0');
        sec = (time[6] - '0')*10 + (time[7] - '0');

        if(time[len - 1] == 'M' && time[len - 2] == 'P') hr = (hr + 12)%24;

        // Normalising
        hr = hr + min/60;
        min = (min % 60) + sec/60;
        sec = (sec%60);
    }

    void disp_24F()
    {
        cout << hr << " : " << min << " : " << sec << endl;
    }

    void disp_AMPM()
    {
        bool pm = hr/12;

        if(hr > 12) hr = hr - 12;
        if(hr == 0) hr += 12;

        if(pm) cout << hr << " : " << min << " : " << sec << " PM" << endl;
        else cout << hr << " : " << min << " : " << sec << " AM" << endl;
    }

    void addMin(int m)
    {
        min += min + m;

        hr = hr + min/60;
        min = min % 60;
    }
};

int main()
{
    TIME a("00:34:24");
    TIME b("12:34:23 PM");

    a.disp_24F();
    a.disp_AMPM();
}