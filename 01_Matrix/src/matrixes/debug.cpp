#include <iostream>
#include "debug.h"
using namespace std;

void test1() 
{
    cout << "test 1" << endl << "A + B" << endl;
    int n;
    cout << "size A = ";
    cin >> n;
    mat<double> A(n);
    cout << "A = " << endl;
    cin >> A; cout << A;

    cout << "size B = ";
    cin >> n;
    mat<double> B(n);
    cout << "B = " << endl;
    cin >> B;
    cout << "A + B" << endl;
    mat<double> C(n);
    try
    {
        C = A + B;
        cout << C;
    }
    catch (const char* er)
    {
        cout << er << endl;
    }
    cout << "test 1 successful" << endl << endl;
}

void test2()
{
    cout << "test 2" << endl << "A - B" << endl;
    int n;
    cout << "size A = ";
    cin >> n;
    mat<double> A(n);
    cout << "A = " << endl;
    cin >> A;

    cout << "size B = ";
    cin >> n;
    mat<double> B(n);
    cout << "B = " << endl;
    cin >> B;

    cout << "A - B" << endl;
    mat<double> C(n);
    try
    {
        C = A - B;
        cout << C;
    }
    catch (const char* er)
    {
        cout << er << endl;
    }
    cout << "test 2 successful" << endl << endl;
}

void test3()
{
    cout << "test 3" << endl << "A * B" << endl;
    int n;
    cout << "size A = ";
    cin >> n;
    mat<double> A(n);
    cout << "A = " << endl;
    cin >> A;

    cout << "size B = ";
    cin >> n;
    mat<double> B(n);
    cout << "B = " << endl;
    cin >> B;

    cout << "A * B" << endl;
    mat<double> C(n);
    try
    {
        C = A * B;
        cout << C;
    }
    catch (const char* er)
    {
        cout << er << endl;
    }
    cout << "test 3 successful" << endl << endl;
}

void test4()
{
    cout << "test 4" << endl << "A + const" << endl;
    int n;
    cout << "size A = ";
    cin >> n;
    mat<double> A(n);
    cout << "A = " << endl;
    cin >> A;

    cout << "const = ";
    double c;
    cin >> c;

    cout << "A + const" << endl;
    mat<double> C(n);
    C = A + c;
    cout << C;
    cout << "test 4 successful" << endl << endl;
}

void test5()
{
    cout << "test 5" << endl << "A - const" << endl;
    int n;
    cout << "size A = ";
    cin >> n;
    mat<double> A(n);
    cout << "A = " << endl;
    cin >> A;

    cout << "const = ";
    double c;
    cin >> c;

    cout << "A - const" << endl;
    mat<double> C(n);
    C = A - c;
    cout << C;
    cout << "test 5 successful" << endl << endl;
}

void test6()
{
    cout << "test 6" << endl << "A * const" << endl;
    int n;
    cout << "size A = ";
    cin >> n;
    mat<double> A(n);
    cout << "A = " << endl;
    cin >> A;

    cout << "const = ";
    double c;
    cin >> c;

    cout << "A * const" << endl;
    mat<double> C(n);
    C = A * c;
    cout << C;
    cout << "test 6 successful" << endl << endl;
}

void test7()
{
    cout << "test 7" << endl << "A * vec" << endl;
    int n;
    cout << "size A = ";
    cin >> n;
    mat<double> A(n);
    cout << "A = " << endl;
    cin >> A;

    cout << "size vec = ";
    cin >> n;
    vect<double> v(n);
    cout << "B = " << endl;
    cin >> v;

    cout << "A * vec" << endl;
    vect<double> C(n);
    try
    {
        C = A * v;
        cout << C;
    }
    catch (const char* er)
    {
        cout << er << endl;
    }
    cout << "test 7 successful" << endl << endl;
}

void test8()
{
    cout << "test 8" << endl << "A == B" << endl;
    int n;
    cout << "size A = ";
    cin >> n;
    mat<double> A(n);
    cout << "A = " << endl;
    cin >> A;

    cout << "size B = ";
    cin >> n;
    mat<double> B(n);
    cout << "B = " << endl;
    cin >> B;

    try
    {
        if (A == B)
            cout << "A = B" << endl;
        else
            cout << "A != B" << endl;
    }
    catch (const char* er)
    {
        cout << er << endl;
    }
    cout << "test 8 successful" << endl << endl;
}

void test9()
{
    cout << "test 9" << endl << "A != B" << endl;
    int n;
    cout << "size A = ";
    cin >> n;
    mat<double> A(n);
    cout << "A = " << endl;
    cin >> A;

    cout << "size B = ";
    cin >> n;
    mat<double> B(n);
    cout << "B = " << endl;
    cin >> B;

    try
    {
        if (A != B)
            cout << "A != B" << endl;
        else
            cout << "A = B" << endl;
    }
    catch (const char* er)
    {
        cout << er << endl;
    }
    cout << "test 9 successful" << endl << endl;
}

void test10()
{
    cout << "test 10" << endl << "A = B" << endl;
    int n;
    cout << "size A = ";
    cin >> n;
    mat<double> A(n);
    cout << "A = " << endl;
    cin >> A;
    mat<double> B(A);
    cout << B;
}