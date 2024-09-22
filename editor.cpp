#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
using namespace std;
#include "linelist.h"

void fileFetch(int argc, char *argv[], LineList &myFEdit);
void FinishUp(char * argv[], LineList& L);

int main(int argc, char *argv[]){	
	//Post: main

	//create a "file" where information can be edited
	LineList myFEdit;
	//enter retrieved text file information into the editable.
	fileFetch(argc, argv, myFEdit);
	//prepare for user input
	string userText;
        int lineNum;
	char userChoice;
/*	 
	  Primary While loop: 
	  Runs continuously, while running, user may enter any of the usable
	  inputs to edit, traverse, and print out the text file.
	  Will notify when the user applies a non existent command.

	  A list of usable commands is as such:
		T: go to the top of the editable file
		B: go to the bottom of the editable file
		I: create a new line to be inserted into the editable.
		D: delete current line
		L: print out current list entirely
		N: go to next line
		P: go to previous line
		E: exit and save the file.
*/
	while(true){
		cout << myFEdit.getCurrLineNum() << "> ";
		cin >> userChoice; cin.ignore(); 
		switch(userChoice){
			case 'T':
				myFEdit.goToTop(); break;
			case 'B':
				myFEdit.goToBottom(); break;
			case 'I':
                            lineNum = myFEdit.getCurrLineNum() + 1;
                            if (myFEdit.getCurrLineNum() > myFEdit.getLength())
                                    lineNum--;
                            cout << lineNum << "> ";
                            getline (cin, userText);
                            myFEdit.insertLine(userText);
                            break;

			case 'D':
				myFEdit.deleteLine(); break;
			case 'L':
				myFEdit.printList(); break;
			case 'N':
				myFEdit.moveNextLine(); break;
			case 'P':
				myFEdit.movePrevLine(); break;
			case 'E':
                                FinishUp(argv, myFEdit);
				break;
			default:
				cout << "Invalid input try again" << endl;
		}
		
	}
return 0;
}


void fileFetch(int argc, char *argv[], LineList &myFEdit){
	//Post: acquire a local text file and enter it into an editable "my file"

	//if the file name is not correct, or no filename is input, an error will notify
  	 if(argc == 1){
		cout << "Error: No filename input!" << endl;
		exit(1);	
	}
	//put the filename in a string and use that name to find the file
	string filename = argv[1];
	ifstream infile(filename.c_str());
	//exit if file opening error
	if(!infile){
		cout << "Error opening file" << endl;
		exit(1);
	}
	//insert file lines into myFEdit
	string line;
	while (getline(infile, line)){
		cout << myFEdit.getCurrLineNum() << "> " << line << endl;
		myFEdit.insertLine(line);
	}
        myFEdit.goToBottom();
	
   infile.close();
}


void FinishUp (char *argv[], LineList& L)
{
        //Post: takes current text and replaces the orginal file text
        
        //begin by opening an out stream
	ofstream outfile;
        string filename = argv[1];
        outfile.open(filename.c_str());
        //return to top of list and enter each line into original file.
	L.goToTop();
        for (int i = 1;  i <= L.getLength();  i++)
        {
                outfile << L.getCurrLine() << endl;
                L.moveNextLine();
        }
        //close and end the program.
	outfile.close();
        exit(1);
}

