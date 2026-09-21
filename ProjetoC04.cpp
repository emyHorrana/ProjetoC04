#include <iostream>
#include <string>
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
    int raridade;      // 0 a 100
};


int inserirItem(string nomeItem, string nomeDono, string propriedadeMagica, int id, int raridade)
{
    cout << "Funcionalidade em construção" << endl;
    return 0;
}

int cadastrarSimilaridade(int idItem1, int idItem2, int similaridade)
{
    cout << "Funcionalidade em construção" << endl;
    return 0;
}

int buscarItensSimilares(int idItem, int valorMinimo)
{
    cout << "Funcionalidade em construção" << endl;
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

                inserirItem(nomeItem, nomeDono, propriedadeMagica, id, raridade);
                break;

            case 2:
                cout << "ID do primeiro item: ";
                cin >> idItem1;

                cout << "ID do segundo item: ";
                cin >> idItem2;

                cout << "Valor da similaridade: ";
                cin >> similaridade;

                cadastrarSimilaridade(idItem1, idItem2, similaridade);
                break;

            case 3:
                cout << "ID do item: ";
                cin >> id;

                cout << "Valor minimo de similaridade: ";
                cin >> valorMinimo;

                buscarItensSimilares(id, valorMinimo);
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