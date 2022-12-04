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

int main()
{
	ifstream arquivoLeituraCsv("SubnationalPeriodLifeTables.csv");
	ofstream arquivoEscritaBin;

	string linha;
	SubnationalPeriodLifeTables registro;

	arquivoEscritaBin.open("SubnationalPeriodLifeTables.bin", ios::binary | ios::out);

	if (!arquivoLeituraCsv)
	{
		cout << "Não foi possível ler o arquivo" << endl;
		return 0;
	}

	string campo;
	unsigned posFimCampo;

	getline(arquivoLeituraCsv, linha);
	int contador = 0;
	char c[1];
	while (getline(arquivoLeituraCsv, linha))
	{
		// Obtem registro, texto - Measure
		posFimCampo = linha.find(',');
		campo = linha.substr(0, posFimCampo);
		linha.erase(0, posFimCampo + 1);
		strcpy(registro.measure, campo.c_str());

		// Obtem registro, float - Quantile
		posFimCampo = linha.find(',');
		campo = linha.substr(0, posFimCampo);
		linha.erase(0, posFimCampo + 1);
		if (campo[campo.length() - 1] == '%')
		{
			campo = campo.substr(0, campo.length() - 1);
			registro.quantile = stof(campo) / 100;
		}
		else
		{
			registro.quantile = stof(campo);
		}

		// Obtem registro, texto - Area
		posFimCampo = linha.find(',');
		campo = linha.substr(0, posFimCampo);
		linha.erase(0, posFimCampo + 1);
		strcpy(registro.area, campo.c_str());

		// Obtem registro, texto - Sex
		posFimCampo = linha.find(',');
		campo = linha.substr(0, posFimCampo);
		linha.erase(0, posFimCampo + 1);
		strcpy(registro.sex, campo.c_str());

		// Obtem registro, texto - Age
		posFimCampo = linha.find(',');
		campo = linha.substr(0, posFimCampo);
		linha.erase(0, posFimCampo + 1);
		strcpy(registro.age, campo.c_str());

		// Obtem registro, texto - Geography
		posFimCampo = linha.find(',');
		campo = linha.substr(0, posFimCampo);
		linha.erase(0, posFimCampo + 1);
		strcpy(registro.geography, campo.c_str());

		// Obtem registro, texto - Ethnic
		posFimCampo = linha.find(',');
		campo = linha.substr(0, posFimCampo);
		linha.erase(0, posFimCampo + 1);
		strcpy(registro.ethnic, campo.c_str());

		// Obtem registro, texto - Value
		posFimCampo = linha.find(',');
		campo = linha.substr(0, posFimCampo);
		linha.erase(0, posFimCampo + 1);
		registro.value = stof(campo);

		cout << '.';

		arquivoEscritaBin.write((const char *)(&registro), sizeof(SubnationalPeriodLifeTables));
		;
	}

	cout << endl;

	arquivoEscritaBin.close();
	arquivoLeituraCsv.close();

	return 0;
}
