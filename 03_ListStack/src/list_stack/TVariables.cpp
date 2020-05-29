#pragma once
#include "input.h"
#include "TStack.h"
#include "TVariables.h"
#include "TPostfix.h"

TVariables::TVariables(int var_limit)
{
    this->var_used = 0;
    this->array = new var[var_limit];
}

TVariables::~TVariables()
{
    delete[] this->array;
}

int TVariables::get_var_used()
{
    return this->var_used;
}

var TVariables::get_var(int i)
{
    if ((i < 0) || (i >= var_used))
        throw "attempt to access non-existing variable";
    else
        return this->array[i];
}

// getting variable names from a string
void TVariables::register_variables(const string& _s)
{
    string s = _s;
    while (true)
    {
        // got operand-variable:
        if (TPostfix::is_letter(s[0]))
        {
            string x = TPostfix::recognize_variable(s);
            bool exists = false;
            for (int i = 0; i < this->var_used; i++)
            {
                if (x == this->array[i].var_name)
                {
                    exists = true;
                    break; // variable is already registered
                }
            }
            if (exists == false)
            {
                this->array[var_used].var_name = x;
                this->var_used++;
            };
            s = s.substr(x.length());
        }
        else
            // not interested in other cases and symbols
            if (s != "")
            {
                s = s.substr(1);
            }
            else break;
    }
};

// input of user values for variables
void TVariables::enter_var_values()
{
    for (int i = 0; i < this->var_used; i++)
    {
        cout << "Enter value for '" << this->array[i].var_name << "':" << endl;
        userproof_input(this->array[i].var_value);
    }
}