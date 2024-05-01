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

// Declaration du CDataframe
DATAFRAME CDataframe;
bool CDataframe_exists = false;

int res = 0;

//OPERATEURS_DE_COMPARAISON egal = { EGAL };
//OPERATEURS_DE_COMPARAISON superieur = { SUPERIEUR };
//OPERATEURS_DE_COMPARAISON inferieur = { INFERIEUR };
//stats_sur_valeur(CDataframe, taille_CDataframe, 10, egal);  

void afficher_menu()
{
    printf("\n");
    printf(" ****************************************************************************\n");
    printf(" *                                                                          *\n");
    printf(" *                         =-    MENU GENERAL    -=                         *\n");
    printf(" *                                                                          *\n");
    printf(" ****************************************************************************\n");
    printf(" *                                                                          *\n");
    printf(" *  1. Creer le CDataframe");
    printf("             ");
    printf(" 2. Charger un CDataframe            *");
    printf("\n");
    printf(" *                                                                          *");
    printf("\n");
    printf(" *  3. Creer une colonne");
    printf("               ");
    printf(" 4. Afficher le nom des colonnes     *");
    printf("\n");
    printf(" *                                                                          *");
    printf("\n");
    printf(" *  5. Gestion donnees (Remplir)");
    printf("       ");
    printf(" 6. Afficher le CDataframe           *");
    printf("\n");
    printf(" *                                                                          *");
    printf("\n");
    printf(" *                                                                          *");
    printf("\n");
    printf(" *                       0. Quitter le programme                            *");
    printf("\n");
    printf(" *                                                                          *");
    printf("\n");
    printf(" *                                                                          *");
    printf("\n");
    printf(" ****************************************************************************\n");
}

int free_all_ressources(DATAFRAME* dataframe)
{
    // liberer la mémoire allouée aux colonnes
    for (int i = 0; i < dataframe->taille; i++)
    {
        // Libérer les données de la colonne si nécessaire
        if (dataframe->colonnes[i]->data != NULL)
            free(dataframe->colonnes[i]->data);

        // Libérer la mémoire allouée pour la structure de colonne
        free(dataframe->colonnes[i]);
    }

    if (dataframe->taille > 0)
        // liberer la mémoires allouée au dataframe
        free(dataframe->colonnes);

    return 0;
}

int main()
{
    int choix = 6; //-1;
    int go = 1;
    int nombre_col = 0;
    int res_choix_menu = -1;

    afficher_menu();
    
    printf("\n\n");
    printf("INSTRUCTIONS:");
    printf("\n");
    printf("Choisissez un des numeros du menu puis validez en appuyant sur la touche Entree\n\n");
    printf("NOTE IMPORTANTE:");
    printf("\n");
    printf("Pour une demo rapide, choisissez dans l'ordre l'entree 1, puis 5,\nensuite 4 et enfin 6\n\n");

    // Boucle jusqu'à ce que la saisie soit valide
    while (go == 1)
    {
        printf("\n");
        printf(" - Choisissez une des entrees du menu puis validez :\n\n");

        //if (choix == -1)
            res_choix_menu = scanf("%d", &choix);

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
                    CDataframe = creer_cdataframe(&CDataframe_exists, "CDataframe1");

                    // dataframe vide créé avec succès
                    if (CDataframe_exists)
                    {
                        printf("\nLe CDataframe a ete cree avec succes\n\n");
                    }
                }
                else
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
                nombre_col = afficher_noms_colonnes(CDataframe);
                printf("\nLe(s) nom(s) de %d colonne(s) ont ete affiche(s)\n\n", nombre_col);
                break;
            case 5:
                printf("\nChoix 5 - Gestion des donnees:\n");
                if (! CDataframe_exists)
                {
                    printf("Veuillez d'abord creer un CDataframe\n\n");
                    break;
                }

                // Peupler le CDataframe artificiellement - Test seulement - 
                res = populate_dataframe_artificially(&CDataframe);
                
                printf("\nLa gestion des donnees sera bientot disponible dans son entierete...\n");
                printf("\nCependant, trois colonnes ont ete ajoutees. Elles contiennent egalement quelques donnees pour cette demo\n");
                printf("Vous pouvez visualiser ces colonnes dans le detail en choisissant l'entree de menu \"6\"\n\n");

                break;

            case 6:
                
                // DEMO:
                CDataframe = creer_cdataframe(&CDataframe_exists, "CDataframe1");
                              
                // Peupler le CDataframe artificiellement - Test seulement - 
                //populate_dataframe_artificially_old(&CDataframe_old, &taille_CDataframe_old);
                res = populate_dataframe_artificially(&CDataframe);

                printf("\nChoix 6 - Affichage du CDataframe:");
                
                if (!CDataframe_exists)
                {
                    printf("\n Impossible d'afficher le CDataframe car il n'existe pas.");
                    printf("\n Veuillez le creer ou le charger a partir d'une source.");
                    break;
                }

                res = afficher_cdataframe(&CDataframe, 0, 0);

                choix = -1;

                break;
            
            case 7:

                // DEMO:
                CDataframe = creer_cdataframe(&CDataframe_exists, "CDataframe1");

                // Peupler le CDataframe artificiellement - Test seulement - 
                //populate_dataframe_artificially_old(&CDataframe_old, &taille_CDataframe_old);
                res = populate_dataframe_artificially(&CDataframe);

                /////////////////////////////////////////////////////////////////////////////////
                // Fonction à tester 2 colonnes
                res = supprimer_colonne(&CDataframe, 2);
                /////////////////////////////////////////////////////////////////////////////////

                printf("\nChoix 6 - Affichage du CDataframe:");

                if (!CDataframe_exists)
                {
                    printf("\n Impossible d'afficher le CDataframe car il n'existe pas.");
                    printf("\n Veuillez le creer ou le charger a partir d'une source.");
                    break;
                }

                res = afficher_cdataframe(&CDataframe, 0, 0);

                choix = -1;

                break;

        default:
            break;
        }
    }
    
    // Libération de la mémoire occupée par les colonnes et le dataframe
    free_all_ressources(&CDataframe);

    return 0;
}
