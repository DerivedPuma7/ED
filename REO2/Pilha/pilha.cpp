#include <iostream>
using namespace std;

typedef char Dado;

class Noh { 
    friend class Pilha;
    private:
        Dado mDado;
        Noh* mPtrProx;
};

class Pilha {
    public:
        Pilha();
        ~Pilha();
        void empilhar(const Dado& dado); // ok
        Dado desempilhar(); // ok
        void limparTudo(); // ok
        int getTamanho();
        Dado espiarTopo() const; // ok
        bool pilhaVazia(); // ok
    private:
        Noh* mPtrTopo;
        int mTamanho;
};

Pilha::Pilha() {
    this->mPtrTopo = NULL;
    this->mTamanho = 0;
}

void Pilha::empilhar(const Dado& dado) {
    Noh* auxiliar = new Noh;

    auxiliar->mDado = dado;
    auxiliar->mPtrProx = this->mPtrTopo;

    this->mPtrTopo = auxiliar;
    this->mTamanho++;
}

Dado Pilha::desempilhar() {
    if (this->mTamanho = 0) {
        cout << "Impossível desempilhar!" << endl;
        return -1;
    }

    Noh* auxiliar;
    auxiliar = this->mPtrTopo;

    Dado valor = auxiliar->mDado;

    this->mPtrTopo = auxiliar->mPtrProx;
    this->mTamanho--;

    delete auxiliar; 
    return valor;
}

void Pilha::limparTudo() {
    // while (this->mPtrTopo != NULL) {} // correto ?
    while (this->mTamanho > 0) {
        this->desempilhar();
    }
}

int Pilha::getTamanho() {
    return this->mTamanho;
}

Dado Pilha::espiarTopo() const {
    Dado valor = this->mPtrTopo->mDado;
    return valor;
}

bool Pilha::pilhaVazia() {
    return (this->mTamanho == 0);
}

Pilha::~Pilha() {
    this->limparTudo();
}

void mostrarMenu() {
    cout << endl;
    cout << "O que você deseja fazer na pilha ?" << endl;
    cout << "Inserir dado: i" << endl;
    cout << "Acessar topo: t" << endl;
    cout << "Desempilhar: d" << endl;
    cout << "Limpar pilha: l" << endl;
    cout << "Pilha vazia: v" << endl;
    cout << "Sair: s" << endl;
    cout << endl;
}

int main() {
    Pilha minhaPilha;

    mostrarMenu();
    char opcaoMenu;
    cin >> opcaoMenu;

    while (opcaoMenu != 's') {
        if (opcaoMenu == 'i') {
            cout << "Insira algum caracter" << endl;
            char dado;
            cin >> dado;
            minhaPilha.empilhar(dado);
        }
        else if (opcaoMenu == 't') {
            char dado;
            dado = minhaPilha.espiarTopo();
            cout << dado << endl;
        }
        else if (opcaoMenu == 'd') {
            char dado;
            dado = minhaPilha.desempilhar();
            cout << "desempilhado o caracter: " + dado << endl;
        }
        else if (opcaoMenu == 'l') {
            minhaPilha.limparTudo();
            cout << "pilha limpa!" << endl;
        }
        else if (opcaoMenu == 'v') {
            bool pilhaVazia;
            pilhaVazia = minhaPilha.pilhaVazia();
            
            string mensagem;
            mensagem = pilhaVazia ? "Pilha vazia" : "Pilha não está vazia";

            cout << mensagem << endl;
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
}