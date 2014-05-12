#ifndef __PARSER_HPP__
#define __PARSER_HPP__

#include <string>
#include "domnode.hpp" 
#include "lexer.hpp"
#include "hash_functions.hpp"
#include "hashmap.hpp"
#include "arraylist.hpp"

dom_node* parse_element(lexer &lex);
hash_map<std::string, std::string> parse_attributes(lexer &lex);
array_list<dom_node*> parse_elements(lexer &lex);


#endif
