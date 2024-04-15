#include <stdio.h>
#include "Colonne.h"

void free_ressources(COLONNE** dataframe, int taille_dataframe)
{
    // liberer la m�moires allou�e aux colonnes
    for (int i = 0; i < taille_dataframe; i++) {
        free(dataframe[i]);
    }

    // liberer la m�moires allou�e au dataframe
    free(dataframe);
}