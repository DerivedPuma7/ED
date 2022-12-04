#include <iostream>
#include <cstring>
#include <fstream>
#include <cstdlib>
#include <string>

using namespace std;

struct SubnationalPeriodLifeTables
{
    char measure[256];
    float quantile;
    char area[256];
    char sex[255];
    char age[255];
    char geography[255];
    char ethnic[255];
    float value;
};

class SubnationalPeriodLifeTablesOperacoes {
    public:
        void busca();
        void busca(int comeco, int fim);
        void print(SubnationalPeriodLifeTables registro);
};

void SubnationalPeriodLifeTablesOperacoes::print(SubnationalPeriodLifeTables registro){
        cout << registro.measure << " | ";
        cout << registro.quantile*100 << "% | ";
        cout << registro.area << " | ";
        cout << registro.sex << " | ";
        cout << registro.age << " | ";
        cout << registro.geography << " | ";
        cout << registro.ethnic << " | ";
        cout << registro.value << endl;
}

void SubnationalPeriodLifeTablesOperacoes::busca(){
    ifstream arquivoLeituraBin("SubnationalPeriodLifeTables.bin");

    SubnationalPeriodLifeTables registro;

    if (!arquivoLeituraBin)
    {
        cout << "Não foi possível abrir o arquivo" << endl;
    }

    int contador = 0;
    do {
        arquivoLeituraBin.seekg(contador * sizeof(SubnationalPeriodLifeTables));
        arquivoLeituraBin.read((char *)&registro, sizeof(SubnationalPeriodLifeTables));

        this->print(registro);

        contador++;
    } while (arquivoLeituraBin); 
};

void SubnationalPeriodLifeTablesOperacoes::busca(int comeco, int fim){
    ifstream arquivoLeituraBin("SubnationalPeriodLifeTables.bin");

    SubnationalPeriodLifeTables registro;

    if (!arquivoLeituraBin)
    {
        cout << "Não foi possível abrir o arquivo" << endl;
    }

    while (comeco <= fim) {
        arquivoLeituraBin.seekg(comeco * sizeof(SubnationalPeriodLifeTables));
        arquivoLeituraBin.read((char *)&registro, sizeof(SubnationalPeriodLifeTables));

        this->print(registro);
        
        comeco++;
    }
};

char menuPrincipal(){
    char opcao;
    system("clear||cls");
    cout << "================ O que você deseja ? ================" << endl;
    cout << "(a) Imprimir todos os registros" << endl;
    cout << "(b) Imprimir registros de posição x a y" << endl;
    cout << "(c) Trocar posição de dois registros" << endl;
    cout << "(d) Alterar dados de uma posição" << endl;
    cout << "(e) Adicionar registro em uma posição" << endl;
    cout << "(f) Sair" << endl;
    cout << "Opção: ";
    cin >> opcao;
    return opcao;
};

void retornarOuSair(){
    char garbage;
    cout << "Precione qualquer tecla para voltar ao menu principal!" << endl;
    cin >> garbage;
};

int main()
{
    char opcao;
    SubnationalPeriodLifeTablesOperacoes operacoes;

    do {
        opcao = menuPrincipal();
        switch (opcao){
            case 'a':
                system("clear||cls");
                cout << "================ Imprimir todos os registros ================" << endl;
                operacoes.busca();
                retornarOuSair();
                break;
            case 'b':
                system("clear||cls");
                cout << "================ Imprimir registros ================" << endl;
                int inicio, fim;
                cout << "Digite a posição de inicio da impressão: ";
                cin >> inicio;
                cout << "Digite a posição de fim da impressão: ";
                cin >> fim;
                operacoes.busca(inicio, fim);
                retornarOuSair();
                break;
            default:
                break;
        }

    } while(opcao != 'f');

    return 0;
}