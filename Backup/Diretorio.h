#ifndef DIRETORIO_H
#define DIRETORIO_H

#include "Arquivo.h"

//  Esta classe representa as propriedades de um diret�rio do sistema de arquivos.
class Diretorio {
public:
	Diretorio();

	void setNome(string nome);
	string getNome();

	void setTamanho(long long tamanho);
	long long getTamanho();

	void setData(Data data);
	Data getData();

	void setHora(Hora hora);
	Hora getHora();

	// Define o n�mero de arquivos do diret�rio.
	void setNumeroDeArquivos(int numeroDeArquivos);

	// Obt�m o n�mero de arquivos do diret�rio.
	int getNumeroDeArquivos();

	// Define o n�mero de subdiret�rios do diret�rio.
	void setNumeroDeSubdiretorios(int numeroDeSubdiretorios);

	// Obt�m o n�mero de subdiret�rios do diret�rio.
	int getNumeroDeSubDiretorios();

	// Define a localiza��o do diret�rio.
	void setLocalizacao(string localizacao);

	// Obt�m a localiza��o do diret�rio.
	string getLocalizacao(); 

private:
	string nome; // Nome do diret�rio.
	long long tamanho; // Tamanho do diret�rio (somat�rio do tamanho de cada arquivo do diret�rio).

	Data data; // Data da �ltima modifica��o do diret�rio.
	Hora hora; // Hora da �ltima modifica��o do diret�rio.

	int numeroDeArquivos, // N�mero de arquivos do diret�rio.
		numeroDeSubDiretorios; // N�mero de subdiret�rios do diret�rio.

	string localizacao; // Localiza��o (caminho absoluto) do diret�rio.
};
#endif