/* IUSCO Victor Stefan - grupa 312CB */
#include "Initializari.h"
TTren InitTTren() /*initializare de trenulet ca na nu aveam*/
{
    TTren lista = malloc(sizeof(struct trenulet));  /*alocare de memorie pentru trenulet*/
    lista->santinela = CreareVagon(SANTINELA);      /*crearea santinlei*/
    lista->mekanik = CreareVagon('#');              /*crearea mecanicului*/
    if (!lista->santinela || !lista->mekanik)
        return NULL;                                /*verificarea alocarii*/
    lista->santinela->next = lista->mekanik;
    lista->santinela->prev = lista->mekanik;
    lista->mekanik->next = lista->santinela;        /*niste legaturi la sanki ca e dublu inlantuita*/
    lista->mekanik->prev = lista->santinela;
    return lista;
}

TComenzi* InitComenzi()                             /*initializare de comenzi ca na nu aveam*/
{
    TComenzi* coada = malloc(sizeof(TComenzi));
    coada->first = NULL;
    coada->last = NULL;
    if (!coada)
        return NULL;
    return coada;
}

TVagon *CreareVagon(char info)                      /*creaza un vagon nou cu un caracter*/
{
    TVagon *v = (TVagon *)malloc(sizeof(TVagon));   /*aloca un spatiu nou pentru vagon*/
    if (!v)
        return NULL;
    v->info = info;                                 /*inserarea informatiei date functiei in campul "info" al vagonului*/
    return v;
}

void AdaugareComanda(TComenzi* coada, char *info)   /*adauga o comanda in coada*/
{
    TComanda *comanda_noua = malloc(sizeof(TComanda));
    if (!comanda_noua)
        return;
    comanda_noua->info = malloc(strlen(info) + 1);
    if (!comanda_noua->info)
        return;
    strcpy(comanda_noua->info, info);
    if (coada->last == NULL)
    {
        coada->last = comanda_noua;
        coada->last->jos = NULL;
        coada->last->sus = NULL;
        coada->first = comanda_noua;
        coada->first->sus = NULL;
        coada->first->jos = NULL;
    }
    else
    {
        coada->last->jos = comanda_noua;
        comanda_noua->sus = coada->last;
        coada->last = comanda_noua;
        coada->last->jos = NULL;
    }
}
void MOVE_LEFT(TTren lista)                         /*muta mecanicul o casuta un vagon mai la stanga*/
{
    if (lista->mekanik == lista->santinela->next)   /*cazul general*/
        lista->mekanik = lista->santinela->prev;
    else
    {
        lista->mekanik = lista->mekanik->prev;      /*cazul cand mecanicul este in primul vagon*/
    }
}

void MOVE_RIGHT(TTren lista)
{
    if (lista->mekanik->next != lista->santinela)   /*cazul general*/
        lista->mekanik = lista->mekanik->next;
    else
    {
        INSERT_RIGHT(lista, '#');                   /*cazul cand mecanicul este in ultimul vagon*/
        lista->mekanik = lista->santinela->prev;
    }
}

void WRITE(TTren lista, char info)                  /*modifica informatia din mecanicul actual*/
{
    lista->mekanik->info = info;
}

void INSERT_LEFT(TTren lista, char info)            /*insereaza un vagon in stanga mecanicului cu caracterul dat functiei*/
{
    TVagon *v = CreareVagon(info);                  /*crearea vagonului*/
    if (!v)
        return;                                     /*verificarea alocarii*/
    lista->mekanik->prev->next = v;
    v->prev = lista->mekanik->prev;
    v->next = lista->mekanik;
    lista->mekanik->prev = v;                       /*legaturile*/
    lista->mekanik = v;                             /*am vazut tarziu ca trebuie si astea bine ca nu am deraiat deloc de la codu initial*/
}

void INSERT_RIGHT(TTren lista, char info)           /*insereaza un vagon cu informatia data dupa mecanic*/
{
    TVagon *v = CreareVagon(info);                  /*crearea vagonului*/
    if (!v)
        return;                                     /*verificarea alocarii*/
    lista->mekanik->next->prev = v;                 /*legaturile*/
    v->next = lista->mekanik->next;
    v->prev = lista->mekanik;
    lista->mekanik->next = v;                       /*legaturile*/
    MOVE_RIGHT(lista);                              /*muta mecanicul la dreapta ca na cerinta*/
}

void CLEAR_CELL(TTren lista)
{
    TVagon *v = lista->mekanik;
    lista->mekanik->prev->next = lista->mekanik->next;
    lista->mekanik->next->prev = lista->mekanik->prev; /*distruge legaturile vechi si leaga casutele din stanga si dreapta casutei sterse*/
    MOVE_LEFT(lista);                               /*mut mecanicu la stanga ca na cerinta*/                                           /*valgrind lol*/
}

void CLEAR_ALL(TTren lista)
{
    lista->mekanik = lista->santinela->prev;
    while (lista->mekanik != lista->santinela->next)/*le sterge de la dreapta la stanga pana raman 2*/
    {
        CLEAR_CELL(lista);
    }
    lista->mekanik->info = '#';                     /*indiferent de care casuta ramane langa santinela ii dau "#" pentru a fie ca la inceput*/
}

void SEARCH(TTren lista, char *de_cautat, FILE* fileout)
{
    char *p = malloc(sizeof(char));                 /*"string" care o sa il compar cu cel cautat*/
    p[0] = '\0';
    TVagon *v = lista->mekanik;
    for (lista->mekanik = lista->mekanik->next; lista->mekanik != v; lista->mekanik = lista->mekanik->next)
    {
        char *temp = malloc(sizeof(char) * 2);
        temp[0] = lista->mekanik->info;
        temp[1] = '\0';
        strcat(p, temp);                            /*adaug la p toate caracterele din lista*/
    }
    char *a = strstr(p, de_cautat);                 /*caut stringul in p cu strstr*/
    if (a == NULL)                                  /*daca nu il gaseste*/
    {
        fprintf(fileout, "ERROR\n");
        return;
    }
    int nr_mutari_dreapta = a - p + 1;              /*formula care afla cate mutari sunt necesare*/
    while (nr_mutari_dreapta > 0)
    {
        lista->mekanik = lista->mekanik->next;
        if(lista->mekanik->next == lista->santinela)/*daca mecanicul ajunge la santinela il mut la dreapta ca na cerinta*/
            lista->mekanik = lista->santinela->next;

        nr_mutari_dreapta--;                        /*muta mecanicu de "nr_mutari_dreapta" ori*/
    }
}

void SEARCH_LEFT(TTren lista, char *de_cautat, FILE* fileout)
{
    char *p = malloc(sizeof(char));
    p[0] = '\0';
    TVagon *v = lista->mekanik;
    for (; v != lista->santinela; v = v->prev)
    {
        char *temp = malloc(sizeof(char) * 2);
        temp[0] = v->info;
        temp[1] = '\0';
        strcat(p, temp);
    }
    char *a = strstr(p, de_cautat);
    if (a == NULL)
    {
        fprintf(fileout, "ERROR\n");
        return;
    }
    int nr_mutari_stanga = a - p + strlen(de_cautat) - 1;
    while (nr_mutari_stanga > 0)
    {
        MOVE_LEFT(lista);
        nr_mutari_stanga--;
    }
}

void SEARCH_RIGHT(TTren lista, char *de_cautat, FILE* fileout)
{
    TVagon *v = lista->mekanik;
    char *p = malloc(sizeof(char));
    do
    {
        char *p = malloc(sizeof(char));
        char *temp = malloc(sizeof(char) * 2);
        temp[0] = v->info;
        temp[1] = '\0';
        strcat(p, temp);
        v = v -> next;
    }while (v!=lista->mekanik);
    char *a = strstr(p, de_cautat);
    if (a == NULL)
    {
        fprintf(fileout, "ERROR\n");
        return;
    }
    int nr_mutari_dreapta = p - a + 1;  // Update the calculation of nr_mutari_dreapta
    while (nr_mutari_dreapta > 0)
    {
        if (lista->mekanik->next == lista->santinela)
            lista->mekanik = lista->santinela->next;
        else
            lista->mekanik = lista->mekanik->next;
        nr_mutari_dreapta--;
    }
}

void SHOW(TTren lista, FILE *fileout)
{
    TVagon *v = lista->mekanik;
    for (v = lista->santinela->next; v != lista->santinela; v=v->next)
    {
        if (v == lista->mekanik)
            fprintf(fileout,"|%c|", v->info);
        else
            fprintf(fileout,"%c", v->info);
    }
    fprintf(fileout,"\n");
}

void SHOW_CURRENT(TTren lista, FILE *fileout)
{
    fprintf(fileout, "%c\n", lista->mekanik->info);
}

void SWITCH(TComenzi* coada)                        /*invarte coada de comenzi*/
{
    if (coada->first == NULL || coada->first == coada->last)
        return;
    TComanda *aux = coada->first;
    TComanda *auy = coada->last;
    while (aux != auy && aux->sus != auy)
    {
        char *temp = aux->info;
        aux->info = auy->info;
        auy->info = temp;
        aux = aux->jos;
        auy = auy->sus;
    }
}

void TRECI_LA_FUNCTIA_URMATOARE(TComenzi* coada)
{
    if (coada->first == NULL)
        return;
    TComanda *curent = coada->first;
    coada->first = coada->first->jos;
    if (coada->first == NULL)
        coada->last = NULL;
}