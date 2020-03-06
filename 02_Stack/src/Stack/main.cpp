#include "postfix.h"
#include <iostream>
#include <string>

using namespace std;

void main()
{
    string input, converted;
    cout << "Enter expression: " << endl;
    getline(std::cin, input);
    try
    {
        converted = postfix::convert_to_postfix(input);
        cout << "Postfix form: " << endl << converted << endl;

        string* keys;
        double* values;
        int num;

        postfix::set_values(converted, keys, values, &num);
        cout << "Result: " << endl << postfix::calc_all(converted, keys, values) << endl;
        delete[] values;
        delete[] keys;
    }
    catch (const char* err_code)
    {
        cout << err_code << endl;
    }
    cout << endl;
    system("pause");
}