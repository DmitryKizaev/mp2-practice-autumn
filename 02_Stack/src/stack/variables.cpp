#pragma once
#include "input.h"
#include "stack.h"
#include "variables.h"
#include "postfix.h"

variables::variables(int var_limit)
{
    this->var_used = 0; // ������� �������������� ����������
    this->array = new var[var_limit];
}

variables::~variables()
{
    delete[] this->array;
}

int variables::get_var_used()
{
    return this->var_used;
}

var variables::get_var(int i)
{
    if ((i < 0) || (i >= var_used))
        throw "attempt to access non-existing variable";
    else
        return this->array[i];
}

// ���� �� ������ ���� ����������
void variables::register_variables(string s)
{
    while (true)
    {
        // ������ �������-����������:
        if (postfix::is_letter(s))
        {
            string x = postfix::recognize_variable(s);
            bool exists = false;
            for (int i = 0; i < this->var_used; i++)
            {
                if (x == this->array[i].var_name)
                {
                    exists = true;
                    break; // ��� �����������
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
            // �� ���������� ��� ������, �������
            if (s != "")
            {
                s = s.substr(1);
            }
            else break;
    }
};

// ���� ��������
void variables::enter_var_values()
{
    for (int i = 0; i < this->var_used; i++)
    {
        cout << "Enter value for '" << this->array[i].var_name << "':" << endl;
        userproof_input(this->array[i].var_value);
    }
}