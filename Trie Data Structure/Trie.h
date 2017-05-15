/*****************************************
 * Instructions
 *  - Replace 'uwuserid' with your uWaterloo User ID
 *  - Select the current calendar term and enter the year
 *  - List students with whom you had discussions and who helped you
 *
 * uWaterloo User ID:  aspuri@uwaterloo.ca
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  (Fall) 2016
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *
 * The following is a list of uWaterloo User IDs of those students
 * I had discussions with in preparing this project:
 *    -
 *
 * The following is a list of uWaterloo User IDs of those students
 * who helped me with this project (describe their help; e.g., debugging):
 *    -
 *****************************************/

#ifndef TRIE_H
#define TRIE_H

#ifndef nullptr
#define nullptr 0
#endif

#include "ece250.h"
#include "Trie_node.h"
#include "Exception.h"
#include <iostream>
#include <string>
#include <cctype>
#include <stdio.h>
using namespace std;

class Trie {
	private:
		Trie_node *root_node;
		int trie_size;

	public:
		Trie();
		~Trie();

		// Accessors

		int size() const;
		bool empty() const;
		bool member( std::string const & ) const;
		bool IsAlphabetic(std::string const &) const;
		bool SearchString(std::string const &) const;
		Trie_node *root() const;
		// Mutators

		bool insert( std::string const & );
		bool erase( std::string const & );
		void clear();

	// Friends

	friend std::ostream &operator<<( std::ostream &, Trie const & );
};

Trie::Trie():
root_node( nullptr ),
trie_size( 0 ) {
	// empty constructor
}

Trie::~Trie() {
	clear();
}

int Trie::size() const {
	return trie_size;
}

bool Trie::empty() const {
	if(trie_size ==0){
		
		return true;
	}
	else{
		return false;
	}
}

Trie_node *Trie::root() const {
	if(root_node != nullptr){
        return root_node;
    }
    
    else{
        return nullptr;
    }
}

bool Trie::IsAlphabetic(std::string const &str)const{ // to be completed.
	for(int i= 0;i<str.length();i++){
	if(str[i] >= 0x41 && str[i] <= 0x5A || str[i] >= 0x61 && str[i] <= 0x7A){
		
		return true;
	}
	else{
		return false;
	}
}
}

bool Trie::member( std::string const &str ) const { // need to complete
	/*
	if(IsAlphabetic(str) == false){
		
		throw illegal_argument();
	}
	*/
	bool notalpha = false;
	
	for (int i = 0; i < str.length(); i++)
	{
		if (!isalpha(str[i]))
			//throw illegal_argument();
		notalpha = true;
	}
	if(notalpha==true){
		
		throw illegal_argument();
		
	}
	if(root_node==nullptr){
		return false;
	}
	return root_node->member(str, 0);
	
}

bool Trie::insert( std::string const &str ) {
	//printf("Here");
	//fflush(stdout);
	bool notalpha = false;
	for (int i = 0; i < str.length(); i++)
	{
		if (!isalpha(str[i]))
			//throw illegal_argument();
		notalpha = true;
	}
	if(notalpha==true){
		
		throw illegal_argument();
		
	}
	
	else
		if(size()==0){
		//printf("Here2");
		//fflush(stdout);
		root_node = new Trie_node();
	
		root_node -> insert(str,0);
		trie_size++;
		return true;
	}
	else 
		if(root_node->member(str,0)==true){ 
		
		return false;
		
	}
	
	else{
		root_node -> insert(str,0);
		trie_size++;
		return true;
	}
}

bool Trie::erase( std::string const &str ) {
	
	if(member(str) == false){ // Is the syntax correct?
		
		return false;
		
	}
	
	if(root_node==nullptr){
		
		return false;
	}	
	
	if(size()==1){
		root_node -> erase(str,0,root_node);
		delete root_node;
		trie_size--;
		return true;
	}
	
	else{
		
		root_node -> erase(str,0,root_node);
		trie_size--;
		return true;
	}
		
}


void Trie::clear() {
	/*
	if(trie_size!=0){
		root_node->clear();
		delete root_node;
		trie_size=0;
		}
		else{
			root_node = 0;
			trie_size = 0;
		}
}
*/

    if(root_node!=nullptr){
		root_node->clear();
		root_node = nullptr;
	}
	      trie_size = 0;
	
}   
        
// You can modify this function however you want:  it will not be tested

std::ostream &operator<<( std::ostream &out, Trie const &trie ) {

	return out;
}

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif