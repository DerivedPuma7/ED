#include "subnationalPeriodLifeTablesStruct.h"
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

typedef struct SubnationalPeriodLifeTables Dado;

bool IntercalaBloco(ifstream auxE[2], ofstream auxS[2], int passo, int saida) {
    string linha;
    bool intercalou = false;
    Dado dados[2];
    int pos[2] = {0, 0};

    bool valido[2] = {false, false};

    while ((pos[0] + pos[1]) < 2 * passo) {

        if ((pos[0] < passo) and (not valido[0])) {
            if (auxE[0].read((char *)&dados[0], sizeof(Dado))) {

                valido[0] = true;
            } else {
                pos[0] = passo;
            }
        }

        if ((pos[1] < passo) and (not valido[1])) {
            if (auxE[1].read((char *)&dados[1], sizeof(Dado))) {

                valido[1] = true;
            } else {
                pos[1] = passo;
            }
        }

        if (valido[0] and valido[1]) { // os dois dados sao validos
            intercalou = true;
            // chave primaria e "Length"
            if (strcmp(dados[0].area, dados[1].area) < 0) {
                // chave primaria de posicao 0 e maior
                // grava no arquivo de saida
                auxS[saida].write((const char *)(&dados[0]), sizeof(Dado));
                valido[0] = false;
                pos[0]++;
            } else if (strcmp(dados[0].area, dados[1].area) > 0) {
                // chave primaria de posicao 1 e maior
                // grava no arquivo de saida
                auxS[saida].write((const char *)(&dados[1]), sizeof(Dado));
                valido[1] = false;
                pos[1]++;
            } else { // chaves primarias iguais, compara chave secundaria "Time"
                if (dados[0].value <= dados[1].value) {
                    // chave secundaria de posicao 0 e maior
                    // grava no arquivo de saida
                    auxS[saida].write((const char *)(&dados[0]), sizeof(Dado));
                    valido[0] = false;
                    pos[0]++;
                } else {
                    // chave secundaria de posicao 1 e maior
                    // grava no arquivo de saida
                    auxS[saida].write((const char *)(&dados[1]), sizeof(Dado));
                    valido[1] = false;
                    pos[1]++;
                }
            }
        } else if (valido[0]) {
            intercalou = true;
            auxS[saida].write((const char *)(&dados[0]), sizeof(Dado));
            valido[0] = false;
            pos[0]++;
        } else if (valido[1]) {
            intercalou = true;
            auxS[saida].write((const char *)(&dados[1]), sizeof(Dado));
            valido[1] = false;
            pos[1]++;
        }
    }

    return intercalou;
}

void MergeExterno() {
    ifstream arqEntrada("SubnationalPeriodLifeTables.bin", ios::binary);
    ofstream arqSaida("SubnationalPeriodLifeTablesOrdenado.bin", ios::binary);
    ofstream arqB1("arqB1.dat", ios::binary);
    ofstream arqB2("arqB2.dat", ios::binary);

    if ((not arqB1) or (not arqB2)) {
        cerr << "Arquivos auxiliares nao abriram!" << endl;
        exit(EXIT_FAILURE);
    }

    Dado umDado;

    cout << "Calculando tamanho do arquivo..." << endl << endl;

    arqEntrada.seekg(0, ios::end);

    unsigned long int tamanho = arqEntrada.tellg();
    cout << "Tamanho do arquivo: " << tamanho << endl;
    
    unsigned long int numRegistros = tamanho / sizeof(umDado);
    cout << "Qtd de registros: " << numRegistros << endl << endl;
    
    float fatorCorrecao = 0.5;
    unsigned long metade = (numRegistros / 2.0) + fatorCorrecao;

    arqEntrada.seekg(0, ios::beg);

    cout << "Realizando a ordenação... " << endl << endl;

    for (long int i = 0; i < metade; i++) {
        //cout << "alo";
        arqEntrada.read((char *)&umDado, sizeof(Dado));
        arqB1.write((char *)&umDado, sizeof(Dado));
    }

    for (long int i = metade; i < numRegistros; i++) {
        arqEntrada.read((char *)&umDado, sizeof(Dado));
        arqB2.write((char *)&umDado, sizeof(Dado));
    }

    arqB1.close();
    arqB2.close();
    arqEntrada.close();

    ifstream auxEntrada[2];
    ofstream auxSaida[2];

    long int passo = 1;
    bool ida = true;
    bool ultimo[2];

    while (passo <= numRegistros) {
        if (ida) {
            auxEntrada[0].open("arqB1.dat", ios::binary);
            auxEntrada[1].open("arqB2.dat", ios::binary);
            auxSaida[0].open("arqC1.dat", ios::binary);
            auxSaida[1].open("arqC2.dat", ios::binary);
        } else {
            auxEntrada[0].open("arqC1.dat", ios::binary);
            auxEntrada[1].open("arqC2.dat", ios::binary);
            auxSaida[0].open("arqB1.dat", ios::binary);
            auxSaida[1].open("arqB2.dat", ios::binary);
        }

        if ((not auxEntrada[0]) or (not auxEntrada[1]) or (not auxSaida[0]) or (not auxSaida[1])) {
            cerr << "Arquivos auxiliares nao puderam ser abertos!" << endl;
            exit(EXIT_FAILURE);
        }

        while ((not auxEntrada[0].eof()) and (not auxEntrada[1].eof())) {
            ultimo[0] = IntercalaBloco(auxEntrada, auxSaida, passo, 0);
            ultimo[1] = IntercalaBloco(auxEntrada, auxSaida, passo, 1);
        }

        auxEntrada[0].close();
        auxEntrada[1].close();
        auxSaida[0].close();
        auxSaida[1].close();

        ida = not(ida);
        passo *= 2;
    }

    // Leitura do arquivo auxiliar para o arquivo de saida

    ifstream auxEnt;

    if (ida) {
        if (ultimo[0]) {
            auxEnt.open("arqB1.dat", ios::binary);
        } else {
            auxEnt.open("arqB2.dat", ios::binary);
        }
    } else {
        if (ultimo[0]) {
            auxEnt.open("arqC1.dat", ios::binary);
        } else {
            auxEnt.open("arqC2.dat", ios::binary);
        }
    }
    if (not auxEnt) {
        cerr << "Arquivo auxiliar nao pode ser aberto!" << endl;
        exit(EXIT_FAILURE);
    }

    while (auxEnt.read((char *)(&umDado), sizeof(Dado))) {
        arqSaida.write((char *)(&umDado), sizeof(Dado));
    }

    auxEnt.close();
    remove("arqB1.dat");
    remove("arqB2.dat");
    remove("arqC1.dat");
    remove("arqC2.dat");
}
