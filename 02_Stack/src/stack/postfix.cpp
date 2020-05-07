#pragma once
#include "stack.h"
#include "variables.h"
#include "postfix.h"

// посимвольный разбор строк: определение типа объекта

bool postfix::is_operator(char c)
{
    return ((c == '+') || (c == '-') || (c == '*') || (c == '/'));
};

bool postfix::is_operator(string s)
{
    return is_operator(s[0]);
};

bool postfix::is_l_bracket(char c)
{
    return (c == '(');
};

bool postfix::is_l_bracket(string s)
{
    return is_l_bracket(s[0]);
};

bool postfix::is_r_bracket(char c)
{
    return (c == ')');
};

bool postfix::is_r_bracket(string s)
{
    return is_r_bracket(s[0]);
};

bool postfix::is_number(char c)
{
    return (isdigit(c));
};

bool postfix::is_number(string s)
{
    return (isdigit(char(s[0])));
};

bool postfix::is_letter(char c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool postfix::is_letter(string s)
{
    return (s[0] >= 'a' && s[0] <= 'z') || (s[0] >= 'A' && s[0] <= 'Z');
}

string postfix::recognize_number(string s)
{
    string number = "";
    // достаем число
    for (int i = 0; i < int(s.length()); i++)
    {
        if (isdigit(s[i]) || s[i] == '.')
            number += s[i];
        else if (s[i] != ' ' && !is_operator(s[i]) && !is_r_bracket(s[i]))
            throw "error: number ends with unexpected symbols (probably variable name starting from digit)";
        else
            break;
    }
    return (number);
};

string postfix::recognize_variable(string s)
{
    string name = "";
    for (int i = 0; i < int(s.length()); i++)
    {
        // собираем имя переменной
        if ((is_operator(s[i])) or (s[i] == ' ') or (is_r_bracket(s[i])))
            break;
        else if (is_l_bracket(s[i]))
            throw "error: variable name contains odd brackets";
        else if (!(is_letter(s[i]) or is_number(s[i])))
            throw "error: variable name contains wrong symbols";
        else
            name += s[i];
    }
    return name;
}

// проверки

int postfix::check_priority(string s)
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

bool postfix::check_brackets(string s)
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

int postfix::check_correct_postfix(string s)
{
    int numbers = 0;
    int operators = 0;
    int variables = 0;
    while (true)
    {
        // Пришёл пробел: убираем
        if (s[0] == ' ')
        {
            s = s.substr(1);
        }
        else
            // Пришел оператор: считаем
            if (is_operator(s))
            {
                operators += 1;
                s = s.substr(1);
            }
            else
                // Пришел операнд-число: считаем
                if (is_number(s))
                {
                    string num = recognize_number(s);
                    s = s.substr(num.length());
                    numbers += 1;
                }
                else
                    // Пришел операнд-переменная:
                    if (is_letter(s))
                    {
                        string x = recognize_variable(s);
                        s = s.substr(x.length());
                        variables += 1;
                    }
                    else
                        // Пришла скобка: ошибка
                        if (is_l_bracket(s) || is_r_bracket(s))
                        {
                            throw "incorrect postfix string: brackets found";
                        }
                        else
                            // Ничего не сработало - мусор, ошибка
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

string postfix::convert_to_postfix(string s)
{
    if (!check_brackets(s))
        throw "incorrect brackets";

    stack <string> operators(s.length() + 1);
    stack <string> results(s.length() + 1);

    bool before_was_operand = false;
    bool before_was_sign = false;

    int operands = 0;
    int signs = 0;

    while (true)
    {
        // Пришёл пробел: частый случай, просто убираем
        if (s[0] == ' ')
        {
            s = s.substr(1);
        }
        else
            // Пришел оператор: смотрим приоритет операции на вершине стека операторов
            // Перекладываем все операции приоритетнее нашей в стек результатов
            // Помещаем нашу операцию в стек операторов
            if (is_operator(s))
            {
                if (before_was_sign == true)
                    throw "wrong input: two operators without a value between";
                string found = "";
                found += s[0];
                if (!operators.is_empty())
                {
                    int curr_prior = check_priority(s);
                    while ((!operators.is_empty()) && (check_priority(operators.peek()) >= curr_prior))
                    {
                        results.push(operators.pop());
                    };
                }
                operators.push(found);
                s = s.substr(1);
                before_was_operand = false; // за последний вызов (этот) мы нашли оператор
                before_was_sign = true;
                signs++;
            }
            else
                // Пришла открывающая скобка: помещаем в стек операторов
                if (is_l_bracket(s))
                {
                    string found = "";
                    found += s[0];
                    operators.push(found);
                    s = s.substr(1);
                    before_was_operand = false; // за последний вызов (этот) мы нашли скобку
                    before_was_sign = false;
                }
                else
                    // Пришла закрывающая скобка:
                    // Перемещаем все из стека операторов в стек результатов, пока не встретим "(", ее удаляем
                    if (is_r_bracket(s))
                    {
                        while (!(is_l_bracket(operators.peek())))
                        {
                            results.push(operators.pop());
                        };
                        string dummy = operators.pop();
                        s = s.substr(1);
                        before_was_operand = false; // за последний вызов (этот) мы нашли скобку
                        before_was_sign = false;
                    }
                    else
                        // Пришел операнд-число:
                        // Преобразуем из строки в число, помещаем в стек результатов
                        if (is_number(s))
                        {
                            if (before_was_operand == true)
                                throw "wrong input: two operands without a sign between";
                            string num = recognize_number(s);
                            results.push(num);
                            s = s.substr(num.length());
                            before_was_operand = true; // нашли операнд-число
                            before_was_sign = false;
                            operands++;
                        }
                        else
                            // Пришел операнд - переменная:
                            if (is_letter(s))
                            {
                                if (before_was_operand == true)
                                    throw "wrong input: two operands without a sign between";
                                string x = recognize_variable(s);
                                results.push(x);
                                s = s.substr(x.length());
                                before_was_operand = true; // нашли операнд-переменную
                                before_was_sign = false;
                                operands++;
                            }
                            else
                            // Другие варианты:
                                // Плохой
                                if (s != "")
                                {
                                    throw "error: unexpected symbols";
                                }
                                else
                                // Хороший. Конец строки: перекладываем из стека в стек
                                {
                                    while (!operators.is_empty())
                                        results.push(operators.pop());
                                    break;
                                };
    }
    if (operands != signs + 1)
        throw "error: incorrect number of operands & operators";
    string result = "";
    results.invert_stack();
    while (!results.is_empty())
    {
        result += results.pop() + " ";
    }
    return result;
}

double postfix::calculate(string s, variables& handler)
// на вход - строка в постфиксной форме, пробелы допустимы
{
    stack <double> num_stack;
    while (true)
    {
        // Пришёл пробел: просто убираем
        if (s[0] == ' ')
        {
            s = s.substr(1);
        }
        else
            // Пришел оператор: достаем из стека 2 последних значения, совершаем операцию, кладем в стек
            if (is_operator(s))
            {
                if (num_stack.is_empty())
                    throw "incorrect postfix string";
                double op_2 = num_stack.pop();
                if (num_stack.is_empty())
                    throw "incorrect postfix string";
                double op_1 = num_stack.pop();

                switch (s[0])
                {
                case '+':
                {
                    num_stack.push(op_1 + op_2);
                    break;
                }
                case '-':
                {
                    num_stack.push(op_1 - op_2);
                    break;
                }
                case '*':
                {
                    num_stack.push(op_1 * op_2);
                    break;
                }
                case '/':
                {
                    if (op_2 == 0)
                        throw "error: division by zero";
                    else
                        num_stack.push(op_1 / op_2);
                    break;
                }
                }
                s = s.substr(1);
            }
            else
                // Пришел операнд-число:
                // Преобразуем из строки в число, помещаем в стек
                if (is_number(s))
                {
                    string num_s = recognize_number(s);
                    double num = stof(num_s);
                    num_stack.push(num);
                    s = s.substr(num_s.length());
                }
                else
                    // Пришел операнд - переменная:
                    // Находим значение, помещаем в стек
                    if (is_letter(s))
                    {
                        string x = recognize_variable(s);
                        for (int i = 0; i < handler.get_var_used(); i++)
                            if (x == handler.array[i].var_name)
                            {
                                num_stack.push(handler.array[i].var_value);
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
    double final = num_stack.pop();
    if (!num_stack.is_empty())
        throw "calculation error: odd values in stack";
    return final;
};