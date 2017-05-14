#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include "pilha.h"
#include <stdint.h>
#include <stdint.h>

/** *************************************************************************************
* Funcao: Edite uma expressao
*
* Descricao:
*   Permite o usuario editar uma expressao ao remover ou adicionar caracteres
*
* Requisitos:
*   expr seja um ponteiro valido para uma string contendo uma expressao
*
* Hipoteses:
*   expr seja um ponteiro para uma string ja declarada e preenchida
*   string expr termine com '\0'
*
* Assertivas de entrada:
*   expr: ponteiro para uma string contendo uma expressao
*
* Assertivas de saida:
*   Se o usuario nao modificar nada
*       a funcao não modifica expressao da entrada
*   FimSe
*   Se o usuario remover algum caracter
*       o(s) caracter(es) removido(s) da expressao recebida
*   FimSe
*   Se o usuario adicionar algum caracter
*       o(s) caracter(es) adicionado(s) a expressao recebida
*   FimSe
*
***************************************************************************************/
void editar(char *expr)
{
    /* assertiva: verifica se expr recebida eh vazia */
    if ( expr[0] == '\0' )
    {
        return;
    } /* if */


    char expr2[100];
    char oper[100];
    char nova[100];

    int i,
        j,
        z,
        x;
    int k = 0;
    int m = 0;

    char y = '0';

    for( i = 0, j = 0; expr[i] != '\0'; i++ )
    {
        if( expr[i] != ' ' && expr[i] != '\n' )
        {
            expr2[j] = expr[i];
            j++;
        } /* if */
    }/* for */

    expr2[j] = '\0';

    x = strlen(expr2);
    printf("\n");

    for( j = 0; j <= x; j++ )
    {
        for( i = 0; i <= x; i++ )
        {
            if(i == j)
            {
                printf("_");
            }/* if */
            printf("%c", expr2[i]);
        }/* for */

        printf("\n\nEscolha uma acao: \nA.\tpara adicionar\nE.\tpara apagar um caracter \nEnter.\tpara mover o cursor \n\nOpcao: ");

        scanf("%[^\n]c", &y);
        getchar();

        printf("\n");

        if (y == 'a' || y == 'A')
        {
            printf("Digite a operacao para ser adicionada: ");
            scanf("%[^\n]s", oper);
            getchar();

            y = strlen(oper);
            for( m = 0; m < y; m++ )
            {
                nova[k] = oper[m];
                k++;
            }/* for */
        }/* if */
        else if( y == 'e' || y == 'E' )
        {
            if(k > 0)
            {
                k--;
            }/* if */
        }/* if */

        nova[k] = expr2[j];
        k++;

        //limpaTela();

        y = '0';

        nova[k] = '\0';

        printf("Nova expressao: %s \n", nova);
    } /* for */

    //limpaTela();
    strcpy(expr, nova);
    printf("\n\n");

}/* editar */

/** *************************************************************************************
* Funcao: Testar expressao
*
* Descricao:
*   Verifica se uma expressao infixada eh valida
*
* Requisitos:
*   expr seja um ponteiro valido para uma string contendo uma expressao na forma infixada
*
* Hipoteses:
*   expr seja um ponteiro para uma string ja declarada e preenchida com uma expressao
*   string expr termine com '\0'
*
* Assertivas de entrada:
*   expr: ponteiro para uma string contendo uma expressao
*
* Assertivas de saida:
*    Se a expr for uma expressao valida na forma infixada
*        a funcao retorna 1
*    Senao
*        a funcao retorna 0
*    FimSe
*
***************************************************************************************/
int testarExpr(char *expr)
{
    /* assertiva: verifica se expr recebida eh vazia */
    if( expr[0] == '\0' )
    {
        return;
    } /* if */

    tipoPilha* p;
    char c = '\0';

    int i,
        operador = 0;

    p = criarPilha();

    for( i = 0; expr[i] != '\0'; i++ )
    {
        if( expr[i] == '+' || expr[i] == '-' || expr[i] == '*' || expr[i] == '/' || expr[i] == '^' )
        {
            if( c == '+' || c == '-' || c == '*' || c == '/' || c == '^' )
            {
                pilha_libera(p);
                return 0;
            }/* if */
        }/* if */
        else if( expr[i] == '(' )
        {
            inserirPilha( p, expr[i] );
        }/* if */
        else if( expr[i] == ')' )
        {
            if( pilha_vazia(p) )
            {
                pilha_libera(p);
                return 0;
            }/* if */
            else
            {
                removerPilha(p);
            }/* else */
        }/* if */

        c = expr[i];
    }/* for */
    if ( expr[i] == '\0' && (c == '+' || c == '-' || c == '*' || c == '/' || c == '^' ))
    {
        pilha_libera(p);
        return 0;
    }/* if */

    if( !pilha_vazia(p) )
    {
        pilha_libera(p);
        return 0;
    }/* if */
    pilha_libera(p);
    return 1;
}/* testarExpr */

/** *************************************************************************************
* Funcao: Comparar prioridades
*
* Descricao:
*   Verifica qual caracter tem maior prioridade de execucao
*
* Requisitos:
*   c1 e c2 sejam dois caracters
*
* Hipoteses:
*   os caracter c1 e c2 sejam dois operadores de '+', '-', '*', '/', '^' ou '('
*
* Assertivas de entrada:
*   c1: caracter de um operador
*   c2: caracter de um operador
*
* Assertivas de saida:
*    Se c1 tiver uma prioridade maior que c2
*        a funcao retorna 1
*    Senao
*        a funcao retorna 0
*    FimSe
*
***************************************************************************************/
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
}/* Prioridade */

/** *************************************************************************************
* Funcao: Transformar expressao para posfixada
*
* Descricao:
*   Transforma uma expressao na forma infixada para a forma posfixada ou polonesa reversa
*
* Requisitos:
*   expr seja um ponteiro valido para uma string contendo uma expressao na forma infixada correta
*
* Hipoteses:
*   pSaida seja um ponteiro valido para uma string vazia
*
* Assertivas de entrada:
*   expr: ponteiro para uma string contendo uma expressao na forma infixada
*   pSaida: ponteiro para uma string vazia
*
* Assertivas de saida:
*    a funcao adiciona na string pSaida a expressao expr na forma posfixada
*
* Inteface Explicita:
*
*
**/
void InfParaPos(char expr[], char *pSaida)
{
    /* verifica ponteiro pSaida eh null */
    if ( pSaida == NULL )
    {
        return;

    } /* if */

    /* verifica se expr recebida eh vazia */
    if ( !testarExpr( expr ))
    {
        return;
    } /* if */

    tipoPilha* p;

    int i = 0,
        j = 0,
        sair;

    char c1,
         c2;

    p = criarPilha();
    inserirPilha(p, '(');

    do
    {
        c1 = expr[i];
        i++;

        if(c1 >= '0' && c1 <= '9')
        {
            /*Le numeros, inclusive com mais de um caracter e '.' */
            do
            {
                pSaida[j] = c1;
                j++;
                c1 = expr[i];
                i++;
            } /* do */
            while((c1 >= '0' && c1 <= '9') || c1 == '.');

            /* adiciona espaco entre caracteres */
            pSaida[j] = ' ';
            j++;
            i--;
            c1 = expr[i-1];
        } /* if */

        else if( c1 == '+' || c1 == '-' || c1 == '*' || c1 == '/' || c1 == '^' )
        {
            sair = 0;
            while(!sair)
            {
                /* verifica prioridades pra decidir se eh hora de realizar a operacao */
                c2 = removerPilha(p);
                if(Prioridade(c1,c2))
                {
                    inserirPilha(p, c2);
                    inserirPilha(p, c1);
                    sair = 1;
                } /* if */
                else
                {
                    pSaida[j] = c2;
                    j++;
                    pSaida[j] = ' ';
                    j++;
                } /* else */
            } /* while */
        } /* if */

        else if(c1 == '(')
        {
            inserirPilha(p, '(');
        } /* if */

        else if( c1 == ')' || c1 == '\0' )
        {
            do
            {
                c2 = removerPilha(p);
                if(c2 != '(')
                {
                    pSaida[j] = c2;
                    j++;
                    pSaida[j] = ' ';
                    j++;
                } /* if */
            } /* do */
            while(c2 != '(');
        } /* if */
    } /* do */
    while(c1 != '\0');

    pSaida[j] = '\0';
    pilha_libera(p);
} /* InfParaPos */

/** *************************************************************************************
* Funcao: Calcular resultado
*
* Descricao:
*   Calcula resultado de uma expressao na forma infixada
*
* Requisitos:
*   expr seja um ponteiro valido para uma string contendo uma expressao na forma posfixada
*
* Hipoteses:
*   expr seja uma expressao valida na forma posfixada
*
* Assertivas de entrada:
*   expr: ponteiro para uma string contendo uma expressao na forma posfixada
*
* Assertivas de saida:
*    a funcao calcula e retorna o resultado da expressao expr recebida
*
***************************************************************************************/
int64_t  calcular(char *expr)
{
    /* assertiva: verifica se expr recebida eh vazia */
    if ( expr[0] == '\0' )
    {
        return 0;
    } /* if */

    tipoPilha* p;

    int i = 0,
        j = 0;

    char c,
         aux[10];

    int64_t  resp = 0.0;

    p = criarPilha();

    c = expr[i];
    i++;

    /* enquanto nao chegar ao final da string */
    while(c != '\0')
    {
        if( c >= '0' && c <= '9' )
        {
            /* le enquanto houver numeros ou '.' */
            do
            {
                aux[j] = c;
                j++;
                c = expr[i];
                i++;
            } /* do */
            while((c >= '0' && c <= '9') || c == '.');

            aux[j] = '\0';

            /* transforma numeros (char) em inteiros e os adiciona na pilha */
            int64_t  z = atof(aux);
            inserirPilha(p, z);

            j = 0;
            i--;
            c = expr[i-1];

        } /* if */
        else if(c == '+')
        {
            /* soma os dois numeros que estao no topo da pilha */
            int64_t  x, y = 0;
            y = removerPilha(p);
            x = removerPilha(p);
            /* adiciona o resultado na pilha */
            inserirPilha(p, x+y);

        } /* if */
        else if(c == '-')
        {
            /* subtrai os dois numeros que estao no topo da pilha */
            int64_t  x, y = 0;
            y = removerPilha(p);
            x = removerPilha(p);
            /* adiciona o resultado na pilha */
            inserirPilha(p, x-y);

        } /* if */
        else if(c == '*')
        {
            /* multiplica os dois numeros que estao no topo da pilha */
            int64_t  x, y = 0;
            y = removerPilha(p);
            x = removerPilha(p);
            inserirPilha(p, x*y);

        } /* if */
        else if(c == '/')
        {
            /* divide os dois numeros que estao no topo da pilha */
            int64_t  x, y = 0;
            y = removerPilha(p);
            x = removerPilha(p);
            inserirPilha(p, x/y);

        } /* if */
        else if(c == '^')
        {
            /* calcula o 2o elemento do topo elevado ao elemento do topo */
            int64_t  x, y = 0;
            y = removerPilha(p);
            x = removerPilha(p);
            inserirPilha(p, pow(x,y));
        } /* if */

        c = expr[i];
        i++;
    } /* while */
    if(!pilha_vazia(p))
    {
        /* elemento na pilha sera o resultado final */
        resp = removerPilha(p);
    } /* if */

    pilha_libera(p);
    return resp;
} /* calcular */
