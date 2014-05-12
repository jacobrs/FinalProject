#ifndef __POSITIONSTREAM_HPP__
#define __POSITIONSTREAM_HPP__

#include <string>
#include <istream>
#include <sstream>

class ipositionstream {
public:
    ipositionstream(std::istream &in);

    char get();
    char peek();
    void ignore();
    
    int line() { return current_line_number; }
    int pos() { return current_pos; }

    operator bool() const { return sin || *in_ptr; }

private:
    void next();

    std::istream *in_ptr;
    std::string current_line;
    std::istringstream sin;
    char current;

    int current_line_number;
    int current_pos;
};

#endif
