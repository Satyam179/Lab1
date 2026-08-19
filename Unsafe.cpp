#include <iostream>
#include <string>
using namespace std;

int main()
{
    int a = 40000;
    short b = a;

    int x = -25;
    unsigned int y = x;

    float f = 123.99;
    int n = f;

    string s = "12abc";
    int num = stoi(s);

    cout << a << " -> " << b << endl;
    cout << x << " -> " << y << endl;
    cout << f << " -> " << n << endl;
    cout << s << " -> " << num << endl;

    return 0;
}