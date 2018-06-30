#ifndef B_tree
#define B_tree

#include <string>
#include <vector>

using namespace std;

typedef struct file_input
{
	// Previous line that will be written in index file
	std::string node_before;

	// New line that will written in index file
	std::string node;

	// Index file line
	int file_line_number;

} file_input;

typedef struct primary_key
{
	std::string primary_key_value;
	std::string NRR;

} primary_key;

class node_B_Tree
{
	private:		
		bool leaf;
		
	public:
		std::vector<primary_key> primary_key_vector;
		std::vector<int> pointer;
		std::vector<int> child;
		void insert_data(std::string primary_key_input,
									   std::string NRR_input,
									   file_input* line_inf);

		void insert_data_non_full(std::string k,
														  std::string NRR_input,
														  file_input* line_inf);

		// Writes data in the index file(it can be root update or data insert)
		void write_data(std::string replace, std::string new_data);

		// Constructs the line corresponding to 
		// the node register in index file
		file_input* register_constructor(int vector_size, file_input* line_inf);
		void split_child(int i, std::vector<primary_key> s);
		void delete_data();
		void search_data();
		bool leaf_verify();

		int index_file_creator(std::string name_in);
};

string primary_key_creator(string line, string line_ws);
bool compare_primary_key(const primary_key &a, const primary_key &b);

#endif