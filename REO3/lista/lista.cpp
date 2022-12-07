#include <iostream>
using namespace std;

typedef int Dado;

int main() {
    return 0;
}

class Noh {
    friend class Lista;
    private:
        Dado dado;
        Noh* proximo;
    public:
        Noh(Dado dado);
};

Noh::Noh(Dado dado) {
    this->dado = dado;
    this->proximo = NULL;
}

class Lista {
    private:
        int tamanho;
        Noh* inicio;
        Noh* fim;
    public:
        Lista();
        ~Lista();
        bool vazia();

        /*_____ INSERÇÃO _____*/
        void inserirEmListaVazia(Dado valor);
        void inserirNoInicioDaLista(Dado valor);
        void inserirNoFimDaLista(Dado valor);
        void inserirEmPosicaoEspecifica(Dado valor, int posicao);

        /*_____ PERCORRIMENTO _____*/
        void percorrerListaIterativo();
        void percorrerListaRecursivo();
        void percorrerListaAux(Noh* umNoh);

        /*_____ BUSCA _____*/
        void buscarNaLista(Dado valor);
};

Lista::Lista() {
    this->inicio = NULL;
    this->fim = NULL;
    this->tamanho = 0;
}

bool Lista::vazia() {
    return this->tamanho == 0;
}

/*_________________________ INSERÇÃO _________________________*/
void Lista::inserirEmListaVazia(Dado valor) {
    Noh* novoNoh = new Noh(valor);

    this->inicio = novoNoh;
    this->fim = novoNoh;
    this->tamanho = 1;
}

void Lista::inserirNoInicioDaLista(Dado valor) {
    if(this->vazia()) this->inserirEmListaVazia(valor);
    
    else {
        Noh* novoNoh = new Noh(valor);
        novoNoh->proximo = this->inicio;
        this->inicio = novoNoh;
    }

    this->tamanho++;
}

void Lista::inserirNoFimDaLista(Dado valor) {
    if(this->vazia()) this->inserirEmListaVazia(valor);

    else {
        Noh* novoNoh = new Noh(valor);
        this->fim->proximo = novoNoh;
        this->fim = novoNoh;
    }

    this->tamanho++;
}

void Lista::inserirEmPosicaoEspecifica(Dado valor, int posicao) {
    if(this->vazia()) this->inserirEmListaVazia(valor);
    else if(posicao == 0) this->inserirNoInicioDaLista(valor);
    else if(posicao == (this->tamanho - 1)) this->inserirNoFimDaLista(valor);
    else {
        Noh* novoNoh = new Noh(valor);
        
        Noh* aux = this->inicio;
        int posAux = 0;

        while(posAux < (posicao - 1)) {
            aux = aux->proximo;
            posAux++;
        }

        novoNoh->proximo = aux->proximo;
        aux->proximo = novoNoh;

        this->tamanho++;
    }
}

/*_________________________ PERCORRIMENTO _________________________*/
void Lista::percorrerListaIterativo() {
    Noh* auxiliar = this->inicio;

    while(auxiliar != NULL) {
        cout << "dado: " << auxiliar->dado << endl;
        auxiliar = auxiliar->proximo;
    }
}

void Lista::percorrerListaRecursivo() {
    Noh* inicio = this->inicio;
    this->percorrerListaAux(inicio);
}

void Lista::percorrerListaAux(Noh* umNoh) {
    if(umNoh != NULL) {
        cout << "dado: " << umNoh->dado << endl;
        percorrerListaAux(umNoh->proximo);
    }
}

/*_________________________ BUSCA _________________________*/
void Lista::buscarNaLista(Dado valor) {
    Noh* auxiliar = this->inicio;

    while(auxiliar != NULL) {
        
    }
}