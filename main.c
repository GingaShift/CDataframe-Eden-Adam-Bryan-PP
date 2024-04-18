#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Colonne.h"
#include "CDataframe.h"
#include "Divers.h"
#include "Alimentation.h"
#include "Analyses_et_stats.h"
#include "Main.h"
#include "String_manager.h"

int ajouter_ligne_de_valeur(int valeur)
{

}

// Todo: A implémenter et à inserer dans CDataframe
int supprimer_ligne_de_valeur(int num_ligne)
{

}

// Todo: A tester et à inserer dans Colonne
int modifier_valeur(COLONNE** dataframe, int taille_dataframe, int num_col, int num_ligne, int valeur)
{
    // Parcourir toutes les colonnes du dataframe
    for (int i = 0; i < taille_dataframe; ++i) {
        
        COLONNE* colonne = dataframe[i];

        // gerer num_col et num_ligne...
        // todo

        // Ajouter la nouvelle valeur à la colonne
        colonne->data[colonne->taille_logique] = valeur;
        colonne->taille_logique++;
    }
}

int afficher_colonnes(int nombre_colonnes)
{

}



int main()
{
    // Creer le CDataframe vide
    COLONNE** CDataframe = NULL;
    int taille_CDataframe = 0;

    // Peupler le CDataframe artificiellement - Test seulement
    populate_dataframe_artificially(&CDataframe, &taille_CDataframe);

    char* chaine;
    chaine = saisie_chaine("Veuillez saisir le nom de la colonne: \n");
    
    // Afficher le nom saisi
    printf("Le nom que vous avez saisi est : %s\n", chaine);

    int res = nom_colonne_existe(CDataframe, chaine, taille_CDataframe);
    if (res == 1)
    {
        printf("%s", "Le nom de la colonne existe déjà");
    }
    else
        printf("%s", "Le nom de la colonne n'existe pas");





    // Afficher colonnes du dataframe
    afficher_colonne(CDataframe, taille_CDataframe, 0);
    afficher_colonne(CDataframe, taille_CDataframe, 1);
    afficher_colonne(CDataframe, taille_CDataframe, 2);

    // Afficher toutes les colonnes du CDataframe par la fonction suivante:
    // Todo : afficher_les_colonnes(COLONNE** dataframe, int taille_CDataframe, int nombre_colonnes_a_afficher)

    OPERATEURS_DE_COMPARAISON egal = {EGAL};
    OPERATEURS_DE_COMPARAISON superieur = {SUPERIEUR};
    OPERATEURS_DE_COMPARAISON inferieur = {INFERIEUR};

    stats_sur_valeur(CDataframe, taille_CDataframe, 10, egal);

    // Libération de la mémoire occupée par les colonnes et le dataframe
    free_ressources(CDataframe, taille_CDataframe);

    return 0;
}