#include "hash_functions.hpp"

#include <climits>

int hash(int i) { 
    return i;
}

int hash(char c) {
    return (int)c;
}

int hash(long l) {
    return (int)(l % (long)INT_MAX);
}

int hash(std::string s) {
    int h = 0;
    for(int i=0; i<s.size(); i++) 
        h += s[i];
    return h;
}
