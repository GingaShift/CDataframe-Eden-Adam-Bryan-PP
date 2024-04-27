#include <stdio.h>
#include "Main.h"
#include "Colonne.h"
#include "CDataframe.h"

int ajouter_colonne_new(DATAFRAME* dataframe, const char* nom_colonne)
{
    // Ajout d'une colonne en utilisant la fonction creer_colonne
    COLONNE* nouvelle_colonne = creer_colonne(nom_colonne);
    if (nouvelle_colonne == NULL)
    {
        printf("\nErreur lors de la création de la colonne.\n");
        return FAILED;
    }

    // Agrandissement du tableau CDataframe pour ajouter la nouvelle colonne
    dataframe->taille ++;
    //        *colonnes = realloc(*colonnes, (*taille_dataframe) * sizeof(COLONNE*));
    dataframe->colonnes = realloc(dataframe->colonnes, (dataframe->taille) * sizeof(COLONNE*));
    if (dataframe == NULL)
    {
        printf("\nErreur d'allocation mémoire lors de l'ajout d'une colonne au CDataframe.\n");
        free(nouvelle_colonne);
        return 1;
    }

    // Ajout de la colonne au dataframe
    // (*colonnes)[*taille_dataframe - 1] = nouvelle_colonne;
    dataframe->colonnes[dataframe->taille - 1] = nouvelle_colonne;
}

int populate_dataframe_artificially_old(COLONNE*** dataframe, int* taille_dataframe)
{
    int ajouter_bloc_lignes_a_toutes_les_colonnes = 0;
    
    if (dataframe == NULL) 
    {
        fprintf(stderr, "Erreur lors de l'ajout de la colonne, le dataframe est NULL.\n");
        return 1;
    }

    // Ajouter une colonne au dataframe
    ajouter_colonne_old(dataframe, taille_dataframe, "Colonne 1");

    // Ajouter une colonne au dataframe
    ajouter_colonne_old(dataframe, taille_dataframe, "Colonne 2");

    inserer_valeur_avec_gestion_memoire_data_colonnes(dataframe, taille_dataframe, 0, 10);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Ajouter une valeur à Colonne 1
    //inserer_valeur((*dataframe)[0], 10, NOMBRE_LIGNES_PAR_BLOC, &ajouter_bloc_lignes_a_toutes_les_colonnes);
    //if (ajouter_bloc_lignes_a_toutes_les_colonnes == 1)
        //ajouter_bloc_lignes_aux_colonnes((*dataframe), (*taille_dataframe), 0);
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////

    inserer_valeur((*dataframe)[0], 12, NOMBRE_LIGNES_PAR_BLOC_DATA_COLONNE, &ajouter_bloc_lignes_a_toutes_les_colonnes);
    inserer_valeur((*dataframe)[0], 256, NOMBRE_LIGNES_PAR_BLOC_DATA_COLONNE, &ajouter_bloc_lignes_a_toutes_les_colonnes);

    // Ajouter une valeur à Colonne 2
    inserer_valeur((*dataframe)[1], 20, NOMBRE_LIGNES_PAR_BLOC_DATA_COLONNE, &ajouter_bloc_lignes_a_toutes_les_colonnes);
    inserer_valeur((*dataframe)[1], 21, NOMBRE_LIGNES_PAR_BLOC_DATA_COLONNE, &ajouter_bloc_lignes_a_toutes_les_colonnes);

    // Ajouter une colonne au dataframe
    ajouter_colonne_old(dataframe, taille_dataframe, "Colonne 3");

    // Ajouter une valeur à Colonne 3
    inserer_valeur((*dataframe)[2], 30, NOMBRE_LIGNES_PAR_BLOC_DATA_COLONNE, &ajouter_bloc_lignes_a_toutes_les_colonnes);
    inserer_valeur((*dataframe)[2], 31, NOMBRE_LIGNES_PAR_BLOC_DATA_COLONNE, &ajouter_bloc_lignes_a_toutes_les_colonnes);

    return 0;
}
int populate_dataframe_artificially_new(DATAFRAME* dataframe)
{
    int ajouter_bloc_lignes_a_toutes_les_colonnes = 0;
    
    // Ajouter une colonne au dataframe
    ajouter_colonne_new(dataframe, "Colonne 1");

    // Ajouter une colonne au dataframe
    ajouter_colonne_new(dataframe, "Colonne 2");

    //inserer_valeur_avec_gestion_memoire_data_colonnes(dataframe, taille_dataframe, 0, 10);
        
    //inserer_valeur((*dataframe)[0], 12, NOMBRE_LIGNES_PAR_BLOC_DATA_COLONNE, &ajouter_bloc_lignes_a_toutes_les_colonnes);
    //inserer_valeur((*dataframe)[0], 256, NOMBRE_LIGNES_PAR_BLOC_DATA_COLONNE, &ajouter_bloc_lignes_a_toutes_les_colonnes);

    // Ajouter une valeur à Colonne 2
    //inserer_valeur((*dataframe)[1], 20, NOMBRE_LIGNES_PAR_BLOC_DATA_COLONNE, &ajouter_bloc_lignes_a_toutes_les_colonnes);
    //inserer_valeur((*dataframe)[1], 21, NOMBRE_LIGNES_PAR_BLOC_DATA_COLONNE, &ajouter_bloc_lignes_a_toutes_les_colonnes);

    // Ajouter une colonne au dataframe
    //ajouter_colonne(dataframe, taille_dataframe, "Colonne 3");

    // Ajouter une valeur à Colonne 3
    //inserer_valeur((*dataframe)[2], 30, NOMBRE_LIGNES_PAR_BLOC_DATA_COLONNE, &ajouter_bloc_lignes_a_toutes_les_colonnes);
    //inserer_valeur((*dataframe)[2], 31, NOMBRE_LIGNES_PAR_BLOC_DATA_COLONNE, &ajouter_bloc_lignes_a_toutes_les_colonnes);

    return SUCCESS;
}
