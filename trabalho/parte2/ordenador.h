#include "subnationalPeriodLifeTablesStruct.h"
#include "auxiliarOrdenador.h"
#include <cstring>
#include <fstream>
#include <iostream>

using namespace std;

// chave primária: "Area"
int comparaChaves(SubnationalPeriodLifeTables registro1, SubnationalPeriodLifeTables registro2, bool chavePrimaria) {
    if(chavePrimaria) {
        return strcmp(registro1.area, registro2.area);
    }

    if(registro1.value <= registro2.value) {
        return -1;
    }
}

bool intercalaBloco(ifstream auxEntrada[2], ofstream auxSaida[2], int passo, int posicaoSaida) {
    bool intercalou = false;
    bool valido[2] = {false, false};
    int arrayPosicao[2] = {0, 0};

    SubnationalPeriodLifeTables registros[2];

    while ((arrayPosicao[0] + arrayPosicao[1]) < 2 * passo) {

        if ((arrayPosicao[0] < passo) && (!valido[0])) {
            if (auxEntrada[0].read((char *)(&registros[0]), sizeof(SubnationalPeriodLifeTables))) {
                valido[0] = true;
            } else {
                arrayPosicao[0] = passo;
            }
        }

        if ((arrayPosicao[1] < passo) && (!valido[1])) {
            if (auxEntrada[1].read((char *)(&registros[1]), sizeof(SubnationalPeriodLifeTables))) {
                valido[1] = true;
            } else {
                arrayPosicao[1] = passo;
            }
        }

        // os dois dados sao válidos
        if (valido[0] && valido[1]) { 
            intercalou = true;
            bool chavePrimaria = true;
            int comparacao = comparaChaves(registros[0], registros[1], chavePrimaria);
            // chave primária de posição 0 é menor
            if (comparacao < 0) {
                // grava no arquivo de posicaoSaida
                auxSaida[posicaoSaida].write((const char *)(&registros[0]), sizeof(SubnationalPeriodLifeTables));
                valido[0] = false;
                arrayPosicao[0]++;
            } 
            // chave primária de posição 1 é maior
            else if (comparacao > 0) {
                // grava no arquivo de posicaoSaida
                auxSaida[posicaoSaida].write((const char *)(&registros[1]), sizeof(SubnationalPeriodLifeTables));
                valido[1] = false;
                arrayPosicao[1]++;
            } 
            // chaves primárias iguais, compara chave secundária "Value"
            else { 
                bool chavePrimaria = false;
                comparacao = comparaChaves(registros[0], registros[1], chavePrimaria);
                if (comparacao == -1) {
                    // chave secundária de posição 0 é menor
                    // grava no arquivo de posicaoSaida
                    auxSaida[posicaoSaida].write((const char *)(&registros[0]), sizeof(SubnationalPeriodLifeTables));
                    valido[0] = false;
                    arrayPosicao[0]++;
                } else {
                    // chave secundária de posição 0 é maior
                    // grava no arquivo de posicaoSaida
                    auxSaida[posicaoSaida].write((const char *)(&registros[1]), sizeof(SubnationalPeriodLifeTables));
                    valido[1] = false;
                    arrayPosicao[1]++;
                }
            }
        } else if (valido[0]) {
            intercalou = true;
            auxSaida[posicaoSaida].write((const char *)(&registros[0]), sizeof(SubnationalPeriodLifeTables));
            valido[0] = false;
            arrayPosicao[0]++;
        } else if (valido[1]) {
            intercalou = true;
            auxSaida[posicaoSaida].write((const char *)(&registros[1]), sizeof(SubnationalPeriodLifeTables));
            valido[1] = false;
            arrayPosicao[1]++;
        }
    }

    return intercalou;
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
