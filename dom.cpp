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

void dom_node::print_spacing(ostream &out, int tabs){
    for(int i = 0; i < tabs; i++)
        out << "\t";
}

array_list<dom_node*> dom_node::get_elements_by_tagname(string tagname){
    array_list<dom_node*>* ret = new array_list<dom_node*>; //returning array list
    if(name == tagname)
        ret->add(this);
    children.reset();
    dom_node* tmp;
    array_list<dom_node*> retarr;
    while(children.has_next()){
        tmp = children.next();
        retarr = tmp->get_elements_by_tagname(tagname);
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

dom_node* dom_node::get_child(int num){
    dom_node* ret = NULL;
    if(num >= get_children().size() || num < 0)
        throw invalid_child_number("The child number demanded is invalid");
    else{
        children.reset();
        for(int i = 0; i <= num; i++){
            ret = children.next();
        }
    }
    return ret;
}

dom_node* dom_node::get_element_by_id(string id){
	attrs.reset();
	while(attrs.has_next()){
		attribute* retattr = attrs.next();
		if(getAttributeID(retattr) == "id"){
			if(id == getAttributeValue(retattr))
				return this;
		}
	}
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


dom::dom(string file){
	ifstream fin(file);
	if(fin.is_open()){
        //istream& in = fin;
        lexer lex(fin);
		head = new dom_node;
        head->set_children(parse_elements(lex));	
    }
}

void dom::pretty_print(ostream &out){
    dom_node* root;
    linked_list<dom_node*> tmp = head->get_children();
    tmp.reset();
    while(tmp.has_next()){
        root = tmp.next();
        root->pretty_print(out, 0);
    }
}

dom_node* dom::get_root(){
    dom_node* root;
    linked_list<dom_node*> tmp = head->get_children();
    tmp.reset();
    if(!tmp.has_next())
        throw invalid_node();
    root = tmp.next();
    return root;
}

array_list<dom_node*> dom::get_elements_by_tagname(string tagname){
    array_list<dom_node*> tmp = get_root()->get_elements_by_tagname(tagname);
    if(tmp.is_empty())
        throw tag_not_found("The tag requested was not found");
    return tmp;
}