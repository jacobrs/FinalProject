#include "domnode.hpp"
#include "parser.hpp"

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

dom::dom(string file){
	ifstream fin(file);
	if(fin.is_open()){
        istream& in = fin;
        lexer lex(in);
        head->set_children(parse_elements(lex));
    }
}