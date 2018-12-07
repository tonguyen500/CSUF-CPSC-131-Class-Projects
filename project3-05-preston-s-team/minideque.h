//
//  minideque.h
//  minidequeproject
//

#ifndef minideque_h
#define minideque_h

#include <vector>
#include <stack>
#include <algorithm>
#include <string>
#include <iostream>


template <typename T>
class minideque {
private:
	std::vector<T> fronthalf_;  // use stack
	std::vector<T> backhalf_;    // use queue

public:
	minideque() = default;                                   // do not change, C++ defaults are ok
	minideque(const minideque<T>& other) = default;          // rule of three       constructor
	minideque& operator=(const minideque<T>& other) = default;				//		copy constructor
	~minideque() = default;													//      Destructor

	size_t size() const;             // TODO
	size_t fronthalfsize() const;    // TODO
	size_t backhalfsize() const;     // TODO
	bool empty()  const;              // TODO

	// balance queue across both vectors if pop_front/back is requested on an empty vector
	// e.g., minideque has this:                  | ABCDEFG
	// after pop_front                        BCD | EFG (A discarded)
	// symmetric logic for converse case: ABCDEFG | ===> ABC | DEF (G discarded) after pop_back
	void pop_front();  // TODO
	void pop_back();   // TODO

	void push_front(const T& value);   // TODO
	void push_back(const T& value);    // TODO

	const T& front() const;   // TODO
	const T& back() const;    // TODO
	T& front();               // TODO
	T& back();                // TODO

	const T& operator[](size_t index) const;  // TODO
	T& operator[](size_t index);              // TODO

	void clear();  // TODO




	friend std::ostream& operator<<(std::ostream& os, const minideque<T>& dq) {    // do not change
		if (dq.empty()) { return os << "minideque is empty"; }

		dq.printFronthalf(os);
		os << "| ";
		dq.printBackhalf(os);
		os << ", front:" << dq.front() << ", back:" << dq.back() << ", size:" << dq.size();
		return os;
	}

	void printFronthalf(std::ostream& os = std::cout) const {                    // do not change
		if (empty()) { std::cout << "fronthalf vector is empty"; }

		for (typename std::vector<T>::const_reverse_iterator crit = fronthalf_.crbegin();
			crit != fronthalf_.crend(); ++crit) {
			os << *crit << " ";
		}
	}

	void printBackhalf(std::ostream& os = std::cout) const {                     // do not change
		if (empty()) { os << "backhalf vector is empty"; }

		for (typename std::vector<T>::const_iterator cit = backhalf_.cbegin();
			cit != backhalf_.cend(); ++cit) {
			os << *cit << " ";
		}
	}

};
template <typename T>
size_t minideque<T>::size() const
{
	return fronthalf_.size() + backhalf_.size();
}

template <typename T>
size_t minideque<T>::fronthalfsize() const
{
	return fronthalf_.size();
}

template <typename T>
size_t minideque<T>::backhalfsize() const
{
	return backhalf_.size();
}


//empty
template <typename T>
bool minideque<T>::empty() const
{
    if (fronthalf_.empty() && backhalf_.empty())
            {
                return true;
            }
}

//popfront
template <typename T>
void minideque<T>::pop_front()
{
    if (fronthalf_.empty()) //if its empty go to clear function
    {
        clear();
    }
    else
    {
        fronthalf_.pop_back();
    }


}

//popback
template <typename T>
void minideque<T>::pop_back()
{
    if (backhalf_.empty())
    {
        clear();
    }
    else
    {
        backhalf_.pop_back();
    }


}

//clear
template <typename T>
void minideque<T>::clear()
{
    if (fronthalf_.empty())
    {
    //for half the number of get size +1 b/c rounding
    for(int i = 0; i!= ((backhalf_.size()+1)/2); i++) // or?
    {
        //insert values into front half from its begin the value at backhalf [i]
        //every loop adds to beginning of vector and pushes first value to end
        //thus first value becomes "element [0]" and our popfront which pops the end of our fronthalf will work
        fronthalf_.insert(fronthalf_.begin(),backhalf_[i]);

    }
    //erase all values we have inserted in, so beginning to half of backhalf vector
    backhalf_.erase(backhalf_.begin(),(backhalf_.begin()+(backhalf_.size()+1)/2));
    }
    else if (backhalf_.empty())
    {
        for(int i = 0; i!= ((fronthalf_.size()+1)/2); i++) // or?
    {
        //insert values into front half from its begin the value at backhalf [i]
        //every loop adds to beginning of vector and pushes first value to end
        //thus first value becomes "element [0]" and our popfront which pops the end of our fronthalf will work
        backhalf_.insert(backhalf_.begin(),fronthalf_[i]);

    }
    //erase all values we have inserted in, so beginning to half of backhalf vector
    fronthalf_.erase(fronthalf_.begin(),(fronthalf_.begin()+(fronthalf_.size()+1)/2));
    }

}



//push_front: pushes back on front half effectively making the back of fronthalf the first element of dequeque
template <typename T>
void minideque<T>::push_front(const T& value)
{
    fronthalf_.push_back(value);
}

//push back: same as push front, but back is middle value of dequeque
template <typename T>
void minideque<T>::push_back(const T& value)
{
    backhalf_.push_back(value);
}

//front const
template <typename T>
 const T& minideque<T>:: front() const
{
    //the front of dequeque is back of vector fronthalf,
    if (fronthalf_.empty())
    {
        return backhalf_.front();// but if empty then the front of backhalf is the front
    }
    return fronthalf_.back();

}

//back const for functionality allows work with reference and non constant so compiler
//doesnt get confused
template <typename T>
 const T& minideque<T>:: back() const
{
    if (backhalf_.empty())
    {
        return fronthalf_.front();
    }
    return backhalf_.back();

}

//front T&
template <typename T>
	T& minideque<T>:: front()
	{
    if (fronthalf_.empty())
    {
        return backhalf_.front();
    }
    return fronthalf_.back();

}

	//back T&
template <typename T>
    T& minideque<T>:: back()
   {
        if (backhalf_.empty())
        {
            return fronthalf_.front();
        }
        return backhalf_.back();

    }

//operator [] overload
template <typename T>
const T& minideque<T>::operator[](size_t index) const
{
    return backhalf_[index];

}

template <typename T>
T& minideque<T>::operator[](size_t index)
{
    return backhalf_[index];

}


#endif /* minideque_h */
