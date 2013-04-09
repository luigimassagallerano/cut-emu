/*
 * FileIterator.cpp
 *
 *  Created on: Feb 18, 2013
 *      Author: while
 */
#include "../include/FileIterator.h"

FileIterator::FileIterator(const char* nomeFile)
{
	this->file.open(nomeFile, ios::in);

	if (!this->file.good()) {
		printf ("Error opening file\n");
		exit(-1);
	}
}

FileIterator::~FileIterator()
{
	if(this->file.is_open()){ this->file.close(); }
}

bool FileIterator::hasNext()
{
	getline (this->file, this->current_line);
	if(this->file.eof()){
		return false;
	}else{
		return true;
	}
}

string FileIterator::next()
{
	return this->current_line;
}





