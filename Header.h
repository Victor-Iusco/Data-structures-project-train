/* IUSCO Victor Stefan - grupa 312CB */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define SANTINELA '~'
/*-----------------------------------*/
typedef struct Vagon
{
    char info;
    struct Vagon *next, *prev;
} TVagon;
/*-----------------------------------*/
typedef struct trenulet
{
    TVagon *mekanik, *santinela;
} *TTren;
/*-----------------------------------*/
typedef struct comanda
{
    char *info;
    struct comanda *sus, *jos;
} TComanda;
/*-----------------------------------*/
typedef struct coada_de_comenzi
{
    TComanda *first, *last;
} TComenzi;
/*-----------------------------------*/

TTren InitTTren();
TComenzi* InitComenzi();
TVagon *CreareVagon(char info);
void AdaugareComanda(TComenzi* coada_de_comenzi, char *info);
void MOVE_LEFT(TTren c);//
void MOVE_RIGHT(TTren c);//
void INSERT_LEFT(TTren c, char info);
void INSERT_RIGHT(TTren c, char info);
void WRITE(TTren c, char info);
void CLEAR_CELL(TTren c);
void CLEAR_ALL(TTren c);
void SEARCH(TTren c, char *de_cautat, FILE* fileout);
void SEARCH_LEFT(TTren c, char *de_cautat, FILE* fileout);
void SEARCH_RIGHT(TTren c, char *de_cautat, FILE* fileout);
void SHOW(TTren c, FILE *fileout);
void SHOW_CURRENT(TTren c, FILE *fileout);
void SWITCH(TComenzi* coada);
void TRECI_LA_FUNCTIA_URMATOARE(TComenzi* coada);



