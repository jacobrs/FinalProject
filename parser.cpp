#include "parser.hpp"

hash_map<std::string, std::string> parse_attributes(lexer& lex) {

    // collect the name/value pairs in hash_map
    hash_map<std::string, std::string> attributes;

    // from grammar rules: when we no longer see an NAME, we're done with the list.
    while(lex.peek().type == ATTRIBUTE_NAME) {
        // grammar rule states that attributes are NAME, then =, then VALUE.
        std::string name = lex.accept().value;
        lex.expect(EQUALS_SIGN);
        lexeme l = lex.expect(ATTRIBUTE_VALUE);
        
        // add entry to hash_map
        attributes.put(name, l.value);       
    }
    return attributes;
}

dom_node* parse_element(lexer& lex) {
    // TODO
    return NULL; 
}

array_list<dom_node*> parse_elements(lexer& lex) {

    // collect nodes in a list.
    array_list<dom_node*> elements;

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
