#include "subnationalPeriodLifeTablesStruct.h"
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

typedef struct SubnationalPeriodLifeTables;

bool IntercalaBloco(ifstream auxE[2], ofstream auxS[2], int passo, int saida) {
    string linha;
    bool intercalou = false;
    SubnationalPeriodLifeTables dados[2];
    int pos[2] = {0, 0};

    bool valido[2] = {false, false};

    while ((pos[0] + pos[1]) < 2 * passo) {

        if ((pos[0] < passo) && (!valido[0])) {
            if (auxE[0].read((char *)&dados[0], sizeof(SubnationalPeriodLifeTables))) {

                valido[0] = true;
            } else {
                pos[0] = passo;
            }
        }

        if ((pos[1] < passo) && (!valido[1])) {
            if (auxE[1].read((char *)&dados[1], sizeof(SubnationalPeriodLifeTables))) {

                valido[1] = true;
            } else {
                pos[1] = passo;
            }
        }

        if (valido[0] && valido[1]) { // os dois dados sao validos
            intercalou = true;
            // chave primaria e "Length"
            if (strcmp(dados[0].area, dados[1].area) < 0) {
                // chave primaria de posicao 0 e maior
                // grava no arquivo de saida
                auxS[saida].write((const char *)(&dados[0]), sizeof(SubnationalPeriodLifeTables));
                valido[0] = false;
                pos[0]++;
            } else if (strcmp(dados[0].area, dados[1].area) > 0) {
                // chave primaria de posicao 1 e maior
                // grava no arquivo de saida
                auxS[saida].write((const char *)(&dados[1]), sizeof(SubnationalPeriodLifeTables));
                valido[1] = false;
                pos[1]++;
            } else { // chaves primarias iguais, compara chave secundaria "Time"
                if (dados[0].value <= dados[1].value) {
                    // chave secundaria de posicao 0 e maior
                    // grava no arquivo de saida
                    auxS[saida].write((const char *)(&dados[0]), sizeof(SubnationalPeriodLifeTables));
                    valido[0] = false;
                    pos[0]++;
                } else {
                    // chave secundaria de posicao 1 e maior
                    // grava no arquivo de saida
                    auxS[saida].write((const char *)(&dados[1]), sizeof(SubnationalPeriodLifeTables));
                    valido[1] = false;
                    pos[1]++;
                }
            }
        } else if (valido[0]) {
            intercalou = true;
            auxS[saida].write((const char *)(&dados[0]), sizeof(SubnationalPeriodLifeTables));
            valido[0] = false;
            pos[0]++;
        } else if (valido[1]) {
            intercalou = true;
            auxS[saida].write((const char *)(&dados[1]), sizeof(SubnationalPeriodLifeTables));
            valido[1] = false;
            pos[1]++;
        }
    }

    return intercalou;
}

void MergeSortExterno() {
    ifstream arquivoLeitura("SubnationalPeriodLifeTables.bin", ios::binary);
    ofstream arquivoEscrita("SubnationalPeriodLifeTablesOrdenado.bin", ios::binary);
    ofstream arquivoTemporarioB1("arquivoTemporarioB1.dat", ios::binary);
    ofstream arquivoTemporarioB2("arquivoTemporarioB2.dat", ios::binary);

    if ((!arquivoTemporarioB1)||(!arquivoTemporarioB2)) {
        cerr << "Arquivos auxiliares nao abriram!" << endl;
        exit(EXIT_FAILURE);
    }

    SubnationalPeriodLifeTables registro;

    cout << "Calculando tamanho do arquivo..." << endl << endl;

    arquivoLeitura.seekg(0, ios::end);

    unsigned long int tamanho = arquivoLeitura.tellg();
    cout << "Tamanho do arquivo: " << tamanho << endl;
    
    unsigned long int numRegistros = tamanho / sizeof(registro);
    cout << "Quantidade de registros: " << numRegistros << endl << endl;
    
    float fatorCorrecao = 0.5;
    unsigned long metade = (numRegistros / 2.0) + fatorCorrecao;

    arquivoLeitura.seekg(0, ios::beg);

    cout << "Realizando a ordenação... " << endl << endl;

    for (long int i = 0; i < metade; i++) {
        //cout << "alo";
        arquivoLeitura.read((char *)&registro, sizeof(SubnationalPeriodLifeTables));
        arquivoTemporarioB1.write((char *)&registro, sizeof(SubnationalPeriodLifeTables));
    }

    for (long int i = metade; i < numRegistros; i++) {
        arquivoLeitura.read((char *)&registro, sizeof(SubnationalPeriodLifeTables));
        arquivoTemporarioB2.write((char *)&registro, sizeof(SubnationalPeriodLifeTables));
    }

    arquivoTemporarioB1.close();
    arquivoTemporarioB2.close();
    arquivoLeitura.close();

    ifstream auxEntrada[2];
    ofstream auxSaida[2];

    long int passo = 1;
    bool ida = true;
    bool ultimo[2];

    while (passo <= numRegistros) {
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

        if ((!auxEntrada[0])||(!auxEntrada[1])||(!auxSaida[0])||(!auxSaida[1])) {
            cerr << "Arquivos auxiliares nao puderam ser abertos!" << endl;
            exit(EXIT_FAILURE);
        }

        while ((!auxEntrada[0].eof()) && (!auxEntrada[1].eof())) {
            ultimo[0] = IntercalaBloco(auxEntrada, auxSaida, passo, 0);
            ultimo[1] = IntercalaBloco(auxEntrada, auxSaida, passo, 1);
        }

        auxEntrada[0].close();
        auxEntrada[1].close();
        auxSaida[0].close();
        auxSaida[1].close();

        ida = !(ida);
        passo *= 2;
    }

    // Leitura do arquivo auxiliar para o arquivo de saida

    ifstream auxEnt;

    if (ida) {
        if (ultimo[0]) {
            auxEnt.open("arquivoTemporarioB1.dat", ios::binary);
        } else {
            auxEnt.open("arquivoTemporarioB2.dat", ios::binary);
        }
    } else {
        if (ultimo[0]) {
            auxEnt.open("arquivoTemporarioC1.dat", ios::binary);
        } else {
            auxEnt.open("arquivoTemporarioC2.dat", ios::binary);
        }
    }
    if (!auxEnt) {
        cerr << "Arquivo auxiliar nao pode ser aberto!" << endl;
        exit(EXIT_FAILURE);
    }

    while (auxEnt.read((char *)(&registro), sizeof(SubnationalPeriodLifeTables))) {
        arquivoEscrita.write((char *)(&registro), sizeof(SubnationalPeriodLifeTables));
    }

    auxEnt.close();
    remove("arquivoTemporarioB1.dat");
    remove("arquivoTemporarioB2.dat");
    remove("arquivoTemporarioC1.dat");
    remove("arquivoTemporarioC2.dat");
}
