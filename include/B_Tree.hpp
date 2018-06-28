#ifndef B_tree
#define B_tree

#include <string>
#include <vector>

using namespace std;

typedef struct primary_key
{
	std::string primary_key_value;
	std::string NRR;

} primary_key;

class node_B_Tree
{
	private:
		int counter;
		int line_number;

	public:
		std::vector<primary_key> primary_key_vector;
		bool leaf;
		std::vector<int> pointer;
		int index_file_creator(std::string name_in);
		void insert_data(std::string primary_key_input, std::string NRR_input);
		void insert_data_non_full(std::string k, std::string NRR_input);
		void split_child();
		void delete_data();
		void search_data();
};

string primary_key_creator(string line, string line_ws);
bool compare_primary_key(const primary_key &a, const primary_key &b);

#endif