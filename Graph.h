#pragma once

class Graph {
public:
	Graph(int V);// Constructor
	Graph(int V, bool** matrix);//Constructor matrix
	Graph(int V, std::list<int>* zz);//adjlist constructor
	int count_edge() { return m_E; }
	bool empty() { if (m_V == 0) return true; return false; }
	int count_vertex() { return m_V; }
	bool findedge(int v, int w);
	void matrix_repr();//prints graph with matrix representation
	void adj_list_print();
	void addEdge(int v, int w);// function to add an edge to graph 
	Graph& operator=(const Graph& ob);//copy assignment
	Graph(const Graph& ob);//copy constructor
	Graph(Graph&& ob) noexcept;//move constructor
	Graph& operator=(Graph&& ob)noexcept;//move assignment
	Graph BCC(); // prints strongly connected components 
	~Graph() { delete[]m_adj; }
private:
	int m_V; //vertex
	int m_E; //edge
	std::list<int>* m_adj; // A dynamic array of adjacency lists 
	// A Recursive DFS based function() 
	void BlockwithArt(int , int[] , int[] ,
		std::stack<int>& , int [], bool[], std::vector<std::vector<int>>& );
};

