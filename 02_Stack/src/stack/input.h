#pragma once
#include <iostream>

using namespace std;

template <typename T>
void userproof_input(T& value)
{
    T x;
    while (true)
    {
        cin >> x;
        if (!cin.good())
        {
            cout << "incorrect format, please retry" << endl;
            cin.clear();
            while (cin.get() != '\n');
        }
        else
        {
            while (cin.get() != '\n');
            value = x;
            break;
        }
    }
};