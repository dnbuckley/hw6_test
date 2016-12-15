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
	for (int i = 0;i < word.size(); ++i) word[i] = tolower(word[i]);					// JDB

	int lo = 0;
	int hi = dictionary.size()-1;
	int mid;int res = 0;

	while(lo <= hi){
		mid = (lo+hi)/2;
		if(word == dictionary[mid])
			{	
			res = 2;
			break;
			}	
		if(word < dictionary[mid])
			hi = mid-1;
		else
			lo = mid+1;
	}

// If word legit as a prefix?

	if (lo < 0 || hi < 0) return res;
	int nc = word.size();
	if (word == dictionary[lo].substr(0,nc) || word == dictionary[hi].substr(0,nc)) res += 1;
	return res;
}
