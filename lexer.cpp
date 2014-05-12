/* TODO
   - comment

 */

#include "lexer.hpp"
#include <cctype>

std::string to_string(symbol s) {
    switch(s) {      
    case TAG_BEGIN:
        return "TAG_BEGIN";
    case TAG_END:
        return "TAG_END";
    case TAG_CLOSE:
        return "TAG_CLOSE";
    case TAG_END_AND_CLOSE:
        return "TAG_END_AND_CLOSE";
    case ATTRIBUTE_NAME:
        return "ATTRIBUTE_NAME";
    case EQUALS_SIGN:
        return "EQUALS_SIGN";
    case ATTRIBUTE_VALUE:
        return "ATTRIBUTE_VALUE";
    case CONTENT:
        return "CONTENT";
    case WHITESPACE:
        return "WHITESPACE";
    }
    return "";
}
    

std::string to_string(lexeme l) {
    std::ostringstream oss;
    oss << to_string(l.type) << "(";
    if(l.value != "")
        oss << "value: " << l.value << ", ";
    oss << "line: " << l.line << ", pos: " << l.pos << ")";
    return oss.str();
}

lexer::lexer(std::istream &in) : ips(in) {
    in_tag = false;
    next();
}

bool lexer::is_whitespace(char c) {
    switch(c){
    case ' ':
    case '\t':
    case '\n':
        return true;
    default:
        return false;
    }
}

bool lexer::is_name_start_char(char c) {
    return isalpha(c) || c == ':' || c == '_';
}

bool lexer::is_name_char(char c) {
    return is_name_start_char(c) || isdigit(c) || c == '-' || c == '.'; 
}


bool lexer::read_name(std::string &value, char delim) {

    // clear any previous string content
    value.clear();

    // verify that the first character is a proper starting NAME character 
    char c = ips.peek();
    if(ips && is_name_start_char(c))
        value += c;
    else
        return false;
    ips.ignore();

    c = ips.peek();
    while(ips && is_name_char(c)) { // util end-of-stream or a non-name character
        ips.ignore();
        value += c;
        c = ips.peek();
    }

    // if we are at the end of a name we should only have whitespace or delimeter, 
    //   anything else indicates an error
    if(ips && !is_whitespace(c) && c != delim) 
        return false;
    else 
        return true;
}

bool lexer::read_text(std::string& value, char delim) {

    // clear any previous string content
    value.clear();
    
    char c = ips.peek();
    // read until end-of-stream or delimeter
    while(ips && c != delim) {
        ips.ignore();
        value += c;
        c = ips.peek();
    }
    return true;
}

lexeme lexer::accept() {
    if(!has_next())
        throw lexer_exception("Error: premature end of stream.");
    lexeme tmp = current_lexeme;
    next();
    return tmp;
}

lexeme lexer::expect(symbol type) {
    if(!has_next())
        throw lexer_exception("Error: premature end of stream.");
     if(current_lexeme.type != type)
        throw parse_exception("Error: expected " + to_string(type) + " but saw " + to_string(current_lexeme));
    return accept();
}

void lexer::next() {

    // detect end-of-stream
    if(!ips) {
        has_current_lexeme = false;
        return;
    }
        
    // lexeme position in the position of the first character
    current_lexeme.line = ips.line();
    current_lexeme.pos = ips.pos();
    current_lexeme.value = "";

    switch(ips.peek()) {
    case '<':  // start a tag
        in_tag = true;
        ips.ignore();

        if(ips.peek() == '/') {  // "</"
            current_lexeme.type = TAG_CLOSE;
            ips.ignore();
        }
        else 
            current_lexeme.type = TAG_BEGIN;

        // read the tag's name
        if(!read_name(current_lexeme.value, '>'))
            throw lexer_exception("Error: expected NAME at " + to_string(current_lexeme));
        
        break;

    case '>': // end a tag
        current_lexeme.type = TAG_END;
        ips.ignore();
        in_tag = false;
        break;

    case '/': // start of close atomic tag
        ips.ignore();
        if(ips.peek() == '>') { // "/>"
            ips.ignore();
            current_lexeme.type = TAG_END_AND_CLOSE;
            in_tag = false;
        }
        else
            throw lexer_exception("Error: expected '>' at " + to_string(current_lexeme));

        break;

    case '=':
        current_lexeme.type = EQUALS_SIGN;
        ips.ignore();
        break;        

    case '"': // start of VALUE (single quoted)
        ips.ignore();
        current_lexeme.type = ATTRIBUTE_VALUE;
        if(read_text(current_lexeme.value, '"'))
            ips.ignore(); // consume a "
        break;

    case '\'': // start of VALUE (double quoted)
        ips.ignore();
        current_lexeme.type = ATTRIBUTE_VALUE;
        if(read_text(current_lexeme.value, '\''))
            ips.ignore(); // comsume a '
        break;

    default: // whitespace, attribute names or plain text

        char c = ips.peek();

        if(is_whitespace(c)) {
            // eagerly consume whitespace
            current_lexeme.type = WHITESPACE;
            ips.ignore();
            c = ips.peek();
            while(is_whitespace(c)){
                ips.ignore();
                c = ips.peek();
            }
        }
        else {
            // if we're in a tag: plain text should be an attribute name
            // otherwise, it is "content"
            if(in_tag) { 
                current_lexeme.type = ATTRIBUTE_NAME;
                if(!read_name(current_lexeme.value, '='))
                    throw lexer_exception("Error: expected NAME at " + to_string(current_lexeme));
            }
            else { 
                current_lexeme.type = CONTENT;
                read_text(current_lexeme.value, '<');
            }
        }
    }

    // whenever we hit a whitespace lexeme, advance to the next lexeme
    if(current_lexeme.type == WHITESPACE)
        next();
    else
        has_current_lexeme = true;
  
}


