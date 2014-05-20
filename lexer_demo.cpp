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
    outfile = "/users/jacob/Documents/School\ Work/Datastructures/finalproject/FinalProject/workspace/out.txt";
    filename = "/users/jacob/Documents/School\ Work/Datastructures/finalproject/FinalProject/workspace/test.txt";
    testfile = "/users/jacob/Documents/School\ Work/Datastructures/finalproject/FinalProject/workspace/sample.txt";
    
    // =============================== //
    //         Alex's Paths            //
    // =============================== //
	//outfile = "./workspace/out.txt";
	//filename = "./workspace/test.txt";
	//testfile = "./workspace/sample.txt";
    
    
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
    dom mydom(filename);
	string tagname = "mov";
	string id = "starwars-ep4";
    //mydom.pretty_print(outf);
    //outf << endl << " =========== INDIVIDUAL TEST ==========" << endl << endl;
    //mydom.get_root()->get_child(0)->get_child(8)->pretty_print(outf, 0);

    try{
        mydom.get_root()->set_innerhtml("<strong>SUCK IT BEN</strong>");
        mydom.pretty_print(outf);
    }catch(parse_exception error) {
        std::cerr << error.message << std::endl;
        return 1; }
    catch(lexer_exception error) {
        std::cerr << error.message << std::endl;
        return 1;
    }
    
    // =============================== //
	//  GET ELEMENTS BY TAGNAME TEST   //
	// =============================== //
	outf << endl << " =========== GET ELEMENTS BY TAG NAME ==========" << endl << endl;
    try{
		outf << "The tag name searched for: " << tagname << endl << endl;
		outf << "Results:" << endl << endl;
        array_list<dom_node*> tmp = mydom.get_elements_by_tagname(tagname);
        while(!tmp.is_empty()){
            tmp.get(0)->pretty_print(outf, 0);
            tmp.remove(0);
        }
    }catch(tag_not_found& e){
        outf << "ERROR: " << e.message << endl;
    }

	// =============================== //
	//     GET ELEMENTS BY ID TEST     //
	// =============================== //
	outf << endl << " =========== GET ELEMENTS BY ID ==========" << endl << endl;
	try{
		outf << "The ID searched for: " << id << endl << endl;
		outf << "Results:" << endl << endl;
		mydom.get_element_by_id(id)->pretty_print(outf, 0);
    }catch(id_not_found& e){
        outf << e.message << endl;
    }

    outf.close();
    return 0;
}

