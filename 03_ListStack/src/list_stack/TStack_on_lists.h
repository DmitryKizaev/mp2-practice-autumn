#pragma once

#include "TList.h"
#include "TStack.h"

using namespace std;

template <typename T>
class TStack_on_lists : public TStack<T>
{
private:
    TList<T, T>* elems;

public:
    TStack_on_lists();
    TStack_on_lists(const TStack_on_lists<T>& s);
    ~TStack_on_lists();

    T pop();
    T peek() const;
    void push(T new_el);
    bool is_full() const;
    bool is_empty() const;

    int get_usage() const;
};

template<typename T>
TStack_on_lists<T>::TStack_on_lists()
{
    elems = new TList<T, T>;
}

template<typename T>
TStack_on_lists<T>::TStack_on_lists(const TStack_on_lists& s)
{
    elems = new TList<T, T>(s.elems);
}

template<typename T>
TStack_on_lists<T>::~TStack_on_lists()
{
    delete elems;
}

template<typename T>
void TStack_on_lists<T>::push(T new_el)
{
    if (this->is_full())
        throw "error: stack_on_lists is already full";
    elems->insert_to_start(new_el, nullptr);
    elems->reset();
}

template <typename T>
T TStack_on_lists<T>::pop()
{
    if (this->is_empty())
        throw "error: stack_on_lists is already empty";
     T tmp = elems->get_first_key();
     elems->remove_head();
     return tmp;
}

template <typename T>
T TStack_on_lists<T>::peek() const
{
    if (this->is_empty())
        throw "error: stack_on_lists is already empty";
    return elems->get_first_key();
}

template <typename T>
bool TStack_on_lists<T>::is_empty() const
{
    return elems->is_empty();
}

template <typename T>
bool TStack_on_lists<T>::is_full() const
{
    return false;
}

template <typename T>
int TStack_on_lists<T>::get_usage() const
{
    cout << "Max usage supported only for array stack" << endl;
    return -1;
};
