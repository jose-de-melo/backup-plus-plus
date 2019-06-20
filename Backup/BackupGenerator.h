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
	// Construtor. Inicializa a vari�vel dirAtual.
	BackupGenerator();

	// Destrutor. Exclui os vector's usados pelo programa depois de encerrada a execu��o.
	~BackupGenerator();



	/*
		Inicia o backup de acordo com os par�metros fornecidos.
	*/
	int iniciar(int argc, char *argv[]);




	/*
		Fun��o utilizada para exibir a ajuda caso o usu�rio forne�a os par�metros incorretos ou insuficientes.
	*/
	inline void exibirAjuda() {
		cout << "Par�metros v�lidos:\n";
		cout << "\n\tPar�metro\t\t\t\t\tDescri��o\n";
		cout << "source:\\path\\filename\t\t\tO drive origem (source), o caminho (path) e" << endl << "\t\t\t\t\ta identifica��o dos arquivos (filename) que" << endl << "\t\t\t\t\tser�o copiados.\n\n";
		cout << "target:\\path\t\t\t\tO drive (target) e caminho (path) de destino" << endl << "\t\t\t\t\tpara onde os arquivos ser�o copiados.\n\n";
		cout << "/s\t\t\t\t\tRealiza um backup de todos os arquivos," << endl << "\t\t\t\t\tdiret�rios e subdiret�rios da localiza��o de" << endl << "\t\t\t\t\torigem indicada.\n\n";
		cout << "/m\t\t\t\t\tCopia todos os arquivos que foram modificados" << endl << "\t\t\t\t\tdesde o �ltimo backup.\n\n";
		cout << "/d:date\t\t\t\t\tRealiza o backup de todos os arquivos que foram" << endl << "\t\t\t\t\tcriados ou modificados a partir da data indicada.\n\n";
		cout << "/t:time\t\t\t\t\tRealiza o backup de todos os arquivos que foram" << endl << "\t\t\t\t\tcriados ou modificados a partir da hora indicada.\n\n";
		cout << "/l:logDrive:\\path\\arquivo\\Log.log\tCria um arquivo de log do backup e especifica a" << endl << "\t\t\t\t\tlocaliza��o de onde o log ser� gravado.\n\n";
	}

private:
	/*
		Realiza um backup simples, copiando somente os arquivos do diret�rio origem.
	*/
	int backupSimples(string origem);

	/*
		Realiza um backup copiando todos os arquivos e subdiret�rios do diret�rio origem.
	*/
	int backupS(string origem);

	/*
		Realiza a c�pia de um arquivo, quando a origem fornecida especificar um �nico arquivo.
	*/
	void copiaUmArquivo(string, string);

	/*
		Realiza um backup copiando todos os arquivos que foram modificados ap�s a data do backup anterior.
	*/
	int backupM(string, Data);

	/*
		Realiza um backup copiando todos os arquivos que foram modificados ap�s a hora fornecida.
	*/
	int backupT(string, Hora);

	/*
	Realiza um backup copiando todos os arquivos que foram modificados ap�s a data fornecida.
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
	Obt�m o n�mero de arquivos e diret�rios do caminho fornecido.
	*/
	void verificaNumeroDiretoriosEArquivos(string, int *, int *);

	/*
		Obt�m todos os arquivos, diret�rios e subdiret�rios do caminho fornecido.
	*/
	int getArquivosESubdiretorios(string);

	/*
		Remove do vector os arquivos que n�o cont�m o caractere coringa especificado.
	*/
	void removerArquivosSemCoringa(string);




	/*
		Realiza a c�pia dos arquivos e diret�rios armazenados nos vector's de acordo com o valor
		inteiro passado como par�metro:
				1 - Copia apenas arquivos
				2 - Copia apenas diret�rios e subdiret�rios
				3 - Copia arquivos, diret�rios e subdiret�rios
	*/
	int copiaArquivosOuDiretorios(string, string, int);




	/*
		Gera um relat�rio do backup realizado armazenando as informa��es dos arquivos copiados em um arquivo de acesso
		sequencial(arquivo texto).
	*/
	void gerarRelatorio(Data, Hora, Data, Hora);

	/*
	Gera um arquivo log com o relat�rio do backup.
	Usa o par�metro string para especificar o caminho onde o arquivo ser� criado. Se a string estiver vazia,
	o arquivo ser� criado no diret�rio corrente.
	*/
	void geraArquivoLog(string, Data , Hora , Data , Hora );

	/*
	Obt�m todos os arquivos copiados no �ltimo backup e os armazena no vector ultimoBackup.
	Retorna true caso exista um backup no arquivo de relat�rio, e false quando n�o existe.
	*/
	bool getArquivosRelatorio();

	// Verifica a quantidade de novos arquivos de acordo com o �ltimo backup realizado.
	size_t verificaNovosArquivos();

	// Verifica a quantidade de arquivos deletados de acordo com o �ltimo backup realizado.
	size_t verificaArquivosExcluidos();

	// Verifica quais arquivos foram atualizados de acordo com o �ltimo backup.
	int verificaArquivosAtualizados();

	/*
		Obt�m a data do �ltimo backup realizado armazenada no arquivo de relat�rio de backup's ou um objeto Data
		com os valores zerados (0/0/0) caso o arquivo esteja vazio, sendo assim o backup atual ser� o primeiro a ser
		realizado.
	*/
	Data getDataUltimoBackup();


	



	vector<Arquivo> arquivos; // Armazena os arquivos do backup.
	vector<Diretorio> diretorios; // Armazena os diret�rios e subdiret�rios do backup.
	vector<Arquivo> ultimoBackup; // Armazena os arquivos do �ltimo backup realizado.
	
	string dirAtual; // Armazena o diret�rio corrente inicial do programa.
	char dir[3000]; // Usada para receber o valor retornado pela fun��o _getcwd


};


#endif // !BACKUPGENERATOR_H

