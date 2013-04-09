/*
 * LineCutter.cpp
 *
 *  Created on: Feb 19, 2013
 *      Author: while
 */

#include "../include/LineCutter.h"

LineCutter::LineCutter(mod modality, bool complement, char delimiter)
{
	this -> modality = modality;
	this -> complement = complement;
	this -> delimiter = delimiter;
}

LineCutter::LineCutter(mod modality, bool complement)
{
	this -> modality = modality;
	this -> complement = complement;
	this -> delimiter = '\t';
}

LineCutter::LineCutter(mod modality)
{
	this -> modality = modality;
	this -> complement = false;
	this -> delimiter = '\t';
}

std::string LineCutter::cutLine(std::string line, bool* toCut)
{
	std::string resultLine;
	switch (this -> modality) {
	case BYTES:
		resultLine = this -> cutBytes(line, toCut);
		break;
	case FIELDS:
		resultLine = this -> cutFields(line, toCut);
		break;
	default:
		std::cout << "Modality not supported." << "\n";
		break;
	}
	return resultLine;
}

std::string LineCutter::cutBytes(std::string line, bool* toCut)
{
	std::string result = "";
	int len = line.length();
	for (int i = 0; i < len ; i++){
		if(this -> complement == false){ /* Complement is OFF */
			if(toCut[i] == true ){
				result += line[i];  /* char to be cut: added! */
			}
		}else{ /* Complement is OFF*/
			if(toCut[i] == false ){
				result += line[i]; /* char NOT to be cut: added! */
			}
		}

	}
	return result;
}

std::string LineCutter::cutFields(std::string line, bool* toCut)
{
	std::istringstream iss(line);
	std::string token;
	std::string result = "";
	int field = 0;
	while(getline(iss, token, this -> delimiter)){
		if(this -> complement == false){ /* Complement is OFF */
			if(toCut[field] == true ){
				result += token;  /* field to be cut: added! */
			}
		}else{ /* Complement is OFF*/
			if(toCut[field] == false ){
				result += token; /* char NOT to be cut: added! */
			}
		}
		field++;
	}
	return result;
}


