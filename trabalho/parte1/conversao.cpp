/*Identificação do grupo:
alunos = {
	1:{
		Nome: Gustavo Ribeiro de Figueiredo
		Turma: 14A
	},
	2:{
		Nome: Cesar Augusto Pires
		Turma: 14A
	},
	3:{
		Nome: Caio César da Rocha
		Turma: 14C
	}
}
*/

#include <iostream>
#include <cstring>
#include <fstream>
#include <cstdlib>
#include <string>

using namespace std;

struct SubnationalPeriodLifeTables
{
	char measure[256];
	float quantile;
	char area[256];
	char sex[255];
	char age[255];
	char geography[255];
	char ethnic[255];
	float value;
};

class LinhaCsv {
	public:
		string atributoLinha;
		string restanteLinha;
		void tratarLinha(string linhaCsv);
		float tratarPorcentagem(string atributoLinha);
};

void LinhaCsv::tratarLinha(string linhaCsv) {
	string campo;
	unsigned posFimCampo;

	posFimCampo = linhaCsv.find(',');
	campo = linhaCsv.substr(0, posFimCampo);
	linhaCsv.erase(0, posFimCampo + 1);

	this->atributoLinha = campo;
	this->restanteLinha = linhaCsv;
}

float LinhaCsv::tratarPorcentagem(string atributoLinha) {
	int ultimaPosicaoAtributo = atributoLinha.length() - 1;
	float atributoRetorno;

	if (atributoLinha[ultimaPosicaoAtributo] == '%') {
		atributoLinha = atributoLinha.substr(0, ultimaPosicaoAtributo);
		atributoRetorno = stof(atributoLinha) / 100;
	}
	else {
		atributoRetorno = stof(atributoLinha);
	}

	return atributoRetorno;
}

int main()
{
	ifstream arquivoLeituraCsv("SubnationalPeriodLifeTables.csv");
	
	ofstream arquivoEscritaBin;
	arquivoEscritaBin.open("SubnationalPeriodLifeTables.bin", ios::binary | ios::out);

	SubnationalPeriodLifeTables registro;
	LinhaCsv linhaCsv;

	if (!arquivoLeituraCsv)
	{
		cout << "Não foi possível ler o arquivo" << endl;
		return 0;
	}

	getline(arquivoLeituraCsv, linhaCsv.restanteLinha);
	while (getline(arquivoLeituraCsv, linhaCsv.restanteLinha))
	{
		linhaCsv.tratarLinha(linhaCsv.restanteLinha);
		strcpy(registro.measure, linhaCsv.atributoLinha.c_str());

		linhaCsv.tratarLinha(linhaCsv.restanteLinha);
		registro.quantile = linhaCsv.tratarPorcentagem(linhaCsv.atributoLinha);

		linhaCsv.tratarLinha(linhaCsv.restanteLinha);
		strcpy(registro.area, linhaCsv.atributoLinha.c_str());

		linhaCsv.tratarLinha(linhaCsv.restanteLinha);
		strcpy(registro.sex, linhaCsv.atributoLinha.c_str());

		linhaCsv.tratarLinha(linhaCsv.restanteLinha);
		strcpy(registro.age, linhaCsv.atributoLinha.c_str());

		linhaCsv.tratarLinha(linhaCsv.restanteLinha);
		strcpy(registro.geography, linhaCsv.atributoLinha.c_str());

		linhaCsv.tratarLinha(linhaCsv.restanteLinha);
		strcpy(registro.ethnic, linhaCsv.atributoLinha.c_str());

		linhaCsv.tratarLinha(linhaCsv.restanteLinha);
		registro.value = stof(linhaCsv.atributoLinha);

		cout << '.';

		arquivoEscritaBin.write((const char *)(&registro), sizeof(SubnationalPeriodLifeTables));
	}

	cout << endl;

	arquivoEscritaBin.close();
	arquivoLeituraCsv.close();

	return 0;
}
