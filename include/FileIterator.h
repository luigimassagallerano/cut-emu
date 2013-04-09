/*
 * FileIterator.h
 *
 *  Created on: Feb 18, 2013
 *      Author: while
 */

#ifndef FILEITERATOR_H_
#define FILEITERATOR_H_

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>

using namespace std;

class FileIterator{

	ifstream file;
	string current_line;

public:

	FileIterator(const char* nomeFile);

	~FileIterator();

	/**
	 * Return the next line of the File
	 */
	string next();

	/**
	 * Check if there are any others lines to read
	 */
	bool hasNext();

};

#endif /* FILEITERATOR_H_ */
