#pragma once
#include <iostream>
#include <string>
#include "stack.h"
#include "postfix.h"
#include "variables.h"

using namespace std;

int main()
{
    while (true)
    {
        string input, converted;
        cout << "Enter expression: " << endl;
        getline(std::cin, input); // считываем всё вместе с пробелами, до конца строки
        try
        {
            converted = postfix::convert_to_postfix(input);
            cout << "Postfix form: " << endl << converted << endl;
            int var_num = postfix::check_correct_postfix(converted);
            variables handler(var_num);
            if (var_num > 0)
            {
                handler.register_variables(converted);
                handler.enter_var_values();
            }
            double final_value = postfix::calculate(converted, handler);
            cout << "Result:" << endl << final_value << endl;
        }
        catch (const char* err_code)
        {
            cout << err_code << endl;
        }
        cout << "-----------------------------------------------" << endl;
    }
    return 0;
}