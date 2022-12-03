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

struct SubnationalPeriodLifeTables
{
	char measure[2]; 
	char quantile[5]; 
	char area[30]; 
	char sex[20]; 
	char age[20]; 
	char geography[40]; 
	char ethnic[20]; 
	char value[10]; 
};

void tratarRegistro(SubnationalPeriodLifeTables &registro, string dados) {
    int tamanhoStringDados = dados.length() - 1;
    int indiceAtributoStruct = 0;

    bool measureCompleto = false;
    bool quantileCompleto = true;
    bool areaCompleto = true;
    bool sexCompleto = true;
    bool agecompleto = true;
    bool geographyCompleto = true;
    bool ethnicCompleto = true;
    bool valueCompleto = true;

    int indiceAttr = 0;

    for(int i = 0; i < tamanhoStringDados; i++) {
        if(!measureCompleto) {
            if(dados[i] == ',') {
                measureCompleto = true;
                quantileCompleto = false;
                indiceAttr = 0;
            }
            else {
                registro.measure[indiceAttr] = dados[i];
                indiceAttr++;
            }
        }
        else if(!quantileCompleto) {
            if(dados[i] == ',') {
                quantileCompleto = true;
                areaCompleto = false;
                indiceAttr = 0;
            }
            else {
                registro.quantile[indiceAttr] = dados[i];
                indiceAttr++;
            }
        }
        else if(!areaCompleto) {
            if(dados[i] == ',') {
                areaCompleto = true;
                sexCompleto = false;
                indiceAttr = 0;
            }
            else {
                registro.area[indiceAttr] = dados[i];
                indiceAttr++;
            }
        }
        else if(!sexCompleto) {
            if(dados[i] == ',') {
                sexCompleto = true;
                agecompleto = false;
                indiceAttr = 0;
            }
            else {
                registro.sex[indiceAttr] = dados[i];
                indiceAttr++;
            }
        }
        else if(!agecompleto) {
            if(dados[i] == ',') {
                agecompleto = true;
                geographyCompleto = false;
                indiceAttr = 0;
            }
            else {
                registro.age[indiceAttr] = dados[i];
                indiceAttr++;
            }
        }
        else if(!geographyCompleto) {
            if(dados[i] == ',') {
                geographyCompleto = true;
                ethnicCompleto = false;
                indiceAttr = 0;
            }
            else {
                registro.geography[indiceAttr] = dados[i];
                indiceAttr++;
            }
        }
        else if(!ethnicCompleto) {
            if(dados[i] == ',') {
                ethnicCompleto = true;
                valueCompleto = false;
                indiceAttr = 0;
            }
            else {
                registro.ethnic[indiceAttr] = dados[i];
                indiceAttr++;
            }
        }
        else if(!valueCompleto) {
            if(dados[i] == ',') {
                valueCompleto = true;
                indiceAttr = 0;
            }
            else {
                registro.value[indiceAttr] = dados[i];
                indiceAttr++;
            }
        }
    }
}

int main(){
	ifstream arquivoLeituraCsv("baseDados.csv");
	ofstream arquivoEscritaBin;
	
	string lixo;
    string dados;
	SubnationalPeriodLifeTables registro;
	
	arquivoEscritaBin.open("SubnationalPeriodLifeTables.bin", ios::binary | ios::out);
	
	if(!arquivoLeituraCsv) {
		cout << "Não foi possível ler o arquivo" << endl;
		return 0;
	}
    char c[1];

	getline(arquivoLeituraCsv, lixo);
	int contador = 0; 

    while ( arquivoLeituraCsv.read(c,0) ) {

        getline(arquivoLeituraCsv, dados);
        tratarRegistro(registro, dados);

		arquivoEscritaBin.write((const char *) (&registro), sizeof(SubnationalPeriodLifeTables));
        cout << contador << endl;
		contador++;
	}

	arquivoEscritaBin.close();
	arquivoLeituraCsv.close();

	return 0;
}
