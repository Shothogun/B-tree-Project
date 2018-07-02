#include "interface.hpp"
#include "IO.hpp"
#include "main_file.hpp"
#include <iostream>
#include <fstream>

int start_menu (int* number_keys, string& registers_file_name)
{
	int option;

	cout << "\n------ Escolha uma opcao de inicializacao da arvore (Numero)------\n";
	cout << "\n>>> Criar arvore vazia (1)\n";
	cout << ">>> Criar arvore do arquivo de registros (2)\n";
	cout << ">>> Terminar programa (3)\n";
	cout << "---OBS: Na terceira opcao o arquivo de indices deve estar formatado corretamente\n";

	cout << "\nSua escolha: ";

	cin >> option;
	cout << "\n";

	switch (option) // busca , inclusao, exclusao
		{
			case 1 :
				ofstream registers_file;
				registers_file.open("lista.txt", ios::out | ios::trunc);
				registers_file.close();
				registers_file_name = "lista.txt";
				index_file_creator ("lista.txt");
				break;

			case 2 :
				cout << "\n--Forneca o nome do arquivo de registros:\n";
				cout << "Arquivo: ";
				cin >> registers_file_name;
				cout << "\n";
				index_file_creator (registers_file_name);
				break;

			case 3 :
				return -1;
				break;

			default :
				cout << "\n--ERROR: Escolha uma opcao valida.\n--Lembre-se de utilizar a numeracao para escolha.\n";
				cout << "--Programa encerrado\n";
				return -1;
				break;
		}

		cout << "\n------ Escolha o numero de chaves por nodo (Um numero positivo menor que 100 e maior que 0) ------\n";
		cout << "\nSua escolha: ";
		cin >> *number_keys;
		if (*number_keys <=0 || *number_keys >= 100)
		{
			cout << "\n--ERROR: Escolha fora do esperado. Programa encerrado.\n";
			return -1;
		}

		return 0;
}

int main_menu (string registers_file, string B_tree_file, node_B_Tree* node)
{
	primary_key tmp_key;

	file_input line_inf;
	int stop = 0;
	int option;
	string prim_key;
	string register_;
	string number;

	int root_line, node_line;
	int line_number;
	int position;

	while (stop == 0)
	{
		cout << "\n------ Qual das seguintes operacoes voce quer realizar? (Numero) ------\n";
		cout << "\n>>> Procurar registro (1)\n";
		cout << ">>> Adicionar registro (2)\n";
		cout << ">>> Excluir registro (3)\n";
		cout << ">>> Terminar programa (4)\n";
		cout << "\nSua escolha: ";

		cin >> option;
		cout << "\n";

		switch (option) // busca , inclusao, exclusao
		{
			case 1 :

				cout << "\n--Forneca a chave primaria do registro a ser procurado:\n\n";
				cin >> prim_key;

				// search

				show_index_file (B_tree_file);				
				break;

			case 2 :
				cout << "\n--Forneca o registro a ser adicionado:\n\n";
				cin >> register_;
				//add in registers file
				//file size - return line_number
				file_input_clear(&line_inf);
				prim_key = primary_key_creator(register_, prim_key);

 				if (line_number < 10)
  			{
  				number = "0" + to_string(line_number);
  			}
  			else if (line_number < 100)
  			{
  				number = to_string(line_number);
  			}

  			node->insert_data(prim_key, number, &line_inf);

				show_index_file (B_tree_file);				
				break;

			case 3 : 

				cout << "\n--Forneca a chave primaria do registro a ser excluido:\n\n";
				cin >> prim_key;

				tmp_key.primary_key_value = prim_key;

				//search

				node_line = parents[0];
				parents.erase(0);

				node->read_data(node_line);

				// Achar a chave
				for (position = 0; position < node->primary_key_vector.size(); position++)
				{
					if (!(node->primary_key_vector[position].primary_key_value.compare(prim_key)))
					{
						tmp_key.NRR = primary_key_vector[position].NRR;
						break;
					}
				}

				node->delete_data(tmp_key, parents, node_line);
				delete_register(registers_file, stoi(tmp_key.NRR));

				show_index_file (B_tree_file);
				break;

			case 4 :
				stop = 1;
				break;

			default :
				cout << "\n--ERROR: Escolha uma opcao valida.\n--Lembre-se de utilizar a numeracao para escolha.\n";
				break;
		}

	} // while 

} // main_menu

