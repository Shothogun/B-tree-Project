#include "B_Tree.hpp"
#include <iostream>						
#include <cstring>
#include <fstream>
#include <algorithm>
#include <cstdlib>
#define Node_size 3

/*******************************

 Every pattern and standards variables names 
 are based in Cormen's aproach

********************************/

// ERRO no 25 aluno(raiz passa a ser o nó 9, que é inexistente)

int node_B_Tree::index_file_creator(std::string name_in)
{
	// Which register position 	in the data file
	int data_placing = 0;

	// Data's NRR in data file
	std::string NRR;

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

	index_file << "R01\n";

	index_file.close();

	while(getline(main_file,line))
	{
		// Initialization of nodes's positions

		// When its the 5 first keys
		if(data_placing < 5)
		{
			line_inf.parent_node_position = 1;
			line_inf.current_node_position = 1;
		}

		// Reinitialization of string "NRR"
		NRR.erase(NRR.begin(), NRR.end());

		// Inserts primary key value to line
		primary_key_input = primary_key_creator(line,primary_key_input);

		if(data_placing < 9)
		{
			NRR += "0";
		}

		NRR += to_string(data_placing+1);

		insert_data(primary_key_input, NRR, &line_inf);

		data_placing++;

		// Returns to root
		set_to_root(&line_inf);

		if(data_placing == 26)
		{
			break;
		}
	}

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
		line_inf->file_line_number++;

		// Update root indicator
		std::string new_root = "R";

		if(line_inf->file_line_number < 10)
		{
			new_root += "0";
		}

		new_root += to_string(line_inf->file_line_number+1);

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

		write_data(line,new_root);

 	  // Creates a new node

		std::vector<primary_key> x;
		std::vector<int> x_child;

		line_inf->current_node_position = line_inf->parent_node_position;
		line_inf->parent_node_position = line_inf->file_line_number + 1;
		
		split_child(&x, &x_child, 0, line_inf);

		set_to_root(line_inf);

		insert_data_non_full(NRR_input, primary_key_input, line_inf);

		line_inf->file_line_number++;

	}

	// Inserts keys if the node is not fulled
	else
	{
		insert_data_non_full(NRR_input, primary_key_input, line_inf);
	}

}

void node_B_Tree::insert_data_non_full(std::string NRR_input,
																			 std::string k, 
																			 file_input* line_inf)
{
	// Right location of insertion
	int i = this->primary_key_vector.size() - 1;

	if(this->leaf_verify() == true)
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


		line_inf = register_constructor(vector_size,
																	  this->primary_key_vector, 
																	  this->child,
																		line_inf);

		write_data(line_inf->node_before,line_inf->node);
	}

	else
	{
		// Seeks right location of insert
		while(i >= 0 && k.compare(this->primary_key_vector[i].primary_key_value) < 0)
		{
			i--;
		}

		i++;

		line_inf->parent_node_position = line_inf->current_node_position;
		line_inf->current_node_position = this->child[i];

		// Gets node parent information
		std::vector<primary_key> x;
		std::vector<int> x_child;

		for(int j = 0; j < this->primary_key_vector.size(); j++)
		{
			x.insert(x.begin(), this->primary_key_vector[j]);
		}

		std::stable_sort (x.begin(), x.end(), compare_primary_key);

		for(int j = 0; j < this->child.size(); j++)
		{
			x_child.insert(x_child.end(), this->child[j]);
		}


		line_inf->node_before = read_data(this->child[i]);

		if(this->primary_key_vector.size() == Node_size)
		{
			line_inf->file_line_number++;

			split_child(&x, &x_child ,i, line_inf);

			if(k.compare(x[i].primary_key_value) > 0 )
			{
				i++;
				line_inf->node_before = read_data(this->child[i]);
				line_inf->current_node_position = this->child[i];
			}
		}

		insert_data_non_full(NRR_input,k,line_inf);
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

	if(replace == "last")
	{
		while(getline(index_file_copy,strTemp))
		{
		  strTemp += "\n";
		  index_file_out << strTemp;
		}

		index_file_out << new_data;
		index_file_out << "\n";
	}


	else
	{
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
			index_file_out << new_data ;
			index_file_out << "\n";
		}

	}

	index_file_copy.close();
  index_file_out.close();

}	

std::string node_B_Tree::read_data(int node_number)
{
	// Data file name
  std::string name = "indicelista";
  std::string extension = ".bt";
  name += extension;

  // Original index file
  ifstream index_file_in(name);

  std::string line;

  // Go to the line where the child is 
	for(int i = 0; i <= node_number; i++)
	{
		getline(index_file_in,line);
	}

	index_file_in.close();

	// Counts how many keys are in the node
	char counter_string[100];

	line.copy(counter_string,2,0);

	int counter = atoi(counter_string);

	// Gets information in the node

	this->primary_key_vector.erase(this->primary_key_vector.begin(), this->primary_key_vector.end());
	this->child.erase(this->child.begin(), this->child.end());

	// Initial position of NRR in file
	int size1 = 3 + Node_size*9;

	for(int i = 0; i < counter ; i++)
	{
		char key[100];
		char NRR[100];


		// Input in the vector as struct 
		primary_key new_data;

		line.copy(key, 8, (3 + 9*i));
		line.copy(NRR, 2, (size1 + 3*i));


		new_data.primary_key_value.append(key, 8);
		new_data.NRR.append(NRR,2);

		std::vector<primary_key>::iterator it;
	  it = this->primary_key_vector.begin();

	  // Inserts the data in the node
		this->primary_key_vector.insert(it,new_data);
	}

	std::stable_sort (this->primary_key_vector.begin(), this->primary_key_vector.end(), compare_primary_key);

	// Initial position of children in file
	int size2 = size1 + Node_size*3;

	// Last child position in file
	int size3 = size2 + Node_size*3 + 1;
 
	char child[100];
	child[2] = '\0';	
	int i = 0;
	line.copy(child, 2, (size2 + i*3));


	while(strcmp(child, "--") != 0 && (size2 + i*3 < size3))
	{
		this->child.insert(this->child.end(), atoi(child));
		i++;	
		line.copy(child, 2, (size2 + i*3));
	}

	return line;
}

file_input* node_B_Tree::register_constructor(int vector_size, 
																							std::vector<primary_key> primary_key_input_vector, 
																							std::vector<int> child,
																							file_input* line_inf)
{
	// Reinitialization of string "node" if node is full
	line_inf->node.erase(line_inf->node.begin(), line_inf->node.end());

	// Writes node counter(amount of keys in node)
	if(vector_size < 10)
	{
		line_inf->node += "0";
	}

	line_inf->node += to_string(vector_size) + "|";

	// Write node's keys
	for(int i = 0; i < vector_size; i++)
	{
		line_inf->node += primary_key_input_vector[i].primary_key_value;
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
		line_inf->node += primary_key_input_vector[i].NRR;
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
	for(int i = 0; i < child.size(); i++)
	{
		if(child[i] < 10)
		{
			line_inf->node += "0";
		}
		
		line_inf->node += to_string(child[i]);
		line_inf->node += "|";
	}

	// Fill the renmant space of childs
	if(child.size() < Node_size + 1)
	{	
		for(int i = 0; i < Node_size - child.size() + 1; i++)
		{
			line_inf->node += "--";
			line_inf->node += "|";
		}
	}

	return line_inf;
}

void node_B_Tree::split_child(std::vector<primary_key>* x,
															std::vector<int>* x_child,
														  int i,
														  file_input* line_inf)
{
	// New node, child of node x
	const int roots_children = 2;
	std::vector<primary_key> z;
	std::vector<int> z_child;

	int vector_size = this->primary_key_vector.size();
	int node_lenght = Node_size/2;	


	// Splits child node in two(z and current node_B_Tree)
	for(int j = node_lenght+1 ; j < vector_size; j++)
	{

		std::vector<primary_key>::iterator it;
	  it = z.begin();	

		z.insert(it,this->primary_key_vector[j]);
	}


	if(line_inf->file_line_number == roots_children)
	{
		x_child->insert(x_child->begin(), line_inf->file_line_number);
		x_child->insert(x_child->begin(), 1);
	}


	else
	{
		if(x_child->size() == 0)
		{
			x_child->insert(x_child->begin(), line_inf->file_line_number);	
			x_child->insert(x_child->begin(), line_inf->current_node_position);
		}

		else
		{
			x_child->insert(x_child->begin()+i+1, line_inf->file_line_number);
		}

	}

	// Input in the vector as struct 
	primary_key new_data;

	new_data.primary_key_value = this->primary_key_vector[node_lenght].primary_key_value;
	new_data.NRR = this->primary_key_vector[node_lenght].NRR;

	x->insert(x->begin()+i,
					 new_data);

	// Removes y's node split keys
	for(int j = node_lenght; j <  vector_size; j++)
	{
		this->primary_key_vector.erase(this->primary_key_vector.begin()+j);
	}

	std::stable_sort (z.begin(), z.end(), compare_primary_key);

	if(this->leaf_verify() == false)
	{
		for (int j = node_lenght+1; j < this->child.size(); j++)
		{
			z_child.insert(z_child.end(),this->child[j]);
		}

		int child_size = this->child.size();

		// Removes y's children split keys
		for(int j = node_lenght+1; j <  child_size; j++)
		{
			this->child.erase(this->child.end()-1);
		}
	}


	// Sorting of the node by the primary key value
	std::stable_sort (x->begin(), x->end(), compare_primary_key);

	int size;

	// Write current node data
	size = this->primary_key_vector.size();
	line_inf = register_constructor(size, 
																	this->primary_key_vector,
																	this->child,
																	line_inf);

	line_inf->node_before = read_data(line_inf->current_node_position);

	write_data(line_inf->node_before, line_inf->node);	

	// Write z node data(current node brother)

	line_inf->node.erase(line_inf->node.begin(), line_inf->node.end());

	size = z.size();
	line_inf = register_constructor(size, 
																	z,
																	z_child,
																	line_inf);

	write_data("last", line_inf->node);
	
	// Write x node data(parent node)


	line_inf->node.erase(line_inf->node.begin(), line_inf->node.end());


	size = x->size();
	line_inf = register_constructor(size, 
																	*x,
																	*x_child,
																	line_inf);

	// x is a new node
	if(line_inf->parent_node_position == line_inf->file_line_number + 1)
	{
		write_data("last", line_inf->node);

	}


	// x already exists
	else
	{
		line_inf->node_before = read_data(line_inf->parent_node_position);
		write_data(line_inf->node_before, line_inf->node);
	}

	line_inf->node_before = read_data(line_inf->parent_node_position);
}

void node_B_Tree::delete_data()
{
	return;
}

void node_B_Tree::search_data()
{
	return;
}

bool node_B_Tree::leaf_verify( )
{
	if (this->child.size() == 0)
	{
		return true;		
	}

	else
	{
		return false;
	}

}

void node_B_Tree::set_to_root(file_input* line_inf)
{
	// Data file name
  std::string name = "indicelista";
  std::string extension = ".bt";
  name += extension;

  // Original index file
  ifstream index_file_in(name);

  std::string line;

  getline(index_file_in, line);

  line.erase(line.begin());

  char child[100];
	child[2] = '\0';

	line.copy(child,2,0);

	int node_number = atoi(child);

	line_inf->parent_node_position = node_number;
	line_inf->current_node_position = node_number;

	// Sets node before(to locate and replace the line)
  line_inf->node_before = read_data(node_number);


	index_file_in.close();

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
