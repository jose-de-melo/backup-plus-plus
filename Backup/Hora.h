#ifndef HORA_H
#define HORA_H

#include <string>

using namespace std;

class Hora {
public:
	// Inicia os atributos do objeto Hora com a hora atual do sistema operacional.
	Hora();

	// Inicia os atributos do objeto Hora com os valores dos parâmetros hora, minuto e segundo.
	Hora(int hora, int minuto, int segundo);

	// Inicia os atributos do objeto Hora com o valor do parâmetro hora ("HH:MM:SS").
	Hora(string hora);

	void setHora(int hora);
	int getHora();

	void setMinuto(int minuto);
	int getMinuto();

	void setSegundo(int segundo);
	int getSegundo();

	// Retorna uma representação do objeto Hora no formato string "HH:MM:SS".
	string toString();
	
	// Verifica se os valores armazenados nas variáveis são válidos.
	bool verificaHora();

	/* Compara dois objetos Hora. Valores de retorno:
				1 se a hora passada como parâmetro for maior que a hora armazenada no objeto
				2 se a hora passada como parâmetro for menor que a hora armazenada no objeto
				3 se as horas forem iguais

	*/
	int compareTo(Hora );


private:
	int hora, minuto, segundo; 
};
#endif