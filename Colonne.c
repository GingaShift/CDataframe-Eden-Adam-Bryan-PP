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
        printf("\nErreur d'allocation de m�moire pour la nouvelle colonne.\n");
        return 0;
    }

    // Initialisation de la nouvelle colonne
    strncpy(nouvelle_colonne->titre, titre, sizeof(nouvelle_colonne->titre) - 1);
    nouvelle_colonne->titre[sizeof(nouvelle_colonne->titre) - 1] = '\0'; // Assure la terminaison de la cha�ne
    nouvelle_colonne->data = NULL;
    nouvelle_colonne->taille_physique = 0;
    nouvelle_colonne->taille_logique = 0;

    return nouvelle_colonne;
}

int inserer_valeur(COLONNE* colonne, int valeur, bool* bloc_lignes_ajoute_a_colonne)
{
    (*bloc_lignes_ajoute_a_colonne) = false;
    
    // V�rifier si le tableau data est vide
    if (colonne->data == NULL)
    {
        // Allouer de la m�moire pour un tableau de X entiers
        colonne->data = malloc(NOMBRE_LIGNES_PAR_BLOC_DATA_COLONNE * sizeof(int));

        if (colonne->data == NULL)
        {
            printf("\nErreur d'allocation m�moire lors de la cr�ation du tableau data de la colonne.\n");
            return 0;
        }

        colonne->taille_physique = NOMBRE_LIGNES_PAR_BLOC_DATA_COLONNE;

        (*bloc_lignes_ajoute_a_colonne) = true;
    }
    // V�rifier si le tableau data est plein
    else if (colonne->taille_logique == colonne->taille_physique)
    {
        // Si le tableau de data est plein, augmenter la taille physique du tableau data par tranche de 256
        int nouvelle_taille = colonne->taille_physique + NOMBRE_LIGNES_PAR_BLOC_DATA_COLONNE;
        
        // Creation du nouveau tableau (compos� de l'ancien tableau auquel on ajoute le bloc de nouvelles lignes vierges) 
        int* nouveau_data = realloc(colonne->data, nouvelle_taille * sizeof(int));
        if (nouveau_data == NULL)
        {
            printf("\nErreur de r�allocation de m�moire lors de l'extension du tableau data de la colonne.\n");
            return 0;
        }
        
        // Assignation du tableau "agrandi"
        colonne->data = nouveau_data;

        // Mise � jour de la taille physique du tableau
        colonne->taille_physique = nouvelle_taille;

        // Savoir qu'il faudra mettre � jour toutes les autres colonnes � la sortie de la fonction afin de preserver la matrice du dataframe
        (*bloc_lignes_ajoute_a_colonne) = true;
    }

    // Ins�rer la valeur dans le tableau data et mettre � jour la taille logique
    colonne->data[colonne->taille_logique] = valeur;
    colonne->taille_logique++;
    
    return 1;
}

int supprimer_colonne(COLONNE* colonne)
{
    // Lib�rer les donn�es de la colonne
    if (colonne->data != NULL)
        free(colonne->data);
    else
        return 0;

    free(colonne);

    return 1;
}

int afficher_colonne(COLONNE* colonne)
{
    if (colonne == NULL)
    {
        printf("\nLa colonne n'existe pas\n");
        return 0;
    }

    if (colonne->taille_logique == 0)
    {
        printf("\nLa colonne %s ne contient aucunes donn�es\n\n", colonne->titre);
        return 1;
    }

    printf("\nVoici le contenu de la colonne \"%s\" :\n\n", colonne->titre);
    
    for (int i = 0; i < colonne->taille_logique; i++)
    {
        printf("[%d] : %d\n", i, colonne->data[i]);
    }
    
    return 1;
}