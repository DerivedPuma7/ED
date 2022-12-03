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

void setMeasure(SubnationalPeriodLifeTables &registro, char caracter, bool &controladorAtributoAtual, bool &controladorProximoAtributo, int &indiceAttr) {
    if(caracter == ',') {
        controladorAtributoAtual = true;
        controladorProximoAtributo = false;
        indiceAttr = 0;
    }
    else {
        registro.measure[indiceAttr] = caracter;
        indiceAttr++;
    }
}

void setQuantile(SubnationalPeriodLifeTables &registro, char caracter, bool &controladorAtributoAtual, bool &controladorProximoAtributo, int &indiceAttr) {
    if(caracter == ',') {
        controladorAtributoAtual = true;
        controladorProximoAtributo = false;
        indiceAttr = 0;
    }
    else {
        registro.quantile[indiceAttr] = caracter;
        indiceAttr++;
    }
}

void setArea(SubnationalPeriodLifeTables &registro, char caracter, bool &controladorAtributoAtual, bool &controladorProximoAtributo, int &indiceAttr) {
    if(caracter == ',') {
        controladorAtributoAtual = true;
        controladorProximoAtributo = false;
        indiceAttr = 0;
    }
    else {
        registro.area[indiceAttr] = caracter;
        indiceAttr++;
    }
}

void setSex(SubnationalPeriodLifeTables &registro, char caracter, bool &controladorAtributoAtual, bool &controladorProximoAtributo, int &indiceAttr) {
    if(caracter == ',') {
        controladorAtributoAtual = true;
        controladorProximoAtributo = false;
        indiceAttr = 0;
    }
    else {
        registro.sex[indiceAttr] = caracter;
        indiceAttr++;
    }
}

void setAge(SubnationalPeriodLifeTables &registro, char caracter, bool &controladorAtributoAtual, bool &controladorProximoAtributo, int &indiceAttr) {
    if(caracter == ',') {
        controladorAtributoAtual = true;
        controladorProximoAtributo = false;
        indiceAttr = 0;
    }
    else {
        registro.age[indiceAttr] = caracter;
        indiceAttr++;
    }
}

void setGeography(SubnationalPeriodLifeTables &registro, char caracter, bool &controladorAtributoAtual, bool &controladorProximoAtributo, int &indiceAttr) {
    if(caracter == ',') {
        controladorAtributoAtual = true;
        controladorProximoAtributo = false;
        indiceAttr = 0;
    }
    else {
        registro.geography[indiceAttr] = caracter;
        indiceAttr++;
    }
}

void setEthnic(SubnationalPeriodLifeTables &registro, char caracter, bool &controladorAtributoAtual, bool &controladorProximoAtributo, int &indiceAttr) {
    if(caracter == ',') {
        controladorAtributoAtual = true;
        controladorProximoAtributo = false;
        indiceAttr = 0;
    }
    else {
        registro.ethnic[indiceAttr] = caracter;
        indiceAttr++;
    }
}

void setValue(SubnationalPeriodLifeTables &registro, char caracter, bool &controladorAtributoAtual, int &indiceAttr) {
    if(caracter == ',') {
        controladorAtributoAtual = true;
        indiceAttr = 0;
    }
    else {
        registro.value[indiceAttr] = caracter;
        indiceAttr++;
    }
}

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
            setMeasure(registro, dados[i], measureCompleto, quantileCompleto, indiceAttr);
        }
        else if(!quantileCompleto) {
            setQuantile(registro, dados[i], quantileCompleto, areaCompleto, indiceAttr);
        }
        else if(!areaCompleto) {
            setArea(registro, dados[i], areaCompleto, sexCompleto, indiceAttr);
        }
        else if(!sexCompleto) {
            setSex(registro, dados[i], sexCompleto, agecompleto, indiceAttr);
        }
        else if(!agecompleto) {
            setAge(registro, dados[i], agecompleto, geographyCompleto, indiceAttr);
        }
        else if(!geographyCompleto) {
            setGeography(registro, dados[i], geographyCompleto, ethnicCompleto, indiceAttr);
        }
        else if(!ethnicCompleto) {
            setEthnic(registro, dados[i], ethnicCompleto, valueCompleto, indiceAttr);
        }
        else if(!valueCompleto) {
            setValue(registro, dados[i], valueCompleto, indiceAttr);
        }
    }
}

int main(){
	ifstream arquivoLeituraCsv("baseDados.csv");
	ofstream arquivoEscritaBin;
	
	string lixo;
    string dadosLeitura;
	SubnationalPeriodLifeTables registro;
	
	arquivoEscritaBin.open("SubnationalPeriodLifeTables.bin", ios::binary | ios::out);
	
	if(!arquivoLeituraCsv) {
		cout << "Não foi possível ler o arquivo" << endl;
		return 0;
	}

    char c[1];
	int contador = 0; 

	getline(arquivoLeituraCsv, lixo);
    while ( arquivoLeituraCsv.read(c,0) ) {
        getline(arquivoLeituraCsv, dadosLeitura);
        tratarRegistro(registro, dadosLeitura);

		arquivoEscritaBin.write((const char *) (&registro), sizeof(SubnationalPeriodLifeTables));

        cout << contador << endl;
		contador++;
	}

	arquivoEscritaBin.close();
	arquivoLeituraCsv.close();

	return 0;
}
