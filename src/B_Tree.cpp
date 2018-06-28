#include "B_Tree.hpp"
#include <iostream>						
#include <cstring>
#include <fstream>
#include <algorithm>

#define Node_size 5

bool compare_primary_key(const primary_key &a, const primary_key &b)
{
  int value = a.primary_key_value.compare(b.primary_key_value);

  if(value < 0)
  {
  	return true;
  }

  else
  {
  	return false;
  }
}

int node_B_Tree::index_file_creator(std::string name_in)
{
	// Original Data base file(lista.txt)
	ifstream main_file;

	// Index_file
	ofstream index_file;

	int file_line_number = 0;

	// Output file name
	std::string name_out = "indicelista";
	std::string extension = ".bt";

	// Node's out in index file
	std::string node;

	// Main's file line
	std::string line;

	// Primary key value
	std::string primary_key_input;

	name_out += extension;

	index_file.open(name_out, ios::out | ios::trunc);
	main_file.open(name_in, ios::in);

	index_file << "1\n";

	while(getline(main_file,line))
	{
		std::string node;
		file_line_number++;

		primary_key_input = primary_key_creator(line,primary_key_input);

		node += to_string(file_line_number);
		if(file_line_number < 10)
		{
			node += " ";
		}
		node += "|";
		node += primary_key_input;
		node += "|";



		cout << node << endl;


	}

	main_file.close();
	index_file.close();

	return 0;
}

void node_B_Tree::insert_data_non_full(std::string k, std::string NRR_input)
{

	// Open file
	ofstream index_file;

	std::string name = "indicelista";
	std::string extension = ".bt";
	std::string output;

	name += extension;

	index_file.open(name, ios::out | ios::app);

	if(/*primary_key_vector.leaf == */true)
	{
		// Input in the vector as struct 
		primary_key new_data;

		new_data.primary_key_value = k;
		new_data.NRR = NRR_input;

		std::vector<primary_key>::iterator it;
	  it = primary_key_vector.begin();

	  // Inserts the data in the node
		primary_key_vector.insert(it,new_data);

		// Sorting of the node by the primary key value
		std::stable_sort (primary_key_vector.begin(), primary_key_vector.end(), compare_primary_key);


	}

	else
	{

	}

	index_file.close();
}

void node_B_Tree::insert_data(std::string primary_key_input, std::string NRR_input)
{

	// Inserts keys if the node is not fulled
	if(primary_key_vector.size() < Node_size)
	{
		
		// Input in the vector as struct 
		primary_key new_data;

		new_data.primary_key_value = primary_key_input;
		new_data.NRR = NRR_input;

		std::vector<primary_key>::iterator it;
	  it = primary_key_vector.begin();

	  // Inserts the data in the node
		primary_key_vector.insert(it,new_data);

		// Sorting of the node by the primary key value
		std::stable_sort (primary_key_vector.begin(), primary_key_vector.end(), compare_primary_key);
	
		return;
	}

	// If it's fulled, splitting and promotion are called in the overflow node 
	else
	{
		
	}

}


void node_B_Tree::split_child()
{

}


void node_B_Tree::delete_data()
{
	return;
}

void node_B_Tree::search_data()
{
	return;
}


string primary_key_creator(std::string line, std::string line_ws)
{

	// Express the character position at the line from main file(lista.txt)
	int position;	

	line_ws.clear();
		
	for (position = 0; position < 46; position++)
	{
		if(position < 3)
		{
			line_ws += toupper(line[position]);
		}

		if(position > 40 && position < 46)
		{
			line_ws += line[position];
		}
	}

	return line_ws;
}
