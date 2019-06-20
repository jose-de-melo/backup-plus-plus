#ifndef DIRETORIO_H
#define DIRETORIO_H

#include "Arquivo.h"

//  Esta classe representa as propriedades de um diretório do sistema de arquivos.
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

	// Define o número de arquivos do diretório.
	void setNumeroDeArquivos(int numeroDeArquivos);

	// Obtém o número de arquivos do diretório.
	int getNumeroDeArquivos();

	// Define o número de subdiretórios do diretório.
	void setNumeroDeSubdiretorios(int numeroDeSubdiretorios);

	// Obtém o número de subdiretórios do diretório.
	int getNumeroDeSubDiretorios();

	// Define a localização do diretório.
	void setLocalizacao(string localizacao);

	// Obtém a localização do diretório.
	string getLocalizacao(); 

private:
	string nome; // Nome do diretório.
	long long tamanho; // Tamanho do diretório (somatório do tamanho de cada arquivo do diretório).

	Data data; // Data da última modificação do diretório.
	Hora hora; // Hora da última modificação do diretório.

	int numeroDeArquivos, // Número de arquivos do diretório.
		numeroDeSubDiretorios; // Número de subdiretórios do diretório.

	string localizacao; // Localização (caminho absoluto) do diretório.
};
#endif