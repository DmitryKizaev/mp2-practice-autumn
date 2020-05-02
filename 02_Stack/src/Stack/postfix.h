#pragma once
#include "stack.h"
#include <iostream>

using namespace std;

class postfix
{
private:
    static bool check_sign(char c);
    static bool check_correct(string s);
    static bool check_const(string symbols);

    static double calc_step(string tmp, double a, double b);
    static double convert_const_v1(string symbols);
    static double convert_const_v2(string symbols);

    static double get_value(string variable, string* keys, double* values);
    static int get_priority(string symb);
    static void push_sign(string sign, stack<string>& operators, stack<string>& result);

public:
    static string convert_to_postfix(string s);
    static void set_values(string s_postfix, string*& keys, double*& values, int* num);
    static double calc_all(string s_postfix, string* keys, double* values);
};