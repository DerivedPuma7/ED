/* 
    lojinha.cpp - aplicação para desenvolvimento de atividade
    de Tipo Abstrado de Dados

    Atividade de  GCC216 - Estruturas de Dados, 2020

    Solução de: Gustavo Ribeiro de Figueiredo
*/

#include <iostream>

using namespace std;

struct produto {
    string nomeDoProduto;
    float valorParaVenda;
    int quantidadeEmEstoque;
    produto();
};

produto::produto() {
    nomeDoProduto.clear();
    valorParaVenda = 0;
    quantidadeEmEstoque = 0;
}

class estoque {
    private:
        // *** AVISO: Não altere os atributos privados da classe *** 
        produto* listaDeProdutos;
        produto* listaDeProdutosAuxiliar;
        int quantidadeDeProdutos;
        int capacidadeMaxima;
    public:
        estoque(int capacidade);
        ~estoque();
        void inserirNovoProduto(const produto& umProduto);
        bool buscarProduto(const string& nome, produto& umProduto);
        void redimensionarCapacidade();
        void criarListaProdutosAuxiliar();
        void copiarListaProdutos();
        friend void simularDescontoEmTodosOsProdutos(estoque umEstoque, float desconto);
};

estoque::estoque(int capacidade) {
    quantidadeDeProdutos = 0;
    capacidadeMaxima = capacidade;
    listaDeProdutos = new produto[capacidadeMaxima];
}

estoque::~estoque() {
    delete [] listaDeProdutos;
}

void estoque::inserirNovoProduto(const produto& umProduto) {
    if (quantidadeDeProdutos == capacidadeMaxima) { // vetor cheio, precisa redimensionar
        redimensionarCapacidade();
    }
    listaDeProdutos[quantidadeDeProdutos] = umProduto;
    quantidadeDeProdutos++;
}

bool estoque::buscarProduto(const string& nome, produto& umProduto) {
    int posicaoAtual = 0;

    while (posicaoAtual < quantidadeDeProdutos and 
           listaDeProdutos[posicaoAtual].nomeDoProduto != nome) 
        posicaoAtual++;

    // se posicaoAtual não for menor que quantidade de produtos, é porque não encontrou
    if (posicaoAtual < quantidadeDeProdutos) {
        umProduto = listaDeProdutos[posicaoAtual];
        return true;
    }

    return false;
}

void estoque::redimensionarCapacidade() { 
    criarListaProdutosAuxiliar();

    int novoTamanho = quantidadeDeProdutos + 1;
    listaDeProdutos = new produto[novoTamanho];

    copiarListaProdutos();
    capacidadeMaxima++;
}

void estoque::criarListaProdutosAuxiliar() {
    listaDeProdutosAuxiliar = new produto[capacidadeMaxima];
    for(int i = 0; i < quantidadeDeProdutos; i++) {
        listaDeProdutosAuxiliar[i] = listaDeProdutos[i];
    }
}
void estoque::copiarListaProdutos() {
    for(int i = 0; i < quantidadeDeProdutos; i++) {
        listaDeProdutos[i] = listaDeProdutosAuxiliar[i];
    }

    delete [] listaDeProdutosAuxiliar;
}

void simularDescontoEmTodosOsProdutos(estoque umEstoque, float desconto) {
    // *** AVISO: Não altere esta função *** 
    for (int i = 0; i < umEstoque.quantidadeDeProdutos; i++) {
        umEstoque.listaDeProdutos[i].valorParaVenda = 
            (1 - (desconto/100)) * umEstoque.listaDeProdutos[i].valorParaVenda;
        cout << umEstoque.listaDeProdutos[i].nomeDoProduto << " "
             << umEstoque.listaDeProdutos[i].valorParaVenda << endl;
    }
    cout << endl;
}


int main() {
    // *** AVISO: Não altere a função principal, o main() *** 
    int capacidadeInicial;

    cout << "Lojinha - Aplicativo para Controlar Estoque\n" 
         << "Entre com capacidade máxima inicial: ";
    cin >> capacidadeInicial;

    estoque estoqueDaLojinha(capacidadeInicial);

    cout << "Lojinha - Escolha a Opção:\n"
         << "i - inserir novo produto\n"
         << "b - buscar por um dado produto a partir do nome\n"
         << "d - simular desconto em todos os produtos\n"
         << "s - para sair do programa" << endl;

    char opcaoDoMenu;
    produto umProduto;
    string nome;
    float desconto;

    cin >> opcaoDoMenu;

    while (opcaoDoMenu != 's') {
        switch(opcaoDoMenu) {
            case 'i' : 
                cout << "Entre com dados do produto (nome, preço, quantidade em estoque):" << endl;
                cin >> umProduto.nomeDoProduto 
                    >> umProduto.valorParaVenda
                    >> umProduto.quantidadeEmEstoque;
                estoqueDaLojinha.inserirNovoProduto(umProduto);
                break;

            case 'b' :
                cout << "Entre com nome do produto para busca: ";
                cin >> nome;
                
                if (estoqueDaLojinha.buscarProduto(nome, umProduto)) 
                    cout << umProduto.nomeDoProduto << " "
                         << umProduto.valorParaVenda << " "
                         << umProduto.quantidadeEmEstoque << endl << endl;
                else 
                    cout << "Produto não encontrado!" << endl << endl;
                break;

            case 'd' : 
                cout << "Entre com valor do desconto (em porcentagem): ";
                cin >> desconto;
                simularDescontoEmTodosOsProdutos(estoqueDaLojinha,desconto);
                break;

            case 's' : // não faz nada, espera retorno ao while para sair 
                break;

            default:
                cout << "Opção inválida!" << endl;
                break;

        }
        cout << "Lojinha - Escolha a Opção:\n"
             << "i - inserir novo produto\n"
             << "b - buscar por um dado produto a partir do nome\n"
             << "d - simular desconto em todos os produtos\n"
             << "s - para sair do programa" << endl;
        cin >> opcaoDoMenu;
    }

    return 0;
}