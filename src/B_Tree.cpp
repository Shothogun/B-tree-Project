#include "B_Tree.hpp"
#include <iostream>
#include <fstream>					

using namespace std;

string primary_key_creator(string line, string line_ws)
{

	// Express the character position at the line from main file(lista.txt)
	int position;

	// Limits the number of Uppercasse in primary Key
	int Uppercase = 0;		

	line_ws.clear();
		
	for (position = 0; position < 46; position++)
	{
		if(line[position] <= 90 && line[position] >= 65 && Uppercase < 3)
		{
			line_ws += line[position];
			Uppercase++;
		}

		if(position > 40 && position < 46)
		{
			line_ws += line[position];
		}
	}

	return line_ws;
}

int empty_index_file_creator (string file_name)
{

	ofstream index_file;

	// Create new B-tree file
	index_file.open (file_name, ios::out | ios::trunc);

	if (index_file.is_open())
	{
		// Create header with the line of the root
		index_file << "#-01\n";
	}

	else 
	{
		cout << "Unable to open file";
		return -1;
	}

	index_file.close();
	return 0;
}

node_B_Tree get_node (string file_name, int line_number)
{	
	const int header_size = 5;
	const int line_size = ;

	string line;

	node_B_Tree node;

	ifstream index_file;

	index_file.open (file_name);

	if (index_file.is_open())
	{
		// Get line in the position wanted
		index_file.seekg(header_size + (line_number - 1) * line_size, index_file.beg);
		getline(index_file, line);
		line2vectors(line, );
	}

	else 
		cout << "Unable to open file";

	return node;
}

int line2vectors (string line, vector, vector)
{
	
}