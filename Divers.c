#include <stdio.h>
#include "Colonne.h"

void free_ressources(COLONNE** dataframe, int taille_dataframe)
{
    // liberer la mémoires allouée aux colonnes
    for (int i = 0; i < taille_dataframe; i++) {
        free(dataframe[i]);
    }

    // liberer la mémoires allouée au dataframe
    free(dataframe);
}