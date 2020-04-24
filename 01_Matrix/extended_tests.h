#pragma once
#include "mat_f.h"

int userproof_input()
{
    int x;
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
            return x;
    }
}

// same operation tests from MAIN
// using vector_formatted & matrix_formatted

void extended_double()
{
    // <DOUBLE> SPECIALIZATION

    // сложение матриц

    int n;

    cout << "you are now testing <DOUBLE> FORMATTED MATRIXES" << endl << endl;
    cout << "test 1" << endl << "A + B" << endl;
    cout << "size A = ";
    n = userproof_input();

    mat_f<double> A(n);

    cout << "A = " << endl;

    cin >> A;

    cout << endl << "Check A:" << endl << endl << A << endl;

    cout << "size B = ";
    n = userproof_input();

    mat_f<double> B(n);

    cout << "B = " << endl;
    cin >> B;
    cout << endl << "Check B:" << endl << endl << B << endl;
    cout << "A + B:" << endl << endl;

    mat_f<double> C(n);

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

    A = mat_f<double>(n);

    cout << "A = " << endl;
    cin >> A;
    cout << endl << "Check A:" << endl << endl << A << endl;

    cout << "size B = ";
    n = userproof_input();

    B = mat_f<double>(n);
    cout << "B = " << endl;
    cin >> B;
    cout << endl << "Check B:" << endl << endl << B << endl;

    cout << "A - B:" << endl << endl;

    C = mat_f<double>(n);
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

    A = mat_f<double>(n);
    cout << "A = " << endl;
    cin >> A;
    cout << endl << "Check A:" << endl << endl << A << endl;

    cout << "size B = ";
    n = userproof_input();

    B = mat_f<double>(n);
    cout << "B = " << endl;
    cin >> B;
    cout << endl << "Check B:" << endl << endl << B << endl;

    cout << "A * B:" << endl << endl;

    C = mat_f<double>(n);
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

    A = mat_f<double>(n);
    cout << "A = " << endl;
    cin >> A;
    cout << endl << "Check A:" << endl << endl << A << endl;

    cout << "const = ";
    double c;
    cin >> c;

    cout << "A + const:" << endl << endl;

    C = mat_f<double>(n);
    C = A + c;
    cout << C;
    cout << endl << "test 4 successful" << endl << endl;

    // вычитание константы

    cout << "test 5" << endl << "A - const" << endl;
    cout << "size A = ";
    n = userproof_input();

    A = mat_f<double>(n);
    cout << "A = " << endl;
    cin >> A;
    cout << endl << "Check A:" << endl << endl << A << endl;

    cout << "const = ";
    cin >> c;

    cout << "A - const:" << endl << endl;

    C = mat_f<double>(n);
    C = A - c;
    cout << C;
    cout << endl << "test 5 successful" << endl << endl;

    // умножение на константу

    cout << "test 6" << endl << "A * const" << endl;
    cout << "size A = ";
    n = userproof_input();

    A = mat_f<double>(n);
    cout << "A = " << endl;
    cin >> A;
    cout << endl << "Check A:" << endl << endl << A << endl;

    cout << "const = ";
    cin >> c;

    cout << "A * const:" << endl << endl;

    C = mat_f<double>(n);
    C = A * c;
    cout << C;
    cout << endl << "test 6 successful" << endl << endl;

    // умножение на вектор

    cout << "test 7" << endl << "A * vect" << endl;
    cout << "size A = ";
    n = userproof_input();

    A = mat_f<double>(n);
    cout << "A = " << endl;
    cin >> A;
    cout << endl << "Check A:" << endl << endl << A << endl;

    cout << "vect dim = ";
    n = userproof_input();

    vect_f<double> V(n);
    cout << "V = " << endl;
    cin >> V;
    cout << endl << "Check V:" << endl << endl << V << endl;

    cout << endl << "A * V:" << endl << endl;

    vect_f<double> D(n);
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

    A = mat_f<double>(n);
    cout << "A = " << endl;
    cin >> A;
    cout << endl << "Check A:" << endl << endl << A << endl;

    cout << "size B = ";
    n = userproof_input();

    B = mat_f<double>(n);
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

    A = mat_f<double>(n);
    cout << "A = " << endl;
    cin >> A;
    cout << endl << "Check A:" << endl << endl << A << endl;

    cout << "size B = ";
    n = userproof_input();

    B = mat_f<double>(n);
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

    A = mat_f<double>(n);
    cout << "A = " << endl;
    cin >> A;
    cout << endl << "Check A:" << endl << endl << A << endl;

    B = mat_f<double>(A);
    cout << endl << "this is B(A):" << endl << endl << B;
}

void extended_int()
{
    // <INT> SPECIALIZATION

    // number of spaces between columns

    // сложение матриц

    int n;

    cout << "you are now testing <INT> FORMATTED MATRIXES" << endl << endl;
    cout << "test 1" << endl << "A + B" << endl;
    cout << "size A = ";
    n = userproof_input();

    mat_f<int> A(n);

    cout << "A = " << endl;
    cin >> A;
    cout << endl << "Check A:" << endl << endl << A << endl;

    cout << "size B = ";
    n = userproof_input();

    mat_f<int> B(n);

    cout << "B = " << endl;
    cin >> B;
    cout << endl << "Check B:" << endl << endl << B << endl;
    cout << "A + B:" << endl << endl;

    mat_f<int> C(n);

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

    A = mat_f<int>(n);

    cout << "A = " << endl;
    cin >> A;
    cout << endl << "Check A:" << endl << endl << A << endl;

    cout << "size B = ";
    n = userproof_input();

    B = mat_f<int>(n);
    cout << "B = " << endl;
    cin >> B;
    cout << endl << "Check B:" << endl << endl << B << endl;

    cout << "A - B:" << endl << endl;

    C = mat_f<int>(n);
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

    A = mat_f<int>(n);
    cout << "A = " << endl;
    cin >> A;
    cout << endl << "Check A:" << endl << endl << A << endl;

    cout << "size B = ";
    n = userproof_input();

    B = mat_f<int>(n);
    cout << "B = " << endl;
    cin >> B;
    cout << endl << "Check B:" << endl << endl << B << endl;

    cout << "A * B:" << endl << endl;

    C = mat_f<int>(n);
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

    A = mat_f<int>(n);
    cout << "A = " << endl;
    cin >> A;
    cout << endl << "Check A:" << endl << endl << A << endl;

    cout << "const = ";
    int c;
    cin >> c;

    cout << "A + const:" << endl << endl;

    C = mat_f<int>(n);
    C = A + c;
    cout << C;
    cout << endl << "test 4 successful" << endl << endl;

    // вычитание константы

    cout << "test 5" << endl << "A - const" << endl;
    cout << "size A = ";
    n = userproof_input();

    A = mat_f<int>(n);
    cout << "A = " << endl;
    cin >> A;
    cout << endl << "Check A:" << endl << endl << A << endl;

    cout << "const = ";
    cin >> c;

    cout << "A - const:" << endl << endl;

    C = mat_f<int>(n);
    C = A - c;
    cout << C;
    cout << endl << "test 5 successful" << endl << endl;

    // умножение на константу

    cout << "test 6" << endl << "A * const" << endl;
    cout << "size A = ";
    n = userproof_input();

    A = mat_f<int>(n);
    cout << "A = " << endl;
    cin >> A;
    cout << endl << "Check A:" << endl << endl << A << endl;

    cout << "const = ";
    cin >> c;

    cout << "A * const:" << endl << endl;

    C = mat_f<int>(n);
    C = A * c;
    cout << C;
    cout << endl << "test 6 successful" << endl << endl;

    // умножение на вектор

    cout << "test 7" << endl << "A * vect" << endl;
    cout << "size A = ";
    n = userproof_input();

    A = mat_f<int>(n);
    cout << "A = " << endl;
    cin >> A;
    cout << endl << "Check A:" << endl << endl << A << endl;

    cout << "vect dim = ";
    n = userproof_input();

    vect_f<int> V(n);
    cout << "V = " << endl;
    cin >> V;
    cout << endl << "Check V:" << endl << endl << V << endl;

    cout << endl << "A * V:" << endl << endl;

    vect_f<int> D(n);
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

    A = mat_f<int>(n);
    cout << "A = " << endl;
    cin >> A;
    cout << endl << "Check A:" << endl << endl << A << endl;

    cout << "size B = ";
    n = userproof_input();

    B = mat_f<int>(n);
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

    A = mat_f<int>(n);
    cout << "A = " << endl;
    cin >> A;
    cout << endl << "Check A:" << endl << endl << A << endl;

    cout << "size B = ";
    n = userproof_input();

    B = mat_f<int>(n);
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

    A = mat_f<int>(n);
    cout << "A = " << endl;
    cin >> A;
    cout << endl << "Check A:" << endl << endl << A << endl;

    B = mat_f<int>(A);
    cout << endl << "this is B(A):" << endl << endl << B;
}