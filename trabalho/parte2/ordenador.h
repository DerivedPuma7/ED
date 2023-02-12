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

    SubnationalPeriodLifeTables dados[2];

    while ((pos[0] + pos[1]) < 2 * passo) {

        if ((pos[0] < passo) && (!valido[0])) {
            if (auxEntrada[0].read((char *)&dados[0], sizeof(SubnationalPeriodLifeTables))) {

                valido[0] = true;
            } else {
                pos[0] = passo;
            }
        }

        if ((pos[1] < passo) && (!valido[1])) {
            if (auxEntrada[1].read((char *)&dados[1], sizeof(SubnationalPeriodLifeTables))) {

                valido[1] = true;
            } else {
                pos[1] = passo;
            }
        }

        if (valido[0] && valido[1]) { // os dois dados sao validos
            intercalou = true;
            // chave primaria e "Area"
            if (strcmp(dados[0].area, dados[1].area) < 0) {
                // chave primaria de posicao 0 e maior
                // grava no arquivo de posicaoSaida
                auxSaida[posicaoSaida].write((const char *)(&dados[0]), sizeof(SubnationalPeriodLifeTables));
                valido[0] = false;
                pos[0]++;
            } else if (strcmp(dados[0].area, dados[1].area) > 0) {
                // chave primaria de posicao 1 e maior
                // grava no arquivo de posicaoSaida
                auxSaida[posicaoSaida].write((const char *)(&dados[1]), sizeof(SubnationalPeriodLifeTables));
                valido[1] = false;
                pos[1]++;
            } else { // chaves primarias iguais, compara chave secundaria "Value"
                if (dados[0].value <= dados[1].value) {
                    // chave secundaria de posicao 0 e maior
                    // grava no arquivo de posicaoSaida
                    auxSaida[posicaoSaida].write((const char *)(&dados[0]), sizeof(SubnationalPeriodLifeTables));
                    valido[0] = false;
                    pos[0]++;
                } else {
                    // chave secundaria de posicao 1 e maior
                    // grava no arquivo de posicaoSaida
                    auxSaida[posicaoSaida].write((const char *)(&dados[1]), sizeof(SubnationalPeriodLifeTables));
                    valido[1] = false;
                    pos[1]++;
                }
            }
        } else if (valido[0]) {
            intercalou = true;
            auxSaida[posicaoSaida].write((const char *)(&dados[0]), sizeof(SubnationalPeriodLifeTables));
            valido[0] = false;
            pos[0]++;
        } else if (valido[1]) {
            intercalou = true;
            auxSaida[posicaoSaida].write((const char *)(&dados[1]), sizeof(SubnationalPeriodLifeTables));
            valido[1] = false;
            pos[1]++;
        }
    }

    return intercalou;
}

void mergeSortExterno() {
    SubnationalPeriodLifeTables registro;
    ifstream arquivoLeitura("SubnationalPeriodLifeTables.bin", ios::binary);
    ofstream arquivoEscrita("SubnationalPeriodLifeTablesOrdenado.bin", ios::binary);
    ofstream arquivoTemporarioB1("arquivoTemporarioB1.dat", ios::binary);
    ofstream arquivoTemporarioB2("arquivoTemporarioB2.dat", ios::binary);

    if ((!arquivoTemporarioB1)||(!arquivoTemporarioB2)) {
        cerr << "Arquivos auxiliares nao abriram!" << endl;
        exit(EXIT_FAILURE);
    }

    cout << "Calculando tamanho do arquivo..." << endl << endl;

    arquivoLeitura.seekg(0, ios::end);

    unsigned long int tamanhoArquivo = arquivoLeitura.tellg();
    cout << "Tamanho do arquivo: " << tamanhoArquivo << endl;
    
    unsigned long int quantidadeRegistros = tamanhoArquivo / sizeof(registro);
    cout << "Quantidade de registros: " << quantidadeRegistros << endl << endl;
    
    float fatorCorrecao = 0.5;
    unsigned long metade = (quantidadeRegistros / 2.0) + fatorCorrecao;

    arquivoLeitura.seekg(0, ios::beg);

    cout << "Realizando a ordenação... " << endl << endl;

    for (long int i = 0; i < metade; i++) {
        arquivoLeitura.read((char *)&registro, sizeof(SubnationalPeriodLifeTables));
        arquivoTemporarioB1.write((char *)&registro, sizeof(SubnationalPeriodLifeTables));
    }

    for (long int i = metade; i < quantidadeRegistros; i++) {
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

        if ((!auxEntrada[0])||(!auxEntrada[1])||(!auxSaida[0])||(!auxSaida[1])) {
            cerr << "Arquivos auxiliares nao puderam ser abertos!" << endl;
            exit(EXIT_FAILURE);
        }

        while ((!auxEntrada[0].eof()) && (!auxEntrada[1].eof())) {
            ultimo[0] = intercalaBloco(auxEntrada, auxSaida, passo, 0);
            ultimo[1] = intercalaBloco(auxEntrada, auxSaida, passo, 1);
        }

        auxEntrada[0].close();
        auxEntrada[1].close();
        auxSaida[0].close();
        auxSaida[1].close();

        ida = !(ida);
        passo *= 2;
    }

    // Leitura do arquivo auxiliar para o arquivo de posicaoSaida

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
