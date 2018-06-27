#ifndef B_TREE_H
#define B_TREE_H

#include <string>
#include <vector>

using namespace std;

typedef struct primary_key
{
	string primary_key_value;
	string NRR;

} primary_key;

class node_B_Tree
{
	private:
		std::vector<primary_key> primary_key_vector;
		std::vector<int> pointer;

	public:
		void insert_data();
		void delete_data();
		void search_data();
};

string primary_key_creator(string line, string line_ws);

int index_file_creator (string file_name);

node_B_Tree get_node (string file_name, int line_number);

#endif