#include "linkedlist.hpp"
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

	void add(dom_node* child);
	void set_text(string);

	void set_inner_html(dom_node* current, string html);
	array_list<dom_node*> get_elements_by_tagname(string tag);

	//access children
	int number_children();
	dom_node* get_child(int);
private:
	string type;
	string name;
	linked_list<attribute*> attrs;
	linked_list<dom_node*> children; 
};

dom_node::dom_node(){
	type = "";
	name = "";
}
dom_node::dom_node(string t){
	type = t;
	name = "";
}

class dom {

public: 
	dom(string filename);
    dom_node* get_element_by_id(string id);
	array_list<dom_node*> get_elements_by_tagname(string tag);
private: 
	dom_node* get_element_by_id(dom_node* current, string id);
	dom_node* head; 
};

dom::dom(string file){
	head = NULL;
}