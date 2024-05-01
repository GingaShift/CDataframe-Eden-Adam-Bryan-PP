#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Colonne.h"
#include "Main.h"
#include "Divers.h"

COLONNE* creer_colonne(const char* titre)
{
    COLONNE* nouvelle_colonne = malloc(sizeof(COLONNE));
    if (nouvelle_colonne == NULL) {
        printf("\nErreur d'allocation de mémoire pour la nouvelle colonne.\n");
        return NULL;
    }

    // Initialisation de la nouvelle colonne
    strncpy(nouvelle_colonne->titre, titre, sizeof(nouvelle_colonne->titre) - 1);
    nouvelle_colonne->titre[sizeof(nouvelle_colonne->titre) - 1] = '\0'; // Assure la terminaison de la chaîne
    nouvelle_colonne->data = NULL;
    nouvelle_colonne->taille_physique = 0;
    nouvelle_colonne->taille_logique = 0;

    return nouvelle_colonne;
}

int inserer_valeur(COLONNE* colonne, int valeur, bool* bloc_lignes_ajoute_a_colonne)
{
    (*bloc_lignes_ajoute_a_colonne) = false;
    
    // Vérifier si le tableau data est vide
    if (colonne->data == NULL)
    {
        // Allouer de la mémoire pour un tableau de X entiers
        colonne->data = malloc(NOMBRE_LIGNES_PAR_BLOC_DATA_COLONNE * sizeof(int));

        if (colonne->data == NULL)
        {
            printf("\nErreur d'allocation mémoire lors de la création du tableau data de la colonne.\n");
            return 0;
        }

        colonne->taille_physique = NOMBRE_LIGNES_PAR_BLOC_DATA_COLONNE;

        (*bloc_lignes_ajoute_a_colonne) = true;
    }
    // Vérifier si le tableau data est plein
    else if (colonne->taille_logique == colonne->taille_physique)
    {
        // Si le tableau de data est plein, augmenter la taille physique du tableau data par tranche de 256
        int nouvelle_taille = colonne->taille_physique + NOMBRE_LIGNES_PAR_BLOC_DATA_COLONNE;
        
        // Creation du nouveau tableau (composé de l'ancien tableau auquel on ajoute le bloc de nouvelles lignes vierges) 
        int* nouveau_data = realloc(colonne->data, nouvelle_taille * sizeof(int));
        if (nouveau_data == NULL)
        {
            printf("\nErreur de réallocation de mémoire lors de l'extension du tableau data de la colonne.\n");
            return 0;
        }
        
        // Assignation du tableau "agrandi"
        colonne->data = nouveau_data;

        // Mise à jour de la taille physique du tableau
        colonne->taille_physique = nouvelle_taille;

        // Savoir qu'il faudra mettre à jour toutes les autres colonnes à la sortie de la fonction afin de preserver la matrice du dataframe
        (*bloc_lignes_ajoute_a_colonne) = true;
    }

    // Insérer la valeur dans le tableau data et mettre à jour la taille logique
    colonne->data[colonne->taille_logique] = valeur;
    colonne->taille_logique++;
    
    return 1;
}

int afficher_colonne(COLONNE* colonne, int taille_dataframe, int num_colonne)
{
    if (colonne == NULL || num_colonne < 0) {
        printf("\nErreur : colonne invalide ou indice de colonne invalide\n");
        return 0;
    }

    if (num_colonne >= taille_dataframe) {
        printf("\nErreur : indice de colonne hors limites\n");
        return 0;
    }

    int nombre_valeurs_affichees = 0;

    for (int i = 0; i < colonne->taille_logique; i++)
    {
        printf("[%d] = %d ", i, colonne->data[i]);
        printf("\n");
        nombre_valeurs_affichees++;
    }
    
    return nombre_valeurs_affichees;
}

int supprimer_colonne(COLONNE* colonne)
{
    // Libérer les données de la colonne
    if (colonne->data != NULL)
        free(colonne->data);

    free(colonne);

    return 1;
}