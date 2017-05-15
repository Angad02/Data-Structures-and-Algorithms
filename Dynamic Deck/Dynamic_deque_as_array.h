#ifndef DYNAMIC_DEQUE_AS_ARRAY_H
#define DYNAMIC_DEQUE_AS_ARRAY_H



#include "ece250.h"
#include "Exception.h"


class Dynamic_deque_as_array
{
    public:
	int *array; // poiner to the array to parse through the array.
	int head1;  // Index of head. 
	int tail1;  // index of tail
	int count;  // counter
	int arraySize; // size of array

	public:
		Dynamic_deque_as_array( int = 10 );
		~Dynamic_deque_as_array();


		int head() const;
		int tail() const;
		int size() const;
		bool empty() const;
		int capacity() const;

		void enqueue_head( const int & );
		void enqueue_tail( const int & );
		int dequeue_head();
		int dequeue_tail();
		void clear();
};
// Constructor of the class 
// initialising head,tail, counter and assignibg the size of the array.
Dynamic_deque_as_array::Dynamic_deque_as_array( int n) {
	
	arraySize = std::max(1,n);         
	array = new int [arraySize]; 
	int head1 = 0;
	int tail1 = 0;
	int count = 0;
	
	
}




Dynamic_deque_as_array::~Dynamic_deque_as_array() { // dealocates the memory allocated for the array.

 delete [] array; 
	
}





int Dynamic_deque_as_array::size() const { // returns the element stored in dequeue.
	return count;
}


int Dynamic_deque_as_array::capacity() const {
	return arraySize;
}


bool Dynamic_deque_as_array::empty() const { // Since, its a boolean return true if array is empty otherwise return false.
     if (count == 0){
	   return true;
	 }
	 else{
	 return false;
	 }
	
}


int Dynamic_deque_as_array::head() const { // return the head of the array, otherwise throw exception.
	
	if(empty()){
		
		throw underflow();
	}
	else{
	
		return array[head1];
	}
	
}


int Dynamic_deque_as_array::tail() const { // return the tail of the array, otherwise throw exception.
	if(empty()){
		
		throw underflow();
	}
	else{
		
		return array[tail1];
	}
}


void Dynamic_deque_as_array::enqueue_head( const int &obj ) { 
	if(empty()){  // if deque is empty then make head = tail =0 and insert the element and increment the counter by 1.
		head1 = 0;
		tail1 = 0;
		array[head1]=obj;
		count = count + 1;
		return;
	}
	
		if(count == arraySize){ // if array is full then copy all the elements in an temp array A.
                                //then delete the previous array and make new array with same name to point to temp array A.
		                        // then enqueue the new element from head and increment counter by 1.
		//int* A = new int [2*arraySize];
		 int* A = new int [2*arraySize]; // initializing temprary array A.
		
		if(head1<=tail1){
			
			for (int i = head1;i<=tail1;i++){ // tail+1
				
				//array[i] = A[i];
				A[i] = array[i];
				
			}
		}    else if(head1>tail1){
				
				for(int i = 0;i <= tail1;i++){
					
					//array[i] = A[i];
					A[i] = array[i];
					
				}
				//for (int k = 0; k < 2*arraySize; ++k)
					//std::cout << A[k] << std::endl;
				for(int j = 0;j <= arraySize  -1 - head1 ;j++){
					A[2*arraySize - (arraySize - head1) + j] = array[head1 + j];
					//array[arraySize-j] = A[2*arraySize-1];
					//A[2*arraySize-1] = array[arraySize - 1 -j];
					
					
				}
				head1 = arraySize - head1 +2;
			
			} 
			     //delete[] array;
	             arraySize = (2*arraySize);
				 delete[] array;
	             //int* temp = array;
	             //array = new int [arraySize];
	             array = A;
				 head1 = ((head1-1) + arraySize) % arraySize ;
				 array[head1] = obj;
	
            	//delete[] temp;
				++count;
		}
		
		else{
	    head1 = ((head1-1) + arraySize) % arraySize ;
		array[head1] = obj;
		count++;
	}
return;	
	
	
	}


void Dynamic_deque_as_array::enqueue_tail( const int &obj ) {// if array is full then copy all the elements in an temp array A.
                                                            //then delete the previous array and make new array with same name to point to temp array A.
		                                                   // then enqueue the new element from tail and increment counter by 1.
	
	if(empty()){
		head1 = 0;
		tail1 = 0;
		array[tail1]=obj;
		count = count + 1;
		return;
	}
	
		if(count == arraySize){
		
		//int* A = new int [2*arraySize];
		 int* A = new int [2*arraySize];
		
		if(head1<=tail1){
			
			for (int i = head1;i<=tail1;i++){ // tail+1
				
				//array[i] = A[i];
				A[i] = array[i];
				
			}
		}    else if(head1>tail1){
				
				for(int i = 0;i <= tail1;i++){
					
					//array[i] = A[i];
					A[i] = array[i];
					
				}
				//for (int k = 0; k < 2*arraySize; ++k)
					//std::cout << A[k] << std::endl;
				for(int j = 0;j <= arraySize  -1 - head1 ;j++){
					A[2*arraySize - (arraySize - head1) + j] = array[head1 + j];
					//array[arraySize-j] = A[2*arraySize-1];
					//A[2*arraySize-1] = array[arraySize - 1 -j];
					
					
				}
				head1 = arraySize - head1 +2;
			
			} 
			     //delete[] array;
	             arraySize = (2*arraySize);
				 delete[] array;
	             //int* temp = array;
	             //array = new int [arraySize];
	             array = A;
				tail1 = ((tail1+1) + arraySize) % arraySize ;
				 array[tail1] = obj;
	
            	//delete[] temp;
				++count;
		}
		
		else{
	    tail1 = ((tail1+1) + arraySize) % arraySize ;
		array[tail1] = obj;
		count++;
	}
return;	
}


int Dynamic_deque_as_array::dequeue_head() { 
	
	if(empty()){                             // if array is empty throw exception.
		
		throw underflow();
	}
	int str = array[head1];                 // otherwise store the head strore str variable.
	
	 if (count == 1){                       // if count is 1 then dequeue the head and make the counter 0.
		head1 = 0;
		tail1 = 0;
		count = 0;
		//return str;
		
	}
	
	else{                                     // otherwise remove the head and decrement the counter by 1.
		//str = array[head1];
		head1 = ((head1+1)+ arraySize)%arraySize;
		count--;
		//return str;
	}
	return str;
	
		//return str;
	}
	

int Dynamic_deque_as_array::dequeue_tail() {			

	if(empty()){                               // if array is empty throw exception.
		
		throw underflow();
	}
	 int str = array[tail1];                  // otherwise store the head strore str variable.
	
	if (count == 1){                         // if count is 1 then dequeue the head and make the counter 0.
		head1 = 0;
		tail1 = 0;
		count = 0;
		//return str;
	}
	
	else{                                   // otherwise remove the head and decrement the counter by 1.
		//str = array[tail1];
		tail1= ((tail1-1)+ arraySize)%arraySize;
		count--;
	}
	
	return str;	

}

void Dynamic_deque_as_array::clear() { // clear all the element from the deque and set the counter to 0.
	count=0;
	head1 = 0;
	tail1 = 0;
	return;
}

#endif