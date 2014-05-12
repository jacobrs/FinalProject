#ifndef __LEXER_HPP__
#define __LEXER_HPP__

#include <string>
#include <istream>
#include "positionstream.hpp"

struct lexer_exception {
    std::string message;
    lexer_exception(std::string msg = "") {
        message = msg;
    }
};

struct parse_exception {
    std::string message;
    parse_exception(std::string msg = "") {
        message = msg;
    }
};

enum symbol { 
    TAG_BEGIN,              // <NAME
    TAG_END,                // >
    TAG_CLOSE,              // </NAME
    TAG_END_AND_CLOSE,      // />
    ATTRIBUTE_NAME,         // NAME 
    EQUALS_SIGN,            // =
    ATTRIBUTE_VALUE,        // "TEXT"
    CONTENT,                // TEXT
    WHITESPACE
};

std::string to_string(symbol s);
    
struct lexeme {
    symbol type;
    std::string value;
    int line;
    int pos;
};

std::string to_string(lexeme l); 

class lexer {
public:
    lexer(std::istream &in);

    bool has_next() { return has_current_lexeme; }
    lexeme peek() { return current_lexeme; }

    lexeme accept();
    lexeme expect(symbol type);

private:

    // the source is set to use the position stream, which gives line numbers and positions.
    ipositionstream ips;

    // test character classes
    bool is_whitespace(char);
    bool is_name_start_char(char);
    bool is_name_char(char);
    bool is_text_char(char);

    // read symbols
    bool read_name(std::string&, char);
    bool read_text(std::string&, char);

    // advance to next lexeme, detecting end of stream and throwing execeptions
    void next();

    // used to differentiate between plain text outside of a tag and attributes inside a tag.
    bool in_tag;

    // stores current lexeme
    bool has_current_lexeme;
    lexeme current_lexeme;
};

#endif
