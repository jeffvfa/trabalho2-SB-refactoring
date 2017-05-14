/*
 * File:   main.c
 * Author: Matheus de Oliveira Vieira   13/0126420
 */

#include <stdio.h>
#include "calculadora.h"
#include <stdint.h>


void limpaTela()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}


int imprime_tela()
{

    char buf[BUFSIZ];
    int opcao = -0;

    do
    {
        /* imprime opcoes ao usuario */

        printf("***** Calculadora ***** \n\n");
        printf("Opcoes disponiveis: \n\n");
        printf("1. Inserir expressao \n");
        printf("3. Editar expressao \n");
        printf("4. Calcular expressao \n");
        printf("6. Sair da aplicacao \n");
        printf("\n");
        printf("Favor escolher uma opcao: ");

        /* le resposta do usuario*/
        if (fgets(buf, sizeof(buf), stdin) != NULL)
            opcao = atoi(buf);

        if(opcao < 1 || opcao > 6)
            printf("\n\nOpcao invalida! Digite novamente \n\n");

    }
    while(opcao < 1 || opcao > 6);

    return opcao;

}


int main(){
    char expr[100];
    char posfix[100];

    int i, opcao = 6;

    int64_t  resultado;

    //FILE *fp, *fp2;

    expr[0]		= '\0';
    posfix[0]	= '\0';

    /* abre arquivo contendo expressoes na forma infixada */
    //fp = fopen("expressao.txt", "r");

    do
    {

        opcao = imprime_tela();
        //limpaTela();
        switch(opcao)
        {

        case 1:
            /* inserir expressao */
            printf("\nInsira uma expressao na forma infixada: \n");
            scanf("%[^\n]s", expr);
            getchar();

            /* verifica se expressao esta correta antes de chamar a funcao InfParaPos */
            if(testarExpr(expr))
            {
                InfParaPos(expr, posfix);
                /* imprime a expressao na ordem posfixada */
                printf("Expressao na ordem polonesa reversa: \n");
                for(i = 0; posfix[i] != '\0'; i++)
                {
                    printf("%c", posfix[i]);
                }

                printf("\n\n");
            }
            else
            {
                printf("IMPRESSAO INCORRETA \n");
            }

            break;

        case 3:
            /* editar expressao */

            if(expr[0] != '\0')
            {
                editar(expr);

                InfParaPos(expr, posfix);
                /* verifica se expressao esta correta antes de chamar a funcao InfParaPos */
                printf("Expressao na ordem polonesa reversa: \n");
                for(i = 0; posfix[i] != '\0'; i++)
                {
                    printf("%c", posfix[i]);
                }

                printf("\n\n");
            }
            else
            {
                printf("Insira uma expressao no programa primeiro \n\n");
            }

            break;

        case 4:
            /* calcular expressao */
            if(posfix[0] != '\0')
            {
                resultado = calcular(posfix);
                /* imprime resultado da expressao */
                printf("%s = %d \n\n", expr, resultado);
            }
            else
            {
                printf("Insira uma expressao no programa primeiro \n\n");
            }

            break;


    }
  }
    /* continua programa enquanto usuario nao decidir sair */
    while( opcao != 6 );

    //fclose( fp );
    printf("\nOBRIGADO POR USAR A APLICACAO\n");

    return 0;
}
