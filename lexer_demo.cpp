#include <iostream>
#include <sstream>
#include <string>
#include <limits>

//#define __MACOSX__

#include "lexer.hpp"

int main(int argc, char** argv) {
    
#ifndef __MACOSX__
    while(true) {
#endif
        std::cin.clear();

        std::cout << "[Type text to send to lexer. Hit CTRL-D when done]" << std::endl;
        std::string line;
        std::string text;
        while(getline(std::cin, line))
            text += line + "\n";
        
        
        std::cout << std::endl << "[Lexemes]" << std::endl;

        std::istringstream sin(text);

        try {
            lexer lex(sin);
            while(lex.has_next())
                std::cout << to_string(lex.accept()) << std::endl;
        }
        catch (lexer_exception e) {
            std::cout << e.message << std::endl;
        }


        std::cout << std::endl;

#ifndef __MACOSX__        
    }
#endif
    
    return 0;
}

