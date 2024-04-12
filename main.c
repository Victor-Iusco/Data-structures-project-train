/* IUSCO Victor Stefan - grupa 312CB */
#include "Initializari.h"

int main()
{
    char comanda[100];
    char* p;
    char* q;
    int nrcomenzi;
    FILE *filein = fopen("tema1.in", "r");
    FILE *fileout = fopen("tema1.out", "w");
    if (!filein)                                                            /*verificari daca se deschid fisierele*/
    {
        printf("Nu s-a putut deschide fisierul de input\n");
        return 1;
    }
    if (!fileout)
    {
        printf("Nu s-a putut deschide fisierul de output\n");
        return 1;
    }
    TTren c = InitTTren();                                                  /*Initializarile de coada si lista*/
    if (!c)
    {
        printf("Nu s-a putut aloca memorie pentru trenulet\n");
        return 1;
    }
    TComenzi* d = InitComenzi();
    if (!d)
    {
        printf("Nu s-a putut aloca memorie pentru coada de comenzi\n");
        return 1;
    }
    fscanf(filein, "%d", &nrcomenzi);
    int w;
    fscanf(filein, "%d", &w);
    while (fgets(comanda, sizeof(comanda), filein))                         /*cat timp se citesc linii din fisier*/
    {
        if (strchr(comanda, '\n') != NULL)
        {
            comanda[strchr(comanda, '\n') - comanda] = '\0';
        }
        if (strcmp(comanda, "SHOW") == 0)
        {
            SHOW(c, fileout);
        }
        else if (strcmp(comanda, "SHOW_CURRENT") == 0)
        {
            SHOW_CURRENT(c, fileout);
        }
        else if (strcmp(comanda, "SWITCH") == 0)
        {
            SWITCH(d);
        }
        else if (strcmp(comanda, "EXECUTE") == 0)
        {
            p = strtok(d->first->info, " ");                                /*pentru functiile care au nevoie si de la 2-lea camp*/
            if (strcmp(p, "MOVE_LEFT") == 0)
            {
                MOVE_LEFT(c);
                TRECI_LA_FUNCTIA_URMATOARE(d);
            }
            else if (strcmp(p, "MOVE_RIGHT") == 0)
            {
                MOVE_RIGHT(c);
                TRECI_LA_FUNCTIA_URMATOARE(d);
            }
            else if (strcmp(p, "INSERT_LEFT") == 0)
            {
                q = strtok(NULL, " ");
                if (c->mekanik == c->santinela->next)
                {
                    fprintf(fileout, "ERROR\n");
                    TRECI_LA_FUNCTIA_URMATOARE(d);
                }
                else
                {
                    INSERT_LEFT(c, q[0]);
                    TRECI_LA_FUNCTIA_URMATOARE(d);
                }
            }
            else if (strcmp(p, "INSERT_RIGHT") == 0)
            {
                q = strtok(NULL, " ");
                INSERT_RIGHT(c, q[0]);
                TRECI_LA_FUNCTIA_URMATOARE(d);
            }
            else if (strcmp(p, "WRITE") == 0)
            {
                q = strtok(NULL, " ");
                WRITE(c, q[0]);
                TRECI_LA_FUNCTIA_URMATOARE(d);
            }
            else if (strcmp(p, "CLEAR_CELL") == 0)
            {
                CLEAR_CELL(c);
                TRECI_LA_FUNCTIA_URMATOARE(d);
            }
            else if (strcmp(p, "CLEAR_ALL") == 0)
            {
                CLEAR_ALL(c);
                TRECI_LA_FUNCTIA_URMATOARE(d);
            }
            else if (strcmp(p, "SEARCH") == 0)
            {
                q = strtok(NULL, " ");
                SEARCH(c, q, fileout);
                TRECI_LA_FUNCTIA_URMATOARE(d);
            }
            else if (strcmp(p, "SEARCH_LEFT") == 0)
            {
                q = strtok(NULL, " ");
                SEARCH_LEFT(c, q, fileout);
                TRECI_LA_FUNCTIA_URMATOARE(d);
            }
            else if (strcmp(p, "SEARCH_RIGHT") == 0)
            {
                q = strtok(NULL, " ");
                SEARCH_RIGHT(c, q, fileout);
                TRECI_LA_FUNCTIA_URMATOARE(d);
            }
        }
        else
        {
            AdaugareComanda(d, comanda);                                    /*cand nu sunt functiile care se executa direct se baga in coada*/
        }
    }
    fclose(filein);
    fclose(fileout);                                                        /*inchid fisierele*/
    return 0;
}
