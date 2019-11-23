#include <iostream>
#include <string.h>
#include <fstream>
using namespace std;

#define MAX_PROD 100
//Struct que armazena todos os produtos presentes
typedef struct product{
	char codigo[5];
	char descricao[40];
	int valor;
	int peso;
}produto;

typedef struct {
	produto prod[MAX_PROD];     //100 produtos
	int valor = 0;              //Valor total
	int peso = 0;               //Peso total
	int n = 0;                  //Quantidade de produtos em prods
}listaProdutos;
typedef produto queue_element;
#include "Queue.h"


//==================FUNÇÕES======================//
void lerArquivo(int *, int *, Queue&);
produto converteArqString(char[]);
void calculaValor(listaProdutos&, listaProdutos&, Queue&, int);
//===============================================//


int main()
{
    //Declara e inicia a fila
    Queue fila;
    initQueue(fila);

    //Capacidade e quantidade de produtos do container
    int numProdutos, tamContainer;

    lerArquivo(&numProdutos, &tamContainer, fila);

    listaProdutos atual;
    listaProdutos principal;


    return 0;
}


//===============================================//


//Ler e armazenar todas as informações necessárias
void lerArquivo(int* numProdutos, int* tamContainer, Queue& fila)
{
    char fraseArquivo[50];
    int valor, peso;
    char nomeArq[20];

    cout << "Digite o nome do arquivo a ser lido: ";
    cin >> nomeArq;
    system("cls");

    //Concatena com ".txt" para poder ler o arquivo
    strcat(nomeArq, ".txt");

    FILE *file;
    file = fopen(nomeArq, "r");

    if(file == NULL)
    {
        printf("Erro na abertura do arquivo");
        exit(0);
    }

    //Leitura do numero de produtos e tamanho do container
    fscanf(file, "%d %d", numProdutos, tamContainer);

    //Leitura das informações de um produto
    for(int i = 0; i < 100; i++)
    {
        fscanf(file, "%s", fraseArquivo);
        produto prod;

        //Função recebe uma linha do arquivo
        //Ex. AAAAA, ProdX, 10, 100
        prod = converteArqString(fraseArquivo);
        insertQ(fila, prod);
    }
    fclose(file);
}


//===============================================//


//Joga as informações dos produtos para a struct
produto converteArqString(char fraseArq[]){

    produto prod;
    char valor[10];
    char peso[10];
    int i = 0, j = 0;

    //Pega o codigo do produto
    for(i; fraseArq[i] != ','; i++){
        prod.codigo[i] = fraseArq[i];
    }
    i++;
    cout << prod.codigo << endl;

    //Pega a descricao do produto
    for(i; fraseArq[i] != ','; i++){
        prod.descricao[j] = fraseArq[i];
        j++;
    }
    i++;
    //cout << prod.descricao << endl;

    //Pega o valor do produto
    j = 0;
    for(i; fraseArq[i] != ','; i++){
        valor[j] = fraseArq[i];
        j++;
    }
    i++;
    //cout << valor << endl;

    //Pega o peso do produto
    j = 0;
    for(i; i < strlen(fraseArq); i++){
        peso[j] = fraseArq[i];
        j++;
    }
    //cout << peso << endl;

    //Converte peso e valor para inteiro
    prod.valor = atoi(valor);
    prod.peso = atoi(peso);


    //cout << prod.codigo << "|" << prod.descricao << "|" << prod.valor << "|" << prod.peso << endl;
    return prod;
}


//===============================================//


//Função que calcula a maximização do lucro
void calculaValor(listaProdutos& atual, listaProdutos& principal, Queue& fila, int tamContainer){
}
