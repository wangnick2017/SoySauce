#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <string>
#include <cstdlib>
using namespace std;

int main()
{
    for (int i = 1; i <= 3; ++i)
    {
        int a, b;
        cin >> a >> b;
        cout << a << "+" << b << "=" << a + b << endl;
    }
    return 0;
}