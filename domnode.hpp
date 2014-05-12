#include "linkedlist.hpp"
#include <fstream>
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

	void set_text(string t){type = t;};
	void set_name(string n){name = n;};
	void set_children(linked_list<dom_node*> tmp){children = tmp;};
	void set_attribute(linked_list<attribute*> tmp){attrs = tmp;};

	string get_name(){return name;};

	void set_inner_html(dom_node* current, string html);
	linked_list<dom_node*> get_elements_by_tagname(string tag);

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
void dom_node::pretty_print(ostream& out, int level){
	//TODO
}



class dom {

public: 
	dom(string filename);
    dom_node* get_element_by_id(string id);
	linked_list<dom_node*> get_elements_by_tagname(string tag);
	void pretty_print(ostream& out, int level);
private: 
	dom_node* get_element_by_id(dom_node* current, string id);
	dom_node* head; 
};

dom::dom(string file){
	fstream fin(file);
	lexer lex(fin);
	head->set_children(parse_elements(lex));
}