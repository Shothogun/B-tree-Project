#define CATCH_CONFIG_MAIN 
#include "B_Tree.hpp"
#include "interface.hpp"
#include <iostream>
#include <string>

int main()
{
	string registers_file;
	string B_tree_file = "indicelista.bt";

	int number_keys = 0;
	int exit;

	exit = start_menu(&number_keys, registers_file);

	if (exit == -1)
	{
		return 0;
	}

	node_B_Tree(number_keys) current_node;

	main_menu(registers_file, B_tree_file, &current_node);

	return 0;
}