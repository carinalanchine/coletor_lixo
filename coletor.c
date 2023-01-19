#include <stdio.h>
#include <stdlib.h>

#define true 1
#define false 0

typedef struct contadorReferencias {
    int contador;
    void* endereco;
    struct contadorReferencias* prox;
} Contador;

Contador* memoria = NULL;

void* malloc2(int tamanho)
{   
    Contador* novo = (Contador*)malloc(sizeof(Contador));
    novo->contador = 1;

    void* novoEndereco = malloc(tamanho);
    novo->endereco = novoEndereco;

    novo->prox = memoria;
    memoria = novo;

    return novoEndereco;
}

void coletaLixo()
{
    Contador* aux = memoria;
    Contador* anterior = NULL;

    while (aux->contador) {
        anterior = aux;
        aux = aux->prox;
    }

    if (anterior == NULL) 
        memoria = aux->prox;

    else 
        anterior->prox = aux->prox;

    free(aux->endereco);
    free(aux);
}

void atrib2(void** endereco1, void* endereco2)
{
    if (*endereco1 != endereco2) {

        Contador* aux = memoria;
        int flagEncontrou = 0;
        int zerouContador = false;

        while (flagEncontrou != 2) {

            if (aux->endereco == *endereco1) {

                aux->contador--;
                flagEncontrou++;

                if (!aux->contador)
                    zerouContador = true;

                if (endereco2 == NULL) break;
            }

            else if (aux->endereco == endereco2) {
                aux->contador++;
                flagEncontrou++;
            }

            aux = aux->prox;
        }

        *endereco1 = endereco2;
        if (zerouContador) coletaLixo();
    }
}

int dump()
{
    if (memoria == NULL) return false;

    Contador* aux = memoria;

    while (aux != NULL) {
        printf("\nEndereco: %p",aux->endereco);
        printf("\nReferencias: %d\n",aux->contador);
        aux = aux->prox;
    }

    return true;
}
