#ifndef STACK_H
#define STACK_H

#include <vector>
#include <stdexcept>

// Use inheritance from std::vector (choose public/private) as appropriate
template <typename T>
class Stack 
{
public:
    Stack();
    ~Stack();
    bool empty() const;
    size_t size() const;
    void push(const T& item);
    void pop();  // throws std::underflow_error if empty
    const T& top() const; // throws std::underflow_error if empty
    // Add other members only if necessary
};

template <typename T> 
bool Stack<T>::empty() const
{
  return std::vector<T>::empty();
}

//size
template <typename T>
size_t Stack<T>::size() const
{
  return std::vector<T>::size();
}

//push
template <typename T>
void Stack<T>::push(const T& item)
{
  std::vector<T>::push_back(item);
}

//pop 
template <typename T>
void Stack<T>::pop()
{
  if(empty()){
    throw std::underflow_error("Stack is empty.");
  }
  std::vector<T>::pop_back();
}

//top
template <typename T>
const T& Stack<T>::top() const
{
  if(empty())
  {
    throw std::underflow_error("Stack is empty.");
  }
  return std::vector<T>::back();
}

#endif