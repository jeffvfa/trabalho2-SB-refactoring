/*	Arquivo Header	*/
#include <stdio.h>
#include <stdint.h>

/*	Estrutura de Lista	*/
struct lista{
	int64_t valor;
	struct lista *prox;
};
typedef struct lista Lista;

/*	Estrutura de Pilha	*/
struct pilha{
	Lista* topo;
};
typedef struct pilha Pilha;

/*	Funções */
Pilha* CriarPilha();
void Push(Pilha* p, int64_t valor);
int64_t Pop(Pilha *p);
int PilhaVazia(Pilha *p);
int64_t PilhaTopo(Pilha* p);
void DestruirPilha (Pilha* p);
