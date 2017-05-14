/*
 * File:   pilha.c
 * Author: Matheus de Oliveira Vieira	13/0126420
 */

#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"
#include <stdint.h>

//Criar pilha
tipoPilha* criarPilha()
{
    tipoPilha* p = (tipoPilha*) malloc(sizeof(tipoPilha));
    p->topo = NULL;
    return p;
}

//Inserir elemento na pilha
void inserirPilha(tipoPilha* p, int64_t  n)
{
    Lista* novo = (Lista*) malloc(sizeof(Lista));
    novo->info = n;
    novo->prox = p->topo;
    p->topo = novo;
}

//Remover elemento na pilha
int64_t  removerPilha(tipoPilha* p)
{
    Lista* t;
    int64_t  v;
    if(pilha_vazia(p))
    {
        //printf("A pilha ja esta vazia\n");
        return (-1); //Retorna -1 para mostrar que a pilha ja estava vazia
    }
    t = p->topo;
    v = t->info;
    p->topo = t->prox;
    free(t);
    //printf("Elemento '%d' foi removido!\n\n", v);
    return v;
}

//Retorna elemento do topo da pilha
int64_t  topoPilha(tipoPilha* p)
{
    if(pilha_vazia(p))
    {
        //printf("A pilha esta vazia\n");
        return (-1); //Retorna -1 para mostrar que a pilha estava vazia
    }
    else
    {
        //printf("Elemento no topo: %d", p->topo->info);
        return (p->topo->info);
    }
}

//Diz se a pilha eh vazia ou nao
int pilha_vazia(tipoPilha* p)
{
    return (p->topo == NULL);
}

//Desaloca toda a pilha
void pilha_libera (tipoPilha* p)
{
    Lista* q = p->topo;
    while (q!=NULL)
    {
        Lista* t = q->prox;
        free(q);
        q = t;
    }
    free(p);
    //printf("Pilha Liberada!");
}
