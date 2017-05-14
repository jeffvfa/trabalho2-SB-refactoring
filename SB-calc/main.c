/*	Arquivo com o corpo das funções	*/
#include <stdio.h>
#include <stdlib.h>
#include "calculadora.h"
#include <stdint.h>


void limpaTela(){
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}


int imprime_tela(){

    char buf[BUFSIZ];
    int opcao = -0;

    do{
        /* imprime opcoes ao usuario */

        printf("***** Calculadora ***** \n\n");
        printf("Opcoes disponiveis: \n\n");
        printf("1. Inserir expressao \n");
        printf("2. Editar expressao \n");
        printf("3. Calcular expressao \n");
        printf("4. Sair da aplicacao \n");
        printf("\n");
        printf("Favor escolher uma opcao: ");

        /* le resposta do usuario*/
        if (fgets(buf, sizeof(buf), stdin) != NULL)
            opcao = atoi(buf);

        if(opcao < 1 || opcao > 4)
            printf("\n\nOpcao invalida! Digite novamente \n\n");

    }
    while(opcao < 1 || opcao > 4);

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

    do{

        opcao = imprime_tela();
        limpaTela();
        switch(opcao){

        case 1:
            /* inserir expressao */
            printf("\nInsira uma expressao na forma infixada: \n");
            scanf("%[^\n]s", expr);
            getchar();

            /* verifica se expressao esta correta antes de chamar a funcao InfParaPos */
            if(testarExpr(expr)){
                InfParaPos(expr, posfix);
                /* imprime a expressao na ordem posfixada */
                printf("Expressao na ordem polonesa reversa: \n");
                for(i = 0; posfix[i] != '\0'; i++)
                {
                    printf("%c", posfix[i]);
                }

                printf("\n\n");
            }
            else{
                printf("IMPRESSAO INCORRETA \n");
            }

            break;

        case 2:
            /* editar expressao */

            if(expr[0] != '\0'){
                editar(expr);

                InfParaPos(expr, posfix);
                /* verifica se expressao esta correta antes de chamar a funcao InfParaPos */
                printf("Expressao na ordem polonesa reversa: \n");
                for(i = 0; posfix[i] != '\0'; i++){
                    printf("%c", posfix[i]);
                }

                printf("\n\n");
            }
            else{
                printf("Insira uma expressao no programa primeiro \n\n");
            }

            break;

        case 3:
            /* calcular expressao */
            if(posfix[0] != '\0'){
                resultado = calcular(posfix);
                /* imprime resultado da expressao */
                printf("%s = %ld \n\n", expr, resultado);
            }
            else{
                printf("Insira uma expressao no programa primeiro \n\n");
            }

            break;


    }
  }
    /* continua programa enquanto usuario nao decidir sair */
    while( opcao != 4 );

    //fclose( fp );

    return 0;
}
