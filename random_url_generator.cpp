/*
Random URL Genrator
Vijay Dwivedi     -     2020CSB1140
Vinay Kumar       -     2020CSB1141
Yadwinder Singh   -     2020CSB1143
*/
#include <iostream>
#include <string>
using namespace std;

string url_generator(int size)
{
    string url;
    static const char alphanum[] =
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    for (int i = 0; i < size; i++)
    {
        url += alphanum[rand() % (sizeof(alphanum) - 1)];
    }
    return url;
}
int main()
{
    cout<<"Enter Length of cache: ";
    int y;
    cin>>y;
    freopen("input.txt", "w", stdout);
    long long int i = 50;
    cout << y;
    cout << endl;
    while (i)
    {
        int x = rand();
        x = x % 80;
        string url = url_generator(x);
        cout << "https://" << url;
        cout << endl;
        i--;
    }
    cout << "-1";
    return 0;
}
