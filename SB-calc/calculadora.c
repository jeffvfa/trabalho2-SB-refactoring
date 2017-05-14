/*	Arquivo com o corpo das funções	*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "pilha.h"
#include <stdint.h>


int64_t to48bit(int64_t num64){
  return num64 & 0x0000FFFFFFFFFFFF;;
}
int64_t modulo(int64_t num){
  int64_t z = (num>0)? num: (-num);
  return z;
}

/* Permite o usuario editar uma expressao ao remover ou adicionar caracteres */
void editar(char *expr){
    if ( expr[0] == '\0' ){
        return ;
    }


    char expr2[100];
    char oper[100];
    char nova[100];

    int i, j, x;
    int k = 0;
    int m = 0;

    char y = '0';

    for( i = 0, j = 0; expr[i] != '\0'; i++ ){
        if( expr[i] != ' ' && expr[i] != '\n' ){
            expr2[j] = expr[i];
            j++;
        }
    }

    expr2[j] = '\0';

    x = strlen(expr2);
    printf("\n");

    for( j = 0; j <= x; j++ ){
        for( i = 0; i <= x; i++ ){
            if(i == j){
                printf("_");
            }
            printf("%c", expr2[i]);
        }

        printf("\n\nEscolha uma acao: \nA.\tpara adicionar\nE.\tpara apagar um caracter \nEnter.\tpara mover o cursor \n\nOpcao: ");

        scanf("%[^\n]c", &y);
        getchar();

        printf("\n");

        if (y == 'a' || y == 'A'){
            printf("Digite a operacao para ser adicionada: ");
            scanf("%[^\n]s", oper);
            getchar();

            y = strlen(oper);
            for( m = 0; m < y; m++ ){
                nova[k] = oper[m];
                k++;
            }
        }else if( y == 'e' || y == 'E' ){
            if(k > 0){
                k--;
            }
        }

        nova[k] = expr2[j];
        k++;

        //limpaTela();

        y = '0';

        nova[k] = '\0';

        printf("Nova expressao: %s \n", nova);
    }

    //limpaTela();
    strcpy(expr, nova);
    printf("\n\n");

}


/* Verifica se uma expressao infixada eh valida */
int testarExpr(char *expr){
    if( expr[0] == '\0' ){
        return 0;
    } /* if */

    Pilha* p;
    char c = '\0';
    int i;

    p = CriarPilha();

    for( i = 0; expr[i] != '\0'; i++ ){
        if( expr[i] == '+' || expr[i] == '-' || expr[i] == '*' || expr[i] == '/' || expr[i] == '^' ){
            if( c == '+' || c == '-' || c == '*' || c == '/' || c == '^' ){
                DestruirPilha(p);
                return 0;
            }
        }
        else if( expr[i] == '(' ){
            Push( p, expr[i] );
        }
        else if( expr[i] == ')' ){
            if( PilhaVazia(p) ){
                DestruirPilha(p);
                return 0;
            }else{
                Pop(p);
            }
        }

        c = expr[i];
    }
    if ( expr[i] == '\0' && (c == '+' || c == '-' || c == '*' || c == '/' || c == '^' )){
        DestruirPilha(p);
        return 0;
    }

    if( !PilhaVazia(p) ){
        DestruirPilha(p);
        return 0;
    }

    DestruirPilha(p);

    return 1;
}

/* Verifica qual caracter tem maior prioridade de execucao */
int Prioridade(char c1, char c2)
{
    int pri1,
        pri2;

    if(c1 == '+' || c1 == '-')
        pri1 = 1;
    else if(c1 == '*' || c1 == '/')
        pri1 = 2;
    else if(c1 == '^')
        pri1 = 4;
    else if(c1 == '(')
        pri1 = 4;

    if(c2 == '(')
        pri2 = 0;
    else if(c2 == '+' || c2 == '-')
        pri2 = 1;
    else if(c2 == '*' || c2 == '/')
        pri2 = 2;
    else if(c2 == '^')
        pri2 = 3;

    return (pri1 > pri2);
}

/*   Transforma uma expressao na forma infixada para a forma posfixada ou polonesa reversa */
void InfParaPos(char expr[], char *pSaida){

    if ( pSaida == NULL ){
        return ;

    }

    if ( !testarExpr( expr )){
        return ;
    }

    Pilha* p;

    int i = 0;
    int j = 0;
    int sair;

    char c1,c2;

    p = CriarPilha();
    Push(p, '(');

    do{
        c1 = expr[i];
        i++;

        if(c1 >= '0' && c1 <= '9'){

            do{
                pSaida[j] = c1;
                j++;
                c1 = expr[i];
                i++;
            }
            while((c1 >= '0' && c1 <= '9') || c1 == '.');

            /* adiciona espaco entre caracteres */
            pSaida[j] = ' ';
            j++;
            i--;
            c1 = expr[i-1];
        }else if( c1 == '+' || c1 == '-' || c1 == '*' || c1 == '/' || c1 == '^' ){
            sair = 0;
            while(!sair){
                /* verifica prioridades pra decidir se eh hora de realizar a operacao */
                c2 = Pop(p);
                if(Prioridade(c1,c2)){
                    Push(p, c2);
                    Push(p, c1);
                    sair = 1;
                }else{
                    pSaida[j] = c2;
                    j++;
                    pSaida[j] = ' ';
                    j++;
                }
            }
        }else if(c1 == '('){
            Push(p, '(');
        }

        else if( c1 == ')' || c1 == '\0' ){
            do{
                c2 = Pop(p);
                if(c2 != '('){
                    pSaida[j] = c2;
                    j++;
                    pSaida[j] = ' ';
                    j++;
                }
            }
            while(c2 != '(');
        }
    }
    while(c1 != '\0');

    pSaida[j] = '\0';
    DestruirPilha(p);
}

/* Calcula resultado de uma expressao na forma infixada */
int64_t  calcular(char *expr){
    if ( expr[0] == '\0' ){
        return 0;
    }

    Pilha* p;

    int i = 0;
	int j = 0;

    char c, aux[10];

    int64_t  resp = 0;

    p = CriarPilha();

    c = expr[i];
    i++;

    /* enquanto nao chegar ao final da string */
    while(c != '\0'){
        if( c >= '0' && c <= '9' ){
            /* le enquanto houver numeros ou '.' */
            do{
                aux[j] = c;
                j++;
                c = expr[i];
                i++;
            }
            while((c >= '0' && c <= '9') || c == '.');

            aux[j] = '\0';

            /* transforma numeros (char) em inteiros e os adiciona na pilha */
            int64_t  z = atof(aux);
            if((modulo(z) & 0xFFFF000000000000) != 0){
              printf("o número não pode ser representado em 48bits\n");
              return 0;
            }
            z = to48bit(z);
            Push(p, z);

            j = 0;
            i--;
            c = expr[i-1];

        }else if(c == '+'){
            /* soma os dois numeros que estao no topo da pilha */
            int64_t  x, y = 0;
            y = Pop(p);
            x = Pop(p);

            if((modulo(x+y) & 0xFFFF000000000000) != 0){
              printf("o número não pode ser representado em 48bits\n");
              return 0;
            }
            /* adiciona o resultado na pilha */
            Push(p, x+y);

        }else if(c == '-'){
            /* subtrai os dois numeros que estao no topo da pilha */
            int64_t  x, y = 0;
            y = Pop(p);
            x = Pop(p);
            /* adiciona o resultado na pilha */

            if((modulo(x-y) & 0xFFFF000000000000) != 0){
              printf("o número não pode ser representado em 48bits\n");
              return 0;
            }

            Push(p, x-y);

        }else if(c == '*'){
            /* multiplica os dois numeros que estao no topo da pilha */
            int64_t  x, y = 0;
            y = Pop(p);
            x = Pop(p);

            if((modulo(x*y) & 0xFFFF000000000000) != 0){
              printf("o número não pode ser representado em 48bits\n");
              return 0;
            }

            Push(p, x*y);

        }else if(c == '/'){
            /* divide os dois numeros que estao no topo da pilha */
            int64_t  x, y = 0;
            y = Pop(p);
            x = Pop(p);

            if((modulo(x/y) & 0xFFFF000000000000) != 0){
              printf("o número não pode ser representado em 48bits\n");
              return 0;
            }

            Push(p, x/y);

        }
        else if(c == '^'){
            // calcula o 2o elemento do topo elevado ao elemento do topo
            int64_t  x, y = 0;
            y = Pop(p);
            x = Pop(p);

            y = pow(x,y);
            if((modulo(y) & 0xFFFF000000000000) != 0){
              printf("o número não pode ser representado em 48bits\n");
              return 0;
            }

            Push(p, pow(x,y));
        }

        c = expr[i];
        i++;
    }
    if(!PilhaVazia(p)){
        /* elemento na pilha sera o resultado final */
        resp = Pop(p);
    }

    DestruirPilha(p);
    return resp;
}
