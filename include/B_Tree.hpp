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

	int parent_node_position;
	int current_node_position;

} file_input;

typedef struct primary_key
{
	std::string primary_key_value;
	std::string NRR;

} primary_key;

// This node always corresponds to the current node in operation
class node_B_Tree
{
	private:		
		std::vector<primary_key> primary_key_vector;
		std::vector<int> child;

		void insert_data(std::string primary_key_input,
									   std::string NRR_input,
									   file_input* line_inf);

		void insert_data_non_full(std::string NRR_input,
															std::string k,
														  file_input* line_inf);

		// Writes data in the index file(it can be root update or data insert)
		void write_data(std::string replace, std::string new_data);

		// Read node from index file(input: line wich node is located in index file)
		// and pass to node_B_tree
		// Returns the read line
		std::string read_data(int node_number);

		// Constructs the line corresponding to 
		// the node register in index file(modify only node from file_input variable)
		file_input* register_constructor(int vector_size, 
																	   std::vector<primary_key> primary_key_input_vector, 
																	 	 std::vector<int> child,
																		 file_input* line_inf);
		void split_child(std::vector<primary_key>* x,
										 std::vector<int>* x_child,
										 int i,
										 file_input* line_inf);
		void set_to_root(file_input* line_inf);
		void delete_data();
		std::vector<int> search_data(node_B_Tree* node, std::string k, std::vector<int>* path);
		bool leaf_verify();
		
	public:
		std::vector<int> search_data(node_B_Tree* node, std::string k, int root_line);
		int index_file_creator(std::string name_in);

};

string primary_key_creator(string line, string line_ws);
bool compare_primary_key(const primary_key &a, const primary_key &b);

#endif