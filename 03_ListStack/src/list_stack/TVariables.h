#pragma once
#include <string>
#include <iostream>

using namespace std;

struct var
{
    string var_name;
    double var_value;
};

class TVariables
{
private:
    int var_used; // number of currently used variables
    var* array;

public:
    TVariables(int var_limit = 10);
    ~TVariables();

    int get_var_used();
    var get_var(int i);

    void register_variables(string postfix);
    void enter_var_values();

    friend class TPostfix; // needed because we use 'recognize' for finding variable names
};