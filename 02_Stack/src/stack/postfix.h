#pragma once
#include <string>
using namespace std;

class variables;

class postfix
{
public:
        // exploring string symbol-by-symbol
        static bool is_operator(const char c);
        static bool is_operator(const string s);

        static bool is_l_bracket(const char c);
        static bool is_l_bracket(const string s);

        static bool is_r_bracket(const char c);
        static bool is_r_bracket(const string s);

        static bool is_number(const char c);
        static bool is_number(const string s);

        static bool is_letter(const char c);
        static bool is_letter(const string s);
        
        // getting whole numbers and variable names
        static string recognize_number(const string s);
        static string recognize_variable(const string s);

        static int check_priority(const string s);

        // checks
        static bool check_brackets(const string s);
        static int check_correct_postfix(string s); // returns number of variables in expression

        // the two main static functions from task
        static string convert_to_postfix(string s);
        static double calculate(string s, variables& handler);
        
};
