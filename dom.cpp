#include "domnode.hpp"
#include "parser.hpp"

dom_node::dom_node(){
	type = "";
	name = "";
    text = "";
}
dom_node::dom_node(string t){
	type = t;
	name = "";
    text = "";
}
dom_node::~dom_node(){
	clear_children();
	clear_attributes();
}

void dom_node::print_spacing(ostream &out, int tabs){
    for(int i = 0; i < tabs; i++)
        out << "\t";
}

array_list<dom_node*> dom_node::get_elements_by_tagname(string tagname){
    array_list<dom_node*>* ret = new array_list<dom_node*>; //returning array list
	if(name == tagname) //found tag name?
        ret->add(this);
    children.reset();
    dom_node* tmp;
    array_list<dom_node*> retarr;
    while(children.has_next()){ //visit next child
        tmp = children.next();
        retarr = tmp->get_elements_by_tagname(tagname); //recursivly check for matched tag name
        //merging with current return array
		while(!retarr.is_empty()){
            ret->add(retarr.get(0));
            retarr.remove(0);
        }
    }
    return *ret;
}

void dom_node::pretty_print(ostream &out, int level){
    print_spacing(out, level);
    if(type != "TEXT"){
        out << "<" << name;
        attribute* tmp;
        attrs.reset();
        string endtag = ">";
        while(attrs.has_next()){
            tmp = attrs.next();
            out << " " << tmp->key << "=\"" << tmp->value << "\"";
            endtag = "/>";
        }
        out << endtag;
        out << endl;
        children.reset();
        while(children.has_next()){
            children.next()->pretty_print(out, (level+1));
            out << endl;
        }
        print_spacing(out, level);
        out << "</" << name << ">";
    }
    else{
        out << text;
    }
}

void dom_node::set_innerhtml(string html){
    istringstream sin(html);
    lexer lex(sin);
	children.clear();	//delete current children
    children = parse_elements(lex);	//set new html
}

dom_node* dom_node::get_child(int num){
    dom_node* ret = NULL;
    if(num >= get_children().size() || num < 0)
        throw invalid_child_number("ERROR: The child number demanded is invalid");
    else{
		//find child
        children.reset();
        for(int i = 0; i <= num; i++){
            ret = children.next();
        }
    }
    return ret;
}

dom_node* dom_node::get_element_by_id(string id){
	//check all attributes of current node
	attrs.reset();
	while(attrs.has_next()){
		attribute* retattr = attrs.next();
		if(getAttributeID(retattr) == "id"){
			if(id == getAttributeValue(retattr))
				return this;
		}
	}
	//visit next child of current node
	children.reset();
	while(children.has_next()){
		dom_node* ptr = children.next();
		ptr = ptr->get_element_by_id(id);
		if(ptr != NULL)
			return ptr;
	}
	return NULL;
}

dom_node* dom::get_element_by_id(string id){
	dom_node* tmp = get_root()->get_element_by_id(id);
	if(tmp == NULL)
		throw id_not_found("ERROR: The querried ID was not found");
	return tmp;
}


dom::~dom(){
	get_root()->clear_children();
	get_root()->clear_attributes();
}

dom::dom(string file){
	ifstream fin(file);
	//open file and begin parsing at root of DOM
	if(fin.is_open()){
        lexer lex(fin);
		head = new dom_node;
        head->set_children(parse_elements(lex));	
    }
	fin.close();
}

void dom::pretty_print(ostream &out){
	//call pretty print on root of DOM
    dom_node* root;
    linked_list<dom_node*> tmp = head->get_children();
    tmp.reset();
    while(tmp.has_next()){
        root = tmp.next();
        root->pretty_print(out, 0);
    }
}

dom_node* dom::get_root(){
	//get the root of DOM
    dom_node* root;
    linked_list<dom_node*> tmp = head->get_children();
    tmp.reset();
    if(!tmp.has_next())
        throw invalid_node("ERROR: Function called on invalid DOM");
    root = tmp.next();
    return root;
}

array_list<dom_node*> dom::get_elements_by_tagname(string tagname){
    array_list<dom_node*> tmp = get_root()->get_elements_by_tagname(tagname);
    if(tmp.is_empty())
        throw tag_not_found("ERROR: The tag requested was not found");
    return tmp;
}

void dom::set_innerhtml(string html){
    get_root()->set_innerhtml(html);
}