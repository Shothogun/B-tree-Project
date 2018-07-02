#include "B_Tree.hpp"
#include <iostream>						
#include <cstring>
#include <fstream>
#include <algorithm>
#include <cstdlib>
#include <cmath>			

using namespace std;

/*
int empty_index_file_creator (string file_name)
{

	ofstream index_file;

	// Create new B-tree file
	index_file.open (file_name, ios::out | ios::trunc);

	if (index_file.is_open())
	{
		// Create header with the line of the root
		index_file << "#-1\n";
	}

	else 
	{
		cout << "Unable to open file";
		return -1;
	}

	index_file.close();
	return 0;
}
*/
node_B_Tree::node_B_Tree(int order)
{
	Node_size = order;
}

int node_B_Tree::delete_data (primary_key del_primary_key, vector<int> parents, int node_line)
{
	file_input line_inf;
	int position;
	int cur_position = -1;
	primary_key tmp_key;
	int tmp_index_NRR;
	int leaf_line;

	if (leaf_verify()) // Delecao caso for no folha
	{
		// Achar a chave
		for (position = 0; position < primary_key_vector.size(); position++)
		{
			if (primary_key_vector[position].NRR.compare(del_primary_key.NRR) &&
					primary_key_vector[position].primary_key_value.compare(del_primary_key.primary_key_value))
			{
				cur_position = position;node_number
				break;
			}
		}

		if (cur_position == -1)
		{
			cout << "Chave nao existente\n";
			return -1;
		}
		else
		{
			primary_key_vector.erase(cur_position);
		}

		leaf_line = node_line;
	}

	else // Delecao caso nao for no folha
	{
		// Achar a chave
		for (position = 0; position < primary_key_vector.size(); position++)
		{
			if (primary_key_vector[position].NRR.compare(del_primary_key.NRR) &&
					primary_key_vector[position].primary_key_value.compare(del_primary_key.primary_key_value))
			{
				cur_position = position;
				break;
			}
		}

		if (cur_position == -1)
		{
			cout << "Chave nao existente\n";
			return -1;
		}

		// Armazenar a posicao do nodo no arquivo de indices
		tmp_index_NRR = node_line;

		// Vai para o sucessor imediato
		leaf_line = go_to_successor (cur_position, parents, node_line);

		// Armazenar a chave a ser trocada
		tmp_key = primary_key_vector [0];
		primary_key_vector.erase(0);

		file_input_clear(&line_inf);
		register_constructor(primary_key_vector.size(), &line_inf);
		write_data(line_inf->node_before, line_inf->node);

		// Volta para o nodo inicial para trocar a chave

		read_data (tmp_index_NRR);

		primary_key_vector[cur_position] = tmp_key;

		file_input_clear(&line_inf);
		register_constructor(primary_key_vector.size(), &line_inf);
		write_data(line_inf->node_before, line_inf->node);

		read_data (leaf_line);
	}

	// Lidar com casos de underflow

	underflow_changer(parents, leaf_line);
}

bool node_B_Tree::leaf_verify()
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

int node_B_Tree::go_to_successor(int cur_position, vector<int> parents, int node_line)
{
	// Filho a direita da chave
	parents.push_back(node_line);
	node_line = child [cur_position + 1];
	read_data(child [cur_position + 1]);

	while (!(leaf_verify()))
	{
		parents.push_back(node_line);
		node_line = child[0];
		// Filho mais a esquerda
		read_data(child [0]);
	}

	return node_line;
}

void node_B_Tree::underflow_changer (vector<int> parents, int node_line)
{
	const int min_number_keys = floor(Node_size / 2);

	int done = 0;

	// Se tiver menos que o minimo de nos e nao for raiz
	if (primary_key_vector.size() < min_number_keys && parents.size() > 0)
	{
		// Tentar fazer redistribuicao

		done = redistribution(parents, node_line);

		// Fazer concatenacao caso nao feita a redistribuicao
		if (done == 0)
		{
			merging (parents, node_line);
			if (primary_key_vector.size() == 0)
			{
				node_line = child[0];
				child.clear();
				read_data(node_line);
				change_root(node_line);
			}
			else 
			{
				node_line = parents[0];
			}
			parents.erase(0);

			underflow_changer (parents, node_line);
		}
	}
}

int node_B_Tree::redistribution (vector<int> parents, int node_line)
{
	file_input line_inf;
	int done;
	int position, cur_position;
	int line = node_line;
	primary_key tmp_key, new_key;
	int tmp_NRR;
	
	read_data (parents[0]);

	// Achar o NRR
	for (position = 0; position < child.size(); position++)
	{
		if (child[position] == line)
		{
			cur_position = position;
			break;
		}
	}

	// Analisar nodos irmaos

	if (cur_position - 1 >= 0)
	{
		read_data (child[cur_position - 1]);

		if (primary_key_vector.size() - 1 > min_number_keys)
		{
			tmp_key = primary_key_vector.back();
			primary_key_vector.pop_back();

			if (!(leaf_verify()))
			{
				tmp_NRR = child.back();
				child.pop_back();
			}

			file_input_clear(&line_inf);
			register_constructor(primary_key_vector.size(), &line_inf);
			write_data(line_inf->node_before, line_inf->node);

			read_data (parents[0]);

			new_key = primary_key_vector[cur_position - 1];
			primary_key_vector[cur_position - 1] = tmp_key;

			file_input_clear(&line_inf);
			register_constructor(primary_key_vector.size(), &line_inf);
			write_data(line_inf->node_before, line_inf->node);

			read_data (child[cur_position]);

			primary_key_vector.emplace(primary_key_vector.begin(), new_key);

			if (!(leaf_verify()))
				{
					child.emplace(child.begin(), tmp_NRR);
				}

			file_input_clear(&line_inf);
			register_constructor(primary_key_vector.size(), &line_inf);
			write_data(line_inf->node_before, line_inf->node);	

			done = 1;

		}
		read_data (parents[0]);

	}

	if (cur_position + 1 < child.size() && done == 0)
	{
		read_data (child[cur_position + 1]);

		if (primary_key_vector.size() - 1 > min_number_keys)
		{
			tmp_key = primary_key_vector[0];
			primary_key_vector.erase(0);

			if (!(leaf_verify()))
			{
				tmp_NRR = child[0];
				child.erase(0);
			}

			file_input_clear(&line_inf);
			register_constructor(primary_key_vector.size(), &line_inf);
			write_data(line_inf->node_before, line_inf->node);

			read_data (parents[0]);

			new_key = primary_key_vector[cur_position];
			primary_key_vector[cur_position] = tmp_key;

			file_input_clear(&line_inf);
			register_constructor(primary_key_vector.size(), &line_inf);
			write_data(line_inf->node_before, line_inf->node);

			read_data (child[cur_position]);

			primary_key_vector.push_back(new_key);

			if (!(leaf_verify()))
				{
					child.push_back(tmp_NRR);
				}

			file_input_clear(&line_inf);
			register_constructor(primary_key_vector.size(), &line_inf);
			write_data(line_inf->node_before, line_inf->node);	
			done = 1;
		}

		read_data (parents[0]);
	}

	read_data (child[cur_position]);
	return done;
}

int node_B_Tree::merging (vector<int> parents,int node_line)
{
	int position, cur_position;
	int done = 0;
	file_input line_inf;

	primary_key tmp_key;
	vector<primary_key> tmp_key_vector;
	vector<int> tmp_child_vector;

	read_data (parents[0]);

	// Achar o NRR
	for (position = 0; position < child.size(); position++)
	{
		if (child[position] == node_line)
		{
			cur_position = position;
			break;
		}
	}


	if (cur_position - 1 >= 0)
	{
		read_data(child[cur_position]);

		tmp_key_vector = primary_key_vector;
		tmp_child_vector = child;

		primary_key_vector.clear();
		child.clear();

		register_constructor(primary_key_vector.size(), &line_inf);
		write_data(line_inf->node_before, line_inf->node);

		read_data(parents[0]);

		tmp_key = primary_key_vector[cur_position - 1];
		primary_key.erase(cur_position - 1);
		child.erase(cur_position);

		file_input_clear(&line_inf);
		register_constructor(primary_key_vector.size(), &line_inf);
		write_data(line_inf->node_before, line_inf->node);

		read_data(child[cur_position-1]);

		primary_key_vector.push_back(tmp_key);
		primary_key_vector.insert(primary_key_vector.begin(), tmp_key_vector.begin(), tmp_key_vector.end()); 
		child.insert(child.begin(), tmp_child_vector.begin(), tmp_child_vector.end());

		file_input_clear(&line_inf);
		register_constructor(primary_key_vector.size(), &line_inf);
		write_data(line_inf->node_before, line_inf->node);

		done = 1;

		read_data(parents[0]);
	}

	if (cur_position + 1 < child.size() && done == 0)
	{
		read_data(child[cur_position]);

		tmp_key_vector = primary_key_vector;
		tmp_child_vector = child;

		primary_key_vector.clear();
		child.clear();

		file_input_clear(&line_inf);
		register_constructor(primary_key_vector.size(), &line_inf);
		write_data(line_inf->node_before, line_inf->node);

		read_data(parents[0]);

		tmp_key = primary_key_vector[cur_position];
		primary_key.erase(cur_position);
		child.erase(cur_position);

		file_input_clear(&line_inf);
		register_constructor(primary_key_vector.size(), &line_inf);
		write_data(line_inf->node_before, line_inf->node);

		read_data(child[cur_position]);

		primary_key_vector.push_back(tmp_key);
		primary_key_vector.insert(primary_key_vector.begin(), tmp_key_vector.begin(), tmp_key_vector.end()); 
		child.insert(child.begin(), tmp_child_vector.begin(), tmp_child_vector.end());

		file_input_clear(&line_inf);
		register_constructor(primary_key_vector.size(), &line_inf);
		write_data(line_inf->node_before, line_inf->node);

		done = 1;

		read_data(parents[0]);
	}

	return done;

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

void file_input_clear (file_input* line_inf)
{
	line_inf->node_before.clear();
	line_inf->node.clear();
	line_inf->file_line_number=0;
	line_inf->child.clear();
}

void change_root (int number_line)
{
	string line;
	int cur_line = 0;
	string number;

	// Data file name
  std::string name = "indicelista";
  std::string extension = ".bt";
  name += extension;

  // Original index file
  ofstream index_file;
  index_file.open(name);

  if (number_line < 10)
  {
  	number = "0" + to_string(number_line);
  }
  else if (number_line < 100)
  {
  	number = to_string(number_line);
  }

  index_file << "R" << number;

  index_file.close();
}