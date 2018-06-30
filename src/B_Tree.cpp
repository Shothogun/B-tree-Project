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
	this->counter = 0;
	const int empty = 0;

	// Which register position 	in the data file
	int data_placing = 0;

	// Vector of data's NRR in data file
	std::string NRR;
	std::vector<std::string> NRR_vector;

	// Original Data base file(lista.txt)
	ifstream main_file;

	// Index_file
	ofstream index_file;


	// Output file name
	std::string name_out = "indicelista";
	std::string extension = ".bt";

	name_out += extension;

	// Node's out in index file
	file_input line_inf;
	line_inf.file_line_number = 1;

	// Main's file line
	std::string line;

	// Primary key value
	std::string primary_key_input;

	index_file.open(name_out, ios::out | ios::trunc);
	main_file.open(name_in, ios::in);

	index_file << "1\n";

	while(getline(main_file,line))
	{
		// Reinitialization of string "node" if node is full
		if(this->primary_key_vector.size() == empty)
		{
			line_inf.node.erase(line_inf.node.begin(), line_inf.node.end());
		}

		// Reinitialization of string "NRR"
		NRR.erase(NRR.begin(), NRR.end());

		// Inserts primary key value to line
		primary_key_input = primary_key_creator(line,primary_key_input);

		if(data_placing < 10)
		{
			NRR += "0";
		}

		NRR += to_string(data_placing+1);

		insert_data_non_full(primary_key_input, NRR, &line_inf);

		data_placing++;

		if(data_placing == 5)
		{
			break;
		}

	}

	cout << line_inf.node << endl;

	main_file.close();
	index_file.close();

	return 0;
}

void node_B_Tree::insert_data_non_full(std::string k, 
																			 std::string NRR_input,
																			 file_input* line_inf)
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
	  it = this->primary_key_vector.begin();

	  // Inserts the data in the node
		this->primary_key_vector.insert(it,new_data);

		// Sorting of the node by the primary key value
		std::stable_sort (this->primary_key_vector.begin(), this->primary_key_vector.end(), compare_primary_key);

		if(primary_key_vector.size() == Node_size)
		{
			for(int i = 0; i < Node_size; i++)
			{
				line_inf->node += this->primary_key_vector[i].primary_key_value;
				line_inf->node += "|";
			}

			for(int i = 0; i < Node_size; i++)
			{
				line_inf->node += this->primary_key_vector[i].NRR;
				line_inf->node += "|";
			}

			for(int i = 0; i < Node_size + 1; i++)
			{
				line_inf->node += "-1";
				line_inf->node += "|";
			}
		}
	}

	else
	{

	}

	index_file.close();
}

void node_B_Tree::insert_data(std::string primary_key_input,
														  std::string NRR_input,
														  file_input* line_inf)
{

	// If it's fulled, splitting and promotion are called in the overflow node 
	if(this->primary_key_vector.size() == Node_size)
	{
		

	}

	// Inserts keys if the node is not fulled
	else
	{
		insert_data_non_full(primary_key_input, NRR_input, line_inf);
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
