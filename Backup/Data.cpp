#include "Data.h"
#include <iostream>
#include <ctime>
#include <string.h>
#include <sstream>

using namespace std;

Data::Data()
{
	time_t now;
	struct tm nowLocal;

	now = time(NULL);
	localtime_s(&nowLocal, &now);

	this->dia = nowLocal.tm_mday;
	this->mes = nowLocal.tm_mon + 1;
	this->ano = nowLocal.tm_year + 1900;
}

Data::Data(int dia, int mes, int ano)
{
	setDia(dia);
	setMes(mes);
	setAno(ano);
}

Data::Data(string data)
{
	sscanf_s(data.c_str(), "%d%*c%d%*c%d", &dia, &mes, &ano);
}

void Data::setDia(int dia)
{
	this->dia = dia;
}

int Data::getDia()
{
	return this->dia;
}

void Data::setMes(int mes)
{
	this->mes = mes;
}

int Data::getMes()
{
	return mes;
}

void Data::setAno(int ano)
{
	this->ano = ano;
}

int Data::getAno()
{
	return ano;
}

string Data::toString()
{
	stringstream d, m, a;
	string data;

	d << dia;
	if (dia < 10)
		data = "0" + d.str() + '/';
	else
		data = d.str() + '/';

	m << mes;
	if (mes < 10)
		data = data + "0" + m.str() + '/';
	else
		data = data + m.str() + '/';

	a << ano;
	data = data + a.str();

	
	return data;
}

bool Data::verificaData()
{
	Data dataAtual;

	if (getAno() > dataAtual.getAno()) {
		return false;
	}

	if (getMes() > dataAtual.getMes() && getAno() == dataAtual.getAno()) {
		return false;
	}

	if (getDia() > dataAtual.getDia() && getMes() == dataAtual.getMes() && getAno() == dataAtual.getAno()) {
		return false;
	}

	if (getMes() > 0 && getMes() <= 12) {
		if (getMes() != 2) {
			if (getDia() > 0 && getDia() <= 31) {
				if (getAno() > 0) {
					return true;
				}
			}
		}
		else {
			if (getDia() <= 29 && (getAno() % 4 == 0)) {
				if (getAno() > 0) {
					return true;
				}
			}
			if (getDia() <= 28 && (getAno() % 4 != 0)) {
				if (getAno() > 0) {
					return true;
				}
			}
		}
	}
	return false;
}

int Data::compareTo(Data data)
{
	long d1, d2;

	d1 = ((getDia()) + (getMes() * 30) + (getAno() * 365));
	d2 = ((data.getDia()) + (data.getMes() * 30) + (data.getAno() * 365));

	//cout << "DATA 1 :: " << toString() << " VALOR :: " << d1 << " DATA 2 :: " << data.toString() << " VALOR :: " << d2 << endl;

	 
	if (d2 > d1)
		return 1;

	if (d2 < d1)
		return 2;

	return 3;
}
