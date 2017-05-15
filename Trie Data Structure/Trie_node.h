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

#ifndef SINGLE_NODE_H
#define SINGLE_NODE_H

#ifndef nullptr
#define nullptr 0
#endif

#include <string>
#include <cctype>
#include <stdio.h>
#include "ece250.h"
using namespace std;

class Trie;

class Trie_node {
	private:
		Trie_node **children;
		bool is_terminal;
		static int const CHARACTERS = 26;


	public:
		Trie_node();
		Trie_node *child( int ) const;

		bool member( std::string const &, int ) const;

		bool insert( std::string const &, int );
		bool erase( std::string const &, int, Trie_node *& );
		void clear();

		friend class Trie;

		// if ptr is a pointer to a Trie_node object
		// in one of the friendly classes, you should:
		//    use   ptr->next_   to modify it
		//    use   ptr->next()      to access it
};

Trie_node::Trie_node():
children( nullptr ),
is_terminal( false ) {
	// empty constructor
}

Trie_node *Trie_node::child( int n ) const { // Is this function already implemented.
	if ( children == nullptr ) {
		return nullptr;
	} else {
		return children[n];
	}
}

bool Trie_node::member( std::string const &str, int depth ) const {	
         if(depth == str.size()){
		//is_terminal = true;
		//printf("depth is %d\n",depth);
	    //fflush(stdout);
		return this->is_terminal;
		//cout << depth;
		//printf(depth);
	    //fflush(stdout);
	    }	
		char ch = str[depth];
		int index = tolower(ch)-'a';
		if (this->children == nullptr){
			return false;
		}
		if((this->children[index])!=nullptr){
			//current = ((current->children[index]));
             return this->children[index]->member(str,depth+1);	
              //return true;			  
		}
		else{			
			return false;
	    }
		 
	//}
	
	/*
	if(this->is_terminal == false){
		return false;
	}	
	else{
		return true;
	}
	*/

}

bool Trie_node::insert( std::string const &str, int depth ) {
	
	//printf("here3");
	//fflush(stdout);
	if(depth == str.size()){
		is_terminal = true;
		return true;
	}
		int deep = depth;	
	char ch = str[deep];
	int index = tolower(ch)-'a';
	
	if (children == nullptr){
		children = new Trie_node*[CHARACTERS];
		for (int i = 0; i < CHARACTERS; i++) {
			children[i] = nullptr;
		}
	}
	 if((this->children[index])==nullptr){
		
		children[index] = new Trie_node();
	}
		
		/*Trie_node*t = new Trie_node;
		root_node = t;
		Trie_node**p = new Trie_node*[CHARACTERS];
		root_node.children = p;
		
		for(int i = 0;i<=26;i++){
			t->children+i = nullptr;
			
		}	*/
         deep++;		
	children[index]->insert(str,deep);
	return true;
}

bool Trie_node::erase( std::string const &str, int depth, Trie_node *&ptr_to_this ) {
	if (is_terminal && str.size() == depth) {
		is_terminal = false;
		if (children == nullptr){
			delete this;
			ptr_to_this = nullptr;
		}
		return true;
	}
	int index = tolower(str[depth]) - 'a';
	bool state = children[index]->erase(str,depth+1,children[index]);
	
	if(state == true){
            
        for(int i = 0;i < CHARACTERS; i++){                   
                
            if(this->children[i] != nullptr){
                    
                return true;
            }
        }
            
            if(this->is_terminal == false){
                delete []children;                                 
                ptr_to_this = nullptr;
                delete this;
            }
               return true;
    }
        
            else{
              
			  return false;
            }

}

	

void Trie_node::clear() {	
	if(this->children == nullptr){
		delete this;
		return;
	}	

	for(int i =0; i<26; i++){
		if(children[i] != nullptr){
			children[i]->clear();
			children[i] = nullptr;
	    }
	}
    delete[] children;
	children = nullptr;
    delete this;	 				
	// then delete this node? how do we signify this node, since clear() function doesn't take any parameter. 
	// how do we recurse on this.since there are no parameter.
}


// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif