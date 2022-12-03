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
#include <fstream>

using namespace std;

struct arquivoCSV
{
	float campo1;
	int campo2;
	char campo3[250];
	float campo4;
	char campo5[250];
	int campo6;
};

int main(){
	ifstream arq("meus_dados.csv");
	ofstream binFile;
	
	string lixo;
	arquivoCSV arquivo;
	
	binFile.open("meus_dados.bin", ios::binary | ios::out);
	
	if(!arq) {
		cout << "Não foi possível ler o arquivo" << endl;
		return 0;
	}

	getline(arq, lixo);
	while ( arq >> arquivo.campo1 ) {
		arq.ignore(256, ';');
		arq >> arquivo.campo2;
		
		arq.ignore(256, ';');
		arq.getline(arquivo.campo3, 256, ';');
		
		arq >> arquivo.campo4;
		
		arq.ignore(256, ';');
		arq.getline(arquivo.campo5, 256, ';');

		arq >> arquivo.campo6;
		
		binFile.write((const char *) (&arquivo), sizeof(arquivo));
	}

	binFile.close();
	arq.close();

	return 0;
}
