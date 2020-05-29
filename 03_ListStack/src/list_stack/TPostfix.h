#pragma once
#include <string>
using namespace std;

class TVariables;

class TPostfix
{
public:
    static bool use_array_stack;
private:
    // exploring string symbol-by-symbol
    static bool is_operator(const char& c);
    static bool is_operator(const string& s);
    static bool is_l_bracket(const char& c);
    static bool is_l_bracket(const string& s);
    static bool is_r_bracket(const char& c);
    static bool is_r_bracket(const string& s);
    static bool is_number(const char& c);
    static bool is_number(const string& s);
    static bool is_letter(const char& c);
    static bool is_letter(const string& s);
        
    // getting whole numbers and variable names
    static string recognize_number(string s);
    static string recognize_variable(string s);

    static int check_priority(string s);
    static bool check_brackets(string s);
public:
    // checker
    static int analyse_postfix(string s); // search for more complicated mistakes in string & count variables
    // the two main static functions
    static string convert_to_postfix(string s);
    static double calculate(string s, TVariables& handler);
        
    friend class TVariables;
};
