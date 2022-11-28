#include <iostream>
using namespace std;

typedef int Dado; // para facilitar a troca de int para outro tipo

// pilha implementada em arranjo 
class pilhav {
    private:
        int capacidade;
        Dado *dados;
        int tamanho;
        int posTopo;
    public:
        pilhav(int cap = 100);
        ~pilhav();
        void empilha(Dado valor);
        Dado desempilha();
        Dado espia(); // acessa elemento do topo, mas não retira
        void depura(); // imprime os dados do vetor da pilha sem removê-los (desempilhar)
        void info();  // imprime informações da pilha (tamanho e  posição do topo)
        int getTopo();
};

int pilhav::getTopo() {
    return this->posTopo;
}

pilhav::pilhav(int capacidade) {
    this->capacidade = capacidade;
    this->tamanho = 0;
    this->posTopo = -1;
    this->dados = new Dado[capacidade];
}

void pilhav::empilha(Dado valor) {
    if(this->posTopo == -1) {
        this->dados[this->posTopo + 1] = valor;
    }
    else {
        this->dados[this->posTopo + 1] = valor;
    }

    this->posTopo++;
    this->tamanho++;
}

Dado pilhav::desempilha() {
    if(this->posTopo == -1) {
        return -1;
    }

    int posicaoDadoTopo = this->posTopo;
    int dadoTopo = this->dados[posicaoDadoTopo];

    this->dados[this->posTopo] = -1;
    this->posTopo--;
    this->tamanho--;

    return dadoTopo;
}

Dado pilhav::espia() {
    return this->dados[this->posTopo];
}

void pilhav::depura() {
    int posicaoTopo = this->posTopo;
    for(int i = 0; i <= posicaoTopo; i++) {
		cout << this->dados[i] << endl;
	}
}

void pilhav::info() {
    cout << this->tamanho << ' ' << this->posTopo << endl;
}

pilhav::~pilhav() {
    int posicaoTopo = this->posTopo;
    while (posicaoTopo >= 0) {
        this->desempilha();
        posicaoTopo--;
    }
}

int main () {
    int capacidadePilha = 20;
    int valorEmpilhar;
    pilhav minhaPilha(capacidadePilha);

    for(int i = 0; i < 5; i++) {
        cin >> valorEmpilhar;
        minhaPilha.empilha(valorEmpilhar);
    }

    for(int i = 0; i < 3; i++) {
        cout << minhaPilha.desempilha() << endl;
    }

    for(int i = 0; i < 4; i++) {
        cin >> valorEmpilhar;
        minhaPilha.empilha(valorEmpilhar);
    }

    for(int i = 0; i < 3; i++) {
        cout << minhaPilha.desempilha() << endl;
    }

    cout << minhaPilha.espia() << endl;
    minhaPilha.depura();
    minhaPilha.info();

    return 0;
}
