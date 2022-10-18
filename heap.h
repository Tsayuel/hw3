#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <vector>

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
   * @brief Returns size of the heap
   * 
   */
  size_t size() const;

private:
  /// Add whatever helper functions and list members you need below
	std::vector<T> list;
	PComparator c;
	int m;
	void trickleUp(int idx);
	void trickleDown(int idx);
	
};

// Add implementation of member functions here
template <typename T, typename PComparator>
Heap<T,PComparator>::Heap(int m, PComparator c)
{
	m=m;
	c=c;
}
template <typename T, typename PComparator>
Heap<T,PComparator>::~Heap()
{

}
template <typename T, typename PComparator>
bool Heap<T,PComparator>::empty() const
{
	if (list.size()==0) return true;
	return false;
}
template <typename T, typename PComparator>
size_t Heap<T,PComparator>::size() const
{
	return list.size();
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
		throw std::underflow_error("Empty Heap");
  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element
	return list[0];
}


template <typename T, typename PComparator>
void Heap<T,PComparator>::trickleUp(int idx)
{
	int parent=(idx-1)/m;
	while(parent>=0 && c(list[idx], list[parent]))
	{
		T temp= list[idx];
		list[idx]=list[parent];
		list[parent]=temp;
		idx=parent;
		parent=(parent-1)/m;
	}
}

template <typename T, typename PComparator>
void Heap<T,PComparator>::push(const T& item)
{
	list.push_back(item);
	trickleUp(list.size()-1);
}


template <typename T, typename PComparator>
void Heap<T,PComparator>::trickleDown(int idx)
{
	int leaf = 0;
	int pre = 0;
	while(true)
	{
		if(leaf*m+1>int(list.size()-1)) break;
		pre=leaf;
		leaf=leaf*m+1;
	}
	if(idx>=leaf) return;
	else if(idx>=pre)
	{
		while(pre<leaf)
		{
			bool b = false;
			for(int i = 1; i<=m; i++)
			{
				if(pre*m+i<=int(list.size()-1))
				{
					b=true;
					break;
				}
			}
			if(!b)
			{
				if(idx==pre) return;
			}
			pre++;
		}
	}
	T maxChild = list[idx*m+1];
	int max_idx = idx*m+1;
	for(int i = 2; i<=m; i++)
	{
		if(idx*m+i>int(list.size()-1)) break;
		if(c(list[idx*m+i], maxChild))
		{
			maxChild = list[idx*m+i];
			max_idx=idx*m+i;
		}
	}
	if(c(maxChild, list[idx])) 
	{
		list[max_idx] = list[idx];
		list[idx] = maxChild;
		trickleDown(max_idx);
	}
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
		throw std::underflow_error("Empty Heap");
  }
	list[0] = list[list.size()-1];
	list.pop_back();
	trickleDown(0);
}



#endif