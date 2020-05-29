#pragma once

template<typename T>
class TStack
{

public:    
    virtual T pop() = 0;
    virtual T peek() const = 0;
    virtual void push(T new_el) = 0;
    virtual bool is_full() const = 0;
    virtual bool is_empty() const = 0;
};
