#pragma once
#include <string>
using namespace std;

class TVariables;

class TPostfix
{
public:
    static bool use_array_stack;
private:
    // recognizing type of input symbol
    static bool is_operator(const char& c);
    static bool is_number(const char& c);
    static bool is_letter(const char& c);
        
    // getting whole numbers and variable names
    static string recognize_number(const string& s);
    static string recognize_variable(const string& s);

    static int check_priority(const string& s);
    static bool check_brackets(const string& s);
public:
    // checker
    static int analyse_postfix(const string& s); // search for more complicated mistakes in string & count variables
    // the two main static functions
    static string convert_to_postfix(const string& s);
    static double calculate(const string& s, TVariables& handler);
        
    friend class TVariables;
};
