#pragma once
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

const int DEFAULT_PRECISION = 2;  
// precision: digits after "."

const int DEFAULT_WIDTH = DEFAULT_PRECISION + 3;
// minimal number of digits to show (default value)
// example: "0.253" : 3 precision digits (253) +2 digits ("0" and ".")

const int DEFAULT_SPACE = 2;  
// number of spaces between columns


template<typename T>
class vect
{
protected:
    int dim;
    T* coord;
    int startindex;

public:
    vect(int _dim = 10, int _startindex = 0);
    vect(const vect& v);
    ~vect();

    vect operator+ (const vect& v);
    vect operator- (const vect& v);
    T operator* (const vect& v);

    vect operator+ (const T t);
    vect operator- (const T t);
    vect operator* (const T t);

    vect& operator= (const vect& v);

    T& operator[] (int i);
    const T& operator[] (int i) const;

    T vect_len() const;

    int get_dim() const;
    int get_startindex() const;
    void set_startindex(int i);

    bool operator==(const vect& v) const;
    bool operator!=(const vect& v) const;

    friend istream& operator>>(istream& in, vect<T>& v)
    {
        for (int i = 0; i < v.dim; i++)
            in >> v.coord[i];
        return in;
    }

    friend ostream& operator<<(ostream& out, const vect<T>& v)
    {
        for (int i = 0; i < v.startindex; i++)
            out << setw(DEFAULT_WIDTH + DEFAULT_SPACE) << right << fixed << " ";
        for (int i = 0; i < v.dim - 1; i++)
            out << setw(DEFAULT_WIDTH + DEFAULT_SPACE) << setprecision(DEFAULT_PRECISION) << right << fixed << v.coord[i];
        out << setw(DEFAULT_WIDTH + DEFAULT_SPACE) << setprecision(DEFAULT_PRECISION) << right << fixed <<  v.coord[v.dim - 1];
        return out;
    }
};


template<typename T>
vect<T>::vect(int _dim, int _startindex)
{
    this->dim = _dim;
    this->startindex = _startindex;
    this->coord = new T[this->dim];
}


template<typename T>
vect<T>::vect(const vect<T>& v)
{
    this->dim = v.dim;
    this->startindex = v.startindex;
    this->coord = new T[this->dim];
    for (int i = 0; i < this->dim; i++)
        this->coord[i] = v.coord[i];
}


template<typename T>
vect<T>::~vect() 
{
    this->dim = 0;
    this->startindex = 0;
    delete[] this->coord;
}


template<typename T>
vect<T> vect<T>::operator+ (const vect<T>& v)
{
    if (this->startindex != v.startindex)
        throw "startindex error";
    if (this->dim != v.dim)
        throw "sum error: different dimensions";
    vect<T> sum(this->dim);
    for (int i = 0; i < this->dim; i++)
        sum.coord[i] = this->coord[i] + v.coord[i];
    return sum;
}


template<typename T>
vect<T> vect<T>::operator- (const vect<T>& v)
{
    if (this->startindex != v.startindex)
        throw "startindex error";
    if (dim != v.dim)
        throw "difference error: different dimensions";
    vect<T> sum(this->dim);
    for (int i = 0; i < this->dim; i++)
        sum.coord[i] = this->coord[i] - v.coord[i];
    return sum;
}


template<typename T>
T vect<T>::operator* (const vect<T>& v)
{
    if (this->startindex != v.startindex)
        throw "startindex error";
    if (this->dim != v.dim)
        throw "* error: different dimensions";
    T vect_scp = 0.0;
    for (int i = 0; i < this->dim; i++)
        vect_scp = vect_scp + this->coord[i] * v.coord[i];
    return vect_scp;
}


template<typename T>
vect<T> vect<T>::operator+ (const T t)
{
    vect<T> sum_c(*this);
    for (int i = 0; i < this->dim; i++)
        sum_c.coord[i] = sum_c.coord[i] + t;
    return sum_c;
}


template<typename T>
vect<T> vect<T>::operator- (const T t)
{
    vect<T> sum_c(*this);
    for (int i = 0; i < this->dim; i++)
        sum_c.coord[i] = sum_c.coord[i] - t;
    return sum_c;
}


template<typename T>
vect<T> vect<T>::operator* (const T t)
{
    vect<T> k_vect(*this);
    for (int i = 0; i < this->dim; i++)
        k_vect.coord[i] = k_vect.coord[i] * t;
    return k_vect;
}


template<typename T>
vect<T>& vect<T>::operator= (const vect<T>& v)
{
    if (*this == v)
        return *this;

    if (this->dim != v.dim)
    {
        this->dim = v.dim;
        delete[] this->coord;
        this->coord = new T[dim];
    }
    this->startindex = v.startindex;

    for (int i = 0; i < this->dim; i++)
        this->coord[i] = v.coord[i];
    return *this;
}


template<typename T>
T& vect<T>::operator[] (int i)
{
    if ((i < 0) || (i >= this->dim))
        throw "[] error: wrong coordinate";
    return this->coord[i];
}


template<typename T>
const T& vect<T>::operator[] (int i) const
{
    if ((i < 0) || (i >= this->dim))
        throw "[] error: wrong coordinate";
    return this->coord[i];
}


template<typename T>
T vect<T>::vect_len() const
{
    T vect_len = 0.0;
    for (int i = 0; i < this->dim; i++)
        vect_len = vect_len + this->coord[i] * this->coord[i];
    return sqrt(vect_len);
}


template<typename T>
bool vect<T>::operator==(const vect<T>& v) const
{
    if ((this->dim != v.dim) || (this->startindex != v.startindex))
        return false;

    for (int i = 0; i < this->dim; i++)
        if (this->coord[i] != v.coord[i])
            return false;
    return true;
}


template<typename T>
bool vect<T>::operator!=(const vect<T>& v) const
{
    return (!(*this == v));
}


template<typename T>
int vect<T>::get_dim() const
{
    return this->dim;
}


template<typename T>
int vect<T>::get_startindex() const
{
    return this->startindex;
}


template<typename T>
void vect<T>::set_startindex(int i)
{
    this->startindex = i;
}
