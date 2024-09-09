#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "WordTree.hpp"
#include "splitCSV.hpp"

using namespace std;

bool carregaDicionario(string nomeArq, int quantCampos, list<Palavra> *lista);
void imprimeLista(list<Palavra> *lista);

int main()
{

    // carrega a lista com os significados
    list<Palavra> lista;
    if (carregaDicionario("dicionario.csv", 2, &lista) != true)
        return false;
    //////////////////////////////////////
    WordTree tree;
    for (auto it : lista)
    {
        tree.addWord(it.getPalavra(), it.getSignificado());
    }

    //o programa só para de rodar se uma palavra que não está na árvore é chamada
    while (1)
    {
        string pal;
        cout << "Por favor digite um prefixo para a busca: ";
        cin >> pal;
        list<string> lista2 = tree.searchAll(pal);
        tree.printLista(lista2, pal);
    }
}

bool carregaDicionario(string nomeArq, int quantCampos, list<Palavra> *lista)
{
    ifstream f(nomeArq);
    if (!f.is_open())
        return false;
    string linhaCSV;

    while (getline(f, linhaCSV))
    {
        vector<string> campos = splitCSV(linhaCSV, ';');
        if (campos.size() != quantCampos)
        {
            f.close();
            return false;
        }
        // adicionar aqui
        Palavra p(campos[0], campos[1]);
        lista->push_back(p);
    }
    f.close();
    return true;
}
void imprimeLista(list<Palavra> *lista)
{
    if (lista->size() != 0)
        while (lista->size() > 0)
        {
            cout << lista->front().getPalavra() << ": " << lista->front().getSignificado() << endl;
            lista->pop_front();
        }
    else
        cout << "A lista esta vazia!";
}
