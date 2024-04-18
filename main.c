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
    int taille_CDataframe = -1;
    COLONNE** CDataframe = NULL;
    bool CDataframe_exists = false;

    printf("************************************************************************\n");
    printf("*                                                                      *\n");
    printf("*                      =-    MENU GENERAL    -=                        *\n");    
    printf("*                                                                      *\n");
    printf("************************************************************************\n");
    printf("\n");
    printf("1. Creer le CDataframe\n\n");
    printf("2. Charger un CDataframe\n\n");
    printf("3. Creer une colonne\n\n");
    printf("0. Quitter le programme\n\n");
    
    int choix = 0;
    int go = 1;

    // Boucle jusqu'à ce que la saisie soit valide
    while (go == 1)
    {
        printf("\nChoisissez un des numeros puis validez en appuyant sur la touche Entree\n\n");
        scanf("%d", &choix);

        if (choix == 1)
        {
            if (CDataframe_exists == false)
            {
                CDataframe = creer_cdataframe(&taille_CDataframe);
                if (CDataframe == NULL && taille_CDataframe == 0)
                {
                    printf("Le CDataframe a ete cree avec succes\n");
                    CDataframe_exists = true;
                    
                    // Peupler le CDataframe artificiellement - Test seulement
                    populate_dataframe_artificially(&CDataframe, &taille_CDataframe);


                }
            }
            else
                printf("Le CDataframe a deja ete cree\n");
        }
        else if (choix == 2)
            printf("Le chargement d'un CDataframe sera bientot disponible...\n");

        if (choix == 0)
            go = 0;
    }
    
    // Libération de la mémoire occupée par les colonnes et le dataframe
    free_ressources(CDataframe, taille_CDataframe);

    return 0;
}


//OPERATEURS_DE_COMPARAISON egal = { EGAL };
//OPERATEURS_DE_COMPARAISON superieur = { SUPERIEUR };
//OPERATEURS_DE_COMPARAISON inferieur = { INFERIEUR };
//stats_sur_valeur(CDataframe, taille_CDataframe, 10, egal);




