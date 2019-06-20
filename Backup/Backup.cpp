#include <iostream>
#include "BackupGenerator.h"
#include <clocale>

/*
	Jos� do Carmo de Melo Silva
	IFSEMG - Campus Barbacena - Sistemas para Internet - 2017


*/
/*
	O programa realiza backup's de arquivos de um diret�rio especificado na linha de comando.

	A fun��o main cria um objeto do tipo BackupGenerator e chama a fun��o iniciar() do objeto, que recebe
	os par�metros fornecidos na linha de comando e inicializa o backup.
*/
int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "portuguese");
	BackupGenerator backup;

	return backup.iniciar(argc, argv);
}