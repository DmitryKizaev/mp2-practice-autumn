#pragma once
#include <string>
using namespace std;

class variables;

class postfix
{
public:
		// ������ ��� �������������� ��������� ����� � �����������:
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

		// ��������� �� ������ ���������� � ����� �������:
		static string recognize_number(string s);
		static string recognize_variable(string s);

		// �������� �� ������������
		static bool check_correct(string s); // �������� ������ �� ������������ ����������� ������
		static int check_correct_postfix(string s); // �����. ���-�� ����������

		// �������� ����������
		static string convert_to_postfix(string s);
		static double calculate(string s, variables& handler);
		
};
