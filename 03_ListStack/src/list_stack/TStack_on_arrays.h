#pragma once

#include <iostream>
#include "TStack.h"

using namespace std;

template <typename T>
class TStack_on_arrays : public TStack<T>
{
private:
    T* elems;
    int size;
    int top;
    int max_usage;
public:
    TStack_on_arrays(int max_size = 10);
    TStack_on_arrays(const TStack_on_arrays<T>& s);
    ~TStack_on_arrays();

    T pop();
    T peek() const;
    void push(T new_el); 
    bool is_full() const;
    bool is_empty() const;

    int get_usage() const;
    TStack_on_arrays<T>& operator=(const TStack_on_arrays<T>& other_stack_on_arrays);
};

// constructors & destructors

template <typename T>
TStack_on_arrays<T>::TStack_on_arrays(int max_size)
{
    max_usage = 0;
    size = max_size;
    top = 0;
    elems = new T[size];
};

template <typename T>
TStack_on_arrays<T>::TStack_on_arrays(const TStack_on_arrays<T>& s)
{
    max_usage = s.max_usage;
    size = s.size;
    top = s.top;
    elems = new T[size];
    for (int i = 0; i < size; i++)
        elems[i] = s.elems[i];
};

template <typename T>
TStack_on_arrays<T>::~TStack_on_arrays()
{
    max_usage = 0;
    size = 0;
    top = 0;
    delete[] elems;
};

// methods

template <typename T>
void TStack_on_arrays<T>::push(T new_el)
{
    if (this->is_full())
        throw "error: stack_on_arrays is already full";
    top++;
    if (top > max_usage)
        max_usage = top;
    elems[top] = new_el;
};

template <typename T>
T TStack_on_arrays<T>::pop()
{
    if (this->is_empty())
        throw "error: stack_on_arrays is already empty";
    T tmp = elems[top];
    top--;
    return tmp;
};

template <typename T>
T TStack_on_arrays<T>::peek() const
{
    if (this->is_empty())
        throw "error: stack_on_arrays is already empty";
    return elems[top];
};

template <typename T>
bool TStack_on_arrays<T>::is_full() const
{
    return (top == size);
};

template <typename T>
bool TStack_on_arrays<T>::is_empty() const
{
    return (top == 0);
};

template<typename T>
TStack_on_arrays<T>& TStack_on_arrays<T>::operator=(const TStack_on_arrays<T>& other_stack_on_arrays)
{
    max_usage = other_stack_on_arrays.max_usage;
    size = other_stack_on_arrays.size;
    top = other_stack_on_arrays.top;
    delete[] elems;
    elems = new T[size];
    for (int i = 0; i < size; i++)
        elems[i] = other_stack_on_arrays.elems[i];
    return *this;
};

template <typename T>
int TStack_on_arrays<T>::get_usage() const
{
    return max_usage;
};
