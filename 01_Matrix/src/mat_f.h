#pragma once
#include "vect_f.h"

template<typename T>
class mat_f;

template<typename T>
int find_width(const mat_f<T>& m);

// ^ mat_f и find_width взаимосвязаны и должны "знать" друг о друге

template<typename T>
class mat_f : public vect_f<vect_f<T> >
{
public:
    mat_f(int _dim = 10, int _width = DEFAULT_WIDTH);
    mat_f(const mat_f& m);
    mat_f(const vect_f<vect_f<T> >& v);
    ~mat_f();

    mat_f operator+ (const mat_f& m);
    mat_f operator- (const mat_f& m);
    mat_f operator* (const mat_f& m);

    mat_f operator+ (const T t);
    mat_f operator- (const T t);
    mat_f operator* (const T t);

    vect_f<T> operator*(const vect_f<T>& v);

    mat_f& operator=(const mat_f& m);
    bool operator== (const mat_f& m) const;
    bool operator!= (const mat_f& m) const;

    void update_width();

    friend istream& operator>>(istream& in, mat_f<T>& m)
    {
        for (int i = 0; i < m.dim; i++)
            in >> m.coord[i];
            if (!in.good())
                throw "input error: incorrect format";
        m.update_width();
        return in;
    }

    friend ostream& operator<<(ostream& out, const mat_f<T>& m)
    {
        for (int i = 0; i < m.dim; i++)
            out_fixed_width(out, m[i], m.width) << endl;
        return out;
    }

    friend int find_width<T>(const mat_f<T>& m);
};


// конструкторы и деструкторы

template<typename T>
mat_f<T>::mat_f(int _dim, int _width) : vect_f<vect_f<T> >(_dim)
{
    this->dim = _dim;
    this->width = _width;
    for (int i = 0; i < this->dim; i++)
        this->coord[i] = vect_f<T>(this->dim - i, i);
}

template<typename T>
mat_f<T>::mat_f(const mat_f<T>& m) : vect_f<vect_f<T> >(m)
{
    this->width = m.width;
}

template<typename T>
mat_f<T>::mat_f(const vect_f<vect_f<T> >& v) : vect_f<vect_f<T> >(v)
{
    this->width = v.width;
}

template<typename T>
mat_f<T>::~mat_f()
{
    this->width = 0;
}

// перегрузки операторов

template<typename T>
mat_f<T> mat_f<T>::operator+ (const mat_f<T>& m)
{
    if (this->dim != m.dim)
        throw "error: different dimensions";
    mat_f<T> tmp(this->dim);
    for (int i = 0; i < this->dim; i++)
        tmp.coord[i] = this->coord[i] + m.coord[i];
    tmp.update_width();
    return tmp;
}

template<typename T>
mat_f<T> mat_f<T>::operator- (const mat_f<T>& m)
{
    if (this->dim != m.dim)
        throw "error: different dimensions";
    mat_f<T> tmp(this->dim);
    for (int i = 0; i < this->dim; i++)
        tmp.coord[i] = this->coord[i] - m.coord[i];
    tmp.update_width();
    return tmp;
}

template<class T>
mat_f<T> mat_f<T>::operator* (const mat_f<T>& m)

{
    if (this->dim != m.dim)
        throw "error: different dimensions";
    mat_f<T> tmp(this->dim);
    for (int i = 0; i < this->dim; i++)
        for (int j = this->coord[i].get_startindex(); j < this->dim; j++)
        {
            tmp.coord[i][j - i] = 0;
            for (int k = i; k <= j; k++)
                tmp.coord[i][j - i] += this->coord[i][k - i] * m.coord[k][j - k];
        }
    tmp.set_width(find_width(tmp));
    return tmp;
}

template<typename T>
vect_f<T> mat_f<T>::operator* (const vect_f<T>& v)
{
    if (this->dim != v.get_dim())
        throw "error: different dimensions";
    vect_f<T> tmp(this->dim);
    for (int i = 0; i < this->dim; i++)
    {
        tmp[i] = 0;
        for (int j = 0; j < this->coord[i].get_dim(); j++)
            tmp[i] += this->coord[i][j] * v[i + j];
    }
    tmp.update_width();
    return tmp;
}

template<typename T>
mat_f<T> mat_f<T>::operator+ (const T t)
{
    mat_f<T> tmp(this->dim);
    for (int i = 0; i < this->dim; i++)
        tmp.coord[i] = this->coord[i] + t;
    tmp.update_width();
    return tmp;
}

template<typename T>
mat_f<T> mat_f<T>::operator- (T t)
{
    mat_f<T> tmp(this->dim);
    for (int i = 0; i < this->dim; i++)
        tmp.coord[i] = this->coord[i] - t;
    tmp.update_width();
    return tmp;
}

template<typename T>
mat_f<T> mat_f<T>::operator* (T t)
{
    mat_f<T> tmp(this->dim);
    for (int i = 0; i < this->dim; i++)
        tmp.coord[i] = this->coord[i] * t;
    tmp.update_width();
    return tmp;
}

template<typename T>
mat_f<T>& mat_f<T>::operator= (const mat_f<T>& m)
{
    if (*this == m)
        return *this;

    if (this->dim != m.dim)
    {
        delete[] this->coord;
        this->coord = new vect_f<T>[m.dim];
        this->dim = m.dim;
        
    }
    this->width = m.width;
    for (int i = 0; i < this->dim; i++)
    {
        this->coord[i] = m.coord[i];
        this->coord[i].set_startindex(i);
    }
    return *this;
}

template<typename T>
bool mat_f<T>::operator== (const mat_f& m) const
{
    if (this->dim != m.dim)
        return false;
    for (int i = 0; i < this->dim; i++)
        if (this->coord[i] != m.coord[i])
            return false;
    return true;
}

template<typename T>
bool mat_f<T>::operator!= (const mat_f<T>& m) const
{
    return (!(*this == m));
}

// методы

template <typename T>
void mat_f<T>::update_width()
// update не пересчитывает все заново, а просто берет наибольший width из значений width векторов
{
    int width = DEFAULT_WIDTH;
    for (int i = 0; i < this->get_dim(); i++)
    {
        if ((*this)[i].get_width() > width)
            width = (*this)[i].get_width();
    }
    this->width = width;
};

// друж. функции

template <typename T>
int find_width(mat_f<T>& m)
// find вызывает метод update_width предка (vect_f) для каждого вектора матрицы
// т.е. width пересчитывается  для каждого из векторов, и затем возвращается наибольшее значение
{
    int width = DEFAULT_WIDTH;
    for (int i = 0; i < m.get_dim(); i++)
    {
        m[i].vect_f<T>::update_width(); // векторное обновление width
        if (m[i].get_width() > width)
            width = m[i].get_width();
    }
    return width;
};
