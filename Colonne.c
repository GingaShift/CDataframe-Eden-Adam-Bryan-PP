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
    nouvelle_colonne->data = NULL;
    nouvelle_colonne->taille_physique = 0;
    nouvelle_colonne->taille_logique = 0;

    // Initialisation du tableau data de cette colonne
    /*for (int i = 0; i < NOMBRE_LIGNES_PAR_COLONNE; i++) {
        nouvelle_colonne->data[i] = VALEUR_PAR_DEFAUT_DATA_COLONNE;
    }*/

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

    // Ajout de la colonne au dataframe
    (*dataframe)[*taille_dataframe - 1] = nouvelle_colonne;
}

int inserer_valeur(COLONNE* colonne, int valeur, int nombre_lignes_par_bloc)
{
    // Vérifier si le tableau data est vide
    if (colonne->data == NULL)
    {
        // Allouer de la mémoire pour un tableau de 10 entiers et l'initialiser à zéro
        colonne->data = malloc(nombre_lignes_par_bloc * sizeof(int));

        if (colonne->data == NULL) {
            fprintf(stderr, "Erreur d'allocation de mémoire lors de la création du tableau data de la colonne.\n");
            return 1;
        }

        colonne->taille_physique = nombre_lignes_par_bloc;
    }
    // Vérifier si le tableau data est plein
    else if (colonne->taille_logique == colonne->taille_physique)
    {
        // Augmenter la taille physique du tableau data par tranche de 256
        int nouvelle_taille = colonne->taille_physique + nombre_lignes_par_bloc;
        int* nouveau_data = realloc(colonne->data, nouvelle_taille * sizeof(int));
        if (nouveau_data == NULL)
        {
            fprintf(stderr, "Erreur de réallocation de mémoire pour le tableau data de la colonne.\n");
            return;
        }
        colonne->data = nouveau_data;
        colonne->taille_physique = nouvelle_taille;
    }

    // Insérer la valeur dans le tableau data et mettre à jour la taille logique
    colonne->data[colonne->taille_logique] = valeur;
    colonne->taille_logique++;
}

void afficher_colonne(COLONNE** dataframe, int taille_dataframe, int indice_colonne)
{
    if (dataframe == NULL || indice_colonne < 0) {
        fprintf(stderr, "Erreur : dataframe invalide ou indice de colonne invalide.\n");
        return;
    }

    if (indice_colonne >= taille_dataframe) {
        fprintf(stderr, "Erreur : indice de colonne hors limites.\n");
        return;
    }

    printf("Valeurs de la colonne %s :\n", dataframe[indice_colonne]->nom);

    for (int i = 0; i < dataframe[indice_colonne]->taille_logique; i++) {
        printf("[%d] = %d ", i, dataframe[indice_colonne]->data[i]);
        printf("\n");
    }
    printf("\n");
}

void renommer_colonne(COLONNE** dataframe, int taille_dataframe, int num_colonne, const char* nouveau_nom)
{
    // Vérifier si le numéro de colonne est valide
    if (num_colonne < 0 || num_colonne >= taille_dataframe) {
        fprintf(stderr, "Numéro de colonne invalide.\n");
        return;
    }

    // Vérifier si le nouveau nom est déjà utilisé par une autre colonne
    for (int i = 0; i < taille_dataframe; ++i) {
        if (i != num_colonne && strcmp(dataframe[i]->nom, nouveau_nom) == 0) {
            fprintf(stderr, "Le nom \"%s\" est déjà utilisé par une autre colonne.\n", nouveau_nom);
            return;
        }
    }

    // Mettre à jour le nom de la colonne
    strncpy(dataframe[num_colonne]->nom, nouveau_nom, sizeof(dataframe[num_colonne]->nom) - 1);
    dataframe[num_colonne]->nom[sizeof(dataframe[num_colonne]->nom) - 1] = '\0';
}

