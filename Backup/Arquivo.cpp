#include "Arquivo.h"

Arquivo::Arquivo()
{
	setNome("");
	setData(*(new Data));
	setHora(*(new Hora));
	setLocalizacao("");
	setTamanho(0);
}

void Arquivo::setNome(string nome)
{
	this->nome = nome;
}

string Arquivo::getNome()
{
	return nome;
}

void Arquivo::setTamanho(unsigned long tamanho)
{
	this->tamanho = tamanho;
}

unsigned long Arquivo::getTamanho()
{
	return tamanho;
}

void Arquivo::setData(Data data)
{
	this->data = data;
}

Data Arquivo::getData()
{
	return data;
}

void Arquivo::setHora(Hora hora)
{
	this->hora = hora;
}

Hora Arquivo::getHora()
{
	return hora;
}

void Arquivo::setLocalizacao(string localizacao)
{
	this->localizacao = localizacao;
}

string Arquivo::getLocalizacao()
{
	return localizacao;
}
