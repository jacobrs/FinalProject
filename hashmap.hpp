/*
  ================================================================================
  
  Class: hash_map<K,V> 
  * Version: 3
  * Author:  Ian Clement <ian.clement@johnabbott.qc.ca>
  * For:     cs406
  * Date:    2014/04/09
  * Purpose: hash_map implementation of the map ADT.

  * Changes from version 2:
      1. moved struct back into the hash_map class but using the templates
         provided to hash_map.

  * Changes from Version 1: 
      1. added serialization (methods).
      2. moved Link struct in it's own header file. Used capital 'L' to 
         differentiate from link() function.
      3. moved exceptions to their own header file.


  ================================================================================ 
*/


#ifndef __HASHMAP_HPP__
#define __HASHMAP_HPP__

#include <algorithm>
#include <fstream>

#define WARN_OBJECT_COPY
#ifdef WARN_OBJECT_COPY
#include <iostream>
#endif

#include "exceptions.hpp"

/* forward declarations to allow (de)serialize(..) to be friend functions */
template <class K, class V>
class hash_map;

template <class K, class V>
int serialize(hash_map<K,V>& map, std::fstream& out);

template <class K, class V>
int deserialize(hash_map<K,V>& map, std::fstream& in);


/* constant for serialization */
const long HASHMAP_SERIAL_ID = 116759315;

/* entry struct to contain key/value pairs */
template <class K, class V>
struct entry {
    K key;
    V value;
    entry() {}
    entry(K key, V value): key(key), value(value) {}
};

const int DEFAULT_TOTAL_BUCKETS = 100;
const double DEFAULT_FACTOR = 0.75;

template <class K, class V>
class hash_map {
public:
    hash_map(int total_buckets = DEFAULT_TOTAL_BUCKETS, double factor = DEFAULT_FACTOR);
    ~hash_map();

    /* copy constructor and `=` operator. */
    hash_map(const hash_map<K,V>& rhs);
    hash_map<K,V>& operator=(const hash_map<K,V>& rhs);

	/*
	  Method: put
	  Purpose:         Associates the specified value with the specified key in this map.
	  Pre-conditions:  None.
	  Post-conditions: The value to which key is mapped to is set to value. If the map previously contained a entry
                       for key (i.e.: contains key(key) is true), the old value is replaced by value.
	*/
    void put(K key, V value);


	/*
	  Method: get
	  Purpose:         Retrieve the value mapped to by the specified key.
	  Pre-conditions:  The map contains a entry for key.
	  Post-conditions: Returns the value to which the specified key is mapped.
	*/
    V get(K key);

	/*
	  Method: remove
	  Purpose:         From this map, remove the entry for the specified key, if it is present.
	  Pre-conditions:  None.
	  Post-conditions: If there is a entry for key, then it is removed, otherwise the map remains the same.
	*/
    V remove(K key);

	/*
	  Method: clear
	  Purpose:         Removes all of the entrys from this map.
	  Pre-conditions:  None.
	  Post-conditions: All entrys are removed from this map.
	*/
    void clear();
    
	/*
	  Method: contains_key
	  Purpose:         Determine is a map contains a entry for the specified key.
	  Pre-conditions:  None.
	  Post-conditions: Returns true if this map contains a entry for the specified key, false otherwise.
	*/
    bool contains_key(K key);

		/*
	  Method: reset
	  Purpose:          Initialize a traversal of the map.
	  Pre-conditions:   
	  Post-conditions:  If the map contains entrys, the traversal cursor is positioned on the first entry. 
                        Otherwise, the traversal is complete (trivially).
	*/
	void reset();

	/*
	  Method: has_next
	  Purpose:          Determine if a traversal can continue.
	  Pre-conditions:   The traversal has been initialized and no put or remove operations have been performed 
	                    since the initialization.
	  Post-conditions:  Returns true is there are elements left in the traversal, false otherwise.
	*/
	bool has_next();

	/*
	  Method: next
	  Purpose:          Return the current entry in the traversal, and then advance the traversal 
	                    cursor to the next entry in the map.
	  Pre-conditions:   The traversal has been initialized and no add or remove operations have been performed 
	                    since the initialization. The traversal still has at least one entry left.
	  Post-conditions:  If there is a next entry, the traversal cursor has advanced to it and it is returned. 
	                    At the end of the traversal cursor is undefined, meaning that is no longer refers to a entry.
	*/
	entry<K,V> next();

	/*
	  Method: is_empty
	  Purpose:         Determine if the map is empty: it contains no key-value entrys.
	  Pre-conditions:  None.
	  Post-conditions: Returns true if this map contains no key-value entrys, false otherwise.
	 */
    /*Returns true if this map contains no key-value entrys.*/
    bool is_empty();

	/*
	  Method: size
	  Purpose:         Determine the number of key-value entrys in this map.
	  Pre-conditions:  None.
	  Post-conditions: Returns the number of key-value entrys in this map.
	*/
    int size() { return map_size; }

    /*
      Method: get_total_buckets
      Purpose:         Determine the size of the bucket array.
      Pre-conditions:  None.
      Post-conditions: Returns the size of the bucket array.
    */
    int get_total_buckets() { return total_buckets; }

    /*
      Function: int serialize(const hash_map<K,V> &map, fstream &file)
      Purpose:         Create a binary serial representation of `map` and write it to `file`.

      Pre-conditions:  The `file` is open and ready for binary writing. 
                       The `put` cursor is positioned at the end of the file for appending.

      Post-condition:  The binary serial representation of `map` is written to `file`. 
                       The `put` cursor is positioned at the end of the file. 
                       The total number of bytes written to the file is returned. 
    */
    friend int serialize<K,V>(hash_map<K,V> &map, std::fstream &file);

    /*
      Function: int deserialize(hash_map<K,V> &map, fstream &file)
      Purpose:         Read the binary serial representation of `map` and recreate the hash_map.

      Pre-conditions:  The `file` is open and ready for binary reading. 
                       The `get` cursor is positioned at the beginning of the serial representation.

      Post-condition:  The binary serial representation is read from `file` and the hash_map recreated without rehashing each entry.
                       The `put` cursor is positioned after the serial representation. 
                       The total number of bytes read from the file is returned. 
    */    
    friend int deserialize<K,V>(hash_map<K,V> &map, std::fstream &file);

private:
            
    struct link {
        link* next;
        entry<K,V> element;
    };
   
    void rehash();

	/* store as array of link pointers */
    link** buckets;

    int map_size;
    int total_buckets;
    double factor;


	/* stores the current position in the traversal */
    int current_bucket;
    link* current;

	/* for checking that the map isn't modified (map size) during a traversal */ 
	bool modified;
};

template <class K, class V>
hash_map<K,V>::hash_map(int total_buckets, double factor):
    total_buckets(total_buckets), 
    factor(factor),
    map_size(0)
{
    // allocate space for buckets
    buckets = new link*[total_buckets];

    // initialize empty buckets as empty lists
    for(int i=0; i<total_buckets; i++)
        buckets[i] = NULL;

    modified = true;
}

template <class K, class V>
hash_map<K,V>::~hash_map() {
    if(buckets != NULL) {
        // for each bucket: delete all links from the "head"
        for(int i=0; i<total_buckets; i++)
            while(buckets[i] != NULL) {
                link* tmp = buckets[i];
                buckets[i] = buckets[i]->next;
                delete tmp;
            }
        delete [] buckets;
    }
}
 
template <class K, class V>
void hash_map<K,V>::clear() {
    for(int i=0; i<total_buckets; i++)
        while(buckets[i] != NULL) {
            link* tmp = buckets[i];
            buckets[i] = buckets[i]->next;
            delete tmp;
        }
}

/* copy constructor */
template <class K, class V>
hash_map<K,V>::hash_map(const hash_map& rhs) {

#ifdef WARN_OBJECT_COPY
    std::cerr << "[Warning] `hash_map` object copied." << std::endl;
#endif

    total_buckets = rhs.total_buckets;
    factor = rhs.factor;
    buckets = new link*[total_buckets];

    // copy each linked list
    for(int i=0; i<total_buckets; i++) {
        if(rhs.buckets[i] == NULL) // empty list
            buckets[i] = NULL;
        else { 
            buckets[i] = new link;

            // use a builder to construct new list starting from "head"
            link* builder = buckets[i];

            // for each link in rhs's bucket[i] list
            for(link* current = rhs.buckets[i]; current != NULL; current = current->next) {
                (builder->element).key = (current->element).key;
                (builder->element).value = (current->element).value;
                
                // create a link unless it's the end
                builder->next = current->next == NULL ? NULL : new link;
                builder = builder->next;
            }
        }
    }
    modified = true;
}

template <class K, class V>
hash_map<K, V>& hash_map<K,V>::operator=(const hash_map& rhs) {
    /* uses "copy-swap" idiom: http://www.cplusplus.com/articles/y8hv0pDG/ */

    // use the copy constructor to create 'tmp'
    hash_map<K, V> tmp(rhs);
    
    // swap tmp's fields with the current object's: 
    std::swap(total_buckets, tmp.total_buckets);
    std::swap(factor, tmp.factor);
    std::swap(buckets, tmp.buckets);
    std::swap(map_size, tmp.map_size);
    modified = true;

    // return the current object
    return *this;    
}

template <class K, class V>
bool hash_map<K,V>::contains_key(K key) {
    // get index by hashing
    int hash_code = ::hash(key);
    int index = hash_code % total_buckets;

    // search list for link containing key
    link* current;
    for(current = buckets[index]; current != NULL && (current->element).key != key; current = current->next); 
    return current != NULL;
}


template <class K, class V>
void hash_map<K,V>::put(K key, V value) {
    // get index by hashing
    int hash_code = ::hash(key);
    int index = hash_code % total_buckets;

    // search for the key in the list
    link* current;
    for(current = buckets[index]; current != NULL && (current->element).key != key; current = current->next);

    // key not found: add an entry to the "head" of the list
    if(current == NULL) {
        current = new link;
        (current->element).key = key;
        (current->element).value = value;
        current->next = buckets[index];
        buckets[index] = current;
        map_size++;
        modified = true;
        
        // added an entry -> rehash
        rehash();
    }
    else // key found: replace value  
        (current->element).value = value;
    
}

template <class K, class V>
V hash_map<K,V>::get(K key) {
    // get index by hashing
    int hash_code = ::hash(key);
    int index = hash_code % total_buckets;

    // search list for the link containing key
    link* current;
    for(current = buckets[index]; current != NULL && (current->element).key != key; current = current->next);

    // throw if key not found: precondition violated.
    if(current == NULL)
        throw key_not_found_exception();

    return (current->element).value;
}


template <class K, class V>
V hash_map<K,V>::remove(K key) {
    // get index by hashing
    int hash_code = ::hash(key);
    int index = hash_code % total_buckets;

    // search list for link containing key, keep track of previous link for deletion.
    link* current;
    link* previous = NULL;
    for(current = buckets[index]; current != NULL && (current->element).key != key; current = current->next)
        previous = current;

    // key not found: precondition violated.
    if(current == NULL)
        throw key_not_found_exception();

    V tmp = current->element.value;
    if(previous == NULL) // remove buckets[i]
        buckets[index] = current->next;
    else             // remove within linked list
        previous->next = current->next;
    delete current;

    map_size--;
    modified = true;

    return tmp;
}

template <class K, class V>
void hash_map<K,V>::rehash() {

    // only rehash when the load factor exceeds the limit
    if((double)map_size / (double)total_buckets < factor)
        return;

    int previous_total_buckets = total_buckets;
    link** previous_buckets = buckets;

    total_buckets *= 2;

    // allocation the new bucket array and initialize to NULLs
    buckets = new link*[total_buckets];
    for(int i=0; i<total_buckets; i++)
        buckets[i] = NULL;
    
    // loop through the previous buckets array and move all links to the new array.
    for(int i=0; i<previous_total_buckets; i++) {

        if(previous_buckets[i] != NULL) { // skip empty lists
            
            // move each link in the linked list to their new position in the larger bucket array
            // recycle the memory by relinking each link.
            // careful: list of keys that hashed to a bucket in the previous bucket size will not necessarily be hashed to the same bucket in the new size.
            
            link* current = previous_buckets[i];
            while(current != NULL) {
                link* tmp = current->next; // store next link since we overwrite `current->next` below
                int index = ::hash((current->element).key) % total_buckets;
                
                // place at the head of the list
                current->next = buckets[index];
                buckets[index] = current;
               
                current = tmp;
            }
        }
    }
    modified = true;
}

template <class K, class V>
void hash_map<K,V>::reset() {
    // starting from the first bucket, move `current` to the next available link
    // if the map is empty current will be NULL
    for(current_bucket = 0; current_bucket < total_buckets && buckets[current_bucket] == NULL; current_bucket++);
    current = (current_bucket < total_buckets) ? buckets[current_bucket] : NULL;
    modified = false;
}

template <class K, class V>
bool hash_map<K,V>::has_next() {
    return current != NULL;
}

template <class K, class V>
entry<K,V> hash_map<K,V>::next() {
    if(current == NULL || modified)
        throw map_traversal_exception();

    // to return the current element in the traversal
    link* tmp = current;

    // if the current list isn't done
    if(current->next != NULL)
        current = current->next;
    else { // move to the next bucket containing links. 
        for(current_bucket++; current_bucket < total_buckets && buckets[current_bucket] == NULL; current_bucket++);
        // set current to NULL if there is no links left
        current = (current_bucket < total_buckets) ? buckets[current_bucket] : NULL;
    }
    return tmp->element;
}

template <class K, class V>
int serialize(hash_map<K,V>& map, std::fstream& out) {
    if(!out.is_open())
        throw serialize_exception();
      
    // TODO

    return -1;
}

template <class K, class V>
int deserialize(hash_map<K,V> &map, std::fstream& in) {
    if(!in.is_open())
        throw serialize_exception();
    
    // TODO
    
    return -1;
}


#endif
