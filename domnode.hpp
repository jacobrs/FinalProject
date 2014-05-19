#ifndef _DOMNODE_HPP_
#define _DOMNODE_HPP_

#include "linkedlist.hpp"
#include "lexer.hpp"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct attribute{
	string key;	//i.e. id, title, etc.
	string value;
	attribute* next;
};

class dom_node{
public:
	dom_node();
	dom_node(string);

	void pretty_print(ostream&, int);

	void set_text(string t){text = t;}
	void set_name(string n){name = n;}
	void set_children(linked_list<dom_node*> tmp){children = tmp;}
	void set_attribute(linked_list<attribute*> tmp){attrs = tmp;}
    
    linked_list<dom_node*> get_children(){return children;};

	string get_name(){return name;}

	void set_inner_html(dom_node*, string);
	linked_list<dom_node*> get_elements_by_tagname(string );

	//access children
	int number_children();
	dom_node* get_child(int);
private:
    void print_spacing(ostream&, int);
	string type;
	string name;
    string text;
	linked_list<attribute*> attrs;
	linked_list<dom_node*> children; 
};

class dom {
public: 
	dom(string);
    dom_node* get_element_by_id(string id);
    void pretty_print(ostream&);
	linked_list<dom_node*> get_elements_by_tagname(string tag);
private: 
	dom_node* get_element_by_id(dom_node* current, string id);
	dom_node* head; 
};

#endif