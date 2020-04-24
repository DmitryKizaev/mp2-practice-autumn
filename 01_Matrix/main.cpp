#pragma once
#include "extended_tests.h"
#include "mat.h"

void main()
{
    int n, mode;
    cout << "SELECT MODE:" << endl << "1 - basic version" << endl << "2 - extended version" << endl;
    do
        cin >> mode;
    while (mode != 1 && mode != 2);
    cout << endl;

    if (mode == 2)
    {
        extended_int();
        extended_double();
    }

    // BASIC VERSION

    // сложение матриц
    cout << "you are now testing <DOUBLE> MATRIXES" << endl << endl;
    cout << "test 1" << endl << "A + B" << endl;
    cout << "size A = ";
    n = userproof_input();

    mat<double> A(n);

    cout << "A = " << endl;
    cin >> A;
    cout << endl << "Check A:" << endl << endl << A << endl;

    cout << "size B = ";
    n = userproof_input();

    mat<double> B(n);

    cout << "B = " << endl;
    cin >> B;
    cout << endl << "Check B:" << endl << endl << B << endl;
    cout << "A + B:" << endl << endl;

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
    cout << endl << "test 1 successful" << endl << endl;

    // вычитание матриц

    cout << "test 2" << endl << "A - B" << endl;
    cout << "size A = ";
    n = userproof_input();

    A = mat<double>(n);

    cout << "A = " << endl;
    cin >> A;
    cout << endl << "Check A:" << endl << endl << A << endl;

    cout << "size B = ";
    n = userproof_input();

    B = mat<double>(n);
    cout << "B = " << endl;
    cin >> B;
    cout << endl << "Check B:" << endl << endl << B << endl;

    cout << "A - B:" << endl << endl;

    C = mat<double>(n);
    try
    {
        C = A - B;
        cout << C;
    }
    catch (const char* er)
    {
        cout << er << endl;
    }
    cout << endl << "test 2 successful" << endl << endl;

    // умножение матриц

    cout << "test 3" << endl << "A * B" << endl;
    cout << "size A = ";
    n = userproof_input();

    A = mat<double>(n);
    cout << "A = " << endl;
    cin >> A;
    cout << endl << "Check A:" << endl << endl << A << endl;

    cout << "size B = ";
    n = userproof_input();

    B = mat<double>(n);
    cout << "B = " << endl;
    cin >> B;
    cout << endl << "Check B:" << endl << endl << B << endl;

    cout << "A * B:" << endl << endl;

    C = mat<double>(n);
    try
    {
        C = A * B;
        cout << C;
    }
    catch (const char* er)
    {
        cout << er << endl;
    }
    cout << endl << "test 3 successful" << endl << endl;

    // сложение с константой

    cout << "test 4" << endl << "A + const" << endl;
    cout << "size A = ";
    n = userproof_input();

    A = mat<double>(n);
    cout << "A = " << endl;
    cin >> A;
    cout << endl << "Check A:" << endl << endl << A << endl;

    cout << "const = ";
    double c;
    cin >> c;

    cout << "A + const:" << endl << endl;

    C = mat<double>(n);
    C = A + c;
    cout << C;
    cout << endl << "test 4 successful" << endl << endl;

    // вычитание константы

    cout << "test 5" << endl << "A - const" << endl;
    cout << "size A = ";
    n = userproof_input();

    A = mat<double>(n);
    cout << "A = " << endl;
    cin >> A;
    cout << endl << "Check A:" << endl << endl << A << endl;

    cout << "const = ";
    cin >> c;

    cout << "A - const:" << endl << endl;

    C = mat<double>(n);
    C = A - c;
    cout << C;
    cout << endl << "test 5 successful" << endl << endl;

    // умножение на константу

    cout << "test 6" << endl << "A * const" << endl;
    cout << "size A = ";
    n = userproof_input();

    A = mat<double>(n);
    cout << "A = " << endl;
    cin >> A;
    cout << endl << "Check A:" << endl << endl << A << endl;

    cout << "const = ";
    cin >> c;

    cout << "A * const:" << endl << endl;

    C = mat<double>(n);
    C = A * c;
    cout << C;
    cout << endl << "test 6 successful" << endl << endl;

    // умножение на вектор

    cout << "test 7" << endl << "A * vect" << endl;
    cout << "size A = ";
    n = userproof_input();

    A = mat<double>(n);
    cout << "A = " << endl;
    cin >> A;
    cout << endl << "Check A:" << endl << endl << A << endl;

    cout << "vect dim = ";
    n = userproof_input();

    vect<double> V(n);
    cout << "V = " << endl;
    cin >> V;
    cout << endl << "Check V:" << endl << endl << V << endl;

    cout << endl << "A * V:" << endl << endl;

    vect<double> D(n);
    try
    {
        D = A * V;
        cout << D << endl;
    }
    catch (const char* er)
    {
        cout << er << endl;
    }
    cout << endl << "test 7 successful" << endl << endl;

    // проверка равенства

    cout << "test 8" << endl << "A == B" << endl;
    cout << "size A = ";
    n = userproof_input();

    A = mat<double>(n);
    cout << "A = " << endl;
    cin >> A;
    cout << endl << "Check A:" << endl << endl << A << endl;

    cout << "size B = ";
    n = userproof_input();

    B = mat<double>(n);
    cout << "B = " << endl;
    cin >> B;
    cout << endl << "Check B:" << endl << endl << B << endl;

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
    cout << endl << "test 8 successful" << endl << endl;

    // проверка неравенства

    cout << "test 9" << endl << "A != B" << endl;
    cout << "size A = ";
    n = userproof_input();

    A = mat<double>(n);
    cout << "A = " << endl;
    cin >> A;
    cout << endl << "Check A:" << endl << endl << A << endl;

    cout << "size B = ";
    n = userproof_input();

    B = mat<double>(n);
    cout << "B = " << endl;
    cin >> B;
    cout << endl << "Check B:" << endl << endl << B << endl;

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
    cout << endl << "test 9 successful" << endl << endl;


    // конструктор копирования

    cout << "test 10" << endl << "A = B" << endl;
    cout << "size A = ";
    n = userproof_input();

    A = mat<double>(n);
    cout << "A = " << endl;
    cin >> A;
    cout << endl << "Check A:" << endl << endl << A << endl;

    B = mat<double>(A);
    cout << endl << "this is B(A):" << endl << endl << B;
}
