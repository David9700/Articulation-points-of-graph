#pragma once
using namespace std;

list<int>* creat_adjlist(int n)
{
	cout << "we have vertexis -";
	for (int i = 0; i < n; i++)
		cout << i << ' ';
	cout << endl;
	list<int>* zz_li = new list<int>[n];
	for (int i = 0; i < n; ++i)
	{
		int k;
		cout << i << "- ";
		for (int j = 0; j < n; j++)
		{
			cin >> k;
			if (k >= n || k < 0)
				break;
			zz_li[i].push_back(k);
			zz_li[k].push_back(i);

		}
	}
	return zz_li;
}

bool** creat_matrix(int n)
{
	//creat 2D matrix for graph representation
	//return **arr and do shallow copy
	cout << "we have vertexis -";
	for (int i = 0; i < n; i++)
		cout << i << ' ';
	cout << endl;
	bool** arr = new bool*[n];
	for (int i = 0; i < n; ++i)
		arr[i] = new bool[n];
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
		{
			int x;
			cin >> x;
			if (x > 0)
				arr[i][j] = 1;
			else arr[i][j] = 0;
		}
	cout << endl;

	return arr;
}
void delete_matrix(bool **matrix,int v)
{//delete given matrix
	for (int i = 0; i < v; ++i)
	{
		delete[]matrix[i];
		matrix[i] = 0;
	}
	delete[]matrix;
	matrix = 0;
}
void delete_adjlist(list<int>*adj)
{
	delete[]adj;
}

list<int>* FileReadTolist(int& V)
{//read in files and return adj list pointer
	list<int>* adj;
	fstream ob;
	string S, T;
	ob.open("Name.txt", ios::in);

	streampos begin, end;
	begin = ob.tellg();
	ob.seekg(0, ios::end);
	end = ob.tellg();
	int size = end - begin;
	ob.close();
	
	char* SS = new char[size];
	ob.open("Name.txt", ios::in);
	ob.read(SS, size);

	int k = 0;
	while (SS[k] != '\n')
	{
		T.push_back(SS[k]);
		k++;
	}

	istringstream(T) >> V;
	adj = new list<int>[V];
	while (SS[k] != '\0' && k < size)
	{
		string index;
		int first;
		while (SS[k] != '-' && SS[k] != '\0' && k < size)
		{
			index.push_back(SS[k]);
			k++;
			istringstream(index) >> first;
		}
		
		if (SS[k] != '\n' && SS[k] != '\0')
			k++;
		while (SS[k] != '\n' && SS[k] != '\0' && SS[k] != '-' && k < size)
		{
			string s;
			while (SS[k] != ' ' && SS[k] != '\0' && SS[k] != '\n' && SS[k] != '-' && k < size)
			{
				s.push_back(SS[k]);
				k++;
			}
			if (SS[k] != '\n' && SS[k] != '\0' && k < size)
				k++;
			int p;
			istringstream(s) >> p;
			adj[first].push_back(p);
		}
	}
	ob.close();

	return adj;
}