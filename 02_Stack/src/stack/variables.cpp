#pragma once
#include "stack.h"
#include "variables.h"
#include "postfix.h"

variables::variables(int _var_limit)
{
	this->var_used = 0; // счетчик использованных переменных
	this->array = new var[_var_limit];
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
	if ((i < 0) || (i > var_used))
		throw "attempt to access non-existing variable";
	else
		return this->array[i];
}

// сбор из строки имен переменных
void variables::register_variables(string s)
{
	while (true)
	{
		// пришел операнд-переменная:
		if (postfix::is_letter(s))
		{
			string x = postfix::recognize_variable(s);
			bool exists = false;
			for (int i = 0; i < this->var_used; i++)
			{
				if (x == this->array[i].var_name)
				{
					exists = true;
					break; // уже встречалась
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
			// не интересный нам символ, убираем
			if (s != "")
			{
				s = s.substr(1);
			}
			else break;
	}
};

// ввод значений
void variables::enter_var_values()
{
	for (int i = 0; i < this->var_used; i++)
	{
		cout << "Enter value for '" << this->array[i].var_name << "':" << endl;
		this->array[i].var_value = userproof_input();
	}
}

double userproof_input()
{
	double x;
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
		{
			while (cin.get() != '\n');
			return x;
		}
	}
}