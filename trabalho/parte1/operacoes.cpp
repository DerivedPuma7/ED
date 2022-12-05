#include <iostream>
#include <cstring>
#include <fstream>
#include <cstdlib>
#include <string>

using namespace std;

struct SubnationalPeriodLifeTables
{
    int id;
    char measure[256];
    float quantile;
    char area[256];
    char sex[255];
    char age[255];
    char geography[255];
    char ethnic[255];
    float value;
};

class Operacoes {
    public:
        void busca();
        void busca(int comeco, int fim);
        void print(SubnationalPeriodLifeTables registro);
        void trocaPosicao(int primeiraPosicao, int segundaPosicao);
        void alterarRegistroPosicao(int posicao);
        void insereNaPosicao(int posicao);
        void transformaEmTxt();
        SubnationalPeriodLifeTables novoDado(int posicao);
};

void Operacoes::print(SubnationalPeriodLifeTables registro){
        cout << registro.id << " | ";
        cout << registro.measure << " | ";
        cout << registro.quantile*100 << "% | ";
        cout << registro.area << " | ";
        cout << registro.sex << " | ";
        cout << registro.age << " | ";
        cout << registro.geography << " | ";
        cout << registro.ethnic << " | ";
        cout << registro.value << endl;
}

void Operacoes::busca(){
    ifstream arquivoLeituraBin("SubnationalPeriodLifeTables.bin");

    SubnationalPeriodLifeTables registro;
    arquivoLeituraBin.seekg(0, arquivoLeituraBin.end);
    int quantidadeRegistros = arquivoLeituraBin.tellg()/sizeof(SubnationalPeriodLifeTables);

    if (!arquivoLeituraBin)
    {
        cout << "Não foi possível abrir o arquivo" << endl;
    }

    int contador = 0;
    while (contador < quantidadeRegistros) {
        arquivoLeituraBin.seekg(contador * sizeof(SubnationalPeriodLifeTables));
        arquivoLeituraBin.read((char *)&registro, sizeof(SubnationalPeriodLifeTables));

        this->print(registro);

        contador++;
    } 
};

void Operacoes::busca(int comeco, int fim){
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

void Operacoes::trocaPosicao(int primeiraPosicao, int segundaPosicao){
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

        int posicaoAux = registroPrimeiraPosicao.id;
        registroPrimeiraPosicao.id = registroSegundaPosicao.id;
        registroSegundaPosicao.id = posicaoAux;

        arquivoLeituraBin.seekg(primeiraPosicao * sizeof(SubnationalPeriodLifeTables));
        arquivoLeituraBin.write((char *)&registroSegundaPosicao, sizeof(SubnationalPeriodLifeTables));

        arquivoLeituraBin.seekg(segundaPosicao * sizeof(SubnationalPeriodLifeTables));
        arquivoLeituraBin.write((char *)&registroPrimeiraPosicao, sizeof(SubnationalPeriodLifeTables));
    }
}

void Operacoes::insereNaPosicao(int posicao) {
    fstream arquivoLeituraBin;
    arquivoLeituraBin.open("SubnationalPeriodLifeTables.bin", ios::binary | ios::out | ios::in);

    if (!arquivoLeituraBin)
    {
        cout << "Não foi possível abrir o arquivo" << endl;
    }

    SubnationalPeriodLifeTables registro = this->novoDado(posicao);
    SubnationalPeriodLifeTables aux1;

    arquivoLeituraBin.seekg(0, arquivoLeituraBin.end);
    int quantidadeRegistros = arquivoLeituraBin.tellg()/sizeof(SubnationalPeriodLifeTables);

    while((quantidadeRegistros) >= (posicao)){

        arquivoLeituraBin.seekg((quantidadeRegistros - 1) * sizeof(SubnationalPeriodLifeTables));
        arquivoLeituraBin.read((char *)&aux1, sizeof(SubnationalPeriodLifeTables));
        aux1.id = quantidadeRegistros + 1;
        arquivoLeituraBin.seekg((quantidadeRegistros) * sizeof(SubnationalPeriodLifeTables));
        arquivoLeituraBin.write((char *)&aux1, sizeof(SubnationalPeriodLifeTables));

        quantidadeRegistros--;
    }

    arquivoLeituraBin.seekg(posicao * sizeof(SubnationalPeriodLifeTables));
    arquivoLeituraBin.write((char *)&registro, sizeof(SubnationalPeriodLifeTables));
}

void Operacoes::alterarRegistroPosicao(int posicao){
    fstream arquivoLeituraBin;
    arquivoLeituraBin.open("SubnationalPeriodLifeTables.bin", ios::binary | ios::out | ios::in);
    if (!arquivoLeituraBin)
    {
        cout << "Não foi possível abrir o arquivo" << endl;
    }

    SubnationalPeriodLifeTables registro = this->novoDado(posicao);

    arquivoLeituraBin.seekg(posicao * sizeof(SubnationalPeriodLifeTables));
    arquivoLeituraBin.write((char *)&registro, sizeof(SubnationalPeriodLifeTables));
}

SubnationalPeriodLifeTables Operacoes::novoDado(int posicao){
    SubnationalPeriodLifeTables registro;
    string garbage;

    registro.id = posicao;
    cout << "Measure: ";
    cin >> registro.measure;
    cout << "Quantile: ";
    cin >> registro.quantile;
    cout << "Area: ";
    cin.ignore();
	getline(cin, garbage);
    strcpy(registro.area, garbage.c_str());
    cout << "Sex: ";
    cin >> registro.sex;
    cout << "Age: ";
    cin.ignore();
	getline(cin, garbage);
    strcpy(registro.age, garbage.c_str());
    cout << "Geography: ";
	getline(cin, garbage);
    strcpy(registro.geography, garbage.c_str());
    cout << "Ethnic: ";
	getline(cin, garbage);
    strcpy(registro.ethnic, garbage.c_str());
    cout << "Value: ";
    cin >> registro.value;

    return registro;
}

void Operacoes::transformaEmTxt() {
    ifstream arquivoLeituraBin("SubnationalPeriodLifeTables.bin");
    if(!arquivoLeituraBin) {
        cout << "Não foi possível abrir o arquivo" << endl;
    }

    ofstream arquivoEscritaTxt("SubnationalPeriodLifeTables.txt");
    SubnationalPeriodLifeTables registro;

    arquivoLeituraBin.seekg(0, arquivoLeituraBin.end);
    int comeco = 0;
    int fim = arquivoLeituraBin.tellg()/sizeof(SubnationalPeriodLifeTables);

    while (comeco <= fim) {
        arquivoLeituraBin.seekg(comeco * sizeof(SubnationalPeriodLifeTables));
        arquivoLeituraBin.read((char *)&registro, sizeof(SubnationalPeriodLifeTables));

        this->print(registro);

        arquivoEscritaTxt << registro.id << " | "
            << registro.measure << " | "
            << registro.quantile*100 << "% | "
            << registro.area << " | "
            << registro.sex << " | "
            << registro.age << " | "
            << registro.geography << " | "
            << registro.ethnic << " | "
            << registro.value << endl;

        comeco++;
    }

    arquivoEscritaTxt.close();
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
    cout << "(f) Gerar arquivo .txt" << endl;
    cout << "(s) Sair" << endl;
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
    Operacoes operacoes;

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
                break;
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
                cout << "Digite a posição: ";
                cin >> posicao;
                operacoes.insereNaPosicao(posicao);
                retornarOuSair();
                break;
            case 'f':
                system("clear||cls");
                cout << "================ Gerar arquivo .txt ================" << endl;
                operacoes.transformaEmTxt();
                retornarOuSair();
                break;
            default:
                break;
        }

    } while(opcao != 's');

    return 0;
}