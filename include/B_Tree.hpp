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

class node_B_tree
{
	private:
		std::vector<primary_key> primary_key_vector;
		std::vector<int> pointer;
};

#endif