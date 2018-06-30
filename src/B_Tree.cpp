#include "B_Tree.hpp"
#include <iostream>						
#include <cstring>
#include <fstream>
#include <algorithm>

#define Node_size 5


// Every pattern and standards variables names 
// are based in Cormen's aproach

int node_B_Tree::index_file_creator(std::string name_in)
{
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

	index_file << "R1\n";

	index_file.close();

	while(getline(main_file,line))
	{
		// Reinitialization of string "node" if node is full
		line_inf.node.erase(line_inf.node.begin(), line_inf.node.end());
		
		// Reinitialization of string "NRR"
		NRR.erase(NRR.begin(), NRR.end());

		// Inserts primary key value to line
		primary_key_input = primary_key_creator(line,primary_key_input);

		if(data_placing < 10)
		{
			NRR += "0";
		}

		NRR += to_string(data_placing+1);

		insert_data(primary_key_input, NRR, &line_inf);

		data_placing++;

		line_inf.node_before = line_inf.node;

		if(data_placing == 10)
		{
			break;
		}

	}

	cout << line_inf.node << endl;
	main_file.close();


	return 0;
}

void node_B_Tree::insert_data(std::string primary_key_input,
														  std::string NRR_input,
														  file_input* line_inf)
{

	// If it's fulled, splitting and promotion are called in the overflow node 
	if(this->primary_key_vector.size() == Node_size)
	{
		// Adds up number of nodes on the B_Tree
		line_inf->file_line_number++;

		// Data file name
  	std::string name = "indicelista";
  	std::string extension = ".bt";	
  	name += extension;

		// Original index file
  	ifstream index_file_in(name);

  	// Gets the root indicator
		std::string line;
  	getline(index_file_in, line);

 	  index_file_in.close();

		// Update root indicator
		std::string new_root = "R";
		new_root += to_string(line_inf->file_line_number);
		write_data(line,new_root);

 	  // Creates a new node
		std::vector<primary_key> s;
		split_child(1, s);
	}

	// Inserts keys if the node is not fulled
	else
	{
		insert_data_non_full(primary_key_input, NRR_input, line_inf);
	}

}

void node_B_Tree::insert_data_non_full(std::string k, 
																			 std::string NRR_input,
																			 file_input* line_inf)
{

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

		int vector_size = this->primary_key_vector.size();

		line_inf = register_constructor(vector_size, line_inf);

		write_data(line_inf->node_before,line_inf->node);
	}

	else
	{

	}
}

void node_B_Tree::write_data(std::string replace, std::string new_data)
{

	// Data file name
  std::string name = "indicelista";
  std::string extension = ".bt";
  name += extension;

	// Verifies if the file is empty
	int verifier = 0;

  // Lines copyied to a auxiliary file
  std::string copy_string;

  // Original index file
  ifstream index_file_in(name);

  // Copy of index file
  fstream index_file_copy("copy.txt", std::fstream::in | std::fstream::out | std::fstream::trunc);

  // Copying process
  while(index_file_in >> copy_string)
  {
    index_file_copy << copy_string + "\n";
  }

  index_file_in.close();

	std::string strTemp;

  // Sets position of character from auxiliary file to begin
  index_file_copy.seekp(0,ios_base::beg);

	// Original index file that will be modified	
	ofstream index_file_out;

	index_file_out.open(name);

	// Line that will be replaced
	std::string strReplace = replace;

	// New line replaced
	std::string strNew = new_data;

	// Seeks the matching line and replaces
	while(getline(index_file_copy,strTemp))
	{
	  if(strTemp == strReplace)
	  {
	    strTemp = strNew;
	  }
	  strTemp += "\n";
	  index_file_out << strTemp;

	  verifier++;
	}

	// If there's only one line(verifier = 1), just writes the node
	if(verifier == 1)
	{
		index_file_out << new_data;
	}

	index_file_copy.close();
  index_file_out.close();
}	

file_input* node_B_Tree::register_constructor(int vector_size, file_input* line_inf)
{
	// Writes node counter(amount of keys in node)
	if(vector_size < 10)
	{
		line_inf->node += "0";
	}

	line_inf->node += to_string(vector_size) + "|";

	// Write node's keys
	for(int i = 0; i < vector_size; i++)
	{
		line_inf->node += this->primary_key_vector[i].primary_key_value;
		line_inf->node += "|";
	}

	// Fill the renmant space of key 
	if(vector_size < Node_size)
	{
		for(int i = 0; i < Node_size - vector_size; i++)
		{
			line_inf->node += "--------";
			line_inf->node += "|";
		}
	}

	// Write key's NRR
	for(int i = 0; i < vector_size; i++)
	{
		line_inf->node += this->primary_key_vector[i].NRR;
		line_inf->node += "|";
	}

	// Fill the renmant space of NRR
	if(vector_size < Node_size)
	{
		for(int i = 0; i < Node_size - vector_size; i++)
		{
			line_inf->node += "-1";
			line_inf->node += "|";
		}
	}

	// Write node's child
	for(int i = 0; i < this->child.size(); i++)
	{
		if(this->child[i] < 10)
		{
			line_inf->node += "0";
		}
		
		line_inf->node += to_string(this->child[i]);
		line_inf->node += "|";
	}

	// Fill the renmant space of childs
	if(this->child.size() < Node_size)
	{	
		for(int i = 0; i < Node_size + 1; i++)
		{
			line_inf->node += "--";
			line_inf->node += "|";
		}
	}

	return line_inf;
}



void node_B_Tree::split_child(int i, std::vector<primary_key> s)
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

bool node_B_Tree::leaf_verify()
{
	return true;
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
