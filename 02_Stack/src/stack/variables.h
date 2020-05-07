#pragma once
#include <string>
#include <iostream>

using namespace std;

struct var
{
    string var_name;
    double var_value;
};

class variables
{
private:
    int var_used; // ������� �������������� ����������
    var* array; // ������ �������� "���-��������"

public:
    variables(int var_limit = 10);
    ~variables();

    int get_var_used();
    var get_var(int i);

    void register_variables(string postfix);
    void enter_var_values();

    friend class postfix; // ���������� recognize
};