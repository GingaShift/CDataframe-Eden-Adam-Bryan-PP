#include <stdio.h>
#include "Colonne.h"

int obtenir_nombre_colonnes(int taille_dataframe)
{
    return taille_dataframe;
}

int obtenir_nombre_lignes(COLONNE** dataframe, int taille_dataframe)
{
    if (taille_dataframe == 0)
        return 0;

    return dataframe[0]->taille_physique;
}

