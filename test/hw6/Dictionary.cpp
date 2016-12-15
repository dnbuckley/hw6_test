/*
 * Dictionary.cpp
 *
 *  Created on: Sep 18, 2016
 *      Author: kempe
 */

// The following is a suggestion for how to proceed.
// Feel free to make any changes you like.

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <vector>
#include <string>
#include "Dictionary.h"

using namespace std;

Dictionary::Dictionary(){}

void Dictionary::addInfo (string dictionary_file_name)
{
	ifstream dictFile (dictionary_file_name.c_str());
	string word;

	if (dictFile.is_open())
	{
		while (getline (dictFile, word))
		{
		  //word.erase(word.length()-1); 
		  /* removes end-of-line character; 
		     uncomment if your dictionary file has Windows style line breaks */
			dictionary.push_back(word);
		}
		dictFile.close ();
		sort(dictionary.begin(), dictionary.end());
	}
	else throw invalid_argument("Cannot open file: " + dictionary_file_name);
	return;
}

int Dictionary::checkWord(std::string word){

	//string mid = dictionary[mid];
	for (int i = 0;i < word.size(); ++i) word[i] = tolower(word[i]);	
	int lo = 0;
	int hi = dictionary.size()-1;
	int mid;int res = 0;

	while(lo <= hi){
		mid = (lo+hi)/2;
		if(word == dictionary[mid])
			return 2;
		if(word < dictionary[mid])
			hi = mid-1;
		else
			lo = mid+1;
	}

// If word legit as a prefix?

	int nc = word.size();
	if (lo >= 0 && lo < dictionary.size()){		
		if (word == dictionary[lo].substr(0,nc)) return 1;
		}
	if (hi >= 0 && hi < dictionary.size()){		
		if (word == dictionary[hi].substr(0,nc)) return 1;
		}
	return 0;
}
