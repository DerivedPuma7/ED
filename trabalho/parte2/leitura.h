#include "subnationalPeriodLifeTablesStruct.h"
#include <iostream>
#include <fstream>

using namespace std;

void print(SubnationalPeriodLifeTables registro){
        cout << registro.id << " | ";
        cout << registro.measure << " | ";
        cout << registro.quantile*100 << "% | ";
        cout << registro.area << " | ";
        cout << registro.sex << " | ";
        cout << registro.age << " | ";
        cout << registro.geography << " | ";
        cout << registro.ethnic << " | ";
        cout << registro.value << endl;
}

void busca(string nomeArquivo){
    cout << endl << nomeArquivo << endl;
    ifstream arquivoLeituraBin(nomeArquivo);

    SubnationalPeriodLifeTables registro;
    arquivoLeituraBin.seekg(0, arquivoLeituraBin.end);
    int quantidadeRegistros = arquivoLeituraBin.tellg()/sizeof(SubnationalPeriodLifeTables);

    if (!arquivoLeituraBin) {
        cerr << "Não foi possível abrir o arquivo" << endl;
        exit(EXIT_FAILURE);
    }

    int contador = 0;
    while (contador < quantidadeRegistros) {
        arquivoLeituraBin.seekg(contador * sizeof(SubnationalPeriodLifeTables));
        arquivoLeituraBin.read((char *)&registro, sizeof(SubnationalPeriodLifeTables));

        print(registro);

        contador++;
    } 
};