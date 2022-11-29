#ifndef HEAP_H
#define HEAP_H

#include <vector> //added this include
#include <functional>
#include <stdexcept> 
#include <algorithm>

#include <iostream>

template <typename T, typename PComparator = std::less<T> >
class Heap
{
public:
  /**
   * @brief Construct a new Heap object
   * 
   * @param m ary-ness of heap tree (default to 2)
   * @param c binary predicate function/functor that takes two items
   *          as an argument and returns a bool if the first argument has
   *          priority over the second.
   */
  Heap(int m=2, PComparator c = PComparator());

  /**
  * @brief Destroy the Heap object
  * 
  */
  ~Heap();

  /**
   * @brief Push an item to the heap
   * 
   * @param item item to heap
   */
  void push(const T& item);

  /**
   * @brief Returns the top (priority) item
   * 
   * @return T const& top priority item
   * @throw std::underflow_error if the heap is empty
   */
  T const & top() const;

  /**
   * @brief Remove the top priority item
   * 
   * @throw std::underflow_error if the heap is empty
   */
  void pop();

  /// returns true if the heap is empty

  /**
   * @brief Returns true if the heap is empty
   * 
   */
  bool empty() const;

  /**
   * @brief Delete value checks if it's okay
   * 
   */
  void heapify_down(int i);

  /**
   * @brief Add value checks if it's okay
   * 
   */
  void heapify_up(int i);

private:
  /// Add whatever helper functions and data members you need below
  std::vector <T> elements; 
  PComparator comp;
  int m_levels;
};

// Add implementation of member functions here

template <typename T, typename PComparator>
Heap<T,PComparator>::Heap(int m, PComparator c)
{
  m_levels = m;
  comp = c;
}

template <typename T, typename PComparator>
Heap<T,PComparator>::~Heap()
{

}

template <typename T, typename PComparator>
bool Heap<T,PComparator>::empty() const
{
  if (elements.empty()) 
    return true;
  return false;
}

template <typename T, typename PComparator>
void Heap<T,PComparator>::heapify_down(int i)
{
  int left = 2*i+1;
  int right = 2*i+2;

  int size = elements.size();
  int to_switch = i;

  if (left < size)
	{
    if (comp(elements[left], elements[i]))
		{ 
      to_switch = left;
    }
  }
  
  if (right < size)
	{
    if (comp(elements[right], elements[to_switch]))
		{
      to_switch = right;
    }
  }

  if (to_switch != i)
	{
    std::swap(elements[i], elements[to_switch]);
    heapify_down(to_switch);
  }
} 

template <typename T, typename PComparator>
void Heap<T,PComparator>::heapify_up(int i)
{
    int i_parent = (i-1)/2;
    if (comp(elements[i], elements[i_parent]))
		{
      std::swap(elements[i_parent], elements[i]);
      heapify_up(i_parent);
    }
}

template <typename T, typename PComparator>
void Heap<T,PComparator>::push (const T &item)
{
  elements.push_back(item);

  int i = elements.size() - 1;
  heapify_up(i);
}


// We will start top() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("is empty");

  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element
  return elements.front();


}


// We will start pop() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
void Heap<T,PComparator>::pop()
{
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("is empty");
  }

  elements[0] = elements.back();
  elements.pop_back();

  heapify_down(0);
}



#endif