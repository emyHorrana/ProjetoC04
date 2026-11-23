#include <iostream>
#include <string>
#include <list>
#include <locale.h>
#include <cmath>

using namespace std;

const int MAX_VERTICES = 100;
struct Ponto { double x, y; };

// João Pedro Ramos Garcia 820
// Mariana Novais Portugal 746
// Emily Horrana Lima Rodrigues Armando 787
// Vinicius Oliveira Braga 743

struct Aresta
{
    int origem;
    int destino;
    int peso; // Similaridade entre os itens
};

struct Item
{
    string nome;
    string dono;
    string propriedadeMagica;
    int id;
    int raridade;
    Ponto *contorno;
    int quantidadeContorno;

    // Ponteiros da árvore organizada por nome
    Item *left;
    Item *right;

    // Ponteiros da árvore organizada por raridade
    Item *leftRaridade;
    Item *rightRaridade;
    int alturaNome;
    int alturaRaridade;
};

Ponto aberturaBolsa[MAX_VERTICES];
int quantidadeAbertura = 0;
bool aberturaCadastrada = false;
Ponto contornoItemAtual[MAX_VERTICES];
int quantidadeContornoAtual = 0;

int maior(int a, int b) { return a > b ? a : b; }

int alturaNome(Item *n) { return n == NULL ? 0 : n->alturaNome; }
int alturaRaridade(Item *n) { return n == NULL ? 0 : n->alturaRaridade; }

Item* rotacaoDireitaNome(Item *y) {
    Item *x = y->left, *t = x->right;
    x->right = y; y->left = t;
    y->alturaNome = 1 + maior(alturaNome(y->left), alturaNome(y->right));
    x->alturaNome = 1 + maior(alturaNome(x->left), alturaNome(x->right));
    return x;
}
Item* rotacaoEsquerdaNome(Item *x) {
    Item *y = x->right, *t = y->left;
    y->left = x; x->right = t;
    x->alturaNome = 1 + maior(alturaNome(x->left), alturaNome(x->right));
    y->alturaNome = 1 + maior(alturaNome(y->left), alturaNome(y->right));
    return y;
}
Item* rotacaoDireitaRaridade(Item *y) {
    Item *x = y->leftRaridade, *t = x->rightRaridade;
    x->rightRaridade = y; y->leftRaridade = t;
    y->alturaRaridade = 1 + maior(alturaRaridade(y->leftRaridade), alturaRaridade(y->rightRaridade));
    x->alturaRaridade = 1 + maior(alturaRaridade(x->leftRaridade), alturaRaridade(x->rightRaridade));
    return x;
}
Item* rotacaoEsquerdaRaridade(Item *x) {
    Item *y = x->rightRaridade, *t = y->leftRaridade;
    y->leftRaridade = x; x->rightRaridade = t;
    x->alturaRaridade = 1 + maior(alturaRaridade(x->leftRaridade), alturaRaridade(x->rightRaridade));
    y->alturaRaridade = 1 + maior(alturaRaridade(y->leftRaridade), alturaRaridade(y->rightRaridade));
    return y;
}

// Insere em AVL por nome.
void insert(Item* &current, string nome, string dono, string propriedadeMagica, int id, int raridade)
{
    if (current == NULL) {
        current = new Item;

        current->id = id;
        current->nome = nome;
        current->dono = dono;
        current->propriedadeMagica = propriedadeMagica;
        current->raridade = raridade;

        current->left = NULL;
        current->right = NULL;
        current->leftRaridade = NULL;
        current->rightRaridade = NULL;
        current->alturaNome = 1;
        current->alturaRaridade = 1;
        current->contorno = NULL;
        current->quantidadeContorno = 0;

    } else if (nome < current->nome) {
        insert(current->left, nome, dono, propriedadeMagica, id, raridade);
    } else {
        insert(current->right, nome, dono, propriedadeMagica, id, raridade);
    }
    current->alturaNome = 1 + maior(alturaNome(current->left), alturaNome(current->right));
    int b = alturaNome(current->left) - alturaNome(current->right);
    if (b > 1 && nome < current->left->nome) current = rotacaoDireitaNome(current);
    else if (b < -1 && nome >= current->right->nome) current = rotacaoEsquerdaNome(current);
    else if (b > 1) { current->left = rotacaoEsquerdaNome(current->left); current = rotacaoDireitaNome(current); }
    else if (b < -1) { current->right = rotacaoDireitaNome(current->right); current = rotacaoEsquerdaNome(current); }
}

void insertRaridade(Item* &current, string nome, string dono, string propriedadeMagica, int id, int raridade)
{
    if (current == NULL) {
        current = new Item;

        current->id = id;
        current->nome = nome;
        current->dono = dono;
        current->propriedadeMagica = propriedadeMagica;
        current->raridade = raridade;

        current->left = NULL;
        current->right = NULL;
        current->leftRaridade = NULL;
        current->rightRaridade = NULL;
        current->alturaNome = 1;
        current->alturaRaridade = 1;
        current->contorno = NULL;
        current->quantidadeContorno = 0;

    } else if (raridade < current->raridade || (raridade == current->raridade && nome < current->nome)) {
        insertRaridade(current->leftRaridade, nome, dono, propriedadeMagica, id, raridade);
    } else {
        insertRaridade(current->rightRaridade, nome, dono, propriedadeMagica, id, raridade);
    }
    current->alturaRaridade = 1 + maior(alturaRaridade(current->leftRaridade), alturaRaridade(current->rightRaridade));
    int b = alturaRaridade(current->leftRaridade) - alturaRaridade(current->rightRaridade);
    bool menor = raridade < current->raridade || (raridade == current->raridade && nome < current->nome);
    bool maior = raridade > current->raridade || (raridade == current->raridade && nome >= current->nome);
    if (b > 1 && menor) current = rotacaoDireitaRaridade(current);
    else if (b < -1 && maior) current = rotacaoEsquerdaRaridade(current);
    else if (b > 1) { current->leftRaridade = rotacaoEsquerdaRaridade(current->leftRaridade); current = rotacaoDireitaRaridade(current); }
    else if (b < -1) { current->rightRaridade = rotacaoDireitaRaridade(current->rightRaridade); current = rotacaoEsquerdaRaridade(current); }
}

// Mostra os itens em ordem alfabética
void show_in_order(Item* current)
{
    if (current != NULL) {
        show_in_order(current->left);

        cout << "ID: " << current->id << endl;
        cout << "Nome: " << current->nome << endl;
        cout << "Dono: " << current->dono << endl;
        cout << "Propriedade magica: " << current->propriedadeMagica << endl;
        cout << "Raridade: " << current->raridade << endl;
        cout << "-----------------------------\n" << endl;

        show_in_order(current->right);
    }
}

Item *search(Item *current, string nome)
{
    if (current == NULL) {
        return NULL;

    } else if (nome == current->nome) {
        return current;

    } else {
        if (nome < current->nome) {
            return search(current->left, nome);
        } else {
            return search(current->right, nome);
        }
    }
}

// Libera a memória utilizada pela árvore binária de nomes
void destruct(Item * &current)
{
    if (current != NULL) {
        destruct(current->left);
        destruct(current->right);

        delete(current);
        current = NULL;
    }
}

// Libera a memória utilizada pela árvore binária de raridades
void destructRaridade(Item * &current)
{
    if (current != NULL) {
        destructRaridade(current->leftRaridade);
        destructRaridade(current->rightRaridade);

        delete(current);
        current = NULL;
    }
}

const int MAX_ITENS = 40000;
Item itens[MAX_ITENS];
int quantidadeItens = 0;
list<Aresta> grafoNovo[MAX_ITENS];
list<Aresta> grafo[MAX_ITENS];

int encontrarItem(int id)
{
    for (int i = 0; i < quantidadeItens; i++) {
        if (itens[i].id == id) {
            return i;
        }
    }

    return -1;
}

double produtoVetorial(Ponto a, Ponto b, Ponto c) {
    return (b.x-a.x)*(c.y-a.y) - (b.y-a.y)*(c.x-a.x);
}

bool poligonoConvexo(Ponto p[], int n) {
    if (n < 3 || n > MAX_VERTICES) return false;
    int sinal = 0;
    for (int i = 0; i < n; ++i) {
        double c = produtoVetorial(p[i], p[(i+1)%n], p[(i+2)%n]);
        if (fabs(c) < 1e-9) continue;
        int atual = c > 0 ? 1 : -1;
        if (sinal && sinal != atual) return false;
        sinal = atual;
    }
    return sinal != 0;
}

bool pontoDentroDoConvexo(Ponto q, Ponto p[], int n) {
    double area = 0;
    for (int i = 0; i < n; ++i)
        area += p[i].x*p[(i+1)%n].y - p[(i+1)%n].x*p[i].y;
    double orientacao = area >= 0 ? 1.0 : -1.0;
    for (int i = 0; i < n; ++i)
        if (orientacao * produtoVetorial(p[i], p[(i+1)%n], q) < -1e-9) return false;
    return true;
}

int lerPoligono(const string &rotulo, Ponto p[]) {
    int n;
    cout << "\nQuantidade de vertices do " << rotulo << " (minimo 3): ";
    cin >> n;
    if (!cin.fail()) cout << n << endl;
    if (cin.fail() || n < 3 || n > MAX_VERTICES) {
        cin.clear(); cin.ignore(10000, '\n');
        return 0;
    }
    for (int i = 0; i < n; ++i) {
        cout << "Vertice " << i+1 << " (x y): ";
        cin >> p[i].x >> p[i].y;
        if (!cin.fail()) cout << p[i].x << " " << p[i].y << endl;
        if (cin.fail()) { cin.clear(); cin.ignore(10000, '\n'); return 0; }
    }
    cin.ignore(10000, '\n');
    return n;
}

bool itemCabeNaAbertura(Ponto contorno[], int quantidade) {
    if (!poligonoConvexo(contorno, quantidade) || !poligonoConvexo(aberturaBolsa, quantidadeAbertura)) return false;
    for (int i = 0; i < quantidade; ++i)
        if (!pontoDentroDoConvexo(contorno[i], aberturaBolsa, quantidadeAbertura)) return false;
    return true;
}

int inserirItem(string nomeItem, string nomeDono, string propriedadeMagica, int id, int raridade)
{
    if (quantidadeItens >= MAX_ITENS) {
        cout << "Inventário cheio!" << endl;
        return 0;
    }

    // Impede IDs repetidos
    if (encontrarItem(id) != -1) {
        cout << "Erro: Já existe um item com esse ID!" << endl;
        return 0;
    }

    // Impede nomes repetidos
    for (int i = 0; i < quantidadeItens; i++) {
        if (itens[i].nome == nomeItem) {
            cout << "Erro: Já existe um item com esse nome!" << endl;
            return 0;
        }
    }

    // Verifica se a raridade está entre 0 e 100
    if (raridade < 0 || raridade > 100) {
        cout << "Erro: A raridade deve estar entre 0 e 100!" << endl;
        return 0;
    }

    // Armazena os dados do item
    itens[quantidadeItens].nome = nomeItem;
    itens[quantidadeItens].dono = nomeDono;
    itens[quantidadeItens].propriedadeMagica = propriedadeMagica;
    itens[quantidadeItens].id = id;
    itens[quantidadeItens].raridade = raridade;
    itens[quantidadeItens].contorno = new Ponto[quantidadeContornoAtual];
    itens[quantidadeItens].quantidadeContorno = quantidadeContornoAtual;
    for (int i = 0; i < quantidadeContornoAtual; ++i)
        itens[quantidadeItens].contorno[i] = contornoItemAtual[i];

    quantidadeItens++;

    return 1;
}

// Cadastra uma relação de similaridade entre dois itens
int cadastrarSimilaridade(int idItem1, int idItem2, int similaridade)
{
    // Impede que um item seja relacionado consigo mesmo
    if (idItem1 == idItem2) {
        cout << "Erro: Um item não pode ser similar a si mesmo!" << endl;
        return 0;
    }

    // Verifica se a similaridade está entre 0 e 100
    if (similaridade < 0 || similaridade > 100) {
        cout << "Erro: A similaridade deve estar entre 0 e 100!" << endl;
        return 0;
    }

    // Procura os dois itens pelo ID
    int indice1 = encontrarItem(idItem1);
    int indice2 = encontrarItem(idItem2);

    if (indice1 == -1 || indice2 == -1) {
        cout << "Erro: Um ou ambos os IDs não foram encontrados." << endl;
        return 0;
    }

    list<Aresta>::iterator it;

    for (it = grafo[indice1].begin(); it != grafo[indice1].end(); it++) {
        if (it->destino == indice2) {
            cout << "Erro: Essa conexão já foi cadastrada!" << endl;
            return 0;
        }
    }

    // Adiciona a conexão nos dois sentidos
    grafo[indice1].push_back({indice1, indice2, similaridade});
    grafo[indice2].push_back({indice2, indice1, similaridade});

    cout << "Similaridade cadastrada com sucesso!" << endl;

    return 1;
}

// Busca os itens similares a um item informado
int buscarItensSimilares(int idItem, string nomeDono, int valorMinimo)
{
    int posicaoItem = encontrarItem(idItem);

    if (posicaoItem == -1) {
        cout << "Item nao encontrado!" << endl;
        return 0;
    }

    list<Aresta>::iterator it;
    bool encontrou = false;

    cout << "\nItens similares encontrados:" << endl;

    // Percorre as conexões do item no grafo
    for (it = grafo[posicaoItem].begin(); it != grafo[posicaoItem].end(); it++) {

        if (it->peso > valorMinimo) {
            int posicaoDestino = it->destino;

            // Não mostra itens pertencentes ao dono informado
            if (itens[posicaoDestino].dono != nomeDono) {

                cout << "ID: " << itens[posicaoDestino].id << endl;
                cout << "Nome: " << itens[posicaoDestino].nome << endl;
                cout << "Dono: " << itens[posicaoDestino].dono << endl;
                cout << "Propriedade magica: "
                     << itens[posicaoDestino].propriedadeMagica << endl;
                cout << "Raridade: " << itens[posicaoDestino].raridade << endl;
                cout << "Similaridade: " << it->peso << endl;
                cout << "-----------------------------\n" << endl;

                encontrou = true;
            }
        }
    }

    if (!encontrou) {
        cout << "Nenhum item encontrado com esses critérios." << endl;
    }

    return 0;
}

// =========================================================================
// Funcionalidades da Entrega Parcial 4
// =========================================================================

// Passo 8: Lista os itens em ordem decrescente de raridade
int listarItensPorRaridade(Item* current)
{
    if (current == NULL) {
        return 0;
    }

    // Percorre primeiro a subarvore da direita
    listarItensPorRaridade(current->rightRaridade);

    cout << "ID: " << current->id << endl;
    cout << "Nome: " << current->nome << endl;
    cout << "Dono: " << current->dono << endl;
    cout << "Propriedade magica: "
         << current->propriedadeMagica << endl;
    cout << "Raridade: " << current->raridade << endl;

    cout << "-----------------------------\n" << endl;

    // Percorre a subarvore da esquerda
    listarItensPorRaridade(current->leftRaridade);

    return 1;
}

// Passo 9: Conta e retorna a quantidade de itens com a mesma propriedade mágica
int contarPropriedadeMagica(Item* current, string propriedadeMagica)
{
    if (current == NULL) {
        return 0;
    }

    int contador = 0;
    if (current->propriedadeMagica == propriedadeMagica) {
        contador = 1;
    }

    return contador
         + contarPropriedadeMagica(current->left, propriedadeMagica)
         + contarPropriedadeMagica(current->right, propriedadeMagica);
}

void copiarDados(Item *dest, Item *orig) {
    dest->id = orig->id; dest->nome = orig->nome; dest->dono = orig->dono;
    dest->propriedadeMagica = orig->propriedadeMagica; dest->raridade = orig->raridade;
}

Item* menorNome(Item *n) { while (n->left != NULL) n = n->left; return n; }
Item* menorRaridade(Item *n) { while (n->leftRaridade != NULL) n = n->leftRaridade; return n; }

void removerDaAVLNome(Item* &n, string nome) {
    if (!n) return;
    if (nome < n->nome) removerDaAVLNome(n->left, nome);
    else if (nome > n->nome) removerDaAVLNome(n->right, nome);
    else {
        if (!n->left || !n->right) {
            Item *filho = n->left ? n->left : n->right;
            delete n; n = filho;
        } else {
            Item *s = menorNome(n->right); copiarDados(n, s);
            removerDaAVLNome(n->right, s->nome);
        }
    }
    if (!n) return;
    n->alturaNome = 1 + maior(alturaNome(n->left), alturaNome(n->right));
    int b = alturaNome(n->left) - alturaNome(n->right);
    if (b > 1 && alturaNome(n->left->left) >= alturaNome(n->left->right)) n = rotacaoDireitaNome(n);
    else if (b > 1) { n->left = rotacaoEsquerdaNome(n->left); n = rotacaoDireitaNome(n); }
    else if (b < -1 && alturaNome(n->right->right) >= alturaNome(n->right->left)) n = rotacaoEsquerdaNome(n);
    else if (b < -1) { n->right = rotacaoDireitaNome(n->right); n = rotacaoEsquerdaNome(n); }
}

void removerDaAVLRaridade(Item* &n, int raridade, string nome) {
    if (!n) return;
    if (raridade < n->raridade || (raridade == n->raridade && nome < n->nome))
        removerDaAVLRaridade(n->leftRaridade, raridade, nome);
    else if (raridade > n->raridade || (raridade == n->raridade && nome > n->nome))
        removerDaAVLRaridade(n->rightRaridade, raridade, nome);
    else {
        if (!n->leftRaridade || !n->rightRaridade) {
            Item *filho = n->leftRaridade ? n->leftRaridade : n->rightRaridade;
            delete n; n = filho;
        } else {
            Item *s = menorRaridade(n->rightRaridade); copiarDados(n, s);
            removerDaAVLRaridade(n->rightRaridade, s->raridade, s->nome);
        }
    }
    if (!n) return;
    n->alturaRaridade = 1 + maior(alturaRaridade(n->leftRaridade), alturaRaridade(n->rightRaridade));
    int b = alturaRaridade(n->leftRaridade) - alturaRaridade(n->rightRaridade);
    if (b > 1 && alturaRaridade(n->leftRaridade->leftRaridade) >= alturaRaridade(n->leftRaridade->rightRaridade)) n = rotacaoDireitaRaridade(n);
    else if (b > 1) { n->leftRaridade = rotacaoEsquerdaRaridade(n->leftRaridade); n = rotacaoDireitaRaridade(n); }
    else if (b < -1 && alturaRaridade(n->rightRaridade->rightRaridade) >= alturaRaridade(n->rightRaridade->leftRaridade)) n = rotacaoEsquerdaRaridade(n);
    else if (b < -1) { n->rightRaridade = rotacaoDireitaRaridade(n->rightRaridade); n = rotacaoEsquerdaRaridade(n); }
}

// Remove raridades abaixo de R nas duas AVLs e atualiza os índices do grafo.
int removerItensMenosRaros(int raridadeMinima, Item* &rootNome, Item* &rootRaridade)
{
    const int antigos = quantidadeItens;
    int mapa[MAX_ITENS];
    int removidos = 0;
    for (int i = 0; i < antigos; ++i) {
        if (itens[i].raridade < raridadeMinima) {
            removerDaAVLNome(rootNome, itens[i].nome);
            removerDaAVLRaridade(rootRaridade, itens[i].raridade, itens[i].nome);
            delete[] itens[i].contorno;
            itens[i].contorno = NULL;
            ++removidos;
            mapa[i] = -1;
        } else {
            mapa[i] = i - removidos;
        }
    }
    for (int i = 0; i < antigos; ++i) grafoNovo[i].clear();
    for (int i = 0; i < antigos; ++i) if (mapa[i] != -1) {
        for (list<Aresta>::iterator it = grafo[i].begin(); it != grafo[i].end(); ++it) {
            int destinoAntigo = it->destino;
            if (destinoAntigo >= 0 && destinoAntigo < antigos && mapa[destinoAntigo] != -1 && i < destinoAntigo) {
                int a = mapa[i], b = mapa[destinoAntigo];
                grafoNovo[a].push_back({a, b, it->peso});
                grafoNovo[b].push_back({b, a, it->peso});
            }
        }
    }
    for (int i = 0; i < antigos; ++i) { grafo[i].clear(); grafo[i].swap(grafoNovo[i]); }

    int novaQuantidade = quantidadeItens - removidos;
    for (int i = 0; i < antigos; ++i) if (mapa[i] != -1 && mapa[i] != i) {
        int destino = mapa[i];
        itens[destino].id = itens[i].id;
        itens[destino].nome = itens[i].nome;
        itens[destino].dono = itens[i].dono;
        itens[destino].propriedadeMagica = itens[i].propriedadeMagica;
        itens[destino].raridade = itens[i].raridade;
        itens[destino].contorno = itens[i].contorno;
        itens[destino].quantidadeContorno = itens[i].quantidadeContorno;
        itens[destino].left = itens[destino].right = NULL;
        itens[destino].leftRaridade = itens[destino].rightRaridade = NULL;
        itens[i].contorno = NULL;
    }
    quantidadeItens = novaQuantidade;
    cout << removidos << " item(ns) removido(s)." << endl;
    return removidos;
}

// Função principal do programa
int main()
{
    setlocale(LC_ALL, "pt_BR.UTF-8");

    Item *rootNome = NULL; // Raiz da árvore binária por nome
    Item *rootRaridade = NULL; // Raiz da árvore binária por raridade

    int opcao = -1;

    int id, raridade, idItem1, idItem2;
    int similaridade, valorMinimo, raridadeMinima, qtdPropriedade;

    string nomeItem, nomeDono, propriedadeMagica;
    string descarte;

    while (opcao != 0) {

        cout << "\n=================================================" << endl;
        cout << "                    M E N U                      " << endl;
        cout << "=================================================" << endl;
        cout << "0. Sair                                          " << endl;
        cout << "1. Inserir item.                                 " << endl;
        cout << "2. Cadastrar similaridade entre itens.           " << endl;
        cout << "3. Buscar itens similares.                       " << endl;
        cout << "4. Verificar a existência de um item.             " << endl;
        cout << "5. Listar itens (ordem alfabética de nome).       " << endl;
        cout << "6. Listar itens (ordem decrescente de raridade).  " << endl;
        cout << "7. Contar itens com mesma propriedade mágica.     " << endl;
        cout << "8. Remover itens menos raros.                     " << endl;
        cout << "-------------------------------------------------" << endl;

        cout << "Escolha uma opção: ";
        cin >> opcao;
        if (!cin.fail()) cout << opcao << endl;

        // Verifica se a opção digitada é numérica
        if (cin.fail()) {
            cin.clear();
            getline(cin, descarte);

            cout << "Entrada inválida! Digite um número." << endl;
            continue;
        }

        cin.ignore(10000, '\n');

        switch (opcao) {
            case 1:

                cout << "Nome do item: ";
                getline(cin, nomeItem);
                cout << nomeItem << endl;

                cout << "Nome do dono: ";
                getline(cin, nomeDono);
                cout << nomeDono << endl;

                cout << "Propriedade magica: ";
                getline(cin, propriedadeMagica);
                cout << propriedadeMagica << endl;

                cout << "ID: ";
                cin >> id;
                if (!cin.fail()) cout << id << endl;

                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(10000, '\n');

                    cout << "ID inválido!" << endl;
                    break;
                }

                cout << "Raridade (0 a 100): ";
                cin >> raridade;
                if (!cin.fail()) cout << raridade << endl;

                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(10000, '\n');

                    cout << "Raridade inválida!" << endl;
                    break;
                }

                cin.ignore(10000, '\n');

                // A abertura é definida na primeira tentativa de cadastro.
                if (!aberturaCadastrada) {
                    quantidadeAbertura = lerPoligono("poligono convexo da abertura da bolsa", aberturaBolsa);
                    if (!poligonoConvexo(aberturaBolsa, quantidadeAbertura)) {
                        cout << "Abertura invalida: informe um poligono convexo com pelo menos 3 vertices." << endl;
                        break;
                    }
                    aberturaCadastrada = true;
                }

                quantidadeContornoAtual = lerPoligono("contorno convexo do item", contornoItemAtual);
                if (!poligonoConvexo(contornoItemAtual, quantidadeContornoAtual)) {
                    cout << "Contorno invalido: informe um poligono convexo com pelo menos 3 vertices." << endl;
                    break;
                }
                if (!itemCabeNaAbertura(contornoItemAtual, quantidadeContornoAtual)) {
                    cout << "Item nao cabe na abertura da bolsa; cadastro cancelado." << endl;
                    break;
                }

                // Só insere nas árvores se o cadastro for válido
                if (inserirItem(nomeItem, nomeDono, propriedadeMagica, id, raridade) == 1) {
                    insert(rootNome, nomeItem, nomeDono, propriedadeMagica, id, raridade);
                    insertRaridade(rootRaridade, nomeItem, nomeDono, propriedadeMagica, id, raridade);

                    cout << "Item inserido com sucesso!" << endl;
                }
                quantidadeContornoAtual = 0;

                break;

            case 2:

                cout << "ID do primeiro item: ";
                cin >> idItem1;
                if (!cin.fail()) cout << idItem1 << endl;

                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(10000, '\n');

                    cout << "ID inválido!" << endl;
                    break;
                }

                cout << "ID do segundo item: ";
                cin >> idItem2;
                if (!cin.fail()) cout << idItem2 << endl;

                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(10000, '\n');

                    cout << "ID inválido!" << endl;
                    break;
                }

                cout << "Valor da similaridade: ";
                cin >> similaridade;
                if (!cin.fail()) cout << similaridade << endl;

                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(10000, '\n');

                    cout << "Similaridade inválida!" << endl;
                    break;
                }

                cin.ignore(10000, '\n');

                cadastrarSimilaridade(idItem1, idItem2, similaridade);

                break;

            // Busca de itens similares
            case 3:

                cout << "ID do item: ";
                cin >> id;
                if (!cin.fail()) cout << id << endl;

                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(10000, '\n');

                    cout << "ID inválido!" << endl;
                    break;
                }

                cin.ignore(10000, '\n');

                cout << "Nome do jogador cujos itens não devem ser incluídos: ";
                getline(cin, nomeDono);
                cout << nomeDono << endl;

                cout << "Valor minimo de similaridade: ";
                cin >> valorMinimo;
                if (!cin.fail()) cout << valorMinimo << endl;

                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(10000, '\n');

                    cout << "Valor mínimo inválido!" << endl;
                    break;
                }
                cin.ignore(10000, '\n');

                if (valorMinimo < 0 || valorMinimo > 100) {
                    cout << "O valor mínimo deve estar entre 0 e 100!" << endl;
                    break;
                }
                buscarItensSimilares(id, nomeDono, valorMinimo);

                break;

            case 4:

                cout << "Nome do item a ser verificado: ";
                getline(cin, nomeItem);
                cout << nomeItem << endl;

                if (search(rootNome, nomeItem) != NULL) {
                    cout << "Item encontrado!" << endl;
                } else {
                    cout << "Item não encontrado!" << endl;
                }

                break;

            case 5:

                if (rootNome == NULL) {
                    cout << "O inventário está vazio." << endl;
                } else {
                    cout << "\n--- ITENS EM ORDEM ALFABÉTICA ---" << endl;
                    show_in_order(rootNome);
                }

                break;

            case 6:
                if (rootRaridade == NULL) {
                    cout << "O inventário está vazio." << endl;
                } else {
                    cout << "\n--- ITENS EM ORDEM DECRESCENTE DE RARIDADE ---" << endl;
                    listarItensPorRaridade(rootRaridade);
                }

                break;

            case 7:

                cout << "Propriedade magica: ";
                getline(cin, propriedadeMagica);
                cout << propriedadeMagica << endl;

                qtdPropriedade = contarPropriedadeMagica(rootNome, propriedadeMagica);
                cout << "Quantidade de itens com a propriedade \"" << propriedadeMagica << "\": " << qtdPropriedade << endl;

                break;

            case 8:
                cout << "Raridade minima: ";
                cin >> raridadeMinima;
                if (!cin.fail()) cout << raridadeMinima << endl;

                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(10000, '\n');

                    cout << "Raridade inválida!" << endl;
                    break;
                }
                cin.ignore(10000, '\n');

                if (raridadeMinima < 0 || raridadeMinima > 100) {
                    cout << "A raridade deve estar entre 0 e 100!" << endl;
                    break;
                }
                removerItensMenosRaros(raridadeMinima, rootNome, rootRaridade);
                break;

            case 0:
                cout << "Saindo..." << endl;
                break;

            default:
                cout << "Entrada invalida!" << endl;
                break;
        }
        cout << endl;
    }

    destruct(rootNome);
    destructRaridade(rootRaridade);
    for (int i = 0; i < quantidadeItens; ++i) {
        delete[] itens[i].contorno;
        itens[i].contorno = NULL;
    }

    return 0;
}