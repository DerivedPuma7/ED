#include "subnationalPeriodLifeTablesStruct.h"
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

bool intercalaBloco(ifstream auxEntrada[2], ofstream auxSaida[2], int passo, int posicaoSaida) {
    bool intercalou = false;
    bool valido[2] = {false, false};
    int pos[2] = {0, 0};

    SubnationalPeriodLifeTables registros[2];

    while ((pos[0] + pos[1]) < 2 * passo) {

        if ((pos[0] < passo) && (!valido[0])) {
            if (auxEntrada[0].read((char *)(&registros[0]), sizeof(SubnationalPeriodLifeTables))) {
                valido[0] = true;
            } else {
                pos[0] = passo;
            }
        }

        if ((pos[1] < passo) && (!valido[1])) {
            if (auxEntrada[1].read((char *)(&registros[1]), sizeof(SubnationalPeriodLifeTables))) {
                valido[1] = true;
            } else {
                pos[1] = passo;
            }
        }

        // os dois dados sao válidos
        if (valido[0] && valido[1]) { 
            intercalou = true;
            // chave primária: "Area"
            // chave primária de posição 0 é menor
            if (strcmp(registros[0].area, registros[1].area) < 0) {
                // grava no arquivo de posicaoSaida
                auxSaida[posicaoSaida].write((const char *)(&registros[0]), sizeof(SubnationalPeriodLifeTables));
                valido[0] = false;
                pos[0]++;
            } 
            // chave primária de posição 1 é maior
            else if (strcmp(registros[0].area, registros[1].area) > 0) {
                // grava no arquivo de posicaoSaida
                auxSaida[posicaoSaida].write((const char *)(&registros[1]), sizeof(SubnationalPeriodLifeTables));
                valido[1] = false;
                pos[1]++;
            } 
            // chaves primárias iguais, compara chave secundária "Value"
            else { 
                if (registros[0].value <= registros[1].value) {
                    // chave secundária de posição 0 é maior
                    // grava no arquivo de posicaoSaida
                    auxSaida[posicaoSaida].write((const char *)(&registros[0]), sizeof(SubnationalPeriodLifeTables));
                    valido[0] = false;
                    pos[0]++;
                } else {
                    // chave secundária de posição 1 é maior
                    // grava no arquivo de posicaoSaida
                    auxSaida[posicaoSaida].write((const char *)(&registros[1]), sizeof(SubnationalPeriodLifeTables));
                    valido[1] = false;
                    pos[1]++;
                }
            }
        } else if (valido[0]) {
            intercalou = true;
            auxSaida[posicaoSaida].write((const char *)(&registros[0]), sizeof(SubnationalPeriodLifeTables));
            valido[0] = false;
            pos[0]++;
        } else if (valido[1]) {
            intercalou = true;
            auxSaida[posicaoSaida].write((const char *)(&registros[1]), sizeof(SubnationalPeriodLifeTables));
            valido[1] = false;
            pos[1]++;
        }
    }

    return intercalou;
}

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

void mergeSortExterno() {
    ifstream arquivoLeitura("SubnationalPeriodLifeTables.bin", ios::binary);
    ofstream arquivoEscrita("SubnationalPeriodLifeTablesOrdenado.bin", ios::binary);
    ofstream arquivoTemporarioB1("arquivoTemporarioB1.dat", ios::binary);
    ofstream arquivoTemporarioB2("arquivoTemporarioB2.dat", ios::binary);
    verificarFalhaAberturaArquivos(arquivoLeitura, arquivoEscrita, arquivoTemporarioB1, arquivoTemporarioB2);

    arquivoLeitura.seekg(0, ios::end);

    SubnationalPeriodLifeTables registro;
    long int tamanhoArquivo = obterTamanhoArquivo(arquivoLeitura);
    long int quantidadeRegistros = obterQuantidadeRegistrosArquivo(tamanhoArquivo, registro);
    exibirInformacoesArquivo(tamanhoArquivo, quantidadeRegistros);

    arquivoLeitura.seekg(0, ios::beg);

    cout << "Iniciando a ordenação!!" << endl << endl;

    float fatorCorrecao = 0.5;
    long metade = (quantidadeRegistros / 2.0) + fatorCorrecao;
    long int inicio = 0;
    tratarBlocosArquivo(inicio, metade, registro, arquivoLeitura, arquivoTemporarioB1);
    tratarBlocosArquivo(metade, quantidadeRegistros, registro, arquivoLeitura, arquivoTemporarioB2);

    fecharArquivo(arquivoTemporarioB1);
    fecharArquivo(arquivoTemporarioB2);
    fecharArquivo(arquivoLeitura);

    ifstream auxEntrada[2];
    ofstream auxSaida[2];

    long int passo = 1;
    bool ida = true;
    bool ultimo[2];

    while (passo <= quantidadeRegistros) {
        if (ida) {
            auxEntrada[0].open("arquivoTemporarioB1.dat", ios::binary);
            auxEntrada[1].open("arquivoTemporarioB2.dat", ios::binary);
            auxSaida[0].open("arquivoTemporarioC1.dat", ios::binary);
            auxSaida[1].open("arquivoTemporarioC2.dat", ios::binary);
        } else {
            auxEntrada[0].open("arquivoTemporarioC1.dat", ios::binary);
            auxEntrada[1].open("arquivoTemporarioC2.dat", ios::binary);
            auxSaida[0].open("arquivoTemporarioB1.dat", ios::binary);
            auxSaida[1].open("arquivoTemporarioB2.dat", ios::binary);
        }

        if (
            verificarFalhaAberturaArquivo(auxEntrada[0]) ||
            verificarFalhaAberturaArquivo(auxEntrada[1]) ||
            verificarFalhaAberturaArquivo(auxSaida[0]) ||
            verificarFalhaAberturaArquivo(auxSaida[1])
        ) {
            cerr << "Arquivos auxiliares nao puderam ser abertos!" << endl;
            exit(EXIT_FAILURE);
        }

        while ((!auxEntrada[0].eof()) && (!auxEntrada[1].eof())) {
            ultimo[0] = intercalaBloco(auxEntrada, auxSaida, passo, 0);
            ultimo[1] = intercalaBloco(auxEntrada, auxSaida, passo, 1);
        }

        fecharArquivo(auxEntrada[0]);
        fecharArquivo(auxEntrada[1]);
        fecharArquivo(auxSaida[0]);
        fecharArquivo(auxSaida[1]);

        ida = !(ida);
        passo *= 2;
    }

    ifstream auxEnt;
    abrirAuxiliarEntrada(auxEnt, ida, ultimo);
    if(verificarFalhaAberturaArquivo(auxEnt)) {
        cerr << "Arquivo auxiliar nao pode ser aberto!" << endl;
        exit(EXIT_FAILURE);
    }

    while (auxEnt.read((char *)(&registro), sizeof(SubnationalPeriodLifeTables))) {
        arquivoEscrita.write((char *)(&registro), sizeof(SubnationalPeriodLifeTables));
    }

    cout << "Ordenação Finalizada!!" << endl;

    fecharArquivo(auxEnt);
    remove("arquivoTemporarioB1.dat");
    remove("arquivoTemporarioB2.dat");
    remove("arquivoTemporarioC1.dat");
    remove("arquivoTemporarioC2.dat");
}
