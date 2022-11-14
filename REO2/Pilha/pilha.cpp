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
        Dado espiarTopo(); // ok
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
    cout << "tamanho da pilha 1: " << this->mTamanho << endl;
    if (this->mTamanho = 0) {
        cout << "Impossível desempilhar!" << endl;
        return '-';
    }
    cout << "tamanho da pilha 2: " << this->mTamanho << endl;

    Noh* auxiliar;
    cout << "tamanho da pilha 3: " << this->mTamanho << endl;
    auxiliar = this->mPtrTopo;
    cout << "tamanho da pilha 4: " << this->mTamanho << endl;

    Dado valor = auxiliar->mDado;
    cout << "tamanho da pilha 5: " << this->mTamanho << endl;

    this->mPtrTopo = auxiliar->mPtrProx;
    cout << "tamanho da pilha 6: " << this->mTamanho << endl;
    this->mTamanho--;
    cout << "tamanho da pilha 7: " << this->mTamanho << endl;

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

Dado Pilha::espiarTopo() {
    Dado valor;
    valor = '-';

    if(this->mPtrTopo != NULL) {
        valor = this->mPtrTopo->mDado;
    }

    return valor;
}

bool Pilha::pilhaVazia() {
    cout << this->mTamanho;
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
            cout << "desempilhado o caracter: " << dado << endl;
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