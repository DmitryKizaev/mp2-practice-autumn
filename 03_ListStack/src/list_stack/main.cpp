#pragma once

#include <locale.h>
#include <iostream>
#include <string>

#include "input.h"
#include "TStack.h"
#include "TPostfix.h"
#include "TVariables.h"

using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");
    while (true)
    {
        int choice = 0;

        while ((choice != 1) && (choice != 2))
        {
            cout << "Enter stack mode: " << endl;
            cout << "1 - stack on arrays " << endl;
            cout << "2 - stack on lists " << endl;
            userproof_input(choice);
        }

        if (choice == 1)
            TPostfix::use_array_stack = true;
        else
            TPostfix::use_array_stack = false;

        string input, converted;
        cout << "Enter infix expression: " << endl;
        getline(cin, input); // getting full line with spaces
        try
        {
            converted = TPostfix::convert_to_postfix(input);
            cout << "Postfix form: " << endl << converted << endl;

            int var_num = TPostfix::analyse_postfix(converted);
            TVariables handler(var_num);
            if (var_num > 0)
            {
                handler.register_variables(converted);
                handler.enter_var_values();
            }
            double final_value = TPostfix::calculate(converted, handler);
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