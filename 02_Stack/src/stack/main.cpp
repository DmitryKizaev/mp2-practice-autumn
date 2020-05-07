#pragma once

#include <locale.h>
#include <iostream>
#include <string>

#include "input.h"
#include "stack.h"
#include "postfix.h"
#include "variables.h"

using namespace std;

// program mode
const int CALCULATE = 1; // calculator OR converter
const int CHOICE = 1; // 1 to test all modes, 0 for standard mode

int main()
{
    setlocale(LC_ALL, "Russian");
    while (true)
    {
        int mode = CHOICE;

        while ((mode != 1) && (mode != 2))
        {
            cout << "Enter mode: " << endl;
            cout << "1 - convert & calculate infix expression " << endl;
            cout << "2 - calculate premade postfix expression " << endl;
            userproof_input(mode);
        }
                
        string input, converted;

        if (mode == 1)
        {
            cout << "Enter infix expression: " << endl;
            getline(cin, input); // getting full line with spaces
            try
            {
                converted = postfix::convert_to_postfix(input);
                cout << "Postfix form: " << endl << converted << endl;
                if (CALCULATE)
                {
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
            }
            catch (const char* err_code)
            {
                cout << err_code << endl;
            }
        }

        if (mode == 2)
        {
            cout << "Enter premade postfix expression: " << endl;
            getline(cin, converted);

            try
            {
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
        }

        cout << "-----------------------------------------------" << endl;
    }
    return 0;
}