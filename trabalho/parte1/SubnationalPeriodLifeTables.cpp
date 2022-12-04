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
        void trocaPosicao(int primeiraPosicao, int segundaPosicao);
        void alterarRegistroPosicao(int posicao);
        void insereNaPosicao(int posicao);
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

    if(comeco < 0) comeco = 0;
    if(comeco > fim) {
        fim = comeco;
        comeco = 0;
    }

    while (comeco <= fim) {
        arquivoLeituraBin.seekg(comeco * sizeof(SubnationalPeriodLifeTables));
        arquivoLeituraBin.read((char *)&registro, sizeof(SubnationalPeriodLifeTables));

        this->print(registro);
        
        comeco++;
    }
};

void SubnationalPeriodLifeTablesOperacoes::trocaPosicao(int primeiraPosicao, int segundaPosicao){
    SubnationalPeriodLifeTables registroPrimeiraPosicao;
    SubnationalPeriodLifeTables registroSegundaPosicao;
    fstream arquivoLeituraBin;

    arquivoLeituraBin.open("SubnationalPeriodLifeTables.bin", ios::binary | ios::out | ios::in);

    SubnationalPeriodLifeTables registro;

    if (!arquivoLeituraBin)
    {
        cout << "Não foi possível abrir o arquivo" << endl;
    }
    else {
        arquivoLeituraBin.seekg(primeiraPosicao * sizeof(SubnationalPeriodLifeTables));
        arquivoLeituraBin.read((char *)&registroPrimeiraPosicao, sizeof(SubnationalPeriodLifeTables));

        arquivoLeituraBin.seekg(segundaPosicao * sizeof(SubnationalPeriodLifeTables));
        arquivoLeituraBin.read((char *)&registroSegundaPosicao, sizeof(SubnationalPeriodLifeTables));

        arquivoLeituraBin.seekg(primeiraPosicao * sizeof(SubnationalPeriodLifeTables));
        arquivoLeituraBin.write((char *)&registroSegundaPosicao, sizeof(SubnationalPeriodLifeTables));

        arquivoLeituraBin.seekg(segundaPosicao * sizeof(SubnationalPeriodLifeTables));
        arquivoLeituraBin.write((char *)&registroPrimeiraPosicao, sizeof(SubnationalPeriodLifeTables));
    }


}

void SubnationalPeriodLifeTablesOperacoes::insereNaPosicao(int posicao) {
    fstream arquivoLeituraBin;
    arquivoLeituraBin.open("SubnationalPeriodLifeTables.bin", ios::binary | ios::out | ios::in);

    if (!arquivoLeituraBin)
    {
        cout << "Não foi possível abrir o arquivo" << endl;
    }

    SubnationalPeriodLifeTables registroDeInteresse;
    SubnationalPeriodLifeTables aux1;
    SubnationalPeriodLifeTables aux2;
    int posicaoDeInteresse = posicao;
    int segundaPosicao;
    int terceiraPosicao;

    cout << sizeof(arquivoLeituraBin) << endl;
    cout << sizeof(SubnationalPeriodLifeTables) << endl;

    do{
        segundaPosicao = posicao + 1;
        terceiraPosicao = posicao + 2;

        arquivoLeituraBin.seekg(posicao * sizeof(SubnationalPeriodLifeTables));
        arquivoLeituraBin.read((char *)&aux1, sizeof(SubnationalPeriodLifeTables));

        arquivoLeituraBin.seekg(segundaPosicao * sizeof(SubnationalPeriodLifeTables));
        arquivoLeituraBin.read((char *)&aux2, sizeof(SubnationalPeriodLifeTables));
        arquivoLeituraBin.write((char *)&aux1, sizeof(SubnationalPeriodLifeTables));

        arquivoLeituraBin.seekg(segundaPosicao + 1 * sizeof(SubnationalPeriodLifeTables));

        posicao = posicao + 1;

        cout << "." << posicao << endl;

        arquivoLeituraBin.seekg(terceiraPosicao * sizeof(SubnationalPeriodLifeTables)); // controle do fim
    }
    while(arquivoLeituraBin);
}

void SubnationalPeriodLifeTablesOperacoes::alterarRegistroPosicao(int posicao){
    fstream arquivoLeituraBin;
    arquivoLeituraBin.open("SubnationalPeriodLifeTables.bin", ios::binary | ios::out | ios::in);
    if (!arquivoLeituraBin)
    {
        cout << "Não foi possível abrir o arquivo" << endl;
    }

    SubnationalPeriodLifeTables registro;
    string garbage;

    cout << "Measure: ";
    cin >> registro.measure;
    cout << "Quantile: ";
    cin >> registro.quantile;
    cout << "Area: ";
    cin >> registro.sex;
    cout << "Sex: ";
    cin >> registro.sex;
    cout << "Age: ";
    cin >> registro.age;
    cout << "Geography: ";
    cin >> registro.geography;
    cout << "Ethnic: ";
    cin >> registro.ethnic;

    arquivoLeituraBin.seekg(posicao * sizeof(SubnationalPeriodLifeTables));
    arquivoLeituraBin.write((char *)&registro, sizeof(SubnationalPeriodLifeTables));
}

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
    cout << "\nPrecione qualquer tecla para voltar ao menu principal!" << endl;
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
            case 'c':
                system("clear||cls");
                cout << "================ Trocar Posição dos registros ================" << endl;
                int primeira, segunda;
                cout << "Digite a primeira posição: ";
                cin >> primeira;
                cout << "Digite a segunda posição: ";
                cin >> segunda;
                operacoes.trocaPosicao(primeira, segunda);
                retornarOuSair();
            case 'd':
                system("clear||cls");
                cout << "================ Mudar Registro de uma Posição ================" << endl;
                int posicao;
                cout << "Digite a posição do registro: ";
                cin >> posicao;
                operacoes.alterarRegistroPosicao(posicao);
                retornarOuSair();
                break;
            case 'e':
                system("clear||cls");
                cout << "================ Inserir registro em uma posição ================" << endl;
                int posicao;
                cout << "Digite a posição: ";
                cin >> posicao;
                operacoes.insereNaPosicao(posicao);
                retornarOuSair();
            default:
                break;
        }

    } while(opcao != 'f');

    return 0;
}