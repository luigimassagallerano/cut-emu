/*
 * main.cpp
 *
 *  Created on: Feb 19, 2013
 *      Author: while
 */

#include "../include/LineCutter.h"
#include "../include/FileIterator.h"
#include <getopt.h>
#include <stdlib.h>

void use_error(){
	cout << "You must specify a list of bytes or fields and an input file." << "\n";
	cout << "Ex: cutem -b 1,2,3 -i FILEPATH " << "\n\n";
	cout << "-b b1,b2,..,bn -i INPUT   select only these bytes " << "\n";
	cout << "-f f1,f2,..,fn -i INPUT   select only these fields; " << "\n";
	cout << "-i INPUT                  work on this input file " << "\n";
	cout << "-d DEL                    use DELIM instead of TAB for field delimiter " << "\n";
	cout << "-c                        complement the set of selected bytes or fields" << "\n\n";
	cout << "Use -b OR -f" << "\n";
	cout << "Use -d ONLY with -f" << "\n";
	exit(-1);
}

void createToCutArray(char* list, bool* toCut, int len){

	for(int i=0; i<len; i++){
		toCut[i] = false;
	}


	std::istringstream iss(list);
	std::string token;
	int field = 0;
	while(getline(iss, token, ',')){
		int value = atoi(token.c_str());
		if( value <= 0){ use_error(); }
		if((value-1) < len-1){
			toCut[(value-1)] = true;
		}
	}
}


int main(int argc, char ** argv){

	bool f_opt = false; char* f_arg;
	bool b_opt = false; char* b_arg;
	bool d_opt = false; char* d_arg;
	bool i_opt = false; char* i_arg;
	bool c_opt = false;

	int c;
	while((c =  getopt(argc, argv, "cf:b:d:i:")) != EOF)
	{
		switch (c)
		{
		case 'f':
			f_opt = true;
			f_arg = optarg;
			break;
		case 'b':
			b_opt = true;
			b_arg = optarg;
			break;
		case 'd':
			d_opt = true;
			d_arg = optarg;
			break;
		case 'i':
			i_opt = true;
			i_arg = optarg;
			break;
		case 'c':
			c_opt = true;
			break;
		default:
			use_error();
			break;
		}
	}

	if(f_opt && b_opt){ use_error(); } /* Bytes OR Fields, not both */
	if(b_opt && d_opt){ use_error(); } /* Delimiter only with Fields */
	if(!i_opt){ use_error();} /* Input file missing */

	LineCutter* cutter;

	if(b_opt){ /* Bytes Mode */
		cutter = new LineCutter(BYTES, c_opt);
	}else{ /* Fields Mode */
		if(d_opt){
			cutter = new LineCutter(FIELDS, c_opt, *d_arg);
		}else{
			cutter = new LineCutter(FIELDS, c_opt);
		}

	}

	FileIterator* fileIt = new FileIterator(i_arg);
	bool* tc;
	while(fileIt -> hasNext()){
		string line = fileIt -> next();
		int len = line.length();
		bool tc[len];
		if(b_opt){
			createToCutArray(b_arg, tc, len);
		}else{
			createToCutArray(f_arg, tc, len);
		}
		std::cout << cutter -> cutLine(line, tc) << "\n";
	}


}




