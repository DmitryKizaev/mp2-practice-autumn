#pragma once

#include "TVariables.h"
#include "TPostfix.h"
#include "TStack.h"
#include "TStack_on_arrays.h"
#include "TStack_on_lists.h"

bool TPostfix::use_array_stack;

// inspecting type of next object in infix string, based on its first symbol

bool TPostfix::is_operator(const char& c)
{
    return ((c == '+') || (c == '-') || (c == '*') || (c == '/'));
};

bool TPostfix::is_number(const char& c)
{
    return (isdigit(c));
};

bool TPostfix::is_letter(const char& c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

string TPostfix::recognize_number(const string& s)
{
    string number = "";
    // getting the whole number
    for (int i = 0; i < int(s.length()); i++)
    {
        if (isdigit(s[i]) || s[i] == '.')
            number += s[i];
        else if (s[i] != ' ' && !is_operator(s[i]) && (s[i] != ')'))
            throw "error: number ends with unexpected symbols (probably variable name starting from digit)";
        else
            break;
    }
    return (number);
};

string TPostfix::recognize_variable(const string& s)
{
    string name = "";
    for (int i = 0; i < int(s.length()); i++)
    {
        // getting the whole variable
        if ((is_operator(s[i])) or (s[i] == ' ') or (s[i] == ')'))
            break;
        else if (s[i] == '(')
            throw "error: variable name contains odd brackets";
        else if (!(is_letter(s[i]) or is_number(s[i])))
            throw "error: variable name contains wrong symbols";
        else
            name += s[i];
    }
    return name;
}

// checks

int TPostfix::check_priority(const string& s)
{
    char c = s[0];

    if (c == '*')
        return 3;
    if (c == '/')
        return 3;
    if (c == '+')
        return 2;
    if (c == '-')
        return 2;
    if (c == '(')
        return 1;
    else
        return 0;
};

bool TPostfix::check_brackets(const string& s)
{
    int lefts = 0, rights = 0;

    for (int i = 0; i < int(s.length()); i++)
    {
        if (s[i] == '(')
            lefts++;
        if (s[i] == ')')
            rights++;
        if (rights > lefts)
            return false;
    }
    if (rights != lefts)
        return false;
    return true;
};

int TPostfix::analyse_postfix(const string& _s)
{
    string s = _s;
    int numbers = 0;
    int operators = 0;
    int variables = 0;
    while (true)
    {
        // got space: ignore
        if (s[0] == ' ')
        {
            s = s.substr(1);
        }
        else
            // got sign: count
            if (is_operator(s[0]))
            {
                operators += 1;
                s = s.substr(1);
            }
            else
                // got operand-number: recognize, count
                if (is_number(s[0]))
                {
                    string num = recognize_number(s);
                    s = s.substr(num.length());
                    numbers += 1;
                }
                else
                    // got operand-variable: recognize, count
                    if (is_letter(s[0]))
                    {
                        string x = recognize_variable(s);
                        s = s.substr(x.length());
                        variables += 1;
                    }
                    else
                        // got bracket: mistake
                        if ((s[0] == '(') || (s[0] == ')'))
                        {
                            throw "incorrect postfix string: brackets found";
                        }
                        else
                            // got something else - mistake
                            if (s != "")
                            {
                                throw "error: unexpected symbols";
                            }
                            else break;
    };
    if (numbers + variables != operators + 1)
        throw "error: incorrect number of operands & operators";
    return variables;
}

string TPostfix::convert_to_postfix(const string& _s)
{
    string s = _s;
    if (!check_brackets(s))
        throw "incorrect brackets";
    
    TStack<string>* p_operators;
    TStack<string>* p_results;
    if (TPostfix::use_array_stack == true)
    {
        p_operators = new TStack_on_arrays <string>(s.length() + 1);
        p_results = new TStack_on_arrays <string>(s.length() + 1);
    }
    else
    {
        p_operators = new TStack_on_lists <string>;
        p_results = new TStack_on_lists <string>;
    }

    bool before_was_operand = false;
    bool before_was_sign = false;

    int operands = 0;
    int signs = 0;

    while (true)
    {
        // got space: ignore
        if (s[0] == ' ')
        {
            s = s.substr(1);
        }
        else
            // got operator:
            // 1. Get priority of element on top of 'operators' stack
            // 2. Move everything with same or higher priority to 'results' stack
            // 3. Put our current operation to 'operators' stack
            if (is_operator(s[0]))
            {
                if (before_was_sign == true)
                    throw "wrong input: two operators without a value between";
                string found = "";
                found += s[0];
                if (!(*p_operators).is_empty())
                {
                    int curr_prior = check_priority(s);
                    while ((!(*p_operators).is_empty()) && (check_priority((*p_operators).peek()) >= curr_prior))
                    {
                        (*p_results).push((*p_operators).pop());
                    };
                }
                (*p_operators).push(found);
                s = s.substr(1);
                before_was_operand = false; // last time (this one) we got operator
                before_was_sign = true;
                signs++;
            }
            else
                // got left bracket: push to 'operators' stack
                if (s[0] == '(')
                {
                    string found = "";
                    found += s[0];
                    (*p_operators).push(found);
                    s = s.substr(1);
                    before_was_operand = false; // last time (this one) we got bracket
                    before_was_sign = false;
                }
                else
                    // got right bracket:
                    // 1. Move each element from 'operators' stack to 'results' stack until we get left bracket
                    // 2. Delete left bracket
                    if (s[0] == ')')
                    {
                        while (((*p_operators).peek()[0]) != '(')
                        {
                            (*p_results).push((*p_operators).pop());
                        };
                        string dummy = (*p_operators).pop();
                        s = s.substr(1);
                        before_was_operand = false; // last time (this one) we got bracket
                        before_was_sign = false;
                    }
                    else
                        // got operand-number:
                        // push to 'results' stack
                        if (is_number(s[0]))
                        {
                            if (before_was_operand == true)
                                throw "wrong input: two operands without a sign between";
                            string num = recognize_number(s);
                            (*p_results).push(num);
                            s = s.substr(num.length());
                            before_was_operand = true; // last time (this one) we got operand-number
                            before_was_sign = false;
                            operands++;
                        }
                        else
                            // got operand-variable:
                            // push to 'results' stack
                            if (is_letter(s[0]))
                            {
                                if (before_was_operand == true)
                                    throw "wrong input: two operands without a sign between";
                                string x = recognize_variable(s);
                                (*p_results).push(x);
                                s = s.substr(x.length());
                                before_was_operand = true; // last time (this one) we got operand-variable
                                before_was_sign = false;
                                operands++;
                            }
                            else
                            // otherwise:
                                // bad situation
                                if (s != "")
                                {
                                    throw "error: unexpected symbols";
                                }
                                else
                                // good situation: eof
                                // move everything left in 'operators' to 'results'
                                {
                                    while (!(*p_operators).is_empty())
                                        (*p_results).push((*p_operators).pop());
                                    break;
                                };
    }
    if (operands != signs + 1)
        throw "error: incorrect number of operands & operators";
    string result = "";

    while (!(*p_results).is_empty())
    {
        result += (*p_results).pop() + " ";
    }

    for (unsigned i = 0; i < result.length() / 2; i++)
        swap(result[i], result[result.length() - 1 - i]);

    delete p_results;
    delete p_operators;
    return result;
}

double TPostfix::calculate(const string& _s, TVariables& handler)
// receives string in postfix form, spaces are allowed
{
    TStack<double>* p_calculation_stack;
    if (TPostfix::use_array_stack == true)
        p_calculation_stack = new TStack_on_arrays <double>;
    else
        p_calculation_stack = new TStack_on_lists <double>;

    string s = _s;
    while (true)
    {
        // got space: ignore
        if (s[0] == ' ')
        {
            s = s.substr(1);
        }
        else
            // got operator:
            // pop 2 values from 'calculation_stack', calculate, push result back
            if (is_operator(s[0]))
            {
                if ((*p_calculation_stack).is_empty())
                    throw "incorrect postfix string";
                double op_2 = (*p_calculation_stack).pop();
                if ((*p_calculation_stack).is_empty())
                    throw "incorrect postfix string";
                double op_1 = (*p_calculation_stack).pop();

                switch (s[0])
                {
                case '+':
                {
                    (*p_calculation_stack).push(op_1 + op_2);
                    break;
                }
                case '-':
                {
                    (*p_calculation_stack).push(op_1 - op_2);
                    break;
                }
                case '*':
                {
                    (*p_calculation_stack).push(op_1 * op_2);
                    break;
                }
                case '/':
                {
                    if (op_2 == 0)
                        throw "error: division by zero";
                    else
                        (*p_calculation_stack).push(op_1 / op_2);
                    break;
                }
                }
                s = s.substr(1);
            }
            else
                // got operand-number:
                // convert from string to double, push into stack
                if (is_number(s[0]))
                {
                    string num_s = recognize_number(s);
                    double num = stof(num_s);
                    (*p_calculation_stack).push(num);
                    s = s.substr(num_s.length());
                }
                else
                    // got operand-variable:
                    // find its value in 'handler', push into stack
                    if (is_letter(s[0]))
                    {
                        string x = recognize_variable(s);
                        for (int i = 0; i < handler.get_var_used(); i++)
                            if (x == handler.array[i].var_name)
                            {
                                (*p_calculation_stack).push(handler.array[i].var_value);
                                break;
                            }
                            else
                                if (i == handler.get_var_used())
                                    throw "error: value for variable not found";
                        s = s.substr(x.length());
                    }
                    else
                        if (s != "")
                        {
                            throw "error: unexpected symbols";
                            break;
                        }
                        else break;

    }
    double final = (*p_calculation_stack).pop();
    if (!(*p_calculation_stack).is_empty())
        throw "calculation error: odd values in stack";
    delete p_calculation_stack;
    return final;
}