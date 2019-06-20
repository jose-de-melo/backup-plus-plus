#include "Diretorio.h"

Diretorio::Diretorio()
{
	setNome("");
	setTamanho(0);
	setData(*(new Data()));
	setHora(*(new Hora()));
	setNumeroDeArquivos(0);
	setNumeroDeSubdiretorios(0);
	setLocalizacao("");
}

void Diretorio::setNome(string nome)
{
	this->nome = nome;
}

string Diretorio::getNome()
{
	return nome;
}

void Diretorio::setTamanho(long long tamanho)
{
	this->tamanho = tamanho;
}

long long Diretorio::getTamanho()
{
	return tamanho;
}

void Diretorio::setData(Data data)
{
	this->data = data;
}

Data Diretorio::getData()
{
	return data;
}

void Diretorio::setHora(Hora hora)
{
	this->hora = hora;
}

Hora Diretorio::getHora()
{
	return hora;
}

void Diretorio::setNumeroDeArquivos(int numeroDeArquivos)
{
	this->numeroDeArquivos = numeroDeArquivos;
}

int Diretorio::getNumeroDeArquivos()
{
	return numeroDeArquivos;
}

void Diretorio::setNumeroDeSubdiretorios(int numeroDeSubdiretorios)
{
	this->numeroDeSubDiretorios = numeroDeSubDiretorios;
}

int Diretorio::getNumeroDeSubDiretorios()
{
	return numeroDeSubDiretorios;
}

void Diretorio::setLocalizacao(string localizacao)
{
	this->localizacao = localizacao;
}

string Diretorio::getLocalizacao()
{
	return localizacao;
}
