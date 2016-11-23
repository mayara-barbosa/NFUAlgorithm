/******************************************************************************
* arquivo: gregoryemayara.c 22/11/2016
* autor: Gregory Mendes e Mayara Barbosa
* curso: BSI
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct linkedlist {
    int valor;
    struct linkedlist *proximo;
};

struct nfulinkedlist {
    int valor;
    int envelhecimento;
    struct nfulinkedlist *proximo;
};

typedef struct linkedlist Fila;
typedef struct nfulinkedlist ListaNFU;


Fila *inicioFila = NULL;
Fila *fimFila = NULL;
Fila *tempIndex = NULL;
int lengthFila = 0;
int pageFaults = 0;
//  1 -> 1 -> 1 -> 1 -> 1 -> LList
//  f                   i  FILA


// Variaveis para NFU
ListaNFU *getUltimoElemento(ListaNFU *index);
ListaNFU *getElemento(int valor, ListaNFU *index);
ListaNFU * getPaginaVelha(ListaNFU *index, ListaNFU *paginaVelha);

ListaNFU *listaNFU = NULL;
int lengthListaNFU = 0;
int pageFaultsNfu = 0;

//Metodos da NFU
void adicionarElementoListaNFU(int valor, int valorInicialEnvelhecimento) {
    ListaNFU *elemento = malloc(sizeof(ListaNFU));
    elemento->valor = valor;
    elemento->envelhecimento = valorInicialEnvelhecimento;
    elemento->proximo = NULL;
    if(listaNFU == NULL) {
        listaNFU = elemento;
    } else {
        ListaNFU *ultimo = getUltimoElemento(listaNFU);
        ultimo->proximo = elemento;
    }
    lengthListaNFU++;
}

ListaNFU *getUltimoElemento(ListaNFU *index) {
    if (index->proximo == NULL)
        return index;
    return getUltimoElemento(index->proximo);
}

ListaNFU *getElemento(int valor, ListaNFU *index)
{
    if(index->valor == valor)
        return index;
    else if(index->proximo == NULL)
        return NULL;
    return getElemento(valor, index->proximo);
}

void cicloCpuNfu(ListaNFU *index){
    if (index == NULL)
        return;
    if (index->proximo != NULL)
        cicloCpuNfu(index->proximo);
    index->envelhecimento = index->envelhecimento >> 1;
}

void trocarElementoNFU(int valor, ListaNFU *index, int valorInicialEnvelhecimento)
{
    index->valor = valor;
    index->envelhecimento = valorInicialEnvelhecimento;
}

void acessarPaginaNFU(ListaNFU *index, int valorInicialEnvelhecimento)
{
    index->envelhecimento = index->envelhecimento | valorInicialEnvelhecimento;//binary operator OR
}

ListaNFU * getPaginaVelha(ListaNFU *index, ListaNFU *paginaVelha)
{
    if (index->envelhecimento == 0) {
        return index;
    } else if (paginaVelha == NULL || index->envelhecimento < paginaVelha->envelhecimento) {
        paginaVelha = index;
    }

    if(index->proximo == NULL) {
        return paginaVelha;
    }
    return getPaginaVelha(index->proximo, paginaVelha);
}

int procurarElementoNFU(int valor, ListaNFU *index)
{
    if(index->valor == valor)
        return 1;
    if(index->proximo == NULL)
        return 0;
    return procurarElementoNFU(valor, index->proximo);
}

void imprimirListaNFU() {
    ListaNFU *index = listaNFU;
    printf("\nLista NFU: ");
    while(index != NULL) {
        printf("[%d | %d] ",index->valor, index->envelhecimento);
        index = index->proximo;
    }
}

int main(int argc, const char * argv[])
{
    FILE *arquivo;
	int valor;
	int leituras = 0;
	int quadros = 4;
    int paginas = 0;
    int valorInicialEnvelhecimento = 8;
    int opcaoArquivo;
    int opcao;
    char info[10];

    printf("Escolha o arquivo para leitura:");
    printf("\n1 - arquivo1.txt");
    printf("\n2 - arquivo2.txt");
    printf("\n3 - arquivo3.txt");
    printf("\n4 - arquivo4.txt");
    printf("\nEscolha: ");

    scanf("%d",&opcaoArquivo);

    switch(opcaoArquivo)
    {
        case 1:
            arquivo = fopen ("arquivo1.txt", "r");
            break;
        case 2:
            arquivo = fopen ("arquivo2.txt", "r");
            break;
        case 3:
            valorInicialEnvelhecimento = 512;
            arquivo = fopen ("arquivo3.txt", "r");
            printf("Selecione o numero de quadros:");
            printf("\n1 - 64 quadros");
            printf("\n2 - 256 quadros");
            printf("\n3 - 1024 quadros");
            printf("\n4 - 4096 quadros");
            printf("\nEscolha: ");
            scanf("%d", &opcao);

            switch(opcao)
            {
                case 1:
                    quadros = 64;
                    break;
                case 2:
                    quadros = 256;
                    break;
                case 3:
                    quadros = 1024;
                    break;
                case 4:
                    quadros = 4096;
                    break;
                default:
                    quadros = 64;
            }
            break;
        case 4:
            valorInicialEnvelhecimento = 512;
            arquivo = fopen ("arquivo4.txt", "r");
            printf("Selecione o numero de quadros:");
            printf("\n1 - 64 quadros");
            printf("\n2 - 256 quadros");
            printf("\n3 - 1024 quadros");
            printf("\n4 - 4096 quadros");
            printf("\nEscolha: ");
            scanf("%d", &opcao);

            switch(opcao)
            {
                case 1:
                    quadros = 64;
                    break;
                case 2:
                    quadros = 256;
                    break;
                case 3:
                    quadros = 1024;
                    break;
                case 4:
                    quadros = 4096;
                    break;
                default:
                    quadros = 64;
            }
            break;
        default:
            opcaoArquivo = 1;
            printf("Arquivo default: arquivo1.txt");
            arquivo = fopen ("arquivo1.txt", "r");
    }


	while(!feof(arquivo) )
	{
		fgets(info,9,arquivo);
		if (!feof(arquivo))
		{
		    paginas++;
		    leituras++;
			valor = atoi(info);
			// NFU
            if (leituras == 30 && opcaoArquivo == 3) {
                cicloCpuNfu(listaNFU);
                leituras = 1;
            } else if (opcaoArquivo != 3) {
                cicloCpuNfu(listaNFU);
            }
            if(lengthListaNFU < quadros) {
                adicionarElementoListaNFU(valor, valorInicialEnvelhecimento);
            } else if (lengthListaNFU == quadros) {
                if(procurarElementoNFU(valor, listaNFU) == 0)
                {
                    ListaNFU *paginaVelha = getPaginaVelha(listaNFU, NULL);
                    trocarElementoNFU(valor, paginaVelha, valorInicialEnvelhecimento);
                    pageFaultsNfu++;
                } else {
                    ListaNFU *index = getElemento(valor, listaNFU);
                    acessarPaginaNFU(index, valorInicialEnvelhecimento);
                }
            }
            imprimirListaNFU();
            printf("\n\n\n");
		}
	}

    printf("\n\n\nRESULTADOS DO ARQUIVO %d", opcaoArquivo);
	printf("\nNFU:\tQuadros: %d \t Paginas: %d \t Page Faults: %d\n\n\n", quadros, paginas, pageFaultsNfu);

    return (0);
}




