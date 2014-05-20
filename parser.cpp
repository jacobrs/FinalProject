#include "parser.hpp"

dom_node* parse_element(lexer& lex) {
    dom_node* tmp = new dom_node;
	linked_list<attribute*> details;

	tmp->set_name(lex.expect(TAG_BEGIN).value);	// get the name
	while(lex.peek().type == ATTRIBUTE_NAME) {
        // grammar rule states that attributes are NAME, then =, then VALUE.
        string name = lex.accept().value;
        lex.expect(EQUALS_SIGN);
        lexeme l = lex.expect(ATTRIBUTE_VALUE);
        
        // add entry to liked_list
		attribute* attr = new attribute;
		attr->key = name;
		attr->value = l.value;
        details.add(attr);       
    }
	//process elements following tag end
	if(lex.peek().type == TAG_END){
		lex.accept();	
		tmp->set_children(parse_elements(lex));
		if(!(tmp->get_name() == lex.peek().value))
			throw invalid_XML("ERROR: Close tag mismatch");
		lex.expect(TAG_CLOSE); 
		lex.expect(TAG_END);
		tmp->set_attribute(details);
		return tmp;
	}
	//process element terminator
	else if(lex.peek().type == TAG_END_AND_CLOSE){
		lex.accept();
		tmp->set_attribute(details);
		return tmp;
	}

    return NULL; 
}

linked_list<dom_node*> parse_elements(lexer& lex) {

    // collect nodes in a list.
    linked_list<dom_node*> elements;

    // from grammar rules: when we see a '<', were done with plain text.
    // also --> when lexer is exhausted.
    while(lex.has_next() && lex.peek().type != TAG_CLOSE) {
        lexeme l = lex.peek();

        if(l.type == CONTENT) {
            // create a new TEXT node (TODO: you should edit this to match your dom_node class)
            dom_node* current = new dom_node("TEXT");
            current->set_text(l.value);
            elements.add(current);
            lex.accept();
        }
        else if(l.type == TAG_BEGIN) {
            // parse the element
            dom_node* current = parse_element(lex);
            if(current == NULL)
                throw parse_exception("Error: something bad happened"); // this should never occur
            elements.add(current);
        }
        else 
            throw parse_exception("Error: unexpected symbol " + to_string(l) + ")... Expected (TAG_CLOSE)");
    }
    return elements;
}
