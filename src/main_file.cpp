#include "main_file.hpp"

#include <fstream>

int delete_register (string registers_file, int file_line)
{
	int line_number = 0;
	string line;

	fstream main_file;
	main_file.open(registers_file);

	while (line_number < file_line)
	{
		getline(main_file, line);
		line_number ++;
	}

	main_file << "*";

	main_file.close();

	return line_number;
}