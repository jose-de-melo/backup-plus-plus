#ifndef ARQUIVO_H
#define ARQUIVO_H

#include "Hora.h"
#include "Data.h"

// Esta classe representa as propriedades de um arquivo do sistema de arquivos.
class Arquivo {
public:
	Arquivo();

	void setNome(string nome);
	string getNome();

	void setTamanho(unsigned long tamanho);
	unsigned long getTamanho();

	void setData(Data data);
	Data getData();

	void setHora(Hora hora);
	Hora getHora();

	// Define a localização do diretório.
	void setLocalizacao(string localizacao);

	// Obtém a localização do diretório.
	string getLocalizacao();

private:
	string nome; // Nome do arquivo.
	unsigned long tamanho; // Tamanho, em bytes, do arquivo. 

	Data data; // Data da última modificação do arquivo.
	Hora hora; // Hora da última modificação do arquivo.

	string localizacao; // Localização (caminho absoluto) do arquivo.
};
#endif