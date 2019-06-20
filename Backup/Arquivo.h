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

	// Define a localiza��o do diret�rio.
	void setLocalizacao(string localizacao);

	// Obt�m a localiza��o do diret�rio.
	string getLocalizacao();

private:
	string nome; // Nome do arquivo.
	unsigned long tamanho; // Tamanho, em bytes, do arquivo. 

	Data data; // Data da �ltima modifica��o do arquivo.
	Hora hora; // Hora da �ltima modifica��o do arquivo.

	string localizacao; // Localiza��o (caminho absoluto) do arquivo.
};
#endif