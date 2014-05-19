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
    mydom.pretty_print(outf);
	outf.close();
    return 0;
}

