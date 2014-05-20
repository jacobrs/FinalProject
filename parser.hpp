#ifndef __PARSER_HPP__
#define __PARSER_HPP__

#include "domnode.hpp" 

linked_list<dom_node*> parse_elements(lexer& lex);
dom_node* parse_element(lexer& lex);

#endif
