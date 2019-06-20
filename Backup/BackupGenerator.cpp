#include <iostream>
#include "BackupGenerator.h"


BackupGenerator::BackupGenerator()
{
	_getcwd(dir, 3000);
	dirAtual = dir;
	dirAtual = dirAtual + "\\";
}

BackupGenerator::~BackupGenerator()
{
	diretorios.clear();
	arquivos.clear();
	ultimoBackup.clear();
}

int BackupGenerator::iniciar(int argc, char *argv[])
{
	Data dataInicial;
	Hora horaInicial;

	string p, p2;
	if (argc < 3) {
		cout << endl << "Parâmentros insuficientes!" << endl << endl;
		exibirAjuda();
		return -1;
	}
	else {
		int pD = 0, pL = 0, pM = 0, pS = 0, pT = 0;

		for (int i = 0; i < argc; i++) {
			p = argv[i];

			if (!_strcmpi(p.c_str(), "/s")) {
				pS = i;
			}

			if (!_strcmpi(p.c_str(), "/m")) {
				pM = i;
			}

			if (p.find("/d") != -1) {
				pD = i;
			}

			if (p.find("/t") != -1) {
				pT = i;
			}

			if (p.find("/l") != -1) {
				pL = i;
			}
		}

		string origem = argv[1];
		string destino = argv[2];
		string coringa = getCaractereCoringa(&origem);
		int copiou = 0;

		if (verificaSeEUmUnicoArquivoParaCopiar(origem) && !strcmp(coringa.c_str(), "")) {
			copiaUmArquivo(origem, destino);
		}
		else {
			if (!pS && !pM && !pD && !pT) {
				if (!backupSimples(origem)) {
					return 0;
				}
			}

			if (pS) {
				if (!backupS(origem)) {
					return 0;
				}
			}

			if (pM) {
				Data dFinal;
				if (pD) {
					Data dtUltimoBackup = getDataUltimoBackup();
					p2 = argv[pD];
					string dt = p2.substr(p2.find("/d") + 2, p2.size() - 1);
					Data data(dt);

					if (!dtUltimoBackup.verificaData()) {
						cout << "Nenhum backup realizado anteriormente!" << endl;
						return 0;
					}
					

					if (!data.verificaData()) {
						cout << endl << "A data fornecida não é válida!" << endl;
						return 0;
					}

					int vData = dtUltimoBackup.compareTo(data);

					if (vData == 1 || vData == 3) {
						dFinal = dtUltimoBackup;
					}
					else if (vData == 2) {
						dFinal = data;
					}
					

					if (!backupM(origem, dFinal)) {
						return 0;
					}
				}
				else {
					dFinal = getDataUltimoBackup();

					if (!backupM(origem, dFinal)) {
						return 0;
					}
				}
			}

			if (pD) {

				if (pM) {
					;
				}
				else if (pS) {
					p2 = argv[pD];
					string dt = p2.substr(p2.find("/d") + 3, p2.size() - 1);
					Data data(dt);


					if (data.verificaData()) {
						if (!backupD(origem, data)) {
							return 0;
						}
					}
					else {
						cout << "A data fornecida não é válida!" << endl;
						return 0;
					}
				}
				else {
					cout << endl << "Erro de sintaxe! O parâmetro [/d] tem que ser usado junto com [/s] ou [/m]" << endl;
					return 0;
				}

			}

			if (pT) {
				if (pS) {
					p2 = argv[pT];
					string hr;
					/* Verifica se o usuário forneceu a hora no formato HH:MM:SS, se fornecer no formato HH:MM
					   será adicionado os segundos no final (:00)
					*/
					if (p2.find_last_of(":") == 8) { 
						hr = p2.substr(p2.find("/t") + 3, p2.size() - 1);
					}
					else {
						hr = p2.substr(p2.find("/t") + 3, p2.size() - 1) + ":00";
					}
 
					Hora hora(hr);

					if (hora.verificaHora()) {
						if (!backupT(argv[1], hora))
							return 0;
					}
					else {
						cout <<  "A hora fornecida não é válida!" << endl;
						return 0;
					}
				}
				else {
					cout << endl << "Erro de sintaxe! O parâmetro [/t] tem que ser usado junto com [/s]" << endl;
					return 0;
				}
			}

		

			if (strcmp(coringa.c_str(), "")) {
				removerArquivosSemCoringa(coringa);
			}

			
			if (pS || pM) {
				copiou = copiaArquivosOuDiretorios(origem, argv[2], 3);
			}
			else {
				copiou = copiaArquivosOuDiretorios(origem, argv[2], 1);
			}
		}
		
		Data dataFinal;
		Hora horaFinal;

		if(copiou)
			gerarRelatorio(dataInicial, horaInicial, dataFinal, horaFinal);

		if (pL) {
			if (copiou) {
				string parametroL = argv[pL];

				if (parametroL.find(":") == -1) {
					geraArquivoLog("", dataInicial, horaInicial, dataFinal, horaFinal);
				}
				else {
					string d;
					if (parametroL.find(" ") != -1) {
						d = parametroL.substr(parametroL.find(":") + 1, parametroL.size() - 1);
					}
					else {
						d = parametroL.substr(parametroL.find(":") + 1, parametroL.size());
					}

					geraArquivoLog(d, dataInicial, horaInicial, dataFinal, horaFinal);
				}
			}
		}

		if(copiou)
			cout << "\nBACKUP CONCLUIDO." << endl;
		return 1;
	}
}

int BackupGenerator::backupSimples(string origem)
{
	if (getArquivosESubdiretorios(origem)) {
		return 1;
	}
	else {
		return 0;
	}
}

string BackupGenerator::getCaractereCoringa(string *origem)
{
	string coringa;

	size_t found = origem->find_last_of("\\");

	coringa = origem->substr(found + 1);

	size_t achou = coringa.find(".");
	size_t achou2 = coringa.find("*");

	if (achou == string::npos)
		return "";
	else {
		if (achou2 == string::npos)
			return "";
		else {
			*origem = origem->substr(0, origem->find_last_of("\\"));
			return coringa;
		}
	}



}

bool BackupGenerator::verificaSeEUmUnicoArquivoParaCopiar(string origem)
{
	if (_chdir(origem.c_str()) == -1) {
		return true;
	}

	return false;


}

Data BackupGenerator::getDataUltimoBackup()
{
	ifstream inputFile;
	string linha, data;
	long nB = 0;
	_chdir(dirAtual.c_str());
	inputFile.open("Relatorio.txt", ios::in);

	if (inputFile) {
		while (!inputFile.eof()) {
			getline(inputFile, linha);
			if (linha.find("Identificação do arquivo") != -1)
				nB++;
		}
		inputFile.close();


		inputFile.open("Relatorio.txt", ios::in);
		inputFile.seekg(0, ios::beg);

		while (!inputFile.eof() && nB) {
			getline(inputFile, linha);
			if (linha.find("Identificação do arquivo") != -1)
				nB--;
		}

		getline(inputFile, linha); // Linha que contém o nome do arquivo
		getline(inputFile, linha); // Linha que contém a data do último backup


		Data date(linha);

		inputFile.close();
		return date;
	}
	else {
		return *(new Data(0, 0, 0));
	}
}

int BackupGenerator::getArquivosESubdiretorios(string origem)
{
	struct _finddata_t arquivo;
	intptr_t hFile;
	struct tm time;

	if (!_chdir(origem.c_str())) {
		hFile = _findfirst("*.*", &arquivo);
		if (_strcmpi(arquivo.name, ".") && _strcmpi(arquivo.name, "..")) {
			_localtime64_s(&time, &arquivo.time_write);
			Data *d = new Data(time.tm_mday, time.tm_mon + 1, time.tm_year + 1900);
			Hora * h = new Hora(time.tm_hour, time.tm_min, time.tm_sec);

			if (arquivo.attrib & _A_SUBDIR) {
				int nArquivos = 0, nDiretorios = 0;
				Diretorio dir;
				dir.setData(*d);
				dir.setHora(*h);
				dir.setTamanho(arquivo.size);
				dir.setNome(arquivo.name);
				string loc = origem + "\\" + dir.getNome();
				dir.setLocalizacao(loc);
				verificaNumeroDiretoriosEArquivos(loc, &nDiretorios, &nArquivos);
				dir.setNumeroDeSubdiretorios(nDiretorios);
				dir.setNumeroDeArquivos(nArquivos);
				diretorios.push_back(dir);
			}
			else {
				Arquivo a;
				a.setData(*d);
				a.setHora(*h);
				a.setTamanho(arquivo.size);
				a.setLocalizacao(origem);
				a.setNome(arquivo.name);
				arquivos.push_back(a);
			}
		}
		while (!_findnext(hFile, &arquivo)) {
			if (strcmp(arquivo.name, ".") && strcmp(arquivo.name, "..")) {
				_localtime64_s(&time, &arquivo.time_write);
				Data *d = new Data(time.tm_mday, time.tm_mon + 1, time.tm_year + 1900);
				Hora * h = new Hora(time.tm_hour, time.tm_min, time.tm_sec);
				if (arquivo.attrib & _A_SUBDIR) {
					int nArquivos = 0, nDiretorios = 0;
					Diretorio dir;
					dir.setData(*d);
					dir.setHora(*h);
					dir.setTamanho(arquivo.size);
					dir.setNome(arquivo.name);
					string loc = origem + "\\" + dir.getNome();
					dir.setLocalizacao(loc);
					verificaNumeroDiretoriosEArquivos(loc, &nDiretorios, &nArquivos);
					dir.setNumeroDeSubdiretorios(nDiretorios);
					dir.setNumeroDeArquivos(nArquivos);
					diretorios.push_back(dir);
				}
				else {
					Arquivo a;
					a.setData(*d);
					a.setHora(*h);
					a.setTamanho(arquivo.size);
					a.setLocalizacao(origem);
					a.setNome(arquivo.name);
					arquivos.push_back(a);
				}
			}
		}
		_findclose(hFile);
		return 1;
	}
	else {
		cout << "Origem :: " << origem << endl;
		cout << "O caminho origem não existe!" << endl;
		return 0;
	}
}

void BackupGenerator::verificaNumeroDiretoriosEArquivos(string origem, int * numeroDir, int * numeroArq)
{
	struct _finddata_t arquivo;
	intptr_t hFile;

	if (!_chdir(origem.c_str())) {
		hFile = _findfirst("*.*", &arquivo);
		if (_strcmpi(arquivo.name, ".") && _strcmpi(arquivo.name, "..")) {
			if (arquivo.attrib & _A_SUBDIR) {
				numeroDir++;
			}
			else {
				numeroArq++;
			}
		}
		while (!_findnext(hFile, &arquivo)) {
			if (strcmp(arquivo.name, ".") && strcmp(arquivo.name, "..")) {
				if (arquivo.attrib & _A_SUBDIR) {
					numeroDir++;
				}
				else {
					numeroArq++;
				}
			}
		}
		_findclose(hFile);
	}
}

bool BackupGenerator::getArquivosRelatorio()
{
	ifstream inputFile;
	string linha;
	long nB = 0;
	string dir = dirAtual + "Relatorio.txt";
	inputFile.open(dir, ios::in);
	inputFile.seekg(0, ios::end);
	streamoff fileSize = inputFile.tellg();

	if (fileSize == 0) {
		return false;
	}
	else {
		if (inputFile) {
			inputFile.seekg(0, ios::beg);
			getline(inputFile, linha);

			while (!inputFile.eof()) {
				getline(inputFile, linha);
				if (linha.find("Arquivos copiados") != -1)
					nB++;
			}


			inputFile.close();
			inputFile.open(dir, ios::in);

			inputFile.seekg(0, ios::beg);
			while (!inputFile.eof() && nB) {
				getline(inputFile, linha);
				if (linha.find("Arquivos copiados") != -1)
					nB--;
			}
			getline(inputFile, linha); // Primeiro arquivo
			while (linha.find("Dados do backup") == -1) {
				if (linha.find("Dados do backup") == -1) {
					string localizacao, nome, d, h, t;

					Data data(d = linha.substr(linha.size() - 21, 10));

					h = linha.substr(linha.size() - 8, linha.size());
					Hora hora(h);

					localizacao = linha.substr(0, linha.find(" - "));
					nome = localizacao.substr(localizacao.find_last_of("\\") + 1, localizacao.size());


					Arquivo arq ;
					arq.setData(data);
					arq.setHora(hora);
					arq.setNome(nome);
					arq.setLocalizacao(localizacao);
					arq.setTamanho(0);

					

					ultimoBackup.push_back(arq);
				}
				getline(inputFile, linha);
			}
			inputFile.close();
		}
		return true;
	}
}

void BackupGenerator::removerArquivosSemCoringa(string coringa)
{
	bool temAsteriscoNoFim = false,
		 temAsteriscoNoInicio = false,
		 temTextoAntesDoPonto = false,
		 temTextoDepoisDoPonto = false;

	if (!_strcmpi(coringa.c_str(), "*.*")) {
		return;
	}

	if (coringa.find_first_of("*") == 0) {
		temAsteriscoNoInicio = true;
		coringa = coringa.substr(1, coringa.size());
	}

	if (coringa.find("*") == coringa.size() - 1) {
		temAsteriscoNoFim = true;
		coringa = coringa.substr(0, coringa.find("*"));
	}

	if (coringa.find(".") != 0) {
		temTextoAntesDoPonto = true;

	}


	if (coringa.find(".") != coringa.size() - 1) {
		temTextoDepoisDoPonto = true;

	}

	string aux = coringa;

	vector<Arquivo>::iterator it;
	for (it = arquivos.begin(); it < arquivos.end();) {
		string tipoArquivo, nome;
		tipoArquivo = it->getNome().substr(it->getNome().find_last_of(".") + 1, it->getNome().size());
		nome = it->getNome().substr(0, it->getNome().find_last_of("."));

		if (temTextoAntesDoPonto && !temAsteriscoNoInicio && !temTextoDepoisDoPonto && temAsteriscoNoFim) {
			coringa = coringa.substr(0, coringa.find("."));
			if (strcmp(nome.c_str(), coringa.c_str())) {
				arquivos.erase(it);
				it = arquivos.begin();
			}
			else {
				it++;
			}
		}

		if (temTextoAntesDoPonto && temAsteriscoNoInicio && !temTextoDepoisDoPonto && temAsteriscoNoFim) {
			coringa = coringa.substr(0, coringa.find("."));
			if (nome.find(coringa) == -1) {
				arquivos.erase(it);
				it = arquivos.begin();
			}
			else {
				it++;
			}
		}

		if (temTextoAntesDoPonto && !temAsteriscoNoInicio && temTextoDepoisDoPonto && temAsteriscoNoFim) {
			string coringa2 = coringa.substr(coringa.find(".") + 1, coringa.size());
			coringa = coringa.substr(0, coringa.find("."));
			if ((strcmp(nome.c_str(), coringa.c_str()) && (tipoArquivo.find(coringa2) == -1))) {
				arquivos.erase(it);
				it = arquivos.begin();
			}
			else {
				it++;
			}
		}

		if (temTextoAntesDoPonto && temAsteriscoNoInicio && temTextoDepoisDoPonto && temAsteriscoNoFim) {
			string coringa2 = coringa.substr(coringa.find(".") + 1, coringa.size());
			coringa = coringa.substr(0, coringa.find("."));

			if (nome.find(coringa) != -1 && (tipoArquivo.find(coringa2) != -1)) {
				it++;
			}
			else {
				arquivos.erase(it);
				it = arquivos.begin();
			}
		}

		if (temTextoAntesDoPonto && temAsteriscoNoInicio && temTextoDepoisDoPonto && !temAsteriscoNoFim) {
			string coringa2 = coringa.substr(coringa.find(".") + 1, coringa.size());
			coringa = coringa.substr(0, coringa.find("."));
			if (nome.find(coringa) == -1 && (strcmp(tipoArquivo.c_str(), coringa2.c_str()))) {
				arquivos.erase(it);
				it = arquivos.begin();
			}
			else {
				it++;
			}
		}

		if (temTextoAntesDoPonto && !temAsteriscoNoInicio && temTextoDepoisDoPonto && !temAsteriscoNoFim) {
			string coringa2 = coringa.substr(coringa.find(".") + 1, coringa.size());
			coringa = coringa.substr(0, coringa.find("."));
			if (strcmp(nome.c_str(), coringa.c_str()) && (strcmp(tipoArquivo.c_str(), coringa2.c_str()))) {
				arquivos.erase(it);
				it = arquivos.begin();
			}
			else {
				it++;
			}
		}

		if (!temTextoAntesDoPonto && temAsteriscoNoInicio && temTextoDepoisDoPonto && temAsteriscoNoFim) {
			coringa = coringa.substr(coringa.find(".") + 1, coringa.size());
			if ((tipoArquivo.find(coringa) == -1)) {
				arquivos.erase(it);
				it = arquivos.begin();
			}
			else {
				it++;
			}
		}

		if (!temTextoAntesDoPonto && temAsteriscoNoInicio && temTextoDepoisDoPonto && !temAsteriscoNoFim) {
			coringa = coringa.substr(coringa.find(".") + 1, coringa.size());
			if (strcmp(tipoArquivo.c_str(), coringa.c_str())) {
				arquivos.erase(it);
				it = arquivos.begin();
			}
			else {
				it++;
			}


		}

		coringa = aux;
	}
}

int BackupGenerator::copiaArquivosOuDiretorios(string origem, string destino, int verificador)
{
	if (arquivos.empty() && diretorios.empty()) {
		cout << "\tNenhum arquivo ou diretório para copiar!!" << endl;
		return 0;
	}
	else {
		if (verificador == 2 || verificador == 3) {
			for (vector<Diretorio>::iterator i = diretorios.begin(); i < diretorios.end(); i++) {

				string dt = destino + "\\" + i->getLocalizacao().substr(origem.size(), i->getLocalizacao().size());
				dt = "\"" + dt + "\"";
				string caminho = "mkdir " + dt;
				system(caminho.c_str());
			}
		}

		string diretorioSaida = "\"" + dirAtual + "saida.txt" + "\"";

		if (verificador == 1 || verificador == 3) {
			for (vector<Arquivo>::iterator i = arquivos.begin(); i != arquivos.end(); i++) {
				string or = i->getLocalizacao() + "\\" + i->getNome();
				string ori = "\"" + or +"\"";
				string ds = destino + "\\" + i->getLocalizacao().substr(origem.size(), i->getLocalizacao().size());
				ds = ds + "\\";
				ds = "\"" + ds + "\"";

				string arq = "copy " + ori + " " + ds +" >> " + diretorioSaida;

				system(arq.c_str());
			}
		}

		if (verificador == 1) {
			diretorios.clear(); // Caso a cópia seja apenas de arquivos, o vector de diretórios é inútil, por isso seus objetos foram apagados.
		}

		diretorioSaida = "ERASE " + diretorioSaida;
		system(diretorioSaida.c_str());


		return 1;
	}


}

void BackupGenerator::gerarRelatorio(Data data, Hora hora, Data data2, Hora hora2)
{
	string relatorio = dirAtual + "Relatorio.txt";
	ofstream outputFile;
	int dataOk = 1, horaOk = 1, vazio = 0;


	outputFile.open(relatorio, ios::app);

	if (ultimoBackup.empty()) {
		if (!getArquivosRelatorio()) {
			vazio = 1;
		}
		else {
			outputFile.seekp(0, ios::end);
		}
	}
	else {
		outputFile.seekp(0, ios::end);
	}

	

	if (outputFile.is_open()) {
		outputFile << "---------- Identificação do arquivo ----------\n";
		outputFile << "Nome: Relatorio.txt\n";
		if (data.getDia() < 10) {
			outputFile << "0" << data.getDia() << "/" << data.getMes() << "/" << data.getAno() << "\n";
			dataOk = 0;
		}
		if (data.getMes() < 10) {
			outputFile << data.getDia() << "/" << "0" << data.getMes() << "/" << data.getAno() << "\n";
			dataOk = 0;
		}
		if (hora.getHora() < 10) {
			outputFile << "0" << hora.getHora() << ":" << hora.getMinuto() << ":" << hora.getSegundo() << "\n";
			dataOk = 0;
		}

		if (hora.getHora() < 10) {
			outputFile << "0" << hora.getHora() << ":" << hora.getMinuto() << ":" << hora.getSegundo() << "\n";
			horaOk = 0;
		}
		if (hora.getMinuto() < 10) {
			outputFile << hora.getHora() << ":" << "0" << hora.getMinuto() << ":" << hora.getSegundo() << "\n";
			horaOk = 0;
		}
		if (hora.getSegundo() < 10) {
			outputFile << hora.getHora() << ":" << hora.getMinuto() << ":" << "0" << hora.getSegundo() << "\n";
			horaOk = 0;
		}

		if (dataOk) {
			outputFile << hora.getHora() << ":" << hora.getMinuto() << ":" << hora.getSegundo() << "\n";
		}
		if (horaOk) {
			outputFile << hora.getHora() << ":" << hora.getMinuto() << ":" << hora.getSegundo() << "\n";
		}


		outputFile << "---------- Arquivos copiados ----------\n";

		for (size_t i = 0; i < arquivos.size(); i++) {
			outputFile << arquivos.at(i).getLocalizacao() << "\\" << arquivos.at(i).getNome() << " - " << arquivos.at(i).getTamanho() << "bytes - " << arquivos.at(i).getData().toString() << " - " << arquivos.at(i).getHora().toString() << "\n";
		}
		outputFile << "\n----------Dados do backup----------\n";
		outputFile << "Início: " << data.toString() << " - " << hora.toString();
		outputFile << "\nTérmino: " << data2.toString() << " - " << hora2.toString();
		outputFile << "\nNº de arquivos copiados: " << arquivos.size();
		outputFile << "\nNº de diretórios copiados: " << diretorios.size();



		if (vazio) {
			outputFile << "\nNº de arquivos novos: " << verificaNovosArquivos();
			outputFile << "\nNº de arquivos atualizados: 0";
			outputFile << "\nNº de arquivos excluídos: 0";
		}
		else {
			outputFile << "\nNº de arquivos novos: " << verificaNovosArquivos();
			outputFile << "\nNº de arquivos atualizados: " << verificaArquivosAtualizados();
			outputFile << "\nNº de arquivos excluídos: " << verificaArquivosExcluidos();
		}
		outputFile << endl;
	}
}

size_t BackupGenerator::verificaNovosArquivos()
{
	size_t n = 0;
	string a1, a2;


	for (size_t i = 0; i < arquivos.size(); i++) {
		a1 = arquivos.at(i).getLocalizacao() + "\\" + arquivos.at(i).getNome();
		for (size_t k = 0; k < ultimoBackup.size(); k++) {
			a2 = ultimoBackup.at(k).getLocalizacao();
			if (!strcmp(a1.c_str(), a2.c_str())) {
				n++;
				break;
			}
		}
	}

	n = arquivos.size() - n;

	return n;
}

size_t BackupGenerator::verificaArquivosExcluidos()
{
	string a1, a2;
	size_t n = 0;
	int achou;


	for (size_t k = 0; k < ultimoBackup.size(); k++) {
		achou = 0;
		a2 = ultimoBackup.at(k).getLocalizacao();
		for (size_t i = 0; i < arquivos.size(); i++) {
			a1 = arquivos.at(i).getLocalizacao() + "\\" + arquivos.at(i).getNome();

			if (!strcmp(a1.c_str(), a2.c_str())) {
				achou = 1;
				break;
			}
		}
		if (!achou)
			n++;
	}

	return n;
}

int BackupGenerator::verificaArquivosAtualizados()
{
	int n = 0;
	string a1, a2;

	for (size_t i = 0; i < arquivos.size(); i++) {
		a1 = arquivos.at(i).getLocalizacao() + "\\" + arquivos.at(i).getNome();
		for (size_t k = 0; k < ultimoBackup.size(); k++) {
			a2 = ultimoBackup.at(k).getLocalizacao();

			if (!strcmp(a1.c_str(), a2.c_str())) {
				if (ultimoBackup.at(k).getData().compareTo(arquivos.at(i).getData()) == 1) {
					n++;
				}
				else {
					if (ultimoBackup.at(k).getData().compareTo(arquivos.at(i).getData()) == 3) {
						if (ultimoBackup.at(k).getHora().compareTo(arquivos.at(i).getHora()) == 1) {
							n++;
						}
					}
				}
			}
		}
	}
	return n;
}

void BackupGenerator::geraArquivoLog(string destino, Data data, Hora hora, Data data2, Hora hora2)
{
	ofstream outputFile;
	int dataOk = 1, horaOk = 1;
	string nome, dest;
	int temBackup = 0;
	int log, aux, i; // variável para verificar se o log será criado apenas no diretório do executável

	if (ultimoBackup.size()) {
		temBackup = 1;
	}


	// Se a função for chamada sem um caminho, o backup é salvo no caminho do executável
	if (!strcmp(destino.c_str(), "")) {
		_chdir(dirAtual.c_str());
		nome = "backup.log";
		outputFile.open(nome.c_str(), ios::app);
		log = 1;
	}
	else { // caso contrário, o arquivo é criado no caminho informado.
		for (i = 0; i < destino.size(); i++)
			if (destino[i] == '\\') {
				aux = i;
			}

		dest = destino.substr(0, aux + 1);
		_chdir(dest.c_str());
		nome = destino.substr(aux + 1, destino.size());
		outputFile.open(nome.c_str(), ios::app);
		log = 0;
	}


	if (outputFile.is_open()) {
		outputFile.seekp(0, ios::end);
		outputFile << "---------- Identificação do arquivo ----------\n";
		outputFile << "Nome: " << nome << "\n";
		if (data.getDia() < 10) {
			outputFile << "0" << data.getDia() << "/" << data.getMes() << "/" << data.getAno() << "\n";
			dataOk = 0;
		}
		if (data.getMes() < 10) {
			outputFile << data.getDia() << "/" << "0" << data.getMes() << "/" << data.getAno() << "\n";
			dataOk = 0;
		}
		if (hora.getHora() < 10) {
			outputFile << "0" << hora.getHora() << ":" << hora.getMinuto() << ":" << hora.getSegundo() << "\n";
			dataOk = 0;
		}

		if (hora.getHora() < 10) {
			outputFile << "0" << hora.getHora() << ":" << hora.getMinuto() << ":" << hora.getSegundo() << "\n";
			horaOk = 0;
		}
		if (hora.getMinuto() < 10) {
			outputFile << hora.getHora() << ":" << "0" << hora.getMinuto() << ":" << hora.getSegundo() << "\n";
			horaOk = 0;
		}
		if (hora.getSegundo() < 10) {
			outputFile << hora.getHora() << ":" << hora.getMinuto() << ":" << "0" << hora.getSegundo() << "\n";
			horaOk = 0;
		}

		if (dataOk) {
			outputFile << hora.getHora() << ":" << hora.getMinuto() << ":" << hora.getSegundo() << "\n";
		}
		if (horaOk) {
			outputFile << hora.getHora() << ":" << hora.getMinuto() << ":" << hora.getSegundo() << "\n";
		}



		outputFile << "---------- Arquivos copiados ----------\n";

		for (size_t i = 0; i < arquivos.size(); i++) {
			outputFile << arquivos.at(i).getLocalizacao() << "\\" << arquivos.at(i).getNome() << " - " << arquivos.at(i).getTamanho() << "bytes - " << arquivos.at(i).getData().toString() << " - " << arquivos.at(i).getHora().toString() << "\n";
		}

		outputFile << "----------Dados do backup----------\n";
		outputFile << "Início: " << data.toString() << " - " << hora.toString();
		outputFile << "\nTérmino: " << data2.toString() << " - " << hora2.toString();
		outputFile << "\nNº de arquivos copiados: " << arquivos.size();
		outputFile << "\nNº de diretórios copiados: " << diretorios.size();

		if (temBackup) {
			outputFile << "\nNº de arquivos novos: " << verificaNovosArquivos();
			outputFile << "\nNº de arquivos atualizados: " << verificaArquivosAtualizados();
			outputFile << "\nNº de arquivos excluídos: " << verificaArquivosExcluidos();
		}
		else {
			outputFile << "\nNº de arquivos novos: " << verificaNovosArquivos();
			outputFile << "\nNº de arquivos atualizados: 0";
			outputFile << "\nNº de arquivos excluídos: 0";
		}

		outputFile << endl;
	}

}

int BackupGenerator::backupS(string origem)
{
	
	if (getArquivosESubdiretorios(origem)) {
		for (size_t i = 0; i < diretorios.size(); i++) {
			getArquivosESubdiretorios(diretorios.at(i).getLocalizacao());
		}
		return 1;
	}
	else {
		return 0;
	}
}

void BackupGenerator::copiaUmArquivo(string origem, string destino)
{
	string arq = "copy " + origem + " " + destino;
	system(arq.c_str());
}

int BackupGenerator::backupM(string origem, Data data)
{
	if (getArquivosESubdiretorios(origem)) {
		for (size_t i = 0; i < diretorios.size(); i++) {
			getArquivosESubdiretorios(diretorios.at(i).getLocalizacao());
		}
	}
	else {
		return 0;
	}

	getArquivosRelatorio();

	


	for (size_t i = 0; i < ultimoBackup.size(); i++) {
		for (vector<Arquivo>::iterator k = arquivos.begin(); k < arquivos.end();k++) {
			string nA = k->getLocalizacao() + "\\" + k->getNome();
			if (!strcmp(ultimoBackup.at(i).getLocalizacao().c_str(), nA.c_str())) {
				int verificaData = data.compareTo(k->getData());
				if (verificaData == 2) {
					arquivos.erase(k);
					k = arquivos.begin();
					break;
				}
				
			}
		}
	}

	/*
		Remove os diretórios que não têm nenhum arquivo modificado após a data fornecida por parâmetro.
	*/
	for (vector<Diretorio>::iterator it = diretorios.begin(); it < diretorios.end(); ) {
		int achou;
		for (size_t i = 0; i < arquivos.size(); i++) {
			achou = 0;
			if (arquivos.at(i).getLocalizacao().find(it->getLocalizacao()) != -1) {
				achou = 1;
				break;
			}
		}
		if (!achou) {
			diretorios.erase(it);
			it = diretorios.begin();
		}
		else {
			it++;
		}

	}
	return 1;
}

int BackupGenerator::backupT(string origem, Hora hora)
{
		if (diretorios.empty() && arquivos.empty()) {
			return 0;
		}

		vector<Diretorio>::iterator it;
		for (it = diretorios.begin(); it < diretorios.end();) {
			int verificaHora = hora.compareTo(it->getHora());
			if (verificaHora == 2) {
				diretorios.erase(it);
				it = diretorios.begin();
			}
			else {
				it++;
			}
		}

		vector<Arquivo>::iterator i;
		for (i = arquivos.begin(); i < arquivos.end();) {
			int verificaHora = hora.compareTo(i->getHora());
			if (verificaHora == 2) {
				arquivos.erase(i);
				i = arquivos.begin();
			}
			else {
				i++;
			}
		}
		return 1;
	
}

int BackupGenerator::backupD(string origem, Data data)
{
	if (diretorios.empty() && arquivos.empty()) {
		return 0;
	}

	for (vector<Diretorio>::iterator it = diretorios.begin(); it != diretorios.end();) {
		int verificaData = data.compareTo(it->getData());
		if (verificaData == 2){
			diretorios.erase(it);
			it = diretorios.begin();
		}
		else {
			it++;
		}
	}

	for (vector<Arquivo>::iterator ite = arquivos.begin(); ite != arquivos.end();) {
		int verificaData2 = data.compareTo(ite->getData());
		if (verificaData2 == 2) {
			arquivos.erase(ite);
			ite = arquivos.begin();
		}
		else {
			ite++;
		}
	}
	return 1;
}