#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fstream>
using namespace std;
typedef struct produto
{
    string codigo = "     ";
    string descricao = "                    ";
    int valor;
    int peso;
} produtos;
typedef produtos queue_element;
#include "Queue.h"


//==============================================================//
void lerArquivo(Queue &, produtos[]);
produto converteArqString(char []);
int stoi(string);
int calculaContainer(int, int, int[], int[], int []);
void printQ(Queue);
int valorTotal(Queue);
int pesoTotal(Queue);
//==============================================================//

int main()
{
    //Declaração da fila
    Queue fila;
    initQueue(fila);

    //Declaração da struct com no máximo de 100 produtos
    produtos todosProds[100];
    lerArquivo(fila, todosProds);


     //Printa todos os produtos escolhidos
    cout << "PRODUTOS ESCOLHIDOS" << endl;
    cout << "COD\t" << "DESCRICAO\t" << "VALOR\t" << "PESO" << endl;
    printQ(fila);
    cout << endl << endl << "VALOR TOTAL: USD " << valorTotal(fila) << endl;
    cout << "PESO TOTAL: " << pesoTotal(fila) << "g";
    return 0;
}


//==============================================================//


void lerArquivo(Queue& fila, produtos prod[]){
    char nomeArq[25], fraseArquivo[50];
    int numProdutos, tamContainer;
    int valor[100], peso[100], pos[100];

    FILE *file;
    cout << "Digite o nome do arquivo desejado: ";
    cin >> nomeArq;
    system("cls");
    strcat(nomeArq, ".txt");
    file = fopen(nomeArq, "r");

    if(file == NULL)
    {
        produto p;
        printf("Erro na abertura do arquivo");
        exit(1);
    }

    //Pega numero de produtos e tamanho do Container
    fscanf(file, "%d %d", &numProdutos, &tamContainer);

    //Pega o restante das informações do arquivo
    for(int i = 0; i < 100; i++)
    {
        produto pr;
        fscanf(file, "%s", fraseArquivo);
        pr = converteArqString(fraseArquivo);
        peso[i] = pr.peso;
        valor[i] = pr.valor;
        prod[i] = pr;
    }
    fclose(file);

    //Funcao para maximizar o lucro
    int p = calculaContainer(tamContainer, numProdutos, peso, valor, pos);

    for(; p>0; p--){
        insertQ(fila, prod[pos[p-1]]);
    }

}


//==============================================================//


produto converteArqString(char fraseArq[])
{
    produto p;
    string peso="               ";
    string valor="              ";
    int i=0, j=0;

    //Pega o codigo do produto
    for(i; fraseArq[i]!=44; i++)
    {
        p.codigo[i] = fraseArq[i];
    }
    i++;

    //Pega a descricao do produto
    for(i; fraseArq[i] != 44; i++)
    {
        p.descricao[j] = fraseArq[i];
        j++;
    }
    i++;

    //Pega o valor do produto
    j=0;
    for(i; fraseArq[i] != 44; i++)
    {
        valor[j] = fraseArq[i];
        j++;
    }
    i++;

    //Pega o peso do produto
    j=0;
    for(i; i < strlen(fraseArq); i++)
    {
        peso[j] = fraseArq[i];
        j++;
    }

    p.valor = stoi(valor);
    p.peso = stoi(peso);

    return p;
}


//==============================================================//



int stoi(string s)
{
    int n;
    char aux[s.length()] ;
    strcpy(aux, s.c_str());
    sscanf(aux, "%d", &n);
    return n;
}


//==============================================================//


int calculaContainer(int tamContainer, int numProd, int peso[], int valor[], int pos[])
{
    int tam;
    int** K = new int*[numProd+1];
    for(int i = 0; i < numProd+1; i++)
        K[i] = new int[tamContainer+1];

    for (int i = 0; i <= numProd; i++)
    {
        for (tam = 0; tam <= tamContainer; tam++)
        {
            if (i == 0 || tam == 0)
                K[i][tam] = 0;
            else if (peso[i - 1] <= tam)
                K[i][tam] = max(valor[i - 1] + K[i - 1][tam - peso[i - 1]], K[i - 1][tam]);
            else
                K[i][tam] = K[i - 1][tam];
        }
    }

    int res = K[numProd][tamContainer];
    int v=0;
    tam = tamContainer;
    for (int i = numProd; i > 0 && res > 0; i--)
    {

        if (res == K[i - 1][tam])
            continue;
        else
        {

            // This item is included.
            pos[v]=i-1;
            v++;

            // Since this weight is included its
            // value is deducted
            res = res - valor[i - 1];
            tam = tam - peso[i - 1];
        }
    }
    return v;
}


//==============================================================//


void printQ(Queue Q)
{
    produto x;
    while(!isEmptyQ(Q))
    {
        x = eliminate(Q);
        cout << x.codigo << "  " << x.descricao;
        printf("%-6d%-6d\n",x.valor,x.peso);
    }
}


//==============================================================//


int valorTotal(Queue Q)
{
    int soma=0;
    while(!isEmptyQ(Q))
    {
        produto Aux = eliminate(Q);
        soma+=Aux.valor;
    }
    return soma;
}


//==============================================================//


int pesoTotal(Queue Q)
{
    int soma = 0;
    while(!isEmptyQ(Q))
    {
        produto aux = eliminate(Q);
        soma = soma + aux.peso;
    }
    return soma;
}
