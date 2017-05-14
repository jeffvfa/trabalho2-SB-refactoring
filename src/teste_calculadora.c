/*
 * File:   teste_paratentizacao.c
 * Author: Matheus de Oliveira Vieira	13/0126420
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <CUnit/Basic.h>
#include "pilha.h"
#include "calculadora.h"

/*
 * CUnit Test Suite
 */

void limpaTela()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

FILE *fp;

int init_suite(void)
{
    fp = fopen("expressao.txt", "r");
    return 0;
}

int clean_suite(void)
{
    fclose(fp);
    return 0;
}

void testAbrirArquivo()
{
    CU_ASSERT(NULL != fp);
}

void testPrioridade()
{
    int OK[6];
    int i;

    OK[0] = !Prioridade('+','*');
    OK[1] = !Prioridade('-','-');
    OK[2] = !Prioridade('*','^');
    OK[3] = Prioridade('/','(');
    OK[4] = Prioridade('^','+');
    OK[5] = Prioridade('(','/');

    for(i = 0; i < 6; i++)
    {
        if(OK[i] == 0)
        {
            CU_ASSERT(0);
        }
    }

    CU_ASSERT(1);
}

void testTestarExpressao()
{
    CU_ASSERT(testarExpr("7+((1+2)*4)-3"));
}

void testOperadoresSeguidos()
{
    CU_ASSERT(!testarExpr("1++2"));
}

void testParentetizacao1()
{
    CU_ASSERT(!testarExpr("(1*5))"));
}

void testParentetizacao2()
{
    CU_ASSERT(!testarExpr("(1*5))+10"));
}

void testParentetizacao3()
{
    CU_ASSERT(!testarExpr("((1*5)+10"));
}

void testOperadorUlimoCaracter()
{
    CU_ASSERT(!testarExpr("5+5*"));
}

void testInfixadaParaPosfixada()
{
    char saida[50];
    char saida_esperada[] = "70 1 2 + 4 * + 3 - ";

    InfParaPos("70+((1+2)*4)-3", saida);

    CU_ASSERT(!strcmp(saida, saida_esperada));
}

void testCalcular()
{
    /* Infixado: 70/2 + ((1 + 2^2) * 4) - 3 */
    CU_ASSERT(52.0 == calcular("70 2 / 1 2 2 ^ + 4 * + 3 - "));
}

void testEditar()
{
    char expr[]		= "10+2";
    char expr2[]	= "1+20";

    printf("\n\n********************************************************\n");
    printf("ATENCAO: REMOVA O NUMERO 0 do 10 E O ADICIONE APOS O 2 \n");
    printf("O RESULTADO DEVE SER \"1+20\"");
    printf("\n********************************************************\n");

    editar(expr);

    CU_ASSERT( !strcmp( expr, expr2 ));
}


int main()
{
    CU_pSuite pSuite = NULL;

    /* Initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* Add the suite to the registry */
    pSuite = CU_add_suite("Suite_1", init_suite, clean_suite);
    if (NULL == pSuite)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Add the tests to the suite*/
    if 	(
        (NULL == CU_add_test(pSuite, "testAbrirArquivo", testAbrirArquivo)) ||
        (NULL == CU_add_test(pSuite, "testPrioridade", testPrioridade)) ||
        (NULL == CU_add_test(pSuite, "testTestarExpressao", testTestarExpressao)) ||
        (NULL == CU_add_test(pSuite, "testOperadoresSeguidos", testOperadoresSeguidos)) ||
        (NULL == CU_add_test(pSuite, "testParentetizacao1", testParentetizacao1)) ||
        (NULL == CU_add_test(pSuite, "testParentetizacao2", testParentetizacao2)) ||
        (NULL == CU_add_test(pSuite, "testParentetizacao3", testParentetizacao3)) ||
        (NULL == CU_add_test(pSuite, "testOperadorUlimoCaracter", testOperadorUlimoCaracter)) ||
        (NULL == CU_add_test(pSuite, "testInfixadaParaPosfixada", testInfixadaParaPosfixada))  ||
        (NULL == CU_add_test(pSuite, "testCalcular", testCalcular)) ||
        (NULL == CU_add_test(pSuite, "testEditar", testEditar))
        //(NULL == CU_add_test(pSuite, "", ))
        //(NULL == CU_add_test(pSuite, "", ))
    )
    {
        CU_cleanup_registry();
        return CU_get_error();
    }


    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
