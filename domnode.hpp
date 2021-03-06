#ifndef _DOMNODE_HPP_
#define _DOMNODE_HPP_

#include "linkedlist.hpp"
#include "arraylist.hpp"
#include "lexer.hpp"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct invalid_child_number {
    std::string message;
    invalid_child_number(std::string msg = "") {
        message = msg;
    }
};
struct tag_not_found {
    std::string message;
    tag_not_found(std::string msg = "") {
        message = msg;
    }
};

struct id_not_found {
    std::string message;
    id_not_found(std::string msg = "") {
        message = msg;
    }
};

struct invalid_node {
    std::string message;
    invalid_node(std::string msg = "") {
        message = msg;
    }
};

struct invalid_XML {
    std::string message;
    invalid_XML(std::string msg = "") {
        message = msg;
    }
};

struct attribute{
	string key;	//i.e. id, title, etc.
	string value;
	attribute* next;
};

class dom_node{
public:
	dom_node();
	~dom_node();
	dom_node(string);

	void pretty_print(ostream&, int);

    // Setters
	void set_text(string t){text = t;}
	void set_name(string n){name = n;}
	void set_children(linked_list<dom_node*> tmp){children = tmp;}
	void set_attribute(linked_list<attribute*> tmp){attrs = tmp;}
    
    // Getters
    linked_list<dom_node*> get_children(){return children;};
	string get_name(){return name;}
	string getAttributeID(attribute* tmp){return tmp->key;}
	string getAttributeValue(attribute* tmp){return tmp->value;}

	// Clearers
	void clear_children(){children.clear();}
	void clear_attributes(){attrs.clear();}
    
    void set_innerhtml(string html);
	array_list<dom_node*> get_elements_by_tagname(string);
	dom_node* get_element_by_id(string id);

	//access children
	int number_children(){return children.size();};
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
	~dom();
    dom_node* get_root();
    dom_node* get_element_by_id(string id);
    void pretty_print(ostream&);
    void set_innerhtml(string);
	array_list<dom_node*> get_elements_by_tagname(string tag);
private: 
	dom_node* head; 
};

#endif