#include "linkedlist.hpp"
using namespace std;

class dom_node{
public:
	dom_node(int t);

	void add(dom_node* child);

	void set_inner_html(dom_node* current, string html);

private:
	int type;
	string name;
	string attribute;
	linked_list<dom_node*> children; 

};


//class dom {
//
//public: 
//	dom(string filename);
//	void add(dom_node*, linked_list<dom_node*>);
//
//
//	 dom_node* get_element_by_id(string id);
//
//	
//
//private: 
//	dom_node* head; 
//
//	void add_node(dom_node* ptr, linked_list<dom_node*> children){
//		ptr = new dom_node;
//		children.add(ptr);
//	}
//};
//
//dom_node::dom_node()
//{
//	head = new node;
//}