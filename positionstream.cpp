#include "positionstream.hpp"

ipositionstream::ipositionstream(std::istream &in) {
    in_ptr = &in;
    current_line_number = 0;
    next();
}

void ipositionstream::next() {
    current_pos++; // this is done either way
    current = sin.get();

    // if the above fails read the next line
    while(!sin) {
        // try reading the next line from `in`
        current_line_number++;
        current_pos = 1;
        getline(*in_ptr, current_line);

        if(!(*in_ptr))
            break; // we have no next...

        current_line += ' ';  // reintroduce the newline as a space
        sin.str(current_line);
        sin.clear();  // clear the error flags
        current = sin.get();
    }
}

char ipositionstream::get() {
    char tmp = current;
    next();
    return tmp;
}

char ipositionstream::peek() {
    return current;
}

void ipositionstream::ignore() {
    next(); 
}



