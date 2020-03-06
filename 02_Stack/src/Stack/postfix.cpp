#include "postfix.h"
#include <iostream>
#include <string>

using namespace std;

bool postfix::check_sign(char c)
{
    return ((c == '+') || (c == '-') || (c == '*') || (c == '/'));
}

bool postfix::check_correct(string s)
{
    int lefts = 0, rights = 0;

    for (int i = 0; i < s.length(); i++)
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
}

bool postfix::check_const(string symbols)
{
    for (int i = 0; i < symbols.length(); i++)
        if (!isdigit(symbols[i]) && (symbols[i] != ' '))
            return false;
    return true;
}


double postfix::calc_step(string tmp, double a, double b)
{
    switch (tmp[0])
    {
        case '*': return a * b;
        case '/': return a / b;
        case '+': return a + b;
        case '-': return a - b;
        default: return 0;
    }
}

double postfix::convert_const_v1(string symbols)
{
    double result = 0;
    for (int i = 0; i < symbols.length(); i++)
    {
        double s = 1;
        for (int j = 1; j < symbols.length() - i; j++)
            s *= 10;

        switch (symbols[i])
        {
        case '0':
            result += s * 0;
            break;
        case '1':
            result += s * 1;
            break;
        case '2':
            result += s * 2;
            break;
        case '3':
            result += s * 3;
            break;
        case '4':
            result += s * 4;
            break;
        case '5':
            result += s * 5;
            break;
        case '6':
            result += s * 6;
            break;
        case '7':
            result += s * 7;
            break;
        case '8':
            result += s * 8;
            break;
        case '9':
            result += s * 9;
            break;
        default:
            break;
        }
    }
    return result;
}

double postfix::convert_const_v2(string symbols)
{   
    try
    {
        return double(stoi(symbols));
    }
    catch (const char* err_code)
    {
        cout << err_code << " in push_sign f in calc_all " << endl;
        return 0;
    }
}

double postfix::get_value(string variable, string* keys, double* values)
{
    for (int i = 0; i < 50; i++)
        if (variable == keys[i])
            return values[i];
    return 0;
}

int postfix::get_priority(string symbols)
{
    switch (symbols[0])
    {
        case '*': return 2;
        case '/': return 1;
        case '+': return 4;
        case '-': return 3;
        default: return 5;
    }
}

void postfix::push_sign(string sign, stack<string>& operators, stack<string>& result)
{
    string s;
    stack<string> oper(50);
    if (!(operators.is_empty()))
    {
        do
        {
            try
            {
                s = operators.pop();
            }
            catch (const char* err_code)
            {
                cout << err_code << " in push_sign f in calc_all " << endl;
            }
            if (get_priority(s) < get_priority(sign))
            {
                oper.push(s);
            }
            else
            {
                operators.push(s);
                operators.push(sign);
            }
            try
            {
                if (!(operators.is_empty()))
                {
                    s = operators.pop();
                    operators.push(s);
                }
            }
            catch (const char* err_code)
            {
                cout << err_code << " in push_sign f " << endl;
            }
        }
        while ((get_priority(s) < get_priority(sign)) && (!(operators.is_empty())));

        if (!(oper.is_empty()))
        {
            operators.push(sign);
            do
            {
                result.push(oper.pop());
            } while (!(oper.is_empty()));
        }
    }
    else
    {
        operators.push(sign);
    }
}

string postfix::convert_to_postfix(string s)
{
    if (s == "")
        throw "Error: line is empty";

    if (!(check_correct(s)))
        throw "Error: incorrect line";

    string tmp = "", var = ""; // tmp - входной элемент строки в цикле, var - переменная до знака
    int j = 0; // счетчик для массива переменных

    stack<string> operators(50);
    stack<string> res_stack(50);
    string res_string = "";

    for (int i = 0; i < s.length(); i++)
    {
        tmp = s[i];
        if (tmp != " ")
        {
            if (check_sign(s[i]) || (s[i] == '('))
            {
                try
                {
                    if (var != "")
                    {
                        reverse(var.begin(), var.end());
                        res_stack.push(var);
                        var = "";
                    }
                }
                catch (const char* err_code)
                {
                    cout << err_code << " in Sign " << endl;
                }
                try
                {
                    if ((tmp != "(") && (!(operators.is_empty())))
                    {
                        push_sign(tmp, operators, res_stack);
                    }
                    else
                    {
                        operators.push(tmp);
                    }
                }
                catch (const char* err_code)
                {
                    cout << err_code << " in oper" << endl;
                }
            }
            else if (s[i] == ')')
            {
                string z = operators.pop();
                try
                {
                    if (var != "")
                    {
                        reverse(var.begin(), var.end());
                        res_stack.push(var);
                        var = "";
                    }
                }
                catch (const char* err_code)
                {
                    cout << err_code << endl;
                }
                do
                {
                    try
                    {
                        res_stack.push(z);
                    }
                    catch (const char* err_code)
                    {
                        cout << err_code << endl;
                    }
                    try
                    {
                        z = operators.pop();
                    }
                    catch (const char* err_code)
                    {
                        cout << err_code << endl;
                    }
                } while (z != "(");
            }
            else
                var += tmp;
        }
    }

    try
    {
        if (var != "")
        {
            reverse(var.begin(), var.end());
            res_stack.push(var);
            var = "";
        }
    }
    catch (const char* err_code)
    {
        cout << err_code << endl;
    }

    string z;
    do
    {
        try
        {
            z = operators.pop();
        }
        catch (const char* err_code)
        {
            cout << err_code << " in end  in do " << endl;
        }
        try
        {
            res_stack.push(z);
        }
        catch (const char* err_code)
        {
            cout << err_code << " in Push in end " << endl;
        }
    }
    while (!(operators.is_empty()));

    while (!(res_stack.is_empty()))
        res_string += (" " + res_stack.pop());

    reverse(res_string.begin(), res_string.end());
    return res_string;
}

void postfix::set_values(string s_postfix, string*& keys, double*& values, int* num)
{
    string tmp = "";
    int flag = 0;
    int p = 0;
    for (int i = 0; i < s_postfix.length(); i++)
    {
        if (s_postfix[i] != ' ')
            tmp += s_postfix[i];
        else
        {
            if (!(check_sign(tmp[0])))
                p++;
            tmp = "";
        }
    }
    tmp = "";

    keys = new string[p];
    for (int i = 0; i < p; i++)
        keys[i] = "";
    values = new double[p];
    p = 0;

    for (int i = 0; i < s_postfix.length(); i++)
    {
        if (s_postfix[i] != ' ')
            tmp += s_postfix[i];
        else
        {
            if (!(check_sign(tmp[0])))
            {
                flag = 0;
                for (int j = (p - 1); j >= 0; j--)
                {
                    if (tmp == keys[j])
                    {
                        flag = 1;
                    }
                }
                if (flag == 0)
                {
                    if (check_const(tmp))
                    {
                        keys[p] = tmp;
                        p++;
                        values[p] = convert_const_v2(tmp);
                    }
                    else
                    {
                        keys[p] = tmp;
                        cout << keys[p] << " = ";
                        cin >> values[p++];
                    }
                }
            }
            tmp = "";
        }
    }
    *num = p;
}

double postfix::calc_all(string s_postfix, string* keys, double* values)
{
    stack<double> calc(50);
    string tmp, tmp1;
    double a, b;

    for (int i = 0; i < s_postfix.length(); i++)
    {
        tmp1 = s_postfix[i];
        if (tmp1 == " ")
        {
            if (check_sign(tmp[0]))
            {
                b = calc.pop();
                a = calc.pop();
                calc.push(calc_step(tmp, a, b));
            }
            else
                calc.push(get_value(tmp, keys, values));
            tmp = "";
        }
        else
            tmp += tmp1;
    }
    return calc.pop();
}