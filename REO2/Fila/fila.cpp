#include <iostream>
using namespace std;
typedef int Dado;

class Noh {
    friend class Fila;
    private:
        Dado valor;
        Noh* ptrProximo;
};

class Fila {
    private: 
        Noh* ptrInicio;
        Noh* ptrFim;
        int tamanho;
    public:
        Fila();
        ~Fila();
        void enqueue(Dado dado);
        Dado dequeue();
        void limpar();
};

Fila::Fila() {
    this->ptrInicio = NULL;
    this->ptrFim = NULL;
    this->tamanho = 0;
}

Fila::~Fila() {
    this->limpar();
}

void Fila::enqueue(Dado dado) {
    Noh* novoNoh = new Noh;
    novoNoh->valor = dado;
    novoNoh->ptrProximo = NULL;

    if(this->tamanho == 0) {
        this->ptrInicio = novoNoh;
        this->ptrFim = novoNoh;
    }
    else {
        this->ptrFim->ptrProximo = novoNoh;
        this->ptrFim = this->ptrFim->ptrProximo;
    }

    this->tamanho++;
}

Dado Fila::dequeue() {
    if(this->tamanho == 0) {
        cout << "Fila vazia, impossível remover!" << endl;
        return -1;
    }

    Noh* aux = this->ptrInicio;
    Dado valor = aux->valor;

    this->ptrInicio = aux->ptrProximo;
    this->tamanho--;
    delete aux;

    return valor;
}

void Fila::limpar() {
    int tamanhoFila = this->tamanho;

    while(tamanhoFila > 0) {
        this->dequeue();
    }
}

void mostrarMenu() {
    cout << endl;
    cout << "O que você deseja fazer na Fila ?" << endl;
    cout << "Inserir dado: i" << endl;
    cout << "Remover dado: r" << endl;
    cout << "Limpar fila: l" << endl;
    cout << "Sair: s" << endl;
    cout << endl;
}

int main() {
    Fila minhaFila;

    mostrarMenu();
    char opcaoMenu;
    cin >> opcaoMenu;

    while (opcaoMenu != 's') {
        if (opcaoMenu == 'i') {
            cout << "Insira algum número" << endl;
            int dado;
            cin >> dado;
            minhaFila.enqueue(dado);
        }
        else if (opcaoMenu == 'r') {
            int dado;
            dado = minhaFila.dequeue();
            cout << "desempilhado o número: " << dado << endl;
        }
        else if (opcaoMenu == 'l') {
            minhaFila.limpar();
            cout << "fila limpa!" << endl;
        }
        else if (opcaoMenu == 's') {
            break;
        }
        else {
            cout << "Opção inválida!" << endl;
        }

        mostrarMenu();
        cin >> opcaoMenu;
    }

    return 0;
}