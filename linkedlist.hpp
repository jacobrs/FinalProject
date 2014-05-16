/*
  ================================================================================
  
  Class: linked_list<T> 
  * Version: 3
  * Author:  Ian Clement <ian.clement@johnabbott.qc.ca>
  * For:     cs406
  * Date:    2014/04/09
  * Purpose: linked list implementation of the list ADT.
  
  * Changes from version 2:
      1. moved struct back into the linked_list class but using the template
         provided to linked_list.

  * Changes from version 1: 
      1. added serialization.
      2. moved link struct in it's own header file. Used capital 'L' to 
         differentiate from link() function.
      3. moved exceptions to their own header file.

  ================================================================================ 
*/


#ifndef __LINKEDLIST_HPP__
#define __LINKEDLIST_HPP__

#include <cstddef>
#include <algorithm>
#include <fstream>

#include "serialization.hpp"
#include "exceptions.hpp"

/* forward declarations to allow (de)serialize(..) to be friend functions */
template <class T>
class linked_list;

template <class T>
int serialize(linked_list<T>& list, std::fstream& out);

template <class T>
int deserialize(linked_list<T>& list, std::fstream& in);


/* constant for serialization */
const long LINKEDLIST_SERIAL_ID = 654733976;


/* Class: linked_list */

template <class T>
class linked_list {
public:
    linked_list();

    /* destructor cleans up the remaining links */
    ~linked_list();

    /* copy constructor and `=` operator. */
    linked_list(const linked_list& list);
    linked_list& operator=(const linked_list& list);

    /* operations that modify the list's size */

    /* 
       Method: add
       Purpose:          Appends the specified element to the end of this list.
       Pre-conditions:   None.
       Post-conditions:  element is the last element of the list. The size of the list is increased by 1.
    */
    void add(T element);
        
    /*
      Method: add
      Purpose:           Inserts the specified element at the specified position in this list.
      Pre-conditions:    position is between 0 and list size (inclusive).
      Post-conditions:   The element is added to the list at position. If position is list size, 
      it is appended to the end of the list. The size of the list is increased by 1.
    */
    void add(int position, T element);

    /*
      Method: remove
      Purpose:           Removes the element at the specified position in this list.
      Pre-conditions:    position is between 0 and list size (exclusive).
      Post-conditions:   The element at postion is removed from the list. The size of the list is decreased by 1.
      The removed element is returned.
    */
    T remove(int position);

    /*
      Method: clear
      Purpose:           Removes all of the elements from this list.
      Pre-conditions:    None.
      Post-conditions:   All elements are removed from the list and the size is set to 0.
    */
    void clear();

    /*
      Method: get
      Purpose:          Retrieve the element at the specified position in this list.
      Pre-conditions:   position is between 0 and list size (exclusive).
      Post-conditions:  Returns the element at position in the list.
    */
    T get(int position);
        
    /*
      Method: set
      Purpose:          Replaces the element at the specified position in this list with the specified element.
      Pre-conditions:   position is between 0 and list size (exclusive).
      Post-conditions:  Sets a new value for the element at location position in the list. 
      Returns the previous value in this location.
    */
    T set(int position, T element);

    /*
      Method: reset
      Purpose:          Initialize a traversal of the list.
      Pre-conditions:   
      Post-conditions:  If the list contains elements, the traversal cursor is positioned on the first element. 
      Otherwise, the traversal is complete (trivially).
    */
    void reset();

    /*
      Method: has_next
      Purpose:          Determine if a traversal can continue.
      Pre-conditions:   The traversal has been initialized and no add or remove operations have been performed 
      since the initialization.
      Post-conditions:  Returns true is there are elements left in the traversal, false otherwise.
    */
    bool has_next();

    /*
      Method: next
      Purpose:          Return the current element in the traversal, and then advance the traversal 
      cursor to the next element in the list.
      Pre-conditions:   The traversal has been initialized and no add or remove operations have been performed 
      since the initialization. The traversal still has at least one element left.
      Post-conditions:  If there is a next element, the traversal cursor has advanced to it and it is returned. 
      At the end of the traversal cursor is undefined, meaning that is no longer refers to an element.
    */
    T next();

    /*
      Method: empty
      Purpose:         Determine if this list contains no elements.
      Pre-conditions:  None.
      Post-conditions: Returns true if this list contains no elements, false otherwise. 
    */
    bool is_empty();

    /*
      Method: size
      Purpose:         Determine the number of elements in this list.
      Pre-conditions:  None.
      Post-conditions: Returns the number of elements in this list.  
    */
    int size();
        
    /*
      Method: contains
      Purpose:         Determine if the provided element is in the list.
      Pre-conditions:  None.
      Post-conditions: Returns true if this list contains no elements false otherwise.
    */
    bool contains(T element);

    /*
      Function: int serialize(linked_list<K,V> &list, fstream &out)
      Purpose:         Create a binary serial representation of `list` and write it to `out`.

      Pre-conditions:  The `out` is open and ready for binary writing. 
                       The `put` cursor is positioned at the end of the file for appending.

      Post-condition:  The binary serial representation of `list` is written to `out`. 
                       The `put` cursor is positioned at the end of the file. 
                       The total number of bytes written to the file is returned. 
    */
    friend int serialize<T>(linked_list<T>& list, std::fstream& out);

    /*
      Function: int deserialize(linked_list<K,V> &list, fstream &in)
      Purpose:         Read the binary serial representation of `list` and recreate the linked_list.

      Pre-conditions:  The `in` is open and ready for binary reading. 
                       The `get` cursor is positioned at the beginning of the serial representation.

      Post-condition:  The binary serial representation is read from `in` and the linked_list recreated.
                       The `put` cursor is positioned after the serial representation. 
                       The total number of bytes read from the file is returned. 
    */ 
    friend int deserialize<T>(linked_list<T>& list, std::fstream& in);
	

private:

    struct link {
        link* next;
        T element;
    };
		
    /*
      Method: add_link
      Purpose: support method to add a link after `current`
    */
    void add_link(link* current, T element) {
        link* tmp = new link;
        tmp->element = element;
        tmp->next = current->next;
        current->next = tmp;
    }
            
    /*
      Method: remove_link
      Purpose: support method to remove a link after `current`
    */
    T remove_link(link* current) {
        link* tmp = current->next;
        T tmp_elem = tmp->element;
        current->next = current->next->next;
        delete tmp;
        return tmp_elem;
    }
                
    /*
      Method: move
      Purpose: support method to add a link after `current`
    */
    link* move(link* current, int i) {
        // move current forward i times.
        for(int j=0; j<i && current != NULL; j++)
            current = current->next;
        return current;
    }

    /* a list is represented with a head "dummy" node to simplify the
     * add/remove operation implementation. */
    link* head; 

    /* a tail pointer is used to make list append operations
     *     add(x), 
     *     add(size(), x)  
     * more efficient */
    link* tail;

    int list_size;

    /* stores the current position in the traversal */
    link* current;

    /* for checking that the list isn't modified (list length) during a traversal */ 
    bool modified;
};

template <class T>
linked_list<T>::linked_list() {
    // create a "dummy" link, representing an empty list
    head = new link;
    head->next = NULL;
    tail = head;
    list_size = 0;
    modified = true;
}

template <class T>
linked_list<T>::~linked_list() {
    // clear deletes everything but the "dummy" link
    clear();
    delete head;
}

template <class T>
linked_list<T>::linked_list(const linked_list<T>& list) {
    // create an empty list
    head = new link;
    tail = head;
    list_size = 0;
    modified = true;
	
    // for each link in the `list` make a corresponding link in the current list. 
    for(link* current = list.head->next; current != NULL; current = current->next) {
        // using tail means it will be at the end of the list at the end of the loop
        tail->next = new link;
        tail = tail->next;
        tail->element = current->element;
        list_size++;
    }

    // set the end of the list correctly.
    tail->next = NULL;
}

template <class T>
linked_list<T>& linked_list<T>::operator=(const linked_list<T>& list) {
    /* uses "copy-swap" idiom: http://www.cplusplus.com/articles/y8hv0pDG/ */

    // use the copy constructor to create 'tmp'
    linked_list<T> tmp(list);

    // swap tmp's fields with the current object's: 
    std::swap(head, tmp.head);
    std::swap(tail, tmp.tail);
    std::swap(list_size, tmp.list_size);	
    modified = true;
	
    // return the current object
    return *this;
}

template <class T>
void linked_list<T>::add(T element) {
    // add a new link at the end of the list, set tail accordingly
    add_link(tail, element);
    tail = tail->next;
    list_size++;
    modified = true;
}

template <class T>
void linked_list<T>::add(int position, T element) {
    if(position < 0 || position > list_size)
        throw invalid_position_exception();

    // when "appending" call the add(x) method
    if(position == list_size) {
        add(element);
        return;
    }

    // move a link pointer to the desired position (point to link "position")
    link* current = move(head, position); 
    add_link(current, element); // place new link between "position" and "position + 1"
    list_size++;
    modified = true;
}

template <class T>
T linked_list<T>::remove(int position) {
    if(position < 0 || position >= list_size)
        throw invalid_position_exception();

    // move a link pointer to the desired position (point to link "position")
    link* current = move(head, position);
    T element = remove_link(current);

    // reset the tail if we're removing the last link
    if(current->next == NULL)
        tail = current;
	
    list_size--;
    modified = true;

    return element;
}

template <class T>
void linked_list<T>::clear() {
    // until there are no more links, delete the link
    while(head->next != NULL) // start _after_ the dummy node
        remove_link(head);
    tail = head; // empty list
    list_size = 0;
    modified = true;
}

template <class T>
T linked_list<T>::get(int position) {
    if(position < 0 || position >= list_size)
        throw invalid_position_exception();

    // move a link pointer to the desired position (point to link "position")
    link* link = move(head->next, position);
    return link->element;
}

template <class T>
T linked_list<T>::set(int position, T element) {
    if(position < 0 || position >= list_size)
        throw invalid_position_exception();

    // move a link pointer to the desired position (point to link "position")
    link* current = move(head->next, position);
    T ret = current->element;
    current->element = element;
    return ret;
}

template <class T>
void linked_list<T>::reset() {
    current = head->next;
    modified = false; // reset this boolean to check for modification within traversal.
}

template <class T>
bool linked_list<T>::has_next() {
    return current != NULL;
}

template <class T>
T linked_list<T>::next() {
    if(current == NULL || modified) 
        throw list_traversal_exception();

    T tmp = current->element;
    current = current->next;
    return tmp;
}

template <class T>
bool linked_list<T>::is_empty() {
    return size() == 0;
}

template <class T>
int linked_list<T>::size() {
    return list_size;
}

template <class T>
bool linked_list<T>::contains(T element) {
    // simple linear search
    link* current = head->next;
    while(current != NULL) {
        if(current->element == element)
            return true;
        current = current->next;
    }
    return false;
}

/* Serialization Format for linked_list<T>:

    [serial_id:int][byte_count:int][size:int][element1:T][element2:T]...[element(size):T]

*/

template <class T>
int serialize(linked_list<T>& list, std::fstream& out) {
    if(!out.is_open())
        throw serialize_exception();
      
    serialize(LINKEDLIST_SERIAL_ID, out);
    int byte_count_pos = out.tellp();
    out.seekp(sizeof(int), std::ios::cur);
    
    int byte_count = 0;
    byte_count += serialize(list.list_size, out);
    
    for(typename linked_list<T>::link* current = (list.head)->next; current != NULL; current = current->next)
        byte_count += serialize(current->element, out);

    int end_pos = out.tellp();
    out.seekp(byte_count_pos);
    serialize(byte_count, out);
    out.seekp(end_pos);

    return byte_count + sizeof(int) + sizeof(long);  // content  + header
}

template <class T>
int deserialize(linked_list<T> &list, std::fstream& in) {
    if(!in.is_open())
        throw serialize_exception();
    
    // check #1: check serial ID
    long id;
    deserialize(id, in);
    if(id != LINKEDLIST_SERIAL_ID)
        throw serialize_exception();

    // check #2: get byte count to check later.
    int content_byte_count;
    deserialize(content_byte_count, in);
    
    // clear the current linked list
    list.clear(); // leaves the dummy node
    list.modified = true; // traversal is interrupted
 
    // keep track of bytes read for checking the content_byte_count
    int byte_count = 0;

    // get list size
    byte_count += deserialize(list.list_size, in);
    
    if(list.list_size > 0 ) {
        typename linked_list<T>::link* builder = list.head; // builder starts at the header     
        for(int i=0; i<list.list_size; i++) {
            builder->next = new typename linked_list<T>::link;
            builder = builder->next;
            byte_count += deserialize(builder->element, in);
        }
        builder->next = NULL;
        list.tail = builder;
    }

    // complete the content byte count check
    if(byte_count != content_byte_count)
        throw serialize_exception();
    
    return content_byte_count + sizeof(int) + sizeof(long); // content + header
}

#endif
