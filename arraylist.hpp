/*################################################################################
  
  array_list class
  * Author:  Ian Clement
  * For:     cs406
  * Purpose: array implementation of list ADT with dynamic memory.
  * Version: 1

  ################################################################################
 */

#ifndef __ARRAYLIST_HPP__
#define __ARRAYLIST_HPP__

#include <cstddef>
#include <algorithm>
using namespace std;

const int DEFAULT_CAPACITY = 8;

//struct invalid_position_exception {};

template <class T>
class array_list {
public:
	array_list();

	/* destructor returns the allocated array */
	~array_list();

	/* copy constructor and operator= are needed to make a "deep" copy of the list */
	array_list(const array_list& list);
	array_list& operator=(const array_list& list);

	/* operations that modify the list's size */
	void add(T element);
	void add(int position, T element);
	T remove(int position);
	void clear();

	/* read and write operations */
	T get(int position);
	T set(int position, T element);

	/* simple list traversal */
    void reset();
    bool has_next();
    T next();

	/* list properties */
	bool is_empty();
	int size();
	bool contains(T element);

private:
	/* support method used to "grow" the dynamic array */
    void expand();

	/* store elements in a dynamic array of size `capacity` */
	T* elements;
    int capacity;
	int list_size;

    /* stores the current position in the traversal */
	int current;
};


template <class T>
array_list<T>::array_list() {
    capacity = DEFAULT_CAPACITY;
    elements = new T[capacity];
    list_size = 0;
}

template <class T>
array_list<T>::~array_list() {
	// return the allocated memory
    delete [] elements;
}

template <class T>
array_list<T>::array_list(const array_list<T>& list) {
	// make an element by element copy of list
	capacity = list.capacity;
	elements = new T[capacity];
	list_size = list.list_size;
	for(int i=0; i<list_size; i++)
		elements[i] = list.elements[i];
}

template <class T>
array_list<T>& array_list<T>::operator=(const array_list<T>& list) {
	/* uses "copy-swap" idiom: http://www.cplusplus.com/articles/y8hv0pDG/ */

	// use the copy constructor to create 'tmp'
	array_list<T> tmp(list);

	// swap tmp's fields with the current object's: 
	swap(capacity, tmp.capacity);
	swap(elements, tmp.elements);
	swap(list_size, tmp.list_size);

	// return the current object.
	return *this;
}

template <class T>
void array_list<T>:: expand() {
	// expand the capacity of the arraylist by doubling the allocated array.
    capacity *= 2;
    T* tmp = new T[capacity];

	// make an element by element copy into the new array
    for(int i=0; i<list_size; i++)
        tmp[i] = elements[i];

	// delete the old array and replace
    delete [] elements;
    elements = tmp;
}

template <class T>
void array_list<T>::add(T element) {
    //  expand if we are at capacity.
	if(list_size >= capacity) 
		expand();
    elements[list_size] = element;
    list_size++;
}

template <class T>
void array_list<T>::add(int position, T element) {
	if(position < 0 && position > list_size)
        throw invalid_position_exception();

	// when "appending" call the add(x) method
	if(position == list_size) {
		add(element);
		return;
	}

	//  expand if we are at capacity.
    if(list_size >= capacity) 
		expand();

	// shift the array upwards to make a new position
    for(int i=list_size; i>position; i--) 
        elements[i] = elements[i-1];

    elements[position] = element;
    list_size++;
}

template <class T>
T array_list<T>::remove(int position) {
	if(position < 0 && position >= list_size)
        throw invalid_position_exception();
    
	// shift the array downwards over the remove positon.
	T ret = elements[position];
	for(int i=position; i<list_size; i++)
        elements[i] = elements[i+1];
    list_size--;
    return ret;
}

template <class T>
void array_list<T>::clear() {
    delete [] elements;
    capacity = DEFAULT_CAPACITY;
    elements = new T[capacity];
    list_size = 0;
}

template <class T>
T array_list<T>::get(int position) {
	if(position < 0 || position >= list_size)
        throw invalid_position_exception();
    return elements[position];
}

template <class T>
T array_list<T>::set(int position, T element) {
	if(position < 0 || position >= list_size)
        throw invalid_position_exception();
    T ret = elements[position];
    elements[position] = element;
    return ret;
}

template <class T>
void array_list<T>::reset() {
    current = 0;
}

template <class T>
bool array_list<T>::has_next() {
    return current < list_size;
}

template <class T>
T array_list<T>::next() {
    // TODO preconditions
    return elements[current++];
}

template <class T>
bool array_list<T>::is_empty() {
    return list_size == 0;
}

template <class T>
int array_list<T>::size() {
    return list_size;
}

template <class T>
bool array_list<T>::contains(T element) {
	// simple linear search
	for(int i=0; i<list_size; i++)
		if(elements[i] == element)
			return true;
	return false;
}

#endif
