#ifndef INTERFACE_H
#define INTERFACE_H

#include "B_Tree.hpp"
#include <string>

using namespace std;

int start_menu (int* number_keys, string& registers_file_name, string& index_file_name);

int main_menu (string registers_file, string B_tree_file, node_B_Tree node);

#endif