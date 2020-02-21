#include <iostream>
#include "mat.h"
#include "debug.h"
using namespace std;

void main()
{
    test1(); //A + B
    test2(); //A - B
    test3(); //A * B
    test4(); //A + const
    test5(); //A - const
    test6(); //A * const
    test7(); //A * vec
    test8(); //A == B
    test9(); //A != B
    test10(); //конструктор копирования
    int i;
    cin >> i;
}