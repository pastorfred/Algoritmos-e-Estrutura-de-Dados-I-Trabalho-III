#include "WordTree.hpp"
#include <sstream>
// #define DEBUG

//////////////////////////////////
//          WordTree            //
//////////////////////////////////
WordTree::WordTree()
{
    root = new CharNode(' ', "");
    totalNodes = 1;
    totalWords = 0;
}
int WordTree::getTotalWords() { return totalWords; }    // feito
int WordTree::getTotalNodes() { return totalNodes; }    // feito
void WordTree::addWord(string word, string significado) // feito
{
    CharNode *auxChar = root;
    for (char obj : word)
    {
        auxChar->addChild(obj, "");
        if (auxChar->findChildChar(obj) != nullptr)
            auxChar = auxChar->findChildChar(obj);
    }
    auxChar->significado = significado;
    totalWords++;
}

CharNode *WordTree::findCharNodeForWord(string word)
{
    int count = 0;        // count pra fazer o loop
    CharNode *aux = root; // nodo aux inicia no root da arvore
    while (count < word.length())
    {                                    // enquanto a palavra não acabou
        char letra = word[count];        // char letra = char na posicao count da palavra
        aux = aux->findChildChar(letra); // nodo aux = nodo na posicao do char letra
        count++;                         // incrementa o count (vai pra proxima letra)
    }
    return aux; // retorna o ultimo nodo inserido na lista (a ultima letra de count)
}

list<string> WordTree::searchAll(string prefix)
{
    list<string> palavras;                       // lista de palavras (que será retornada)
    CharNode *aux = findCharNodeForWord(prefix); // nodo aux que começa no final do prefixo
    if (aux != nullptr) //se houver um nodo no final do prefixo
    {
        if (aux->significado != "") // se a ultima letra do prefixo tiver significado
        {
            palavras.push_back(aux->getWord()); // coloca o nodo da letra no final da lista de palavras
            return palavras;                    // retorna a lista de palavras
        }                                       // se tiver um nodo no final do prefixo
        list<CharNode *>::iterator k;           // cria iterador k para percorrer a lista de subtrees
        for (k = aux->subtrees.begin(); k != aux->subtrees.end(); k++)
        {                                                   // enquanto não chega no final da lista de subtrees
            list<string> temp = searchAll((*k)->getWord()); // cria uma nova lista de strings temp e chama o metodo recursivamente para todos os filhos
            // isso é para não sobrescrever a lista de palavras
            // a recursão funciona pois a cada loop, uma letra e acresecntada ao final da palavra do nodo,
            // avancando o nodo aux um subtree para baixo
            palavras.merge(temp); //"merge" a lista temporária com a lista final
        }
    }
    return palavras; // retorna a lista de palavras
}

void WordTree::printLista(list<string> lista, string pal)
{
    list<string>::iterator k;
    cout << "Lista de palavras com o prefixo " << pal << ": " << endl;
    for (k = lista.begin(); k != lista.end(); k++)
    {
        cout << (*k) << endl;
    }
    cout << endl
         << "Escreva uma palavra da lista para achar a definicao: " << endl;
    string palavra;
    cin >> palavra;
    CharNode *pala = findCharNodeForWord(palavra);
    for (k = lista.begin(); k != lista.end(); k++)
    {
        if (pala->getWord() == (*k))
        {
            cout << endl << pala->getWord() << ": " << pala->significado << endl << endl;
            return; 
        }
    }
}

/*
list<string> WordTree::searchAll(string prefix)
{
    list<string> palavras;
    CharNode *aux = findCharNodeForWord(prefix);
    palavras = searchAllRec(aux, palavras);
    return palavras;
}

list<string> WordTree::searchAllRec(CharNode *nodo, list<string> palavras)
{
    if (nodo != nullptr)
    {
        for (int i = 0; i < nodo->getSubtreesSize(); i++)
        {
            list<CharNode *>::iterator k;
            for (k = nodo->subtrees.begin(); k != nodo->subtrees.end(); k++)
            {
                if ((*k)->significado != "")
                {
                    palavras.push_back((*k)->getWord());
                }
            }
            list<string> temp = searchAllRec(nodo->getSubtree(i), palavras);
            palavras.merge(temp);
        }
    }
    return palavras;
}
*/
//////////////////////////////////
//          CharNode            //
//////////////////////////////////
CharNode::CharNode(char element, string significado) // feito
{
    father = NULL;
    character = element;
    this->significado = significado;
}
CharNode *CharNode::addChild(char element, string significado) // feito
{
    CharNode *auxCharNode = findChildChar(element);
    if (auxCharNode != nullptr)
    {
        auxCharNode->significado = significado;
        return auxCharNode;
    }

    auxCharNode = new CharNode(element, significado);
    auxCharNode->father = this;
    subtrees.push_back(auxCharNode);
    return auxCharNode;
}
int CharNode::getSubtreesSize() // feito
{
    return (int)subtrees.size();
}
CharNode *CharNode::getSubtree(int idx) // feito
{
    list<CharNode *> aux = subtrees;
    for (int i = 0; i < idx; i++)
    {
        aux.pop_front();
    }
    return aux.front();
}
string CharNode::getWord() // feito
{
    stringstream ss;
    CharNode *auxChar = this;
    list<char> aux;
    aux.clear();
    while (auxChar->character != ' ')
    {
        aux.push_front(auxChar->character);
        auxChar = auxChar->father;
    }
    while (aux.size())
    {
        ss << aux.front();
        aux.pop_front();
    }
    return ss.str();
}
CharNode *CharNode::findChildChar(char element) // feito
{
    list<CharNode *> auxLista = subtrees;
    while (auxLista.size())
    {
        if (element == auxLista.front()->character)
            break;
        auxLista.pop_front();
    }
    if (auxLista.size())
        return auxLista.front();
    return nullptr;
}
