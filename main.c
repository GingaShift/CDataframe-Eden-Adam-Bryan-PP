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

//OPERATEURS_DE_COMPARAISON egal = { EGAL };
//OPERATEURS_DE_COMPARAISON superieur = { SUPERIEUR };
//OPERATEURS_DE_COMPARAISON inferieur = { INFERIEUR };
//stats_sur_valeur(CDataframe, taille_CDataframe, 10, egal);  

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

int afficher_cdataframe(COLONNE** dataframe, int taille_dataframe, int nombre_col)
{   
    if (dataframe == NULL)
    {
        printf("Veuillez d'abord creer le CDataframe et le remplir\n\n");
        return FAILED;
    }
    
    printf("\n\n");

    int nombre_colonnes_a_afficher = 0;

    // affichage de la ligne des noms de toutes les colonnes voulues
    for(int i=0; i < nombre_col; i++)
    {
        printf("Col %d - \"%s\"  ||  ", i, dataframe[i]->nom);

    }

    printf("\n\n");

    // Commentaire final
    switch (taille_dataframe)
    {
        case 0:
            printf("Il n'y a aucune colonne a afficher dans le CDataframe");
            break;
        case 1:
            printf("Une colonne a ete affichee pour ce CDataframe");
            break;
        default:
            printf("%d colonnes ont ete affiches pour ce CDataframe", taille_dataframe);
            break;
    }

    printf("\n\n");

    return SUCCESS;
}

int main()
{
    // Creation et ini du CDataframe
    int taille_CDataframe = -1;
    COLONNE** CDataframe = NULL;
    bool CDataframe_exists = false;

    // a mettre dans fonction "afficher_menu_general"
    printf("\n");
    printf("************************************************************************\n");
    printf("*                                                                      *\n");
    printf("*                     =-    MENU GENERAL    -=                         *\n");    
    printf("*                                                                      *\n");
    printf("************************************************************************\n");
    printf("\n");
    printf("1. Creer le CDataframe");
    printf("                  ");
    printf("2. Charger un CDataframe\n\n");
    printf("3. Creer une colonne");
    printf("                    ");
    printf("4. Afficher le nom des colonnes\n\n");
    printf("5. Gestion des donnees (Ajout, Suppr, Stats, Autre...)\n\n");
    printf("6. Afficher le CDataframe\n\n");
    printf("0. Quitter le programme\n\n");
    
    int choix = 0;
    int go = 1;
    int nombre_col = 0;

    printf("\nChoisissez un des numeros du menu puis validez en appuyant sur la touche Entree\n\n");
    printf("POUR UNE DEMO RAPIDE, CHOISISSEZ DANS L'ORDRE L'ENTREE 1, PUIS 4 ET, ENFIN 6\n\n");

    // Boucle jusqu'à ce que la saisie soit valide
    while (go == 1)
    {
        scanf("%d", &choix);

        // a mettre dans fonction "manager_choix_menu_general" et creer aussi une fonction "manager_choix_menu_gestion_des_donnees"
        switch (choix)
        {
            case 0:
                //system("cls");
                go = 0;
                break;
            
            case 1:
                printf("\nChoix 1 - Creation du CDataframe:\n");
                
                // si le dataframe n'existe pas
                if (! CDataframe_exists)
                {
                    CDataframe = creer_cdataframe(&taille_CDataframe, &CDataframe_exists);
                    
                    // dataframe vide créé avec succès
                    if (CDataframe == NULL && taille_CDataframe == 0)
                    {
                        printf("\nLe CDataframe a ete cree avec succes\n");

                        // si le CDataframe a été créé, taille_CDataframe passe de -1 à 0. taille_CDataframe = 0 signifie qu'il a été créé via creer_cdataframe
                        taille_CDataframe == 0;

                        // Peupler le CDataframe artificiellement - Test seulement
                        populate_dataframe_artificially(&CDataframe, &taille_CDataframe);

                        printf("\nTrois colonnes ont ete ajoutees. Elles contiennent quelques donnees pour un test rapide\n\n");
                    }
                }
                else if (taille_CDataframe >= 0)
                    printf("\nLe CDataframe a deja ete cree\n");
                break;
            case 2:
                printf("\nChoix 2 - Chargement du CDataframe:\n");
                printf("\nLe chargement d'un CDataframe sera bientot disponible...\n\n");
                break;
            case 3:
                printf("\nChoix 3 - Creation d'une colonne:\n");
                printf("\nLa creation d'une colonne sera bientot disponible...\n\n");
                break;
            case 4:
                printf("\nChoix 4 - Affichage du nom des colonnes:\n");
                nombre_col = afficher_noms_colonnes(CDataframe, taille_CDataframe);
                printf("\n Le(s) nom(s) de %d colonne(s) ont ete affiche(s)\n\n", nombre_col);
                break;
            case 5:
                printf("\nChoix 5 - Gestion des donnees:\n");
                printf("\nLa gestion des donnees sera bientot disponible...\n\n");
                break;
            case 6:
                printf("\nChoix 6 - Affichage du CDataframe:");
                afficher_cdataframe(CDataframe, taille_CDataframe, taille_CDataframe);
                break;
        default:
            break;
        }
    }
    
    // Libération de la mémoire occupée par les colonnes et le dataframe
    free_ressources(CDataframe, taille_CDataframe);

    return 0;
}
