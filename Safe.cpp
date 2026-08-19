#include <iostream>
#include <string>
#include <climits>
using namespace std;

int main()
{
    int a = 40000;

    if(a >= SHRT_MIN && a <= SHRT_MAX)
    {
        short b = a;
        cout << a << " -> " << b << endl;
    }
    else
        cout << "Int to short is incorrect" << endl;


    int x = -25;

    if(x >= 0)
    {
        unsigned int y = x;
        cout << x << " -> " << y << endl;
    }
    else
        cout << "signed to unsigned is incorrect" << endl;


    float f = 123.99;

    if(f >= INT_MIN && f <= INT_MAX && f == (int)f)
    {
        int n = f;
        cout << f << " -> " << n << endl;
    }
    else
        cout << "float to int is incorrect" << endl;


    string s = "12abc";

    try
    {
        size_t p;
        int num = stoi(s, &p);

        if(p == s.length())
            cout << s << " -> " << num << endl;
        else
            cout << "String to numeric is incorrect" << endl;
    }
    catch(...)
    {
        cout << "String to numeric is incorrect" << endl;
    }

    return 0;
}