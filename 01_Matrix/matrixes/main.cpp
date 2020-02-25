#include <iostream>
#include "mat.h"
#include "debug.h"
using namespace std;

void main()
{
	setlocale(LC_ALL, "Russian");
	test1(); // сложение матриц
	test2(); // вычитание матриц
	test3(); // умножение матриц
	test4(); // сложение с константой
	test5(); // вычитание константы
	test6(); // умножение на константу
	test7(); // умножение на вектор
	test8(); // проверка равенства
	test9(); // проверка неравенства
	test10(); // конструктор копирования
	system("pause");
}