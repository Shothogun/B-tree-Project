OA_Projeto2 

	ALUNOS:
				Giordano Suffert Monteiro - 17/0011160
				Otho Teixeira Komatsu - 17/0020142

Para compilar o programa e necessario a utilizacao do programa "makefile", e devem ser utilizados os 
seguintes comandos na linha de comando dentro da pasta "src":

		make

O executavel sera criado na pasta "exec" com nome "main" assim como o aquivo com os indices organizados 
como uma arvore binaria que serao criados na execucao do programa.

Para executa-lo e preciso que o arquivo com os registros a serem utilizados estejam no diretorio "exec" 
juntamente com o executavel.

E importante saber que o programa espera arquivos e inputs dentro do determinado pela especificacao do
projeto, conferindo apenas alguns erros de input pelo usuario mas nao a formatacao de toda informacao
passada para ele.

Alem disso, os dados passados para o programa não devem ultrapassar o tamanho máximo indicado pelo 
espaço separado para cada elemento no arquivo de registros (Nome-40/Matricula-5/Curso-2/Turma-1).

Sobre o algoritmo:

No programa em questao e utilizada uma formatacao no arquivo de indices que segue o seguinte padrao:
			Primeira linha- Cabecalho com a linha da raiz "R(numero)"
			Outras linhas- Um nodo com: chaves primarias, NRR no arquivo de registros, NRR dos filhos. A 
			correspondencia entre os dados e feita pela ordem em que eles aparecem. Um nodo sem dados e igual a um 
			nodo inexistente.

No arquivo de registros, um '*' indica que o registro foi removido.