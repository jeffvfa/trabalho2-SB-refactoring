#include <stdint.h>
/*
 * File:   pilha.h
 * Author: Matheus de Oliveira Vieira	13/0126420
 */

typedef struct lista
{
    int64_t  info;
    struct lista *prox;
} Lista;

typedef struct tpPilha
{
    Lista *topo;
} tipoPilha;

tipoPilha* criarPilha(void);

void inserirPilha(tipoPilha* p, int64_t  n);

int64_t  removerPilha(tipoPilha* p);

int64_t  topoPilha(tipoPilha* p);

int pilha_vazia(tipoPilha* p);

void pilha_libera (tipoPilha* p);
