#include "Hora.h"
#include <ctime>
#include <iostream>
#include <string.h>
#include <sstream>

using namespace std;

Hora::Hora()
{
	time_t now;
	struct tm nowLocal;

	now = time(NULL);
	localtime_s(&nowLocal, &now);

	setHora(nowLocal.tm_hour);
	setMinuto(nowLocal.tm_min);
	setSegundo(nowLocal.tm_sec);
}

Hora::Hora(int hora, int minuto, int segundo)
{
	setHora(hora);
	setMinuto(minuto);
	setSegundo(segundo);
}

Hora::Hora(string hora)
{
	sscanf_s(hora.c_str(), "%d%*c%d%*c%d", &this->hora, &minuto, &segundo); 
}

void Hora::setHora(int hora)
{
	this->hora = hora;
}

int Hora::getHora()
{
	return hora;
}

void Hora::setMinuto(int minuto)
{
	this->minuto = minuto;
}

int Hora::getMinuto()
{
	return minuto;
}

void Hora::setSegundo(int segundo)
{
	this->segundo = segundo;
}

int Hora::getSegundo()
{
	return segundo;
}

string Hora::toString()
{
	stringstream hr, m, s;
	string h;

	hr << hora;
	if (hora < 10)
		h = "0" + hr.str() + ":";
	else
		h = hr.str() + ":";



	m << minuto;
	if(minuto < 10)
		h =  h + "0" + m.str() + ":";
	else
		h = h + m.str() + ":";

	s << segundo;

	if (segundo < 10)
		h = h + "0" + s.str();
	else
		h = h + s.str();



	return h;
}

bool Hora::verificaHora()
{
	if ((getHora() <= 23 && getHora() >= 0) && (getMinuto() >= 0 && getMinuto() < 60)) {
			return true;
	}
	
	return false;
}

int Hora::compareTo(Hora hora)
{
	long h1, h2;

	h1 = (getHora() * 3600) + (getMinuto()*60) + getSegundo();
	h2 = (hora.getHora() * 3600) + (hora.getMinuto()*60) + hora.getSegundo();

	if (h2 > h1)
		return 1;
	if (h2 < h1)
		return 2;

	return 3;
}
