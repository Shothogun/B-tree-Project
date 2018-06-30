#include "IO.hpp"
#include <fstream>
#include <iostream>

int show_index_file (string index_file)
{
	ifstream B_Tree;
	string line;

	B_Tree.open(index_file);

	if (B_Tree.is_open())
	{
		cout << "\n------ B_Tree : Index File ------\n\n";

		while (getline(B_Tree, line))
		{
			cout << line << "\n";
		}
	}
	else 
	{
		cout << "Unable to open file";
		return -1;
	}

	return 0;
}

using namespace std;