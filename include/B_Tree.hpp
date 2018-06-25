#ifndef B_tree
#define B_tree

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
		int index_file_creator();
		void insert_data();
		void delete_data();
		void search_data();
};

string primary_key_creator(string line, string line_ws);

#endif