/*
 * LineCutter.h
 *
 *  Created on: Feb 18, 2013
 *      Author: while
 */

#ifndef LINECUTTER_H_
#define LINECUTTER_H_

#include <string>
#include <iostream>
#include <sstream>

enum mod { BYTES = 1, FIELDS = 2 };

class LineCutter{

private:

	mod modality; /* operating modality */
	bool complement; /* complement operation */
	char delimiter; /* delimiter for fields, default = \t */

	/**
	 * Cut the bytes from the line
	 */
	std::string cutBytes(std::string line, bool* toCut);
	/**
	 * Cut the Fields from the line
	 */
	std::string cutFields(std::string line, bool* toCut);

public:

	LineCutter(mod modality, bool complement, char delimiter);
	LineCutter(mod modality, bool complement);
	LineCutter(mod modality);

	/**
	 * Accepts a line. Modifies it according to the state of the object and return it.
	 */
	std::string cutLine(std::string line, bool* toCut);

};


#endif /* LINECUTTER_H_ */
