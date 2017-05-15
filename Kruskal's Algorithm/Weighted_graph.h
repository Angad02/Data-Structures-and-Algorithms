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

#ifndef WEIGHTED_GRAPH_H
#define WEIGHTED_GRAPH_H

#ifndef nullptr
#define nullptr 0
#endif

#include <iostream>
#include <limits>
#include "Exception.h"
#include "Disjoint_sets.h"

using namespace std;

class Weighted_graph {
	private:
		static const double INF;
		double** graph;
		int num_nodes;
		int num_edges;
		int *graph_degree;          // Matrix to store the degree for the each Node

		// Do not implement these functions!
		// By making these private and not implementing them, any attempt
		// to make copies or assignments will result in errors
		Weighted_graph( Weighted_graph const & );
		Weighted_graph &operator=( Weighted_graph );

		// your choice

	public:
		Weighted_graph( int = 50 ); // do we have to change this to 50 as it says in proj description??
		~Weighted_graph();

		int degree( int ) const;
		int edge_count() const;
		std::pair<double, int> minimum_spanning_tree () const;
        
		bool insert_edge( int, int, double );
		bool erase_edge( int, int );
		void clear_edges();
		pair<int,int> findmin(double**) const;

	// Friends

	friend std::ostream &operator<<( std::ostream &, Weighted_graph const & );
};

const double Weighted_graph::INF = std::numeric_limits<double>::infinity(); // what does this line means 

Weighted_graph::Weighted_graph(int n ) {
	
	if(n<0){
		throw illegal_argument();
	}
	else{
		graph = new double*[n];          // creates a row for graph matrix
    for(int i = 0; i < n; i++) {
        graph[i] = new double[n];    // create a column for graph matrix
    }
    graph_degree=new int[n];
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            graph[i][j] = INF;       // set  each node to Infinity.
        }
		 graph_degree[i] = 0;                // Degree of each node to 0.
    }
    num_edges=0;
    num_nodes=n;
	}
}

Weighted_graph::~Weighted_graph() {
	
	for(int i = 0; i < num_nodes; i++)
    {
        delete [] graph[i];
    }
    delete [] graph;
    delete [] graph_degree;
    num_nodes=0;

}

int Weighted_graph::degree(int u) const {
	if (u<0||u>=num_nodes) {
        throw illegal_argument();
    }
        return graph_degree[u];
	/*	
	else{	
		int count = 0;
		for(int i =0;i<num_nodes;i++){
			if(graph[u][i]!=INF){
				
				count = count+1;
			}
			return count;
		}
	}
	*/


}

int Weighted_graph::edge_count() const {
	return num_edges;
}

bool Weighted_graph::erase_edge(int i, int j) {
	
	if ((i >= num_nodes || j >= num_nodes)||i<0 || j<0) { // out of bound
        throw illegal_argument();
    }
        if(i==j){ // if i=j
	        
			return true;
    }
	if ( graph[i][j]!=INF && graph[j][i]!=INF) { // condition for edge to exist
		//cout<<"pu"<<endl;
            graph[i][j]=INF;
            graph[j][i]=INF;
			graph_degree[i]--;
            graph_degree[j]--;
            num_edges--;
			return true;
        }
		
	else 
		if ( graph[i][j]==INF && graph[j][i]==INF){ // condition for edge not existing
			return false;
		}
	/*	
	else
        if(i==j){ // if i=j
	        
			return true;
    }
	*/
}

void Weighted_graph::clear_edges() {
	//int n = 50;
	for(int i = 0; i < num_nodes; i++) {
        for(int j = 0; j < num_nodes; j++) {
            graph[i][j] = INF;       // set  each node to Infinity.
        }
		 graph_degree[i] = 0;                // Degree of each node to 0.
    }
    num_edges=0;
    //num_nodes=n;


}

bool Weighted_graph::insert_edge( int i, int j, double d ) {
	if(i==j){
		return false;
	}
	if ((i >= num_nodes || j >= num_nodes)|| d<=0  ||i<0 || j<0) {
        throw illegal_argument();
    }
    else{
        if (graph[i][j]==INF && d!=0) { // if no edge exist then add a new edge
                                              
            graph_degree[i]++;
            graph_degree[j]++;
            num_edges++;
        }
        graph[i][j]=d;
        graph[j][i]=d;
		//cout<<"av"<<endl;
		return true;

    }
    if (d!=0) {               // if edge already exist then update it
        graph[i][j]=d;
        graph[j][i]=d;
		return true;
    }
}


pair<int,int> Weighted_graph::findmin(double ** graph_copy)const {
	
	double min = INF;
	int u,v;
	for (int i = 0; i < num_nodes; i++) {
		for (int j = 0; j < num_nodes; j++) {
			//cout<<i<<j <<endl;
			if (graph_copy[i][j] < min) {
				min = graph_copy[i][j];
				//cout<<"here4" <<endl;
				u = i;
				v = j;
			}
			
		}
	}
	graph_copy[u][v] = INF;
	graph_copy[v][u] = INF;	
	//cout<<"here4"<<endl;
	return pair<int, int> (u, v);
}	


std::pair<double, int> Weighted_graph::minimum_spanning_tree() const{
	             
  //cout << "here1"<<endl;
   int edgestested =0;
   std::pair<int,int> nodes;
   double totalweight =0.0;
	int edgesincluded =0;
	
	//cout<<"1"<<endl;
	double ** graph_copy = new double*[num_nodes];
	for (int i = 0; i < num_nodes; i++) {
		graph_copy[i] = new double[num_nodes];
		for (int j = 0; j < num_nodes; j++) {
			graph_copy[i][j] = graph[i][j];
		}		
	}
	
	Disjoint_set *sets = new Disjoint_set(num_nodes);
    for(int i =0;i<num_edges;i++){
		nodes = findmin(graph_copy);
		//cout<<"here3" <<endl;
		//cout<<edgestested<< " min = " << nodes.first << " " << nodes.second << endl; obj
		edgestested++;		
		if(sets->find_set(nodes.first) != sets->find_set(nodes.second)){
			sets->union_sets(nodes.first,nodes.second);
			int m = nodes.first;
			int n = nodes.second;
			double val = graph[m][n];
			totalweight = totalweight+val;
			edgesincluded++;
			
			if(edgesincluded == num_nodes - 1){	
				break;
			}
		}
	}	
	for (int i = 0; i < num_nodes; i++) {
		delete[] graph_copy[i];
	}
	delete[] graph_copy;
	delete sets;
	return std::pair<double, int>( totalweight, edgestested);
}

std::ostream &operator<<( std::ostream &out, Weighted_graph const &graph ) {
	

	return out;
}


#endif