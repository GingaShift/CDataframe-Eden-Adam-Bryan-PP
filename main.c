#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Colonne.h"
#include "CDataframe.h"
#include "Divers.h"
#include "Alimentation.h"

// Todo: A implémenter et à inserer dans CDataframe
int supprimer_ligne()
{

}

// Todo: A tester et à inserer dans Colonne
int modifier_valeur(COLONNE** dataframe, int taille_dataframe, int num_col, int num_ligne, int valeur)
{
    // Parcourir toutes les colonnes du dataframe
    for (int i = 0; i < taille_dataframe; ++i) {
        COLONNE* colonne = dataframe[i];

        // Vérifier si la colonne est pleine
        if (colonne->taille_logique >= NOMBRE_LIGNES_PAR_BLOC) {
            fprintf(stderr, "La colonne %s est pleine. Impossible d'ajouter une nouvelle ligne.\n", colonne->nom);
            continue;
        }

        // Ajouter la nouvelle valeur à la colonne
        colonne->data[colonne->taille_logique] = valeur;
        colonne->taille_logique++;
    }
}


typedef enum {
    SUPERIEUR,
    EGAL,
    INFERIEUR
} Condition;

int stats_sur_valeur(COLONNE** CDataframe, int taille_dataframe, int valeur, Condition operateur_de_comparaison)
{
    int total = 0;

    for (int i = 0; i < taille_dataframe; i++) {

        for (int k = 0; k < CDataframe[i]->taille_logique; k++) {

            switch (operateur_de_comparaison)
            {
                case SUPERIEUR:
                    if (CDataframe[i]->data[k] > valeur)
                        total++;
                    break;
                case EGAL:
                    if (CDataframe[i]->data[k] == valeur)
                        total++;
                    break;
                case INFERIEUR:
                    if (CDataframe[i]->data[k] < valeur)
                        total++;
                    break;
                default:
                    break;
            }
        }
    }

    return total;
}



int main()
{
    // Creer le CDataframe vide
    COLONNE** CDataframe = NULL;
    int taille_CDataframe = 0;

    // Peupler le CDataframe artificiellement - Test seulement
    populate_dataframe_artificially(&CDataframe, &taille_CDataframe);
    
    // Afficher colonnes du dataframe
    afficher_colonne(CDataframe, taille_CDataframe, 0);
    afficher_colonne(CDataframe, taille_CDataframe, 1);

    // Afficher toutes les colonnes du CDataframe par la fonction suivante:
    // Todo : afficher_les_colonnes(COLONNE** dataframe, int taille_CDataframe, int nombre_colonnes_a_afficher)

    // Libération de la mémoire occupée par les colonnes et le dataframe
    // A deplacer dans Divers
    free_ressources(CDataframe, taille_CDataframe);

    return 0;
}