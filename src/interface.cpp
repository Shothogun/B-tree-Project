#include "interface.hpp"
#include "IO.hpp"
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
	file_input line_inf;
	int stop = 0;
	int option;

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
				// Pegar o necessario para criador de chave primaria
				cout << "\n--Forneca a chave primaria do registro a ser procurado:\n";
				show_index_file (B_tree_file);				
				break;

			case 2 :
				cout << "\n--Forneca o registro a ser adicionado:\n";
				show_index_file (B_tree_file);				
				break;

			case 3 : 
				// Pegar o necessario para criador de chave primaria
				cout << "\n--Forneca a chave primaria do registro a ser excluido:\n";
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

