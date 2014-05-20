/*
  ================================================================================
  
  Final Project: HTML DOM tree
  * Version:	Final
  * Author:		Jacob Gagne and Alex Genio
  * For:		Ian Clément
  * Date:		May 20th, 2014
  * Purpose:	This program creates a DOM tree from an XML file. Each element
				is parsed and stored as a dom_node within the DOM tree. Various
				functionality (printing tree, printing subtrees, setting inner html
				getting element by id and tag name, and getting a child) is
				implemented to facilitate DOM tree navigation and manipulation.
				This implementation resembles that of Javascript.
  ================================================================================ 
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <limits>
#include "domnode.hpp"

int main(int argc, char** argv) 
{
    string filename = ""; // file to parse into dom (star wars example)
    string outfile = "";  // file where pretty print outputs
    string testfile = ""; // file pretty print dom takes input (UL example)
    
    // =============================== //
    //         Jacob's Paths           //
    // =============================== //
   /* outfile = "/users/jacob/Documents/School\ Work/Datastructures/finalproject/FinalProject/workspace/out.txt";
    filename = "/users/jacob/Documents/School\ Work/Datastructures/finalproject/FinalProject/workspace/test.txt";
    testfile = "/users/jacob/Documents/School\ Work/Datastructures/finalproject/FinalProject/workspace/sample.txt";*/
    
    // =============================== //
    //         Alex's Paths            //
    // =============================== //
	outfile = "./workspace/out.txt";
	filename = "./workspace/test.txt";
	testfile = "./workspace/sample.txt";
    
    
	// =============================== //
    //          Ian's Paths            //
    // =============================== //
	//filename = " ";
    //outfile = " ";
    //testfile = " ";
    
    
    // =============================== //
    //         MAIN BEGINS             //
    // =============================== //
    
	ofstream outf(outfile);
	string tagname = "actor";
	string id = "starwars-ep4";
	string error = "The program has stopped...";
	
	try {
		dom mydom(filename);

		outf << " =========== PRETTY PRINT ON DOM ==========" << endl << endl;
		mydom.pretty_print(outf);
		outf << endl;
		outf << endl << " =========== PRETTY PRINT ON NODE ==========" << endl << endl;
		mydom.get_root()->get_child(0)->get_child(8)->pretty_print(outf, 0);
		outf << endl;

		outf << endl << " =========== SET INNER HTML ==========" << endl << endl;
        mydom.get_root()->set_innerhtml("<a class=\"header-logo-invertocat\" href=\"https://github.com/\"><span class=\"mega-octicon octicon-mark-github\"></span></a>");
        mydom.pretty_print(outf);
		outf << endl;

		outf << endl << " =========== GET ELEMENTS BY TAG NAME ==========" << endl << endl;
		outf << "The tag name searched for: " << tagname << endl << endl;
		outf << "Results:" << endl << endl;
        array_list<dom_node*> tmp = mydom.get_elements_by_tagname(tagname);
        while(!tmp.is_empty()){
            tmp.get(0)->pretty_print(outf, 0);
            tmp.remove(0);
        }
		outf << endl;

		outf << endl << " =========== GET ELEMENTS BY ID ==========" << endl << endl;
		outf << "The ID searched for: " << id << endl << endl;
		outf << "Results:" << endl << endl;
		mydom.get_element_by_id(id)->pretty_print(outf, 0);
		outf << endl;

	}catch(lexer_exception& e){
		outf << e.message << endl;
		outf << error;
	}catch(invalid_XML& e){
		outf << e.message << endl;
		outf << error;
	}catch(parse_exception& e){
		outf << e.message << endl;
		outf << error;
	}catch(invalid_node& e){
		outf << e.message << endl;
		outf << error;
	}catch(invalid_child_number& e){
		outf << e.message << endl;
		outf << error;
    }catch(tag_not_found& e){ 
        outf << e.message << endl;
		outf << error;
    }catch(id_not_found& e){
        outf << e.message << endl;
		outf << error;
    }
    outf.close();
    return 0;
}

