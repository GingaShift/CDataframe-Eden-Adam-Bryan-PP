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


int main()
{
    // Creation et ini du CDataframe
    int taille_CDataframe;
    COLONNE** CDataframe;

    printf("************************************************************************\n");
    printf("*                                                                      *\n");
    printf("*                      =-    MENU GENERAL    -=                        *\n");    
    printf("*                                                                      *\n");
    printf("************************************************************************\n");

    int choix = 0;
    int go = 1;

    // Boucle jusqu'à ce que la saisie soit valide
    while (go == 1)
    {
        printf("\n\n");
        printf("1. Creer CDataframe (tapez 1)\n\n");
        printf("2. Charger CDataframe (tapez 2)\n");

        scanf("%d", &choix);

        /*if (choix == 1)
        {
            CDataframe = creer_cdataframe(&taille_CDataframe);
        }
        else if (choix == 2)
            printf("Le chargement d'un CDataframe sera bientot disponible\n");*/

        
        if (choix==1)
            go = 0;
    }
     


    // Libération de la mémoire occupée par les colonnes et le dataframe
    free_ressources(CDataframe, taille_CDataframe);

    return 0;

// Peupler le CDataframe artificiellement - Test seulement
//populate_dataframe_artificially(&CDataframe, &taille_CDataframe);

//OPERATEURS_DE_COMPARAISON egal = { EGAL };
//OPERATEURS_DE_COMPARAISON superieur = { SUPERIEUR };
//OPERATEURS_DE_COMPARAISON inferieur = { INFERIEUR };
//stats_sur_valeur(CDataframe, taille_CDataframe, 10, egal);

}


