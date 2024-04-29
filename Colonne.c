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

    // Initialisation du tableau data de cette colonne
    /*for (int i = 0; i < NOMBRE_LIGNES_PAR_COLONNE; i++) {
        nouvelle_colonne->data[i] = VALEUR_PAR_DEFAUT_DATA_COLONNE;
    }*/

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
            return 1;
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
            fprintf(stderr, "Erreur de réallocation de mémoire lors de l'extention du tableau data de la colonne.\n");
            return 1;
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
    
    return 0;
}

int afficher_colonne(COLONNE** dataframe, int taille_dataframe, int num_colonne)
{
    if (dataframe == NULL || num_colonne < 0) {
        fprintf(stderr, "\n\nErreur : dataframe invalide ou indice de colonne invalide.\n\n");
        return 1;
    }

    if (num_colonne >= taille_dataframe) {
        fprintf(stderr, "\n\nErreur : indice de colonne hors limites.\n\n");
        return 1;
    }

    //printf("Valeurs de la colonne %s :\n", dataframe[num_colonne]->nom);

    int nombre_valeurs_affichees = 0;

    for (int i = 0; i < dataframe[num_colonne]->taille_logique; i++) {
        printf("[%d] = %d ", i, dataframe[num_colonne]->data[i]);
        printf("\n");
        nombre_valeurs_affichees++;
    }
    
    return nombre_valeurs_affichees;
}
