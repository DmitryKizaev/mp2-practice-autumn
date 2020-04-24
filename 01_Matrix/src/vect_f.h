#pragma once
#include "vect.h"

template<typename T>
class vect_f;

template<typename T>
int find_width(const vect_f<T>& v);

// ^ vect_f и find_width взаимосвязаны и должны "знать" друг о друге

template<typename T>
class vect_f : public vect<T>
{
protected:
    int width;

public:
    vect_f(int _dim = 10, int _startindex = 0, int _width = DEFAULT_WIDTH);
    vect_f(const vect_f& v);
    ~vect_f();

    vect_f operator+ (const vect_f& v);
    vect_f operator- (const vect_f& v);

    vect_f operator+ (const T t);
    vect_f operator- (const T t);
    vect_f operator* (const T t);

    vect_f& operator= (const vect_f& v);

    int get_width() const;
    void set_width(int i);
    void update_width();

    friend istream& operator>>(istream& in, vect_f<T>& v)
    {
        T user_input;
        for (int i = 0; i < v.dim; i++)
            while (true)
            {
                in >> user_input;
                if (!in.good() or in.peek() != '\n') // peek чтобы не совали double в int
                {
                    cout << "incorrect format, please retry" << endl;
                    cin.clear();
                    while (cin.get() != '\n');
                }
                else // все ок
                {
                    v.coord[i] = user_input;
                    break;
                }
            }
        v.set_width(find_width(v));
        return in;
    }

    friend ostream& operator<<(ostream& out, const vect_f<T>& v) 
    // вывод вектора со своей width, используется при обычном выводе вектора
    {
        for (int i = 0; i < v.startindex; i++)
            out << setw(v.width + DEFAULT_SPACE) << right << fixed << " ";
        for (int i = 0; i < v.dim - 1; i++)
            out << setw(v.width + DEFAULT_SPACE) << setprecision(DEFAULT_PRECISION) << right << fixed << v.coord[i];
        out << setw(v.width + DEFAULT_SPACE) << setprecision(DEFAULT_PRECISION) << right << fixed << v.coord[v.dim - 1];
        return out;
    }

    friend ostream& out_fixed_width(ostream& out, const vect_f<T>& v, int _width)
    // вывод вектора с заданной width, используется в матрицах для унификации ширины поля,
    // когда для всех векторов вне зависимости от их собств. width нужно применить width матрицы
    {
        for (int i = 0; i < v.startindex; i++)
            out << setw(_width + DEFAULT_SPACE) << right << fixed << " ";
        for (int i = 0; i < v.dim - 1; i++)
            out << setw(_width + DEFAULT_SPACE) << setprecision(DEFAULT_PRECISION) << right << fixed << v.coord[i];
        out << setw(_width + DEFAULT_SPACE) << setprecision(DEFAULT_PRECISION) << right << fixed << v.coord[v.dim - 1];
        return out;
    }

    friend int find_width<T>(const vect_f<T>& v);
};

// специализация шаблона друж. функции find_width под векторы чисел разных типов

// реализация для целых чисел
template <>
int find_width<int>(const vect_f<int>& v)
{
    int width = DEFAULT_WIDTH; // начинаем со стандартного значения
    for (int i = 0; i < v.dim; i++) // идем по вектору
    {
        int len = int(to_string(v.coord[i]).length()); // запишем длину
        if (len > width) // если результат шире и не помещается в текущее поле
            width = len; // записать его как новую ширину поля
    }
    return width;
}

template <>
int find_width<long>(const vect_f<long>& v)
{
    int width = DEFAULT_WIDTH; // начинаем со стандартного значения
    for (int i = 0; i < v.dim; i++) // идем по вектору
    {
        int len = int(to_string(v.coord[i]).length()); // запишем длину
        if (len > width) // если результат шире и не помещается в текущее поле
            width = len; // записать его как новую ширину поля
    }
    return width;
}

// реализация для десятичных дробей
template <>
int find_width<double>(const vect_f<double>& v)
{
    int width = DEFAULT_WIDTH; // начинаем со стандартного значения
    for (int i = 0; i < v.dim; i++) // идем по вектору
    {
        string converted = to_string(v.coord[i]); // конвертируем i-й элемент (число) в строку
        converted = converted.substr(0, converted.find(".") + 1 + DEFAULT_PRECISION); // обкусываем до указанной точности
        int len = int(converted.length());
        if (len > width) // если результат шире и не помещается в текущее поле 
            width = len; // записать его как новую ширину поля
    }
    return width;
}

template <>
int find_width<float>(const vect_f<float>& v)
{
    int width = DEFAULT_WIDTH; // начинаем со стандартного значения
    for (int i = 0; i < v.dim; i++) // идем по вектору
    {
        string converted = to_string(v.coord[i]); // конвертируем i-й элемент (число) в строку
        converted = converted.substr(0, converted.find(".") + 1 + DEFAULT_PRECISION); // обкусываем до указанной точности
        int len = int(converted.length());
        if (len > width) // если результат шире и не помещается в текущее поле 
            width = len; // записать его как новую ширину поля
    }
    return width;
}

// конструкторы и деструкторы класса vect_f

template<typename T>
vect_f<T>::vect_f(int _dim, int _startindex, int _width) : vect<T>(_dim, _startindex) // инициализатор
{
    this->width = _width;
}

template<typename T>
vect_f<T>::vect_f(const vect_f<T>& v) : vect<T>(v)
{
    this->width = v.width;
}

template<typename T>
vect_f<T>::~vect_f()  // деструктор предка будет вызван автоматически, явно не вызываем
{
    this->width = 0;
}

// перегрузки операторов класса vect_f

template<typename T>
vect_f<T> vect_f<T>::operator+ (const vect_f<T>& v)
{
    if (this->startindex != v.startindex)
        throw "startindex error";
    if (this->dim != v.dim)
        throw "sum error: different dimensions";
    vect_f<T> sum(this->dim);
    for (int i = 0; i < this->dim; i++)
        sum.coord[i] = this->coord[i] + v.coord[i];
    sum.update_width();
    return sum;
}

template<typename T>
vect_f<T> vect_f<T>::operator- (const vect_f<T>& v)
{
    if (this->startindex != v.startindex)
        throw "startindex error";
    if (this->dim != v.dim)
        throw "difference error: different dimensions";
    vect_f<T> sum(this->dim);
    for (int i = 0; i < this->dim; i++)
        sum.coord[i] = this->coord[i] - v.coord[i];
    sum.update_width();
    return sum;
}

template<typename T>
vect_f<T> vect_f<T>::operator+ (const T t)
{
    vect_f<T> sum_c(*this);
    for (int i = 0; i < this->dim; i++)
        sum_c.coord[i] = sum_c.coord[i] + t;
    sum_c.update_width();
    return sum_c;
}

template<typename T>
vect_f<T> vect_f<T>::operator- (const T t)
{
    vect_f<T> sum_c(*this);
    for (int i = 0; i < this->dim; i++)
        sum_c.coord[i] = sum_c.coord[i] - t;
    sum_c.update_width();
    return sum_c;
}

template<typename T>
vect_f<T> vect_f<T>::operator* (const T t)
{
    vect_f<T> k_vect_f(*this);
    for (int i = 0; i < this->dim; i++)
        k_vect_f.coord[i] = k_vect_f.coord[i] * t;
    k_vect_f.update_width();
    return k_vect_f;
}

template<typename T>
vect_f<T>& vect_f<T>::operator= (const vect_f<T>& v)
{
    if (*this == v)
        return *this;

    if (this->dim != v.dim)
    {
        this->dim = v.dim;
        delete[] this->coord;
        this->coord = new T[this->dim];
    }
    this->startindex = v.startindex;
    this->width = v.width;

    for (int i = 0; i < this->dim; i++)
        this->coord[i] = v.coord[i];
    return *this;
}

// методы класса vect_f

template<typename T>
int vect_f<T>::get_width() const
{
    return this->width;
}

template<typename T>
void vect_f<T>::set_width(int i)
{
    this->width = i;
}

template<typename T>
void vect_f<T>::update_width()
{
    this->width = find_width(*this);
}
