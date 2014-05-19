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