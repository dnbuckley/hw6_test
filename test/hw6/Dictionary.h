/*
 * Dictionary.h
 *
 *  Created on: Sep 18, 2016
 *      Author: kempe
 */

// The following is a suggestion for how to proceed.
// Feel free to make any changes you like.

#ifndef DICTIONARY_H_
#define DICTIONARY_H_

#include <string>
#include <vector>

class Dictionary {
public:
	Dictionary();
	void addInfo (std::string dictionary_file_name);

	int checkWord(std::string word);

	// what else will this need?
private:
	std::vector<std::string> dictionary;

};


#endif /* DICTIONARY_H_ */
