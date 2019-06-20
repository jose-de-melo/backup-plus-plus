#ifndef DATA_H
#define DATA_H

#include <string>
#include <ctime>

using namespace std;

class Data {
public:
	// Inicia os atributos do objeto Data com a data atual do sistema operacional.
	Data();

	// Inicia os atributos do objeto Data com os valores dos parâmetros dia, mes e ano.
	Data(int dia, int mes, int ano);

	// Inicia os atributos do objeto Data com o valor do parâmetro data ("DD/MM/AAAA").
	Data(string data);

	void setDia(int dia);
	int getDia();

	void setMes(int mes);
	int getMes();

	void setAno(int ano);
	int getAno();

	// Retorna uma representação do objeto Data no formato string "DD/MM/AAAA".
	string toString();

	// Verifica se a data é uma data válida
	bool verificaData();

	/*
		Faz a comparação de duas datas. Valores de retorno :

			1 se a data passada como parâmetro for maior que a data armazenada no objeto
			2 se a data passada como parâmetro for menor que a data armazenada no objeto
			3 se as datas forem iguais
	*/
	int compareTo(Data);

private:
	int dia, mes, ano; 
};
#endif