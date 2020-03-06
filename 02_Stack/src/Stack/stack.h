#pragma once
#include <iostream>

using namespace std;

template <class T>
class stack
{
private:
    T* elems; 
    int size;
    int top;
public:
    stack(int _size = 10);
    stack(const stack<T>& tmp);
    ~stack();
    void push(T tmp);
    T pop();
    stack& operator=(const stack& tmp);
    bool is_full()const;
    bool is_empty()const;
};

template <class T>
stack<T>::stack(int _size)
{
    size = _size;
    top = 0;
    elems = new T[size];
}

template <class T>
stack<T>::stack(const stack<T>& tmp)
{
    size = tmp.size;
    top = tmp.top;
    elems = new T[size];
    for (int i = 0; i < size; i++)
        elems[i] = tmp.elems[i];
}

template <class T>
stack<T>::~stack()
{
    size = 0;
    top = 0;
    delete[] elems;
}

template <class T>
void stack<T>::push(T a)
{
    if (this->is_full())
        throw "Is Full";
    top++;
    elems[top] = a;
}

template <class T>
T stack<T>::pop()
{
    if (this->is_empty())
        throw "Is Empty";
    T tmp = elems[top];
    top--;
    return tmp;
}

template <class T>
bool stack<T>::is_full()const
{
    return (top == size);
}

template <class T>
bool stack<T>::is_empty()const
{
    return (top == 0);
}

template<class T>
stack<T>& stack<T>::operator=(const stack<T>& tmp)
{
    size = tmp.size;
    top = tmp.top;
    delete[] elems;
    elems = new T[size];
    for (int i = 0; i < size; i++)
        elems[i] = tmp.elems[i];
    return *this;
}
