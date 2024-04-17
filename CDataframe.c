#include <stdio.h>
#include "Main.h"
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

int ajouter_bloc_lignes_aux_colonnes(COLONNE** dataframe, int taille_dataframe, int num_colonne_a_ignorer)
{
    // Parcourir toutes les colonnes du dataframe
    for (int i = 0; i < taille_dataframe; ++i) {
    
        if (i == num_colonne_a_ignorer)
            continue;

        COLONNE* colonne = dataframe[i];

        // Allouer de la mémoire pour x nouvelles lignes
        int nouvelle_taille = colonne->taille_physique + NOMBRE_LIGNES_PAR_BLOC_DATA_COLONNE;
        int* nouvelle_data = realloc(colonne->data, nouvelle_taille * sizeof(int));
        if (nouvelle_data == NULL) {
            fprintf(stderr, "Erreur d'allocation de mémoire pour la colonne %s.\n", colonne->nom);
            continue; // Passer à la prochaine colonne en cas d'erreur
        }

        // Mettre à jour les données de la colonne
        colonne->taille_physique = nouvelle_taille;
        colonne->data = nouvelle_data;
    }
}

int inserer_valeur_avec_gestion_memoire_data_colonnes(COLONNE*** dataframe, int* taille_dataframe, int num_col, int valeur)
{
    int ajouter_bloc_lignes_a_toutes_les_colonnes = 0;

    // Ajouter valeur à colonne
    int ret = inserer_valeur((*dataframe)[num_col], valeur, NOMBRE_LIGNES_PAR_BLOC_DATA_COLONNE, &ajouter_bloc_lignes_a_toutes_les_colonnes);
    if (ret == FAILED) {
        fprintf(stderr, "Erreur d'allocation de mémoire lors de la création du tableau data de la colonne.\n");
        return 0;
    }

    if (ajouter_bloc_lignes_a_toutes_les_colonnes == 1)
        ajouter_bloc_lignes_aux_colonnes((*dataframe), (*taille_dataframe), num_col);

    return 1;
}

