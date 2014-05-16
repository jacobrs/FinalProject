#include "serialization.hpp"


/*
  Function: int serialize(const T &x, fstream file)
  Purpose: Create a binary representation of `x` and write it to `file`.
  Preconditions: `file` is open and read for writing. The `put` cursor is positioned at the end of the file for appending.
  Postcondition: The binary representation of `x` is written to `file`. The `put` cursor is positioned at the end of the file. The number of bytes written to the file is returned. 
 */

/* int */

int serialize(const int &i, std::fstream& file) {
    if(!file.is_open())
        throw serialize_exception();
    file.clear();
    file.write((char*)&i, sizeof(int));
    return sizeof(int);
}

int deserialize(int &i, std::fstream& file) {
    if(!file.is_open())
        throw serialize_exception();
    file.clear();
    file.read((char*)&i, sizeof(int));
    return sizeof(int);
}

/* char */

int serialize(const char &c, std::fstream& file) {
    if(!file.is_open())
        throw serialize_exception();
    file.clear();
    file.write(&c, 1);
    return 1;
}

int deserialize(char &c, std::fstream& file) { 
    if(!file.is_open())
        throw serialize_exception();
    file.clear();
    file.read(&c, 1);
    return 1;
}

/* long */

int serialize(const long &l, std::fstream& file) {
    if(!file.is_open())
        throw serialize_exception();
    file.clear();
    file.write((char*)&l, sizeof(long));
    return sizeof(long);
}
int deserialize(long &l, std::fstream& file) {
    if(!file.is_open())
        throw serialize_exception();
    file.clear();
    file.read((char*)&l, sizeof(long));
    return sizeof(long);
}

/* double */

int serialize(const double &d, std::fstream& file) {
    if(!file.is_open())
        throw serialize_exception();
    file.clear();
    file.write((char*)&d, sizeof(double));
    return sizeof(double);
}

int deserialize(double &d, std::fstream& file) {
    if(!file.is_open())
        throw serialize_exception();
    file.clear();
    file.read((char*)&d, sizeof(double));
    return sizeof(double);
}

/* std:string */

int serialize(const std::string &s, std::fstream& file) {
    if(!file.is_open())
        throw serialize_exception();
    
    serialize(STRING_SERIAL_ID, file);
    serialize((int)s.length(), file); // cast needed since length() returns a `size_type`

    file.write(s.c_str(), s.length());
    
    return s.length() + sizeof(long) + sizeof(int); // content + header
}

int deserialize(std::string &s, std::fstream& file) {
    if(!file.is_open())
        throw serialize_exception();
    
    long id;
    int size;
    deserialize(id, file);
    deserialize(size, file);

    if(id != STRING_SERIAL_ID || size < 0)
        throw serialize_exception();

    char* buffer = new char[size+1];
    file.read(buffer, size * sizeof(char));
    buffer[size] = '\0';
    s = std::string(buffer);
    delete buffer;

    return size + sizeof(long) + sizeof(int);
}

