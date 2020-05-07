#pragma once
#include <string>
using namespace std;

class variables;

class postfix
{
public:
        // exploring string symbol-by-symbol
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
        
        // getting whole numbers and variable names
        static string recognize_number(string s);
        static string recognize_variable(string s);

        static int check_priority(string s);

        // checks
        static bool check_brackets(string s);
        static int check_correct_postfix(string s); // returns number of variables in expression

        // the two main static functions from task
        static string convert_to_postfix(string s);
        static double calculate(string s, variables& handler);
        
};
