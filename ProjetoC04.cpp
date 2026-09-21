#include <iostream>
#include <string>
#include <list>

using namespace std;

// Pedro Gabriel da Silva 739
// João Pedro Ramos Garcia 820
// Mariana Novais Portugal 746
// Emily Horrana Lima Rodrigues Armando 787
// Vinicius Oliveira Braga 743

struct Item
{
    string nome;
    string dono;
    string propriedadeMagica;
    int id;
    int raridade;
};

struct Aresta
{
    int origem;  
    int destino;
    int peso;
};

const int MAX_ITENS = 40000;
Item itens[MAX_ITENS];
int quantidadeItens = 0;

list<Aresta> grafo[MAX_ITENS];

int encontrarItem(int id)
{
    for(int i = 0; i < quantidadeItens; i++)
    {
        if(itens[i].id == id)
        {
            return i;
        }
    }
    return -1;
}

int inserirItem(string nomeItem, string nomeDono, string propriedadeMagica, int id, int raridade)
{
    if(quantidadeItens >= MAX_ITENS) {
        cout << "Inventário cheio!" << endl;
        return 0;
    }

    if(encontrarItem(id) != -1) {
        cout << "Erro: Já existe um item com o ID " << id << "!" << endl;
        return 0;
    }

    itens[quantidadeItens].nome = nomeItem;
    itens[quantidadeItens].dono = nomeDono;
    itens[quantidadeItens].propriedadeMagica = propriedadeMagica;
    itens[quantidadeItens].id = id;
    itens[quantidadeItens].raridade = raridade;

    quantidadeItens++;

    cout << "Item inserido com sucesso!" << endl;
    return 1;
}

int cadastrarSimilaridade(int idItem1, int idItem2, int similaridade)
{
    int indice1 = encontrarItem(idItem1);
    int indice2 = encontrarItem(idItem2);

    if(indice1 == -1 || indice2 == -1) {
        cout << "Erro: Um ou ambos os IDs não foram encontrados." << endl;
        return 0;
    }

    // Cria a aresta usando as posições reais no vetor
    grafo[indice1].push_back({indice1, indice2, similaridade});
    grafo[indice2].push_back({indice2, indice1, similaridade});

    cout << "Similaridade cadastrada com sucesso!" << endl;
    return 1;
}

int buscarItensSimilares(int idItem, string nomeDono, int valorMinimo)
{
    int posicaoItem = encontrarItem(idItem);

    if(posicaoItem == -1)
    {
        cout << "Item nao encontrado!" << endl;
        return 0;
    }

    list<Aresta>::iterator it;
    bool encontrou = false;

    cout << "Itens similares encontrados:" << endl;

    for(it = grafo[posicaoItem].begin(); it != grafo[posicaoItem].end(); it++)
    {
        if(it->peso > valorMinimo)
        {
            int posicaoDestino = it->destino;

            if(itens[posicaoDestino].dono != nomeDono) 
            {
                cout << "ID: " << itens[posicaoDestino].id << endl;
                cout << "Nome: " << itens[posicaoDestino].nome << endl;
                cout << "Dono: " << itens[posicaoDestino].dono << endl;
                cout << "Propriedade magica: " << itens[posicaoDestino].propriedadeMagica << endl;
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

int verificarItem(int idItem)
{
    cout << "Funcionalidade em construção" << endl;
    return 0;
}


int listarItensAlfabeticamente()
{
    cout << "Funcionalidade em construção" << endl;
    return 0;
}


int listarItensPorRaridade()
{
    cout << "Funcionalidade em construção" << endl;
    return 0;
}


int contarPropriedadeMagica(string propriedadeMagica)
{
    cout << "Funcionalidade em construção" << endl;
    return 0;
}


int removerItensMenosRaros(int raridadeMinima)
{
    cout << "Funcionalidade em construção" << endl;
    return 0;
}


int main()
{
    int opcao = -1;
    int id;
    int raridade;
    int idItem1;
    int idItem2;
    int similaridade;
    int valorMinimo;
    int raridadeMinima;
    string nomeItem;
    string nomeDono;
    string propriedadeMagica;


    while(opcao != 0)
    {
        cout << "=================================================" << endl;
        cout << "                    M E N U                      " << endl;
        cout << "=================================================" << endl;

        cout << "0. Sair                                          " << endl;
        cout << "1. Inserir item.                                 " << endl;
        cout << "2. Cadastrar similaridade entre itens.          " << endl;
        cout << "3. Buscar itens similares.                       " << endl;
        cout << "4. Verificar a existência de um item.            " << endl;
        cout << "5. Listar itens (ordem alfabética de nome).      " << endl;
        cout << "6. Listar itens (ordem decrescente de raridade). " << endl;
        cout << "7. Contar itens com mesma propriedade mágica.    " << endl;
        cout << "8. Remover itens menos raros.                    " << endl;

        cout << "-------------------------------------------------" << endl;

        cout << "Escolha uma opção: ";
        cin >> opcao;


        switch(opcao)
        {

            case 1:

                cout << "Nome do item: ";
                cin >> nomeItem;

                cout << "Nome do dono: ";
                cin >> nomeDono;

                cout << "Propriedade magica: ";
                cin >> propriedadeMagica;

                cout << "ID: ";
                cin >> id;
                cout << "Raridade (0 a 100): ";
                cin >> raridade;

                inserirItem(
                    nomeItem,
                    nomeDono,
                    propriedadeMagica,
                    id,
                    raridade
                );

                break;

            case 2:

                cout << "ID do primeiro item: ";
                cin >> idItem1;

                cout << "ID do segundo item: ";
                cin >> idItem2;

                cout << "Valor da similaridade: ";
                cin >> similaridade;


                cadastrarSimilaridade(
                    idItem1,
                    idItem2,
                    similaridade
                );

                break;

            case 3:

                cout << "ID do item: ";
                cin >> id;

                cout << "Nome do jogador: ";
                cin >> nomeDono;

                cout << "Valor minimo de similaridade: ";
                cin >> valorMinimo;


                buscarItensSimilares(
                    id,
                    nomeDono,
                    valorMinimo
                );

                break;

            case 4:

                cout << "ID do item: ";
                cin >> id;

                verificarItem(id);

                break;

            case 5:

                listarItensAlfabeticamente();

                break;

            case 6:

                listarItensPorRaridade();

                break;

            case 7:

                cout << "Propriedade magica: ";
                cin >> propriedadeMagica;

                contarPropriedadeMagica(propriedadeMagica);

                break;

            case 8:

                cout << "Raridade minima: ";
                cin >> raridadeMinima;

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


    return 0;
}