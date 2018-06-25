#include "B_Tree.hpp"
#include <iostream>						


string primary_key_creator(string line, string line_ws)
{

	// Express the character position at the line from main file(lista.txt)
	int position;

	// Limits the number of Uppercasse in primary Key
	int Uppercase = 0;		

	line_ws.clear();
		
	for (position = 0; position < 46; position++)
	{
		if(line[position] <= 90 && line[position] >= 65 && Uppercase < 3)
		{
			line_ws += line[position];
			Uppercase++;
		}

		if(position > 40 && position < 46)
		{
			line_ws += line[position];
		}
	}

	return line_ws;
}
