#ifndef LINEAR_HASH_TABLE_H
#define LINEAR_HASH_TABLE_H

/*****************************************
 * UW User ID:  aspuri
 * Submitted for ECE 250
 * Semester of Submission:  (Fall) 2016
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *****************************************/

#include "Exception.h"
#include "ece250.h"

enum state {EMPTY, OCCUPIED, DELETED};

template<typename T>
class LinearHashTable {
	private:
		int count;
		int power;
		int array_size;
        	int mod;
		T *array;            // This array will contain values placed in the hash table.
		state *occupied;
	     double loadfactor;
         int h1( T const & ) const; // first hash function
           int isize ;		
          	
            

	public:
		LinearHashTable( int = 5 );
		~LinearHashTable();
		int size() const;
		int capacity() const;
		double load_factor() const;
		bool empty() const;
		bool member( T const & ) const;
		T bin( int ) const;


		void insert( T const & );
		bool remove( T const & );
		void clear();
		void print() const;
};

template<typename T >
LinearHashTable<T >::LinearHashTable( int m ):
array_size( 1 << m ){
	
	array = new T [array_size];
       isize = array_size;	
	occupied = new state [array_size];
	power =m;
	
	for ( int i = 0; i < array_size; ++i ) {
		occupied[i] = EMPTY;
	}
}

template<typename T >
LinearHashTable<T >::~LinearHashTable() { // destructor for the hashtable.
	
	delete [] array;
    delete [] occupied;
}

template<typename T >
int LinearHashTable<T >::size() const { // returns the number of element stored in the hashtable.
   
	return count;
}
// Return the Capacity of the hash tabel
template<typename T >
int LinearHashTable<T >::capacity() const {
    
	 return array_size;
}
// Return the load factor of the hash table.
template<typename T >
double LinearHashTable<T >::load_factor() const {
    
	 
	
	return (float)count/(float)array_size;
}
// Return true if hash table is empty otherwise false.
template<typename T >
bool LinearHashTable<T >::empty() const {
   
	if (count==0){
		return true;
	}
	return false;
}
// the function determine the bin in which value has to stored.
template<typename T >
int LinearHashTable<T >::h1( T const &obj ) const { 
	int hash1 = static_cast<int>(obj);
     
    if(hash1>0){
		
		return hash1 % array_size;
	}
	
	else{
		
		return (hash1 + array_size) % array_size;
	}
		
	} 	 

	
// Return true if the object is in the hash table else false.
template<typename T >
bool LinearHashTable<T >::member( T const &obj ) const {
	
	int probe = h1(obj);
	int k = probe;
	int i=0;
	while (occupied[probe] != EMPTY){
      
            if (array[probe] == obj && occupied[probe]==OCCUPIED) {
                return true;
            }
     
		i++;
        probe=(k + i) % array_size;
        
    }
    return false;
}
// Return the entry in bin n.
template<typename T >
T LinearHashTable<T >::bin( int n ) const {
    
	return array[n]; // return the entry in the bin.
}

template<typename T >
void LinearHashTable<T >::insert( T const &obj ) {
	 
	
	  int probe = h1(obj); // assign the value of the hash function after 1st mod to probe.
	
     if (load_factor() > 0.75){ // if loadfactor is greater than 0.75
	array_size = 2*array_size; // double the size of the array
        T *new_array = new T[array_size]; // create a new array of double size.
        state *new_occupied = new state[array_size]; // make a new status array of double size.
		
		 for(int j = 0; j<array_size; j++){ // assign the status of all elemets in new array as EMPTY.
            
            new_occupied[j] = EMPTY; 
        }
		
		
		 // rehash the values from the previous array insert it into the new array of double the size.
		for(int j = 0; j < (array_size)/2; j++){ // 
			if(occupied[j] == OCCUPIED){
				int k=0;
				int hash = ((int)array[j]+array_size)%array_size;
				int temp = hash;
		    
			  while(new_occupied[hash]== OCCUPIED){
			   k++;
			   hash=(temp+ k) % array_size;
			
			  }
			  new_array[hash] = array[j];            
              new_occupied[hash] = occupied[j];
		
		
		    }  
		 
	    }
		// delete the previous array and assign the new array of double size as the only array.
		T *temp_array = array;
		//delete[] array;
        array = new_array;
        delete [] temp_array;
        
        state *temp_occupied = occupied;
        occupied = new_occupied;
        delete [] temp_occupied;
		int i=0;
		 int hash = ((int)obj + i + array_size)%array_size;
        int temp = hash;
		
		while(occupied[hash]==OCCUPIED){
			i++;
			hash = (temp +i)%array_size;
			
		}
        
        array[hash] = obj;
        occupied[hash] = OCCUPIED;
        count++;
	}
		else{
		int i =0;
		int t = probe; 
		while (occupied[probe] == OCCUPIED) {
			 i++;
        probe=(t + i) % array_size;
       // i++;
          }
        // if (occupied[probe] != OCCUPIED) {
          array[probe]=obj;
          occupied[probe]=OCCUPIED;
          count++;
          //}
		
		}
	
	
	
	}


template<typename T >
bool LinearHashTable<T >::remove( T const &obj ) {
	// enter your implemetation here
	/*if (count==0) {
        throw underflow();
    }
	*/
	int probe = h1(obj);
	//int t = probe;
	//int k =0;
	
	if(member(obj) == false){  // if there are no members in the table then return false.
        
        return false;
    }
	else{
	if(load_factor() <= 0.25 && capacity() != isize){ // if load factor is less than equal to 0.25
	
	    array_size = array_size/2; // shrink the size of the array to half.
        T *new_array = new T[array_size]; // create a new array of half size
        state *new_occupied = new state[array_size]; // create a new status array of half the size.
		//probe = h1(obj);
		int t = probe; // store the value of 1st mod in t.
		
		 for(int j = 0; j<array_size; j++){ // initally make all the element status in the new array as EMPTY
                
                new_occupied[j] = EMPTY;
            }
		
		// rehash the values from the previous array of double size and insert it into the new array of half size.
		for(int i = 0; i < 2*array_size; i++){ 
		       if(occupied[i]==OCCUPIED){
				   
				   int k=0;
				int hash = (((int)array[i])%array_size);
				int temp = hash;
				   
			   
		
		while(new_occupied[hash]== OCCUPIED){
                //k++;
                k++;
                hash = (temp+k)%array_size;
				
            }
			 new_array[hash] = array[i];
            new_occupied[hash] = occupied[i];
			
		
		//return true;
		}
		}
		// delete the previous array and assign the new array of half size as the only array.
        T *temp_array = array;
        array = new_array;
        delete [] temp_array;
        
        state *temp_occupied = occupied;
        occupied = new_occupied;
        delete [] temp_occupied;
		 
		// return true;
		
	}
	
	
		
	// otherwise delete the elements and decrement the counter.
	//else{
		int k =0;
		probe = h1(obj);
		int t = probe;
		//probe = h1(obj);
		
	    while (occupied[probe] == OCCUPIED) {
       
            if (array[probe] == obj) { // if the element we want to delete is found delete it.
			                           // otherwise go to the else statement and hash for the value
				
                occupied[probe]=DELETED;
                count--;
			
                return true;
            }
        else{
			
		k++;
        probe=(t+k) % array_size; // hash for the value
		
		}
		
    }
	                                   
            occupied[probe] = DELETED;  // delete the value once found.                         
            count--;  
			return true;
		}
	
	
}
// Clear the all values of the hash table and set array state to empty.
template<typename T >
void LinearHashTable<T >::clear() {
	
	count=0;
    for (int i=0; i<array_size; i++) {
        occupied[i]=EMPTY;
    }
}
// Prints the all the values in the hash table.
template<typename T >
void LinearHashTable<T >::print() const{
	for(int i=0; i < array_size;i++){
       
            std::cout << array[i] << std::endl;
			
       
    }
	for(int i=0; i < array_size;i++){
       
            std::cout <<  occupied[i] << std::endl;
			
       
    }
	
}

#endif