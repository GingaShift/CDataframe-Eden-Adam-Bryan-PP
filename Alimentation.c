#include <stdio.h>
#include "Colonne.h"

int populate_dataframe_artificially(COLONNE*** dataframe, int* taille_dataframe)
{
    if (dataframe == NULL)
    {
        fprintf(stderr, "Erreur lors de l'ajout de la colonne, le dataframe est NULL.\n");
        return 1;
    }

    // Ajouter une colonne au dataframe
    ajouter_colonne(dataframe, taille_dataframe, "Colonne 1");

    // Ajouter une valeur à Colonne 1
    inserer_valeur((*dataframe)[0], 1, NOMBRE_LIGNES_PAR_BLOC);
    inserer_valeur((*dataframe)[0], 2, NOMBRE_LIGNES_PAR_BLOC);

    // Ajouter une colonne au dataframe
    ajouter_colonne(dataframe, taille_dataframe, "Colonne 2");

    // Ajouter une valeur à Colonne 2
    inserer_valeur((*dataframe)[1], 1000, NOMBRE_LIGNES_PAR_BLOC);
    inserer_valeur((*dataframe)[1], 2000, NOMBRE_LIGNES_PAR_BLOC);
}
