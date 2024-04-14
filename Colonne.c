#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Colonne.h"

COLONNE* creer_colonne(const char* nom) {
    COLONNE* nouvelle_colonne = malloc(sizeof(COLONNE));
    if (nouvelle_colonne == NULL) {
        fprintf(stderr, "Erreur d'allocation de mémoire pour la nouvelle colonne.\n");
        return NULL;
    }

    // Initialisation de la nouvelle colonne
    strncpy(nouvelle_colonne->nom, nom, sizeof(nouvelle_colonne->nom) - 1);
    nouvelle_colonne->nom[sizeof(nouvelle_colonne->nom) - 1] = '\0'; // Assure la terminaison de la chaîne
    nouvelle_colonne->taille_physique = 0;
    nouvelle_colonne->taille_logique = 0;

    // Initialisation du tableau data de cette colonne
    for (int i = 0; i < NOMBRE_LIGNES_PAR_COLONNE; i++) {
        nouvelle_colonne->data[i] = 0;
    }

    return nouvelle_colonne;
}

int ajouter_colonne(COLONNE*** dataframe, int* taille_dataframe, const char* nom_colonne)
{
    if (dataframe == NULL)
    {
        fprintf(stderr, "Erreur lors de la l'ajout de la colonne, le dataframe est NULL.\n");
        return 1;
    }

    // Ajout d'une colonne en utilisant la fonction creer_colonne
    COLONNE* nouvelle_colonne = creer_colonne(nom_colonne);
    if (nouvelle_colonne == NULL)
    {
        fprintf(stderr, "Erreur lors de la création de la colonne.\n");
        return 1;
    }

    // Agrandissement du tableau CDataframe pour ajouter la nouvelle colonne
    (*taille_dataframe)++;
    *dataframe = realloc(*dataframe, (*taille_dataframe) * sizeof(COLONNE*));
    if (*dataframe == NULL)
    {
        fprintf(stderr, "Erreur d'allocation mémoire pour CDataframe.\n");
        free(nouvelle_colonne);
        return 1;
    }

    // Ajout de la colonne au tableau
    (*dataframe)[*taille_dataframe - 1] = nouvelle_colonne;
}

void afficher_colonne(COLONNE** dataframe, int indice_colonne, int taille_CDataframe)
{

    if (dataframe == NULL || indice_colonne < 0) {
        fprintf(stderr, "Erreur : dataframe invalide ou indice de colonne invalide.\n");
        return;
    }

    if (indice_colonne >= taille_CDataframe) {
        fprintf(stderr, "Erreur : indice de colonne hors limites.\n");
        return;
    }

    printf("Valeurs de la colonne %s :\n", dataframe[indice_colonne]->nom);

    for (int i = 0; i < dataframe[indice_colonne]->taille_physique; i++) {
        printf("Ligne %d = %d ", i, dataframe[indice_colonne]->data[i]);
        printf("\n");
    }
    printf("\n");
}

