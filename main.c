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
#include "SaveLoadCSV.h"
#include "Sort.h"

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

#pragma region code_main

int res = 0;

#pragma region menu_management

void afficher_menu()
{
    printf("\n");
    printf("    **************************************************************************************************************\n");
    printf("    *                                                                                                            *\n");
    printf("    *                                         =-    MENU GENERAL    -=                                           *\n");
    printf("    *                                                                                                            *\n");
    printf("    **************************************************************************************************************\n");
    printf("    *                                                                                                            *\n");
    printf("    *  \033[4m1. Alimentation\033[0m                                          \033[4m2. Affichage\033[0m                                     *\n");
    printf("    *                                                                                                            *\n");
    printf("    *      1. Creation d'un CDataframe vide                      1. Afficher tout le CDataframe                  *\n");
    printf("    *                                                                                                            *\n");
    printf("    *      2. Remplissage du CDataframe a partir                 2. Afficher une partie des lignes               *\n");
    printf("    *         de saisies utilisateurs                               du CDataframe selon une limite               *\n");
    printf("    *      3. Remplissage en dur du CDataframe                      fournie par l'utilisateur                    *\n");
    printf("    *                                                                                                            *\n    ");
    printf("    *                                                  3. Afficher une partie des                                *\n");
    printf("    *                                                     colonnes du CDataframe selon                           *\n");
    printf("    *                                                     une limite fournie par                                 *\n");
    printf("    *                                                     l'utilisateur                                          *\n");
    printf("    *                                                                                                            *\n");
    printf("    *                                                                                                            *\n");
    printf("    *                                                                                                            *\n");
    printf("    *  \033[4m3. Operations usuelles\033[0m                          \033[4m4. Analyse et statistiques\033[0m                                *\n");
    printf("    *                                                                                                            *\n");
    printf("    *      1. Ajouter une ligne de valeurs au           1. Afficher le nombre de lignes                          *\n");
    printf("    *         CDataframe                                2. Afficher le nombre de colonnes                        *\n");
    printf("    *                                                                                                            *\n");
    printf("    *      2. Supprimer une ligne de valeurs du         3. Nombre de cellules contenant une                      *\n");
    printf("    *         CDataframe                                   valeur egale a x                                      *\n");
    printf("    *                                                                                                            *\n");
    printf("    *      3. Ajouter une colonne au CDataframe         4. Nombre de cellules contenant une                      *\n");
    printf("    *      4. Supprimer une colonne du CDataframe          valeur superieure a x                                 *\n");
    printf("    *                                                                                                            *\n");
    printf("    *      5. Renommer le titre d'une colonne du        5. Nombre de cellules contenant une                      *\n");
    printf("    *         CDataframe                                   valeur inferieure a x                                 *\n");
    printf("    *                                                                                                            *\n");
    printf("    *      6. Verifier l'existence d'une valeur         6. Quitter le programme                                  *\n");
    printf("    *         (recherche) dans le CDataframe                                                                     *\n");
    printf("    *                                                                                                            *\n");
    printf("    *      7. Acceder/remplacer la valeur se                                                                     *\n");
    printf("    *         trouvant dans une cellule du                                                                       *\n");
    printf("    *         CDataframe en utilisant son                                                                        *\n");
    printf("    *         numero de ligne et de colonne                                                                      *\n");
    printf("    *                                                                                                            *\n");
    printf("    *      8. Afficher les noms des colonnes                                                                     *\n");
    printf("    *                                                                                                            *\n");
    printf("    *                                                                                                            *\n");
    printf("    **************************************************************************************************************\n");
}

void process_user_menu_choice(int sub_section_number)
{
    // Controler le fait que user ait entre un choix compris dans une certaine plage seulement

    // Extraire le num de section principale choisie (toujours le premier num)
    int main_section_number = obtenir_premier_chiffre(sub_section_number);
    
    switch (main_section_number)
    {
        case 1:
            process_user_menu_choice_main_section_1(sub_section_number);
            break;
        case 2:

            break;
        case 3:

            break;
        case 4:

            break;
        case 5:
            process_user_menu_choice_main_section_5(sub_section_number);
            break;
        default:
            break;
    }
}

int process_user_menu_choice_main_section_1(int sub_section_number)
{

}

int process_user_menu_choice_main_section_2(int sub_section_number)
{

}

int process_user_menu_choice_main_section_3(int sub_section_number)
{

}

int process_user_menu_choice_main_section_4(int sub_section_number)
{

}

int process_user_menu_choice_main_section_5(int sub_section_number)
{
    switch (sub_section_number)
    {
        case 51:

            // Effacer l'écran et aficher le menu
            system("cls");
            afficher_menu();
            break;
        
        default:
            break;
    }
}

#pragma endregion menu_management

int main()
{
    int choix_menu = 7; //7; // -1 = Choix manu, sinon indiquer la valeur choisit pr choix auto
    int go = 1;
    int nombre_col = 0;
    int res_choix_menu = -1; // 0 = Choix manu; -1 = Choix auto;

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
        printf(" - Choisissez une des entrees du menu puis validez par la touche Entree:\n\n");

        if (choix_menu == -1)
            res_choix_menu = scanf("%d", &choix_menu);

        //process_user_menu_choice(choix_menu);

        switch (choix_menu)
        {
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

        case 6:

            printf("\nChoix 6 : [Lib du titre]\n");

            // DEMO:
            CDataframe1 = creer_cdataframe(&CDataframe1_exists, "CDataframe1");

            // Peupler le CDataframe artificiellement - Test seulement - 
            res = remplir_dataframe_automatiquement(CDataframe1);

            res = afficher_cdataframe(&CDataframe1, 0, 0);

            choix_menu = -1;

            break;

        case 7:

            printf("\nChoix 7 : [Lib du titre]\n");

            bool block_cells_added_to_column = false;

            CDataframe2 = create_cdataframe(&CDataframe2_exists, "Dataframe 2");

            // TODO: res = populate_dataframe_automatically(CDataframe2);

            add_column(CDataframe2, INT, "Col_INT");
            add_column(CDataframe2, STRING, "Col_STRING");
            add_column(CDataframe2, DOUBLE, "Col_DOUBLE");
            add_column(CDataframe2, STRUCTURE, "Col_STRUCTURE");

            int i1 = 52;
            int i2 = 44;
            int i3 = 15;
            int i4 = 18;
            int i5 = 0;
            int i6 = 0;

            i1 = 5;
            i2 = 3;
            i3 = 7;
            i4 = 1;
            i5 = 9;
            i6 = 2;

            insert_value(CDataframe2->columns[0], &i1, &block_cells_added_to_column);
            insert_value(CDataframe2->columns[0], &i2, &block_cells_added_to_column);
            insert_value(CDataframe2->columns[0], &i3, &block_cells_added_to_column);
            insert_value(CDataframe2->columns[0], &i4, &block_cells_added_to_column);
            insert_value(CDataframe2->columns[0], &i5, &block_cells_added_to_column);
            insert_value(CDataframe2->columns[0], &i6, &block_cells_added_to_column);

            /////////////////////////////////////////////////////////////////////////////////////////
            // Tri de la colonne par quicksort
            printf("\nContenu de la colonne \"%s\" AVANT trie :\n", CDataframe2->columns[0]->title);
            print_column(CDataframe2->columns[0], false, NO_LIMIT);

            quick_sort_column(CDataframe2->columns[0], 0, CDataframe2->columns[0]->size - 1, 0);

            printf("\nContenu de la colonne \"%s\" APRES trie :\n", CDataframe2->columns[0]->title);
            print_col_by_index(CDataframe2->columns[0]);
            /////////////////////////////////////////////////////////////////////////////////////////

            sauvegarder_types_colonnes_dans_fichier_csv(CDataframe2, NOMBRE_FICHIER_CSV);

            break;

                //Afficher CDataframe
                if (!CDataframe1_exists)
                {
                    printf("\n Impossible d'afficher le CDataframe car il n'existe pas.");
                    printf("\n Veuillez le creer ou le charger a partir d'une source.");
                    break;
                }

                res = afficher_cdataframe(CDataframe1, NO_LIMIT, 20);

                choix_menu = -1;

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