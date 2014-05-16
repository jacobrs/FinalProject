#ifndef __SERIALIZATION_HPP__
#define __SERIALIZATION_HPP__

#include <string>
#include <fstream>

#include "exceptions.hpp"

/* (de)serialization functions for primitive types and std::string */

int serialize(const int &i, std::fstream& file);
int deserialize(int &i, std::fstream& file);

int serialize(const char &c, std::fstream& file);
int deserialize(char &c, std::fstream& file);

int serialize(const long &l, std::fstream& file);
int deserialize(long &l, std::fstream& file);

int serialize(const double &d, std::fstream& file);
int deserialize(double &d, std::fstream& file);

const long STRING_SERIAL_ID = 972045398;
int serialize(const std::string &s, std::fstream& file);
int deserialize(std::string &s, std::fstream& file);

#endif

