#include<iostream>
#include<list>
#include<stack>
#include<vector>
#include<queue>
#include<cassert>
#include "Graph.h"

using namespace std;

int min(int x, int y)
{
	return x < y ? x : y;
}

Graph::Graph(int V) :m_V{ V }, m_E{0}
{
	assert(m_V >= 0);
	m_adj = new list<int>[V];
}

Graph::Graph(int V, bool** matrix):m_V{V},m_E{0}
{
	assert(m_V >= 0);
	m_adj = new list<int>[V];
	for (int i = 0; i < V; ++i)
	{
		for (int j = i + 1; j < V; ++j)
		{
			if (matrix[i][j] == 1)
				addEdge(i, j);
		}
	}
}
Graph::Graph(int V, list<int>* zz):m_V{V},m_E{0} //constructor for adj list
{
	assert(m_V >= 0);
	m_adj = new list<int>[m_V];
	for(int i=0;i<m_V;++i)
		for (auto j = zz[i].begin(); j != zz[i].end(); ++j)
		{
				addEdge(*j, i);
		}
}

Graph::Graph(const Graph& ob) :m_V{ ob.m_V }, m_E{ ob.m_E }//copy constructor
{
	//cout << "copy constructor " << endl;
	m_adj = new list<int>[m_V];
	for (int i = 0; i < m_V; ++i)
		for (auto j = ob.m_adj[i].begin(); j != ob.m_adj[i].end(); ++j)
			m_adj[i].push_back(*j);
}

void Graph::matrix_repr() 
{ //print graph matrix representation
	assert(m_V >= 0);
	if (m_V == 0) { return;}
	
	bool** arr = new bool* [m_V];
	for (int i = 0; i < m_V; ++i)
		arr[i] = new bool[m_V];

	for (int i = 0; i < m_V; ++i)
	{
		arr[i][i] = 0;
		for (int j = i + 1; j < m_V; ++j)
		{
			if (findedge(i, j))
			{
				arr[i][j] = 1;
				arr[j][i] = 1;
			}
			else {
				arr[i][j] = 0;
				arr[j][i] = 0;
			}
		}
	}
	for (int i = 0; i < m_V; ++i)
	{
		for (int j = 0; j < m_V; ++j)
		{
			cout << arr[i][j] << ' ';
		}
		cout << endl;
	}

	for (int i = 0; i < m_V; ++i)
	{
		delete[]arr[i];
		arr[i] = 0;
	}
	delete[]arr;
	arr = 0;
}

void Graph::adj_list_print() 
{//print adj list representation
	assert(m_V >= 0);
	for (int i = 0; i < m_V; ++i)
	{
		cout << i << ' ';
		for (auto j = m_adj[i].begin(); j != m_adj[i].end(); ++j)
		{
			cout << *j << ' ';
		}
		cout << endl;
	}
}

Graph& Graph::operator=(const Graph& ob) 
{//copy assignmnent operator
	if (this != &ob)
	{
		if (m_V != ob.m_V)
		{
			delete[]m_adj;
			m_adj = nullptr;
			m_adj = new list<int>[ob.m_V];
			m_V = ob.m_V; m_E = ob.m_E;
			for (int i = 0; i < m_V; ++i)
				for (auto j = ob.m_adj[i].begin(); j != ob.m_adj[i].end(); ++j)
					addEdge(i, *j);
		}
		else {
			m_E = ob.m_E;
			for (int i = 0; i < m_V; ++i)
			{
				if (m_adj[i].size() > 0)
				{
					m_adj[i].clear();
				}
				for (auto j = ob.m_adj[i].begin(); j != ob.m_adj[i].end(); ++j)
					addEdge(i,*j);
			}
		}
	}
	return *this;
}


Graph::Graph(Graph&& ob)noexcept :m_V{ ob.m_V }, m_E{ ob.m_E } //noexcept
{	
	//cout << "move constructor " << endl;
	m_adj = new list<int>[m_V];
	for (int i = 0; i < m_V; ++i)
		for (auto j = ob.m_adj[i].begin(); j != ob.m_adj[i].end(); ++j)
			addEdge(i, *j);
	delete[]ob.m_adj;
	ob.m_adj = nullptr;
}

Graph& Graph::operator=(Graph&& ob) noexcept//move assignment
{
	//cout << "move assignment " << endl;
	if (this != &ob)
	{
		if (m_V != ob.m_V)
		{
			delete[]m_adj;
			m_adj = nullptr;
			m_adj = new list<int>[ob.m_V];
			m_V = ob.m_V; m_E = ob.m_E;
			for (int i = 0; i < m_V; ++i)
				for (auto j = ob.m_adj[i].begin(); j != ob.m_adj[i].end(); ++j)
					addEdge(i, *j);
		}
		else {
			m_E = ob.m_E;
			for (int i = 0; i < m_V; ++i)
			{
				if (m_adj[i].size() > 0)
				{
					m_adj[i].clear();
				}
				for (auto j = ob.m_adj[i].begin(); j != ob.m_adj[i].end(); ++j)
					addEdge(i, *j);
			}
		}
	}
	delete[]ob.m_adj;
	ob.m_adj = nullptr;
	return *this;
}

void Graph::addEdge(int v, int w)
{
	assert(v < m_V && w < m_V);
	m_adj[v].push_back(w);
	m_adj[w].push_back(v);
	++m_E;
}

bool Graph::findedge(int v, int w)
{
	if (v >= m_V)
	{
		cout << "out of range";
		return false;
	}
	if (m_adj[v].empty())
		return false;
	for (auto x = m_adj[v].begin(); x != m_adj[v].end(); ++x)
	{
		if (*x == w)
		{
			return true;
		}
	}
	return false;
}

void Graph::BlockwithArt(int u, int disc[], int low[], stack<int>& st,
	int parent[], bool art_p[], vector<vector<int>>& block)
{ 
	static int time = 0;
	// Initialize discovery time and low value 
	disc[u] = low[u] = ++time;
	int children = 0;

	// Go through all vertices adjacent to this 
	list<int>::iterator i;
	for (i = m_adj[u].begin(); i != m_adj[u].end(); ++i) {
		int v = *i; // v is current adjacent of 'u' 

		// If v is not visited yet, then recur for it 
		if (disc[v] == -1) {
			++children;
			parent[v] = u;
			// store the vertexes in stack 
			st.push(u);
			st.push(v);

			BlockwithArt(v, disc, low, st, parent, art_p, block);

			// Check if the subtree rooted with 'v' has a 
			// connection to one of the ancestors of 'u' 
			// Case 1 -- per Strongly Connected Components Article 
			low[u] = min(low[u], low[v]);

			// If u is an articulation point, 
			// pop all edges from stack till u -- v 

			if ((parent[u] == -1 && children > 1) || (parent[u] != -1 && low[v] >= disc[u])) {
				art_p[u] = true;
				//for 2D vector static
				static int freesp = 0;
				vector<int> block1;
				//cout <<" "<< u << "  " << endl;
				while (st.top() != u) {
					cout << st.top()<<' ';
					if (art_p[st.top()] && !count(block1.begin(), block1.end(), st.top()))//'count' if vector haven't the element
					{
						block1.push_back(st.top());
					}
					st.pop();
				}
				if (art_p[st.top()] && !count(block1.begin(), block1.end(), st.top()))//if articulation point,karelia count noric stugel apahovutyan hamar
				{
					cout << st.top() << ' '; //"-s member:-";
					block1.push_back(st.top());
				}
				cout << endl;
				block[freesp] = vector<int>(block1.size());
				
				for (size_t j = 0; j < block1.size(); ++j)
					block[freesp][j] = block1[j];
				st.pop();//verjin miakcman keti hamar
				++freesp;
			}
		}
		// Update low value of 'u' only of 'v' is still in stack 
		// (i.e. it's a back edge, not cross edge). 
		// Case 2 -- per Strongly Connected Components Article 
		else if (v != parent[u]) {
			low[u] = min(low[u], disc[v]);
			if (disc[v] < disc[u]) {
				st.push(u);
			}
		}
	}
}

Graph Graph::BCC()
{
	vector<vector<int>> block(m_V);
	bool* art_p = new bool[m_V];
	int* disc = new int[m_V];
	int* low = new int[m_V];
	int* parent = new int[m_V];
	stack<int> st; 
	// Initialize disc and low, and parent arrays 
	for (int i = 0; i < m_V; ++i) {
		art_p[i] = false;
		disc[i] = -1;
		low[i] = -1;
		parent[i] = -1;
	}
	for (int i = 0; i < m_V; ++i) {
		if (disc[i] == (-1))
			BlockwithArt(i, disc, low, st, parent, art_p, block);

		vector<int> cur;
		//cout << "stack size :" << st.size();
		if (st.size() > 0)
		{
			while (st.size() > 0) {
				cout << st.top() << ' ';
				if (art_p[st.top()] && !count(cur.begin(), cur.end(), st.top()))
				{
					cur.push_back(st.top());		
				}
				st.pop();
			}
			cout << endl;
			if (cur.size() != 0)
			{//find free memory in vector<vector<>> to allocate memory for block,zz index to that memory
				int j = 0;
				for (; j < m_V; ++j)
				{
					if (block[j].empty())
					{
						block[j] = vector<int>(cur.size());
						break;
					}
				}
				//write articulation points block in vector<vector<>>
				for (size_t i = 0; i < cur.size(); ++i)
				{
					block[j][i] = cur[i];
				}
			}
		}
	}
	int g = 0;
	vector<int> art_n;
	cout << "articulation points are "<<endl;
	for (int i = 0; i < m_V; ++i)
	{
		if (art_p[i])
		{
			art_n.push_back(i);
			++g;
			cout << i <<"-s number in new graph is- "<<(art_n.size()-1)<< endl;
		}
	}
	cout << endl;
	if (g == 0)
	{
		cout << "The graph doesn't have an articulaion point" << endl;
		Graph ob(0);
		return ob;
	}
	Graph ob1(g);
	//cout << "New block -";
	for (int i = 0; i < m_V; ++i)
	{
		if (block[i].empty())
			continue;
		if (block[i].size() > 1)
		{
			for (size_t j = 0; j < block[i].size(); ++j)
			{
				for (size_t fk = 0; fk < art_n.size(); ++fk)
				{
					if (art_n[fk] == block[i][j])
					{
						block[i][j] = fk;
						break;
					}
				}
			}
			for (size_t j = 0; j < block[i].size(); ++j)
			{
				for (size_t k =j+1; k < block[i].size(); ++k)
				{					
					ob1.m_adj[block[i][k]].push_back(block[i][j]);
				}
			}
		}
	}
	delete[]art_p;
	delete[]disc;
	delete[]low;
	delete[]parent;
	return ob1;
}

