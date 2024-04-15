#include <stdio.h>
#include "Colonne.h"

void free_ressources(COLONNE** dataframe, int taille_dataframe)
{
    for (int i = 0; i < taille_dataframe; i++) {
        free(dataframe[i]);
    }

    free(dataframe);
}