#include "interface.hpp"
#include "B_Tree.hpp"
#include <iostream>

int start_menu ()
{
	int option;
	string registers_file_name;
	string index_file_name;

	cout << "\n------ Escolha uma opcao de inicializacao da arvore (Numero)------\n";
	cout << "\n>>> Criar arvore vazia (1)\n";
	cout << "\n>>> Criar arvore do arquivo de registros (2)\n";
	cout << "\n>>> Criar arvore do arquivo de registros e de indices (3)\n";
	cout << ">>> Terminar programa (4)\n";
	cout << "\n---OBS: Na terceira opcao o arquivo de indices deve estar formatado corretamente\n";

	cout << "\nSua escolha: ";

	cin >> option;
	cout << "\n";

	switch (option) // busca , inclusao, exclusao
		{
			case 1 :
				//register_file_creator ("registers_file.txt")
				empty_index_file_creator ("index_file.bt");
				break;

			case 2 :
				cout << "\n--Forneca o nome do arquivo de registros:\n";
				cout << "Arquivo: ";
				cin >> registers_file_name;
				cout << "\n";
				break;
				// Cria arquivo de indices
				empty_index_file_creator ("index_file.bt");

			case 3 : 
				cout << "\n--Forneca o nome do arquivo de registros:\n";
				cout << "Registros: ";
				cin >> registers_file_name;
				cout << "\n";
				cout << "\n--Forneca o nome do arquivo de indices:\n";
				cout << "Indices: ";
				cin >> index_file_name;
				cout << "\n";

				break;

			case 4 :
				return -1;
				break;

			default :
				cout << "\n--ERROR: Escolha uma opcao valida.\n--Lembre-se de utilizar a numeracao para escolha.\n";
				cout << "--Programa encerrado\n";
				return -1;
				break;
		}
		return 1;
}

int main_menu (string registers_file, string B_tree_file)
{
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
				cout << ""
				break;

			case 2 :
				cout << "\n--Forneca o registro a ser adicionado:\n";
				break;

			case 3 : 
				// Pegar o necessario para criador de chave primaria
				cout << ""
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

