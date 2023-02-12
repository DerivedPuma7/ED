#include <iostream>
#include <fstream>
#include "subnationalPeriodLifeTablesStruct.h"

using namespace std;

long int obterTamanhoArquivo(ifstream &arquivo) {
    return arquivo.tellg();
}

long int obterQuantidadeRegistrosArquivo(long int tamanhoArquivo, SubnationalPeriodLifeTables registro) {
    return tamanhoArquivo / sizeof(registro);
}

void exibirInformacoesArquivo(long int tamanhoArquivo, long int quantidadeRegistros) {
    cout << "Informações sobre o arquivo:" << endl << endl;
    cout << "Tamanho do arquivo: " << tamanhoArquivo << endl;
    cout << "Quantidade de registros: " << quantidadeRegistros << endl << endl;
}

bool verificarFalhaAberturaArquivo(ifstream &arquivo) {
    if ( !arquivo ) return true;
    return false;
}

bool verificarFalhaAberturaArquivo(ofstream &arquivo) {
    if ( !arquivo ) return true;
    return false;
}

void verificarFalhaAberturaArquivos(ifstream &arquivoLeitura, ofstream &arquivoEscrita, ofstream &arquivoTemporarioB1, ofstream &arquivoTemporarioB2) {
    if ( 
        verificarFalhaAberturaArquivo(arquivoLeitura) ||
        verificarFalhaAberturaArquivo(arquivoEscrita)
    ) {
        cerr << "Arquivos principais não abriram corretamente!" << endl;
        exit(EXIT_FAILURE);
    }

    if ( 
        verificarFalhaAberturaArquivo(arquivoTemporarioB1) || 
        verificarFalhaAberturaArquivo(arquivoTemporarioB2)
    ) {
        cerr << "Arquivos auxiliares não abriram corretamente!" << endl;
        exit(EXIT_FAILURE);
    }
}

void tratarBlocosArquivo(long int inicio, long int fim, SubnationalPeriodLifeTables &registro, ifstream &arquivoLeitura, ofstream &arquivoEscrita) {
    for (inicio; inicio < fim; inicio++) {
        arquivoLeitura.read((char *)(&registro), sizeof(SubnationalPeriodLifeTables));
        arquivoEscrita.write((char *)(&registro), sizeof(SubnationalPeriodLifeTables));
    }
}

void fecharArquivo(ofstream &arquivo) {
    arquivo.close();
}

void fecharArquivo(ifstream &arquivo) {
    arquivo.close();
}

void abrirAuxiliarEntrada(ifstream &arquivoAuxiliarEntrada, bool ida, bool ultimo[]) {
    if (ida) {
        if (ultimo[0]) {
            arquivoAuxiliarEntrada.open("arquivoTemporarioB1.dat", ios::binary);
        } else {
            arquivoAuxiliarEntrada.open("arquivoTemporarioB2.dat", ios::binary);
        }
    } else {
        if (ultimo[0]) {
            arquivoAuxiliarEntrada.open("arquivoTemporarioC1.dat", ios::binary);
        } else {
            arquivoAuxiliarEntrada.open("arquivoTemporarioC2.dat", ios::binary);
        }
    }
}