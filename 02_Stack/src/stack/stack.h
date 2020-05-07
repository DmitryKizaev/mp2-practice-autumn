#pragma once
#include <iostream>

using namespace std;

template <typename T>
class stack
{
private:
    T* elems;
    int size;
    int top;
public:
    stack(int max_size = 10);
    stack(const stack<T>& s);
    ~stack();

    T pop();
    T peek() const;
    void push(T new_el); 
    bool is_full() const;
    bool is_empty() const;
    stack<T>& invert_stack();

    stack<T>& operator=(const stack<T>& other_stack);

    friend ostream& operator << (ostream& stream, const stack<T> _stack)
    {
        stack<T> tmp = _stack;
        tmp.invert_stack();
        stream << "bottom -> ";
        while (!(tmp.is_empty()))
            stream << "'" << tmp.pop() << "' -> ";
        stream << "top" << endl;
        return stream;
    };
};

// конструкторы и деструкторы

template <typename T>
stack<T>::stack(int max_size)
{
    size = max_size;
    top = 0;
    elems = new T[size];
};

template <typename T>
stack<T>::stack(const stack<T>& s)
{
    size = s.size;
    top = s.top;
    elems = new T[size];
    for (int i = 0; i < size; i++)
        elems[i] = s.elems[i];
};

template <typename T>
stack<T>::~stack()
{
    size = 0;
    top = 0;
    delete[] elems;
};

// методы

template <typename T>
void stack<T>::push(T new_el)
{
    if (this->is_full())
        throw "error: stack is already full";
    top++;
    elems[top] = new_el;
};

template <typename T>
T stack<T>::pop()
{
    if (this->is_empty())
        throw "error: stack is already empty";
    T tmp = elems[top];
    top--;
    return tmp;
};

template <typename T>
T stack<T>::peek() const
{
    if (this->is_empty())
        throw "error: stack is already empty";
    return elems[top];
};

template <typename T>
bool stack<T>::is_full() const
{
    return (top == size);
};

template <typename T>
bool stack<T>::is_empty() const
{
    return (top == 0);
};

template<typename T>
stack<T>& stack<T>::operator=(const stack<T>& other_stack)
{
    size = other_stack.size;
    top = other_stack.top;
    delete[] elems;
    elems = new T[size];
    for (int i = 0; i < size; i++)
        elems[i] = other_stack.elems[i];
    return *this;
};

template<typename T>
stack<T>& stack<T>::invert_stack()
{
    if (this->is_empty())
        return *this;
    stack <T> shadow(*this);
    this->top = 0;
    while (!shadow.is_empty())
        this->push(shadow.pop());
    return *this;
};