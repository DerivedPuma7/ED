#include <iostream>
using namespace std;

typedef int Dado;

class Heap {
    private:
        Dado* dados;
        int capacidade;
        int tamanho;
    public:
        Heap(int capacidade);
        ~Heap();
        void constroi(Dado vetor[], int tamanho);
        void corrigeDescendo(int i);
        void corrigeSubindo(int i);
        int encontraPai(int i);
        int encontraFilhoEsquerdo(int i);
        int encontraFilhoDireito(int i);
        void troca(int indice1, int indice2);
        void insere(Dado dado);
        Dado retira();
};

Heap::Heap(int capacidadeHeap) {
    this->capacidade = capacidadeHeap;
    this->dados = new Dado[this->capacidade];
    this->tamanho = 0;
}

Heap::~Heap() {
    delete[] this->dados;
}

void Heap::constroi(Dado vetor[], int tamanho) {
    for(int i = 0; i < tamanho; i++) {
        this->dados[i] = vetor[i];
    }
    this->tamanho = tamanho;

    int indiceMetadeVetor = (this->tamanho - 1) / 2;

    for(int i = indiceMetadeVetor; i >= 0; i--) {
        corrigeDescendo(i);
    }
}

void Heap::troca(int indice1, int indice2) {
    int copiaIndice2 = this->dados[indice2];

    this->dados[indice2] = this->dados[indice1];
    this->dados[indice1] = copiaIndice2;
}

int Heap::encontraFilhoEsquerdo(int i) {
    return (2 * i) + 1;
}

int Heap::encontraFilhoDireito(int i) {
    return (2 * i) + 2;
}

int Heap::encontraPai(int i) {
    return ((i - 1) / 2);
}

void Heap::corrigeDescendo(int i) {
    int posicaoFilhoEsquerdo = this->encontraFilhoEsquerdo(i);
    int posicaoFilhoDireito = this->encontraFilhoDireito(i);
    int posicaoMaior = i;

    int POSICAO_FINAL = this->tamanho - 1;
    if(
        (posicaoFilhoEsquerdo <= POSICAO_FINAL) and 
        (this->dados[posicaoFilhoEsquerdo] > this->dados[posicaoMaior])
    ) {
        posicaoMaior = posicaoFilhoEsquerdo;
    }
    if(
        (posicaoFilhoDireito <= POSICAO_FINAL) and 
        ((this->dados[posicaoFilhoDireito] > this->dados[posicaoMaior]))
    ) {
        posicaoMaior = posicaoFilhoDireito;
    }

    if(posicaoMaior != i) {
        this->troca(i, posicaoMaior);
        this->corrigeDescendo(posicaoMaior);
    }
}

void Heap::corrigeSubindo(int i) {
    int posicaoPai = encontraPai(i);

    int POSICAO_INICIO = 0;
    if(
        (posicaoPai >= POSICAO_INICIO) and 
        (this->dados[i] > this->dados[posicaoPai])
    ) {
        this->troca(i, posicaoPai);
        this->corrigeSubindo(posicaoPai);
    }
}

void Heap::insere(Dado dado) {
    if(this->tamanho == this->capacidade) {
        cout << "Capaciade máxima do Heap atingida";
    }
    else {
        int POSICAO_FINAL = this->tamanho;

        this->dados[POSICAO_FINAL] = dado;
        corrigeSubindo(POSICAO_FINAL);
        this->tamanho++;
    }
}

Dado Heap::retira() {
    if (this->tamanho < 1){
		cerr << "Heap não possui nenhum noh!" << endl;
		return -1;
	}

    int POSICAO_INICIO = 0;
    int POSICAO_FINAL = this->tamanho - 1;
    Dado aux = this->dados[POSICAO_INICIO];

    troca(POSICAO_INICIO, POSICAO_FINAL);
    this->tamanho--;
    corrigeDescendo(POSICAO_INICIO);

    return aux;
}

int main(){
    int tamanhoVetor = 5, capacidadeHeap = 5;

	Heap H1(capacidadeHeap);

	Dado vet[tamanhoVetor];
	int elementos;
	
    cout << "começar o for agora" << endl;
	for (int i = 0; i < tamanhoVetor; i++){
        cout << "entrei for, insere elemento" << endl;
		cin >> elementos;
        cout << "acabei de inserir elemento" << endl;
		vet[i] = elementos;
        cout << "elemento inserido foi o " << vet[i] << endl;
	}
	
	H1.constroi(vet, tamanhoVetor);
	
	cout << H1.retira() << endl;

	H1.insere(66);
	for (int i = 0; i < 5; i++){
		cout << H1.retira() << " ";
	}
	
	return 0;
}