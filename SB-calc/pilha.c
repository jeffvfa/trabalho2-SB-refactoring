/*	Arquivo com o corpo das funções	*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "pilha.h"

/*	-----Funções de pilha-----	*/
/*Função para verificar se a pilha está vazia*/
int PilhaVazia(Pilha *p){
	return(p->topo == NULL);
}

/*Função de criar uma pilha*/
Pilha* CriarPilha(){
	Pilha* p = (Pilha*)malloc(sizeof(Pilha));
	p->topo = NULL;
	return (p);
}

/*Função de empilhar*/
void Push(Pilha* p, int64_t valor){
	Lista* novo = (Lista*)malloc(sizeof(Lista));
	novo->valor = valor;
	novo->prox = p->topo;
	p->topo = novo;
}

/*Função de remover da pilha*/
int64_t Pop(Pilha *p){
	Lista* t;
	int64_t valor;

	if(PilhaVazia(p)){
		printf("Pilha vazia.\n");
		return(-1);
	}else{
		t = p->topo;
		valor = t->valor;
		p->topo = t->prox;
		free(t);
		return(valor);
	}
}

/*Função que retorna o valor do elemento do topo da pilha*/
int64_t  TopoPilha(Pilha* p){
    if(PilhaVazia(p)){
		printf("Pilha vazia.\n");
        return (-1);
    }
    else{
        return (p->topo->valor);
    }
}

//Desaloca toda a pilha
void DestruirPilha (Pilha* p){
    Lista* q = p->topo;
    while (q!=NULL){
        Lista* t = q->prox;
        free(q);
        q = t;
    }
    free(p);
}
