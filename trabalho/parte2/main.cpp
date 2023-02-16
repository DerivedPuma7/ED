/*Identificação do grupo:
alunos = [
    {
        Nome: Gustavo Ribeiro de Figueiredo
        Turma: 14A
    },
    {
        Nome: Cesar Augusto Pires
        Turma: 14A
    }
]
*/
#include "conversor.h"
#include "ordenador.h"
#include "leitura.h"
#include <iostream>

using namespace std;

const string NOME_ARQUIVO_DESORDENADO = "SubnationalPeriodLifeTables.bin";
const string NOME_ARQUIVO_ORDENADO = "SubnationalPeriodLifeTablesOrdenado.bin";

void imprimirDados(bool ordenados) {
    string titulo = "\nDeseja visualizar os dados DESORDENADOS ?\n\n";
    if(ordenados) titulo = "\nDeseja visualizar os dados ORDENADOS ?\n\n";

    cout << titulo;
    cout << "Sim: Digite 1" << endl << "Não: Digite 0" << endl;
    int imprimir;
    cin >> imprimir;

    if(imprimir) {
        if(ordenados) return busca(NOME_ARQUIVO_ORDENADO);
        busca(NOME_ARQUIVO_DESORDENADO);
    }
}

int main() {
    cout << "Realizando conversão do arquivo CSV em binário\n\n";
    converterCSV();

    bool ordenados = false;
    imprimirDados(ordenados);

    cout << "Realizando ordenação do arquivo\n\n";
    mergeSortExterno();

    ordenados = true;
    imprimirDados(ordenados);

    return 0;
}