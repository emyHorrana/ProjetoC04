
#include <iostream>
#include <string>
#include <list>
#include <locale.h>

using namespace std;

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

    // Ponteiros da árvore organizada por nome
    Item *left;
    Item *right;

    // Ponteiros da árvore organizada por raridade
    Item *leftRaridade;
    Item *rightRaridade;
};

// Insere um item na árvore binária em ordem alfabética
void insert(Item* &current, string nome, string dono,string propriedadeMagica, int id, int raridade)
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

    } else if (nome < current->nome) {
        insert(current->left, nome, dono, propriedadeMagica, id, raridade);

    } else {
        insert(current->right, nome, dono, propriedadeMagica, id, raridade);
    }
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

    }
    else if (raridade < current->raridade || (raridade == current->raridade && nome < current->nome)) {
        insertRaridade(current->leftRaridade, nome, dono, propriedadeMagica, id, raridade);
    }
    else {
        insertRaridade(current->rightRaridade, nome, dono, propriedadeMagica, id, raridade);
    }
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
        cout << "-----------------------------" << endl;

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

// Libera a memória utilizada pela árvore binária
void destruct(Item * &current)
{
    if (current != NULL) {
        destruct(current->left);
        destruct(current->right);

        delete(current);
        current = NULL;
    }
}

const int MAX_ITENS = 40000;
Item itens[MAX_ITENS];
int quantidadeItens = 0;

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

int inserirItem(string nomeItem, string nomeDono,string propriedadeMagica, int id, int raridade)
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

    cout << "Itens similares encontrados:" << endl;

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
                cout << "-----------------------------" << endl;

                encontrou = true;
            }
        }
    }

    if (!encontrou) {
        cout << "Nenhum item encontrado com esses critérios." << endl;
    }

    return 0;
}

// Funcionalidades da Entrega Parcial 4 (Em construção)

// Lista os itens em ordem decrescente de raridade
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

    cout << "-----------------------------" << endl;

    // Percorre a subarvore da esquerda
    listarItensPorRaridade(current->leftRaridade);

    return 1;
}

// Conta os itens que possuem a mesma propriedade mágica
int contarPropriedadeMagica(string propriedadeMagica)
{
    cout << "Funcionalidade em construção" << endl;
    return 0;
}

// Remove os itens que possuem raridade abaixo do valor informado
int removerItensMenosRaros(int raridadeMinima)
{
    cout << "Funcionalidade em construção" << endl;
    return 0;
}

// Função principal do programa
int main()
{
    setlocale(LC_ALL, "pt_BR.UTF-8");

    Item *rootNome = NULL; // Raiz da árvore binária
    Item *rootRaridade = NULL;

    int opcao = -1;

    int id, raridade, idItem1, idItem2;
    int similaridade, valorMinimo, raridadeMinima;

    string nomeItem, nomeDono, propriedadeMagica;
    string descarte;

    while (opcao != 0) {

        cout << "=================================================" << endl;
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

                cout << "Nome do dono: ";
                getline(cin, nomeDono);

                cout << "Propriedade magica: ";
                getline(cin, propriedadeMagica);

                cout << "ID: ";
                cin >> id;

                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(10000, '\n');

                    cout << "ID inválido!" << endl;
                    break;
                }

                cout << "Raridade (0 a 100): ";
                cin >> raridade;

                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(10000, '\n');

                    cout << "Raridade inválida!" << endl;
                    break;
                }

                cin.ignore(10000, '\n');

                // Só insere na árvore se o cadastro for válido
                if (inserirItem(nomeItem, nomeDono, propriedadeMagica, id, raridade) == 1) {
                    insert(rootNome, nomeItem, nomeDono,propriedadeMagica, id, raridade);
                    insertRaridade(rootRaridade, nomeItem, nomeDono, propriedadeMagica, id, raridade);

                    cout << "Item inserido com sucesso!" << endl;
                }

                break;
            case 2:

                cout << "ID do primeiro item: ";
                cin >> idItem1;

                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(10000, '\n');

                    cout << "ID inválido!" << endl;
                    break;
                }

                cout << "ID do segundo item: ";
                cin >> idItem2;

                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(10000, '\n');

                    cout << "ID inválido!" << endl;
                    break;
                }

                cout << "Valor da similaridade: ";
                cin >> similaridade;

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

                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(10000, '\n');

                    cout << "ID inválido!" << endl;
                    break;
                }

                cin.ignore(10000, '\n');

                cout << "Nome do jogador cujos itens não devem ser incluídos: ";
                getline(cin, nomeDono);

                cout << "Valor minimo de similaridade: ";
                cin >> valorMinimo;

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
                    cout << "--- ITENS EM ORDEM ALFABÉTICA ---" << endl;
                    show_in_order(rootNome);
                }

                break;

            case 6:
                if (rootRaridade == NULL) {
                    cout << "O inventário está vazio." << endl;
                } else {
                    cout << "--- ITENS EM ORDEM DECRESCENTE DE RARIDADE ---" << endl;
                    listarItensPorRaridade(rootRaridade);
                }

                break;
            case 7:

                cout << "Propriedade magica: ";
                getline(cin, propriedadeMagica);

                contarPropriedadeMagica(propriedadeMagica);

                break;

            case 8:
                cout << "Raridade minima: ";
                cin >> raridadeMinima;

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
                removerItensMenosRaros(raridadeMinima);
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
    destruct(rootRaridade);

    return 0;
}
