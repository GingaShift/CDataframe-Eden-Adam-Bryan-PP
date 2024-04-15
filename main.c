#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Colonne.h"
#include "Divers.h"

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

// Todo: A implémenter
int supprimer_ligne()
{

}

// Todo: A tester
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

int main()
{
    // Creer le CDataframe vide
    COLONNE** CDataframe = NULL;
    int taille_CDataframe = 0;

    // Todo: A faire
    // Peupler le CDataframe artificiellement
    // populate_dataframe_artificially

    // Ajouter une colonne au dataframe
    ajouter_colonne(&CDataframe, &taille_CDataframe, "Colonne 1");

    // Ajouter une valeur à Colonne 1
    inserer_valeur(CDataframe[0], 1, NOMBRE_LIGNES_PAR_BLOC);
    inserer_valeur(CDataframe[0], 2, NOMBRE_LIGNES_PAR_BLOC);

    afficher_colonne(CDataframe, taille_CDataframe, 0);

    // Ajouter une colonne au dataframe
    ajouter_colonne(&CDataframe, &taille_CDataframe, "Colonne 2");

    // Ajouter une valeur à Colonne 2
    inserer_valeur(CDataframe[1], 1000, NOMBRE_LIGNES_PAR_BLOC);
    inserer_valeur(CDataframe[1], 2000, NOMBRE_LIGNES_PAR_BLOC);
        
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