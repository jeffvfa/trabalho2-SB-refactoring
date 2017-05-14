/*	Arquivo Header	*/
#include <stdint.h>
#include <stdint.h>

void editar(char *expr);
int testarExpr(char *expr);
int Prioridade(char c, char t);
void InfParaPos(char expr[], char *pSaida);
int64_t calcular(char *expr);
int64_t to48bit(int64_t);
