/*Identificação do grupo:
alunos = {
    1:{
        Nome: Gustavo Ribeiro de Figueiredo
        Turma: 14A
    },
    2:{
        Nome: Cesar Augusto Pires
        Turma: 14A
    }
}
*/
#include "conversor.h"
#include "ordenador.h"
#include <iostream>

using namespace std;

int main() {
    cout << "Realizando conversão do arquivo CSV em binário\n\n";
    converterCSV();

    cout << "Realizando ordenação do arquivo\n\n";
    mergeSortExterno();

    return 0;
}