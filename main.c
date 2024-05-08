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

#pragma region code_main

int res = 0;

#pragma region CDataframe 1

// Declaration du CDataframe
DATAFRAME1* CDataframe1;
bool CDataframe1_exists = false;

int free_all_ressources(DATAFRAME1* dataframe)
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

    return 1;
}

#pragma endregion CDataframe 1

#pragma region CDataframe 2

// Declaration du CDataframe
DATAFRAME2* CDataframe2;
bool CDataframe2_exists = false;

int free_ressources(DATAFRAME2* dataframe)
{
    // liberer la mémoire allouée aux colonnes
    for (int i = 0; i < dataframe->size; i++)
    {
        // Libérer les données de la colonne si nécessaire
        if (dataframe->columns[i]->data != NULL)
            free(dataframe->columns[i]->data);

        // Libérer la mémoire allouée pour la structure de colonne
        free(dataframe->columns[i]);
    }

    if (dataframe->size > 0)
        // liberer la mémoires allouée au dataframe
        free(dataframe->columns);

    return 1;
}

#pragma endregion CDataframe 2


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

    // Boucle jusqu'à ce que la saisie soit valide
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
            if (!CDataframe1_exists)
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

            bool nouveau_bloc_cellules_ajouté_a_colonne = false;

            CDataframe2 = create_cdataframe(&CDataframe1_exists, "Dataframe 2");

            // DEMO DF2:
            //COLUMN* col = create_column(INT, "MyIntegerColumn");

            add_column(CDataframe2, UINT, "Col_1");
            add_column(CDataframe2, INT, "Col_2");
           
            unsigned int value1 = 10;
            if (insert_value(CDataframe2->columns[0], &value1, &nouveau_bloc_cellules_ajouté_a_colonne))
                printf("\nValeur col 0, cell 0: %d", *((unsigned int*)CDataframe2->columns[0]->data[0]));

                printf("\nValeur col 0, cell 0: %d", *((unsigned int*)CDataframe2->columns[0]->data[0]));

            unsigned int value2 = 11;
            if (insert_value(CDataframe2->columns[0], &value2, &nouveau_bloc_cellules_ajouté_a_colonne))
                printf("\nValeur col 0, cell 1: %d", *((unsigned int*)CDataframe2->columns[0]->data[1]));

            int value3 = 20;
            if (insert_value(CDataframe2->columns[1], &value3, &nouveau_bloc_cellules_ajouté_a_colonne))
                printf("\nValeur col 1, cell 0: %d", *((int*)CDataframe2->columns[1]->data[0]));

            int value4 = 21;
            if (insert_value(CDataframe2->columns[1], &value4, &nouveau_bloc_cellules_ajouté_a_colonne))
                printf("\nValeur col 1, cell 1: %d", *((int*)CDataframe2->columns[1]->data[1]));
            
            char str[50];
            convert_value(CDataframe2->columns[1], 1, str, sizeof(str));
            printf("\nConverted value: %s\n", str);


            break;

                // FIN DEMO DF2:

                // DEMO DF1:
                //CDataframe = gestion_creation_cdataframe(&CDataframe_exists);
                CDataframe1 = creer_cdataframe(&CDataframe1_exists, "Dataframe 1");

                // Peupler le CDataframe artificiellement - Test seulement - 
                res = populate_dataframe_artificially(CDataframe1);

                /////////////////////////////////////////////////////////////////////////////////
                // Emplacement de la fonction à tester:

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
    
    // Libération de la mémoire occupée par les colonnes et le dataframe
    free_all_ressources(&CDataframe1);

    return 1;

}

#pragma endregion code_main

//////////////////////////////////////////////////////////////////////////

#pragma region gestion_choix_menu

#pragma region CDataframe 1

DATAFRAME1* gestion_creation_cdataframe(bool* dataframe_exists)
{
    printf("\nChoix 1 - Creation du CDataframe:\n");

    // Demander le nom du CDataframe
    char* chaine = saisie_chaine("\nVeuillez saisir le nom du CDataframe:\n");

    DATAFRAME1* dataframe = creer_cdataframe(dataframe_exists, chaine);

    if (dataframe != NULL)
        printf("\nLe CDataframe a ete cree avec succes\n\n");

    return dataframe;
}

#pragma endregion CDataframe 1

#pragma region CDataframe 2

#pragma endregion CDataframe 2

#pragma endregion gestion_choix_menu
