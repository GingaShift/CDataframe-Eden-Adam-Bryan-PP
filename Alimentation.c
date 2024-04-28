#include <stdio.h>
#include "Main.h"
#include "Colonne.h"
#include "CDataframe.h"

int populate_dataframe_artificially(DATAFRAME* dataframe)
{
    int ajouter_bloc_lignes_a_toutes_les_colonnes = 0;
    
    // Ajouter une colonne au dataframe
    ajouter_colonne(dataframe, "Colonne 1");

    // Ajouter une colonne au dataframe
    ajouter_colonne(dataframe, "Colonne 2");

    inserer_valeur_avec_gestion_memoire_data_colonnes_new(dataframe, 0, 10);
    
    inserer_valeur_avec_gestion_memoire_data_colonnes_new(dataframe, 0, 11);

    inserer_valeur_avec_gestion_memoire_data_colonnes_new(dataframe, 0, 12);

    // Ajouter une valeur à Colonne 2
    inserer_valeur_avec_gestion_memoire_data_colonnes_new(dataframe, 1, 20);
    inserer_valeur_avec_gestion_memoire_data_colonnes_new(dataframe, 1, 21);

    // Ajouter une colonne au dataframe
    ajouter_colonne(dataframe, "Colonne 3");

    // Ajouter quelques valeurs à Colonne 3
    inserer_valeur_avec_gestion_memoire_data_colonnes_new(dataframe, 2, 30);
    inserer_valeur_avec_gestion_memoire_data_colonnes_new(dataframe, 2, 31);

    return 0;
}
