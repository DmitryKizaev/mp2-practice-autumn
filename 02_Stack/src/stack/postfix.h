#pragma once
#include <string>
using namespace std;

class variables;

class postfix
{
public:
		// методы для преобразования инфиксной формы в постфиксную:
		static bool is_operator(char c);
		static bool is_operator(string s);

		static bool is_l_bracket(char c);
		static bool is_l_bracket(string s);

		static bool is_r_bracket(char c);
		static bool is_r_bracket(string s);

		static bool is_number(char c);
		static bool is_number(string s);

		static bool is_letter(char c);
		static bool is_letter(string s);
		
		static int check_priority(string s);

		// получение из строки переменных и чисел целиком:
		static string recognize_number(string s);
		static string recognize_variable(string s);

		// проверки на правильность
		static bool check_correct(string s); // проверка строки на правильность расстановки скобок
		static int check_correct_postfix(string s); // возвр. кол-во переменных

		// основной функционал
		static string convert_to_postfix(string s);
		static double calculate(string s, variables& handler);
		
};
