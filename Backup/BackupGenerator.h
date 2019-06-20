#ifndef BACKUPGENERATOR_H
#define BACKUPGENERATOR_H

/*
	Classe para gerenciar os backup's realizados pelo programa.
*/


#include <iostream>
#include <time.h>
#include <string>
#include <io.h>
#include <direct.h>
#include <vector>
#include <fstream>
#include "Data.h"
#include "Hora.h"
#include "Arquivo.h"
#include "Diretorio.h"

using namespace std;

class BackupGenerator {
public:
	// Construtor. Inicializa a variável dirAtual.
	BackupGenerator();

	// Destrutor. Exclui os vector's usados pelo programa depois de encerrada a execução.
	~BackupGenerator();



	/*
		Inicia o backup de acordo com os parâmetros fornecidos.
	*/
	int iniciar(int argc, char *argv[]);




	/*
		Função utilizada para exibir a ajuda caso o usuário forneça os parâmetros incorretos ou insuficientes.
	*/
	inline void exibirAjuda() {
		cout << "Parâmetros válidos:\n";
		cout << "\n\tParâmetro\t\t\t\t\tDescrição\n";
		cout << "source:\\path\\filename\t\t\tO drive origem (source), o caminho (path) e" << endl << "\t\t\t\t\ta identificação dos arquivos (filename) que" << endl << "\t\t\t\t\tserão copiados.\n\n";
		cout << "target:\\path\t\t\t\tO drive (target) e caminho (path) de destino" << endl << "\t\t\t\t\tpara onde os arquivos serão copiados.\n\n";
		cout << "/s\t\t\t\t\tRealiza um backup de todos os arquivos," << endl << "\t\t\t\t\tdiretórios e subdiretórios da localização de" << endl << "\t\t\t\t\torigem indicada.\n\n";
		cout << "/m\t\t\t\t\tCopia todos os arquivos que foram modificados" << endl << "\t\t\t\t\tdesde o último backup.\n\n";
		cout << "/d:date\t\t\t\t\tRealiza o backup de todos os arquivos que foram" << endl << "\t\t\t\t\tcriados ou modificados a partir da data indicada.\n\n";
		cout << "/t:time\t\t\t\t\tRealiza o backup de todos os arquivos que foram" << endl << "\t\t\t\t\tcriados ou modificados a partir da hora indicada.\n\n";
		cout << "/l:logDrive:\\path\\arquivo\\Log.log\tCria um arquivo de log do backup e especifica a" << endl << "\t\t\t\t\tlocalização de onde o log será gravado.\n\n";
	}

private:
	/*
		Realiza um backup simples, copiando somente os arquivos do diretório origem.
	*/
	int backupSimples(string origem);

	/*
		Realiza um backup copiando todos os arquivos e subdiretórios do diretório origem.
	*/
	int backupS(string origem);

	/*
		Realiza a cópia de um arquivo, quando a origem fornecida especificar um único arquivo.
	*/
	void copiaUmArquivo(string, string);

	/*
		Realiza um backup copiando todos os arquivos que foram modificados após a data do backup anterior.
	*/
	int backupM(string, Data);

	/*
		Realiza um backup copiando todos os arquivos que foram modificados após a hora fornecida.
	*/
	int backupT(string, Hora);

	/*
	Realiza um backup copiando todos os arquivos que foram modificados após a data fornecida.
	*/
	int backupD(string, Data);




	/*
		Remove o caractere coringa contido na string e o valor do mesmo como string.
	*/
	string getCaractereCoringa(string*);

	/*
		Verifica se o caminho fornecido em origem especifica um arquivo.
	*/
	bool verificaSeEUmUnicoArquivoParaCopiar(string);


	/*
	Obtém o número de arquivos e diretórios do caminho fornecido.
	*/
	void verificaNumeroDiretoriosEArquivos(string, int *, int *);

	/*
		Obtém todos os arquivos, diretórios e subdiretórios do caminho fornecido.
	*/
	int getArquivosESubdiretorios(string);

	/*
		Remove do vector os arquivos que não contém o caractere coringa especificado.
	*/
	void removerArquivosSemCoringa(string);




	/*
		Realiza a cópia dos arquivos e diretórios armazenados nos vector's de acordo com o valor
		inteiro passado como parâmetro:
				1 - Copia apenas arquivos
				2 - Copia apenas diretórios e subdiretórios
				3 - Copia arquivos, diretórios e subdiretórios
	*/
	int copiaArquivosOuDiretorios(string, string, int);




	/*
		Gera um relatório do backup realizado armazenando as informações dos arquivos copiados em um arquivo de acesso
		sequencial(arquivo texto).
	*/
	void gerarRelatorio(Data, Hora, Data, Hora);

	/*
	Gera um arquivo log com o relatório do backup.
	Usa o parâmetro string para especificar o caminho onde o arquivo será criado. Se a string estiver vazia,
	o arquivo será criado no diretório corrente.
	*/
	void geraArquivoLog(string, Data , Hora , Data , Hora );

	/*
	Obtém todos os arquivos copiados no último backup e os armazena no vector ultimoBackup.
	Retorna true caso exista um backup no arquivo de relatório, e false quando não existe.
	*/
	bool getArquivosRelatorio();

	// Verifica a quantidade de novos arquivos de acordo com o último backup realizado.
	size_t verificaNovosArquivos();

	// Verifica a quantidade de arquivos deletados de acordo com o último backup realizado.
	size_t verificaArquivosExcluidos();

	// Verifica quais arquivos foram atualizados de acordo com o último backup.
	int verificaArquivosAtualizados();

	/*
		Obtém a data do último backup realizado armazenada no arquivo de relatório de backup's ou um objeto Data
		com os valores zerados (0/0/0) caso o arquivo esteja vazio, sendo assim o backup atual será o primeiro a ser
		realizado.
	*/
	Data getDataUltimoBackup();


	



	vector<Arquivo> arquivos; // Armazena os arquivos do backup.
	vector<Diretorio> diretorios; // Armazena os diretórios e subdiretórios do backup.
	vector<Arquivo> ultimoBackup; // Armazena os arquivos do último backup realizado.
	
	string dirAtual; // Armazena o diretório corrente inicial do programa.
	char dir[3000]; // Usada para receber o valor retornado pela função _getcwd


};


#endif // !BACKUPGENERATOR_H

