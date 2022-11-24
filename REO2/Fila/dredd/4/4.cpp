#include <iostream>
using namespace std;
typedef string Dado;

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
        bool vazia();
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
    }
    else {
        this->ptrFim->ptrProximo = novoNoh;
    }
    this->ptrFim = novoNoh;
    this->tamanho++;
}

Dado Fila::dequeue() {
    Noh* aux = this->ptrInicio;
    Dado valor = aux->valor;

    this->ptrInicio = aux->ptrProximo;
    this->tamanho--;
    if(this->tamanho == 0) {
		this->ptrInicio = NULL;
	}
    delete aux;

    return valor;
}

void Fila::limpar() {
    while(this->tamanho > 0) {
        this->dequeue();
    }
}

bool Fila::vazia() {
    return this->tamanho == 0;
}

void atender(Fila &filaNormal, Fila &filaPrioritaria, int &qntdNormalAtendidos, int &qntdPrioridadeAtendidos) {
    string nomeClienteAtendido;

    if( qntdPrioridadeAtendidos < 3 ) {
        if(! filaPrioritaria.vazia() ) {
            nomeClienteAtendido = filaPrioritaria.dequeue();
            cout << nomeClienteAtendido << endl;
            qntdPrioridadeAtendidos++;
        }
        else {
            if(! filaNormal.vazia() ){
                nomeClienteAtendido = filaNormal.dequeue();
                qntdPrioridadeAtendidos = 0;
                cout << nomeClienteAtendido << endl;
            }
            else {
                cout << "aguardando" << endl;
            }
        }
        
        qntdNormalAtendidos = (qntdPrioridadeAtendidos == 3) ? 0 : qntdNormalAtendidos;
    }
    else {
        if(! filaNormal.vazia() ) {
            nomeClienteAtendido = filaNormal.dequeue();
            qntdPrioridadeAtendidos = 0;
            cout << nomeClienteAtendido << endl;
            qntdNormalAtendidos++;
        }
        else {
            if(! filaPrioritaria.vazia() ) {
                nomeClienteAtendido = filaPrioritaria.dequeue();
                cout << nomeClienteAtendido << endl;
            }
            else {
                cout << "aguardando" << endl;
            }
        }

        qntdPrioridadeAtendidos = (qntdNormalAtendidos == 1) ? 0 : qntdPrioridadeAtendidos;
    }
}

int main() {
    Fila filaNormal;
    Fila filaPrioritaria;

    string opcaoMenu;
    string nome;
    cin >> opcaoMenu;
    if(opcaoMenu == "normal" || opcaoMenu == "prioridade") {
        cin >> nome;
    }

    int qntdNormalAtendidos = 0;
    int qntdPrioridadeAtendidos = 0;

    while(opcaoMenu != "sair")  {
        if(opcaoMenu == "normal") {
            filaNormal.enqueue(nome);
        }
        else if(opcaoMenu == "prioridade") {
            filaPrioritaria.enqueue(nome);
        }
        else if(opcaoMenu == "atender") {
            atender(filaNormal, filaPrioritaria, qntdNormalAtendidos, qntdPrioridadeAtendidos);
        }
        else if(opcaoMenu == "fim") {
            break;
        }

        cin >> opcaoMenu;
        if(opcaoMenu == "normal" || opcaoMenu == "prioridade") {
            cin >> nome;
        }
    }

    return 0;
}
