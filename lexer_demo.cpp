#include <iostream>
#include <sstream>
#include <string>
#include <limits>
#include "domnode.hpp"
//#include "parser.hpp"

//#define __MACOSX__

//#include "lexer.hpp"

int main(int argc, char** argv) 
{
    string filename = "";
    //Jacob's Path
    //filename = "/users/jacob/Documents/School\ Work/Datastructures/finalproject/FinalProject/workspace/test.txt";
	//Alex's Path
	filename = "./workspace/test.txt";
	//Ian's Path
	//filename = " ";
	dom root(filename);
	
    return 0;
}

