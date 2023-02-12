#include "subnationalPeriodLifeTablesStruct.h"
#include <iostream>
#include <cstring>
#include <fstream>
#include <cstdlib>
#include <string>

using namespace std;

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

void converterCSV() {
    ifstream arquivoLeituraCsv("SubnationalPeriodLifeTables.csv");
    
    ofstream arquivoEscritaBin;
    arquivoEscritaBin.open("SubnationalPeriodLifeTables.bin", ios::binary | ios::out);

    SubnationalPeriodLifeTables registro;
    LinhaCsv linhaCsv;

    if (!arquivoLeituraCsv) {
        cerr << "Não foi possível ler o arquivo" << endl;
        exit(EXIT_FAILURE);
    }

    getline(arquivoLeituraCsv, linhaCsv.restanteLinha);
    int contador = 1;
    while (getline(arquivoLeituraCsv, linhaCsv.restanteLinha)) {
        registro.id = contador;

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

        arquivoEscritaBin.write((const char *)(&registro), sizeof(SubnationalPeriodLifeTables));
        cout << '.';
        contador++;
    }

    cout << endl;

    arquivoEscritaBin.close();
    arquivoLeituraCsv.close();

}
