#ifndef DATA_H
#define DATA_H

#include <string>
#include <ctime>

using namespace std;

class Data {
public:
	// Inicia os atributos do objeto Data com a data atual do sistema operacional.
	Data();

	// Inicia os atributos do objeto Data com os valores dos par�metros dia, mes e ano.
	Data(int dia, int mes, int ano);

	// Inicia os atributos do objeto Data com o valor do par�metro data ("DD/MM/AAAA").
	Data(string data);

	void setDia(int dia);
	int getDia();

	void setMes(int mes);
	int getMes();

	void setAno(int ano);
	int getAno();

	// Retorna uma representa��o do objeto Data no formato string "DD/MM/AAAA".
	string toString();

	// Verifica se a data � uma data v�lida
	bool verificaData();

	/*
		Faz a compara��o de duas datas. Valores de retorno :

			1 se a data passada como par�metro for maior que a data armazenada no objeto
			2 se a data passada como par�metro for menor que a data armazenada no objeto
			3 se as datas forem iguais
	*/
	int compareTo(Data);

private:
	int dia, mes, ano; 
};
#endif