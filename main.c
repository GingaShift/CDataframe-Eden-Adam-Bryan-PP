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
#include "Gestion_actions_utilisateur.h"

int res = 0;

#pragma region CDataframe 1

// Declaration du CDataframe
DATAFRAME1* CDataframe1;
bool CDataframe1_exists = false;

int free_all_ressources(DATAFRAME1* dataframe)
{
    // liberer la m�moire allou�e aux colonnes
    for (int i = 0; i < dataframe->taille; i++)
    {
        // Lib�rer les donn�es de la colonne si n�cessaire
        if (dataframe->colonnes[i]->data != NULL)
            free(dataframe->colonnes[i]->data);

        // Lib�rer la m�moire allou�e pour la structure de colonne
        free(dataframe->colonnes[i]);
    }

    if (dataframe->taille > 0)
        // liberer la m�moires allou�e au dataframe
        free(dataframe->colonnes);

    return 1;
}

#pragma endregion Fin CDataframe 1

#pragma region CDataframe 2

// Declaration du CDataframe
DATAFRAME2* CDataframe2;
bool CDataframe2_exists = false;

int free_ressources(DATAFRAME2* dataframe)
{
    // liberer la m�moire allou�e aux colonnes
    for (int i = 0; i < dataframe->size; i++)
    {
        // Lib�rer les donn�es de la colonne si n�cessaire
        if (dataframe->columns[i]->data != NULL)
            free(dataframe->columns[i]->data);

        // Lib�rer la m�moire allou�e pour la structure de colonne
        free(dataframe->columns[i]);
    }

    if (dataframe->size > 0)
        // liberer la m�moires allou�e au dataframe
        free(dataframe->columns);

    return 1;
}

#pragma endregion Fin CDataframe 2


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

int main()
{
    int choix = 7; //-1;
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

    // Boucle jusqu'� ce que la saisie soit valide
    while (go == 1)
    {
        printf("\n");
        printf(" - Choisissez une des entrees du menu puis validez :\n\n");

        if (choix == -1)
            res_choix_menu = scanf("%d", &choix);

        // a mettre dans fonction "manager_choix_menu_general" et creer aussi une fonction "manager_choix_menu_gestion_des_donnees"
        switch (choix)
        {
            case 0:
                //system("cls");
                go = 0;
                break;
            
            case 1:

                if (CDataframe1_exists)
                {
                    printf("\nLe CDataframe a deja ete cree\n");
                    break;
                }

                CDataframe1 = gestion_creation_cdataframe(&CDataframe1_exists);
                
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
                nombre_col = afficher_noms_colonnes(CDataframe1);
                printf("\nLe(s) nom(s) de %d colonne(s) ont ete affiche(s)\n\n", nombre_col);
                break;

            case 5:
                
                printf("\nChoix 5 - Gestion des donnees:\n");
                if (! CDataframe1_exists)
                {
                    printf("Veuillez d'abord creer un CDataframe\n\n");
                    break;
                }

                // Peupler le CDataframe artificiellement - Test seulement - 
                res = populate_dataframe_artificially(CDataframe1);
                
                break;

            case 6:
                
                // DEMO:
                CDataframe1 = creer_cdataframe(&CDataframe1_exists, "CDataframe1");
                              
                // Peupler le CDataframe artificiellement - Test seulement - 
                //populate_dataframe_artificially_old(&CDataframe_old, &taille_CDataframe_old);
                res = populate_dataframe_artificially(CDataframe1);

                printf("\nChoix 6 - Affichage du CDataframe:");
                
                if (!CDataframe1_exists)
                {
                    printf("\n Impossible d'afficher le CDataframe car il n'existe pas.");
                    printf("\n Veuillez le creer ou le charger a partir d'une source.");
                    break;
                }

                res = afficher_cdataframe(&CDataframe1, 0, 0);

                choix = -1;

                break;
            
            case 7:

                CDataframe2 = create_cdataframe(&CDataframe1_exists, "Dataframe 2");

                // DEMO DF2:
                //COLUMN* col = create_column(INT, "MyIntegerColumn");
                
                add_column(CDataframe2, INT, "Col_Un");

                int value1 = 10;
                if (insert_value(CDataframe2->columns[0], &value1))
                    printf("\nValeur col 0, cell 0: %d", *((int*)CDataframe2->columns[0]->data[0]));
                
                int value2 = 11;
                if (insert_value(CDataframe2->columns[0], &value2))
                    printf("\nValeur col 0, cell 1: %d", *((int*)CDataframe2->columns[0]->data[1]));

                add_column(CDataframe2, INT, "Col_Deux");

                int value3 = 20;
                if (insert_value(CDataframe2->columns[1], &value3))
                    printf("\nValeur col 1, cell 0: %d", *((int*)CDataframe2->columns[1]->data[0]));

                int value4 = 21;
                if (insert_value(CDataframe2->columns[1], &value4))
                    printf("\nValeur col1, cell 1: %d", *((int*)CDataframe2->columns[1]->data[1]));
                break;

                // FIN DEMO DF2:

                // DEMO DF1:
                //CDataframe = gestion_creation_cdataframe(&CDataframe_exists);
                CDataframe1 = creer_cdataframe(&CDataframe1_exists, "Dataframe 1");

                // Peupler le CDataframe artificiellement - Test seulement - 
                res = populate_dataframe_artificially(CDataframe1);

                /////////////////////////////////////////////////////////////////////////////////
                // Emplacement de la fonction � tester:

                /////////////////////////////////////////////////////////////////////////////////

                printf("\nChoix 6 - Affichage du CDataframe:");

                if (!CDataframe1_exists)
                {
                    printf("\n Impossible d'afficher le CDataframe car il n'existe pas.");
                    printf("\n Veuillez le creer ou le charger a partir d'une source.");
                    break;
                }

                res = afficher_cdataframe(CDataframe1, NO_LIMIT, 20);

                choix = -1;

                break;

        default:
            break;
        }
    }
    
    // Lib�ration de la m�moire occup�e par les colonnes et le dataframe
    free_all_ressources(&CDataframe1);

    return 1;
}
