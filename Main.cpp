#include <cassert>
#include <iostream>
#include <fstream>
#include <list> 
#include <sstream>
#include <stack> 
#include <vector>
#include "Creatgraph.h"
#include "Graph.h"

using namespace std;

int main()
{
	unsigned i;
	cout << "If you want a matrix representation press 1: " << '\n' << "If adjecency list representation press 2: ";
	cout << '\n' << "If read from file with adjecency list representation,press 3: " << endl;
	cin >> i;
	switch (i)
	{
	case 2:
	{
		cout << "write vertex count- ";
		int z;
		cin >> z;
		if (z == 0)
		{
			cout << "Your graph is empty" << endl;
			return 0;
		}
		cout << "write adjecency vertex" << endl;
		list<int>* adj = creat_adjlist(z);
		Graph given_g(z, adj);
		delete_adjlist(adj);
		cout << "Blocks are" << endl;
		Graph art_p_g = given_g.BCC();
		cout << endl;
		cout << "adj list representation graph of articulation points " << endl;
		art_p_g.adj_list_print();
		cout << "if graph empty- " << boolalpha << art_p_g.empty() << endl;
		cout << "how much edges it have- " << art_p_g.count_edge() << endl;
		cout << "how much vertexes it have- " << art_p_g.count_vertex() << endl;
		break;
	}
	case 1:
	{
		cout << "write a 2D matrix size -";
		int z;
		cin >> z;
		if (z == 0)
		{
			cout << "Your graph is empty" << endl;
			return 0;
		}
		cout << "write a matrix" << endl;
		bool** f = creat_matrix(z);
		Graph given_g(z, f);
		delete_matrix(f, z);
		cout << "Blocks are" << endl;
		Graph art_p_g = given_g.BCC();
		cout << "matrix representation graph of articulation points " << endl;
		art_p_g.matrix_repr();
		cout << "graph empty- " << boolalpha << art_p_g.empty() << endl;
		cout << "how much edges it have- " << art_p_g.count_edge() << endl;
		cout << "how much vertexes it have- " << art_p_g.count_vertex() << endl;
		break;
	}
	case 3:
	{
		cout << "In file's first line write vertex count " << '\n';
		cout << "Started with second line write adjecency list representation of the graph" << '\n';
		cout << "If your file is ready,please press 1 and then enter- ";
		cin >> i;
		if (i == 1)
		{
			int V;
			//cin >> z;
			//cout << "write adjecency vertexes in " << endl;
			list<int>* adj = FileReadTolist(V);
			if (V == 0)
			{
				cout << "Your graph is empty" << endl;
				return 0;
			}
			Graph given_g(V, adj);
			delete_adjlist(adj);
			cout << "Blocks are" << endl;
			Graph art_p_g = given_g.BCC();
			cout << endl;
			cout << "adj list representation graph of articulation points " << endl;
			art_p_g.adj_list_print();
			cout << "if graph empty- " << boolalpha << art_p_g.empty() << endl;
			cout << "how much edges it have- " << art_p_g.count_edge() << endl;
			cout << "how much vertexes it have- " << art_p_g.count_vertex() << endl;
		}
			break;
		}
	}
	system("pause");//this is for visual studio 2017
	return 0;
}