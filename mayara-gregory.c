/******************************************************************************
* arquivo: mayara-gregory.c 19/11/2016
* autor: Mayara Barbosa e Gregory Mendes
* curso: BSI
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* A estrutura abaixo define o registro do arquivo que deverá ser lido  */
typedef struct estrutura_paginas_virtuais{
    int valor;
    struct estrutura_paginas_virtuais *prox;
} stPagVirtual;

stPagVirtual *inicio, *pagina, *pag_ant;

int main(int argc, const char * argv[])
{

	FILE *arquivo;
	int valor;
	char req[10];

	arquivo = fopen ("/home/puc/SO1_Memorias/arquivo2.txt", "r");
    pagina = malloc(sizeof(struct estrutura_paginas_virtuais));
    inicio = pagina;
    pag_ant = pagina;
    inicio->valor=valor; 
    fgets(req,9,arquivo);       			/* Le o arquivo */
	valor = atoi(req);						/* Converte o string lido para inteiro */
	printf ("\nValor lido: %d", valor);
    inicio->valor=valor;
    inicio->prox = NULL;

	while(!feof(arquivo) )
	{
		fgets(req,9,arquivo);				/* Le o arquivo */
		if (!feof(arquivo))					/* Verifica se é fim de arquivo */
		{
			valor = atoi(req);
			printf ("\nValor lido: %d", valor);

            pagina = malloc(sizeof(stPagVirtual)); 		/* Aloca nova página na memória  */
            pagina->valor=valor;						

            pag_ant->prox = pagina;						/* Inclui a página na estrutura */
            pag_ant = pagina;
            pagina->prox = NULL;
		}
	}
    pagina = inicio;
    while (pagina != NULL)			/* passa por toda a lista e mostra o conteúdo  */
    {
  			printf ("\nValor da lista encadeada: %d", pagina->valor);
  			pagina = pagina->prox;
    }

    return (0);
}




