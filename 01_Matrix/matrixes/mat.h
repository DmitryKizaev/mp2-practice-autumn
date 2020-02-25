#pragma once
#include "vect.h"


template<typename T>
class mat : public vect<vect<T> >
{
public:
    mat(int _dim = 10);
    mat(const mat& m);
    mat(const vect<vect<T> >& v);
    ~mat();

    mat operator+ (const mat& m);
    mat operator- (const mat& m);
    mat operator* (const mat& m);

    mat operator+ (const T t);
    mat operator- (const T t);
    mat operator* (const T t);

    vect<T> operator*(const vect<T>& v);
   
    mat& operator=(const mat& m);
    bool operator== (const mat& m) const;
    bool operator!= (const mat& m) const;

    friend istream& operator>>(istream& in, mat<T>& m)
    {
        for (int i = 0; i < m.dim; i++)
            in >> m.coord[i];
        return in;
    }

    friend ostream& operator<<(ostream& out, const mat<T>& m)
    {
        for (int i = 0; i < m.dim; i++)
            out << m[i] << endl;
        return out;
    }
};

template<typename T>
mat<T>::mat(int _dim) : vect<vect<T> > (_dim)
{
    this->dim = _dim;
    for (int i = 0; i < this->dim; i++)
        this->coord[i] = vect<T>(this->dim - i, i);
}

template<typename T>
mat<T>::mat(const mat<T>& m) : vect<vect<T> >(m)
{}

template<typename T>
mat<T>::mat(const vect<vect<T> > &v) : vect<vect<T> >(v)
{}

template<typename T>
mat<T>::~mat()
{}

template<typename T>
mat<T> mat<T>::operator+ (const mat<T>& m)
{
    if (this->dim != m.dim)
        throw "error: different dimensions";
    mat<T> tmp(this->dim);
    for (int i = 0; i < this->dim; i++)
        tmp.coord[i] = this->coord[i] + m.coord[i];
    return tmp;
}

template<typename T>
mat<T> mat<T>::operator- (const mat<T>& m)
{
    if (this->dim != m.dim)
        throw "error: different dimensions";
    mat<T> tmp(this->dim);
    for (int i = 0; i < this->dim; i++)
        tmp.coord[i] = this->coord[i] - m.coord[i];
    return tmp;
}

template<class T>
mat<T> mat<T>::operator* (const mat<T>& m)
<<<<<<< Updated upstream

=======
<<<<<<< HEAD
=======

>>>>>>> 65634bb4510f02c08ec0bb188c1c5f39479fa5b6
>>>>>>> Stashed changes
{
    if (this->dim != m.dim)
        throw "error: different dimensions";
    mat<T> tmp(this->dim);
    for (int i = 0; i < this->dim; i++)
        for (int j = this->coord[i].get_startindex(); j < this->dim; j++)
        {
            tmp.coord[i][j - i] = 0.0;
            for (int k = i; k <= j; k++)
                tmp.coord[i][j - i] = tmp.coord[i][j - i] + this->coord[i][k - i] * m.coord[k][j - k];
        }
    return tmp;
}


template<typename T>
vect<T> mat<T>::operator* (const vect<T>& v)
{
    if (this->dim != v.get_dim())
        throw "error: different dimensions";
    vect<T> tmp(this->dim);
    for (int i = 0; i < this->dim; i++)
    {
        tmp[i] = 0;
        for (int j = 0; j < this->coord[i].get_dim(); j++)
            tmp[i] +=  this->coord[i][j] * v[i + j];
    }
    return tmp;
}

template<typename T>
mat<T> mat<T>::operator+ (const T t)
{
    mat<T> tmp(this->dim);
    for (int i = 0; i < this->dim; i++)
        tmp.coord[i] = this->coord[i] + t;
    return tmp;
}

template<typename T>
mat<T> mat<T>::operator- (T t)
{
    mat<T> tmp(this->dim);
    for (int i = 0; i < this->dim; i++)
        tmp.coord[i] = this->coord[i] - t;
    return tmp;
}

template<typename T>
mat<T> mat<T>::operator* (T t)
{
    mat<T> tmp(this->dim);
    for (int i = 0; i < this->dim; i++)
        tmp.coord[i] = this->coord[i] * t;
    return tmp;
}

template<typename T>
mat<T>& mat<T>::operator= (const mat<T>& m)
{
    if (*this == m)
        return *this;

    if (this->dim != m.dim)
    {
        this->dim = m.dim;
        delete this->coord;
        this->coord = new vect<T>[this->dim];
    }
    for (int i = 0; i < this->dim; i++)
    {
        this->coord[i] = m.coord[i];
        this->coord[i].set_startindex(i);
    }
    return *this;
}

template<typename T>
bool mat<T>::operator== (const mat& m) const
{
    if (this->dim != m.dim)
        return false;
    for (int i = 0; i < this->dim; i++)
        if (this->coord[i] != m.coord[i])
            return false;
    return true;
}

template<typename T>
bool mat<T>::operator!= (const mat<T>& m) const
{
    return (!(*this == m));
}
