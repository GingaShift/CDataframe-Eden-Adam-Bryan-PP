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

// Declaration du CDataframe
DATAFRAME2* CDataframe2;

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

DATAFRAME2* manage_creation_of_cdataframe()
{
    // Demander le nom du CDataframe
    char* dataframe_title = saisie_chaine("\n Veuillez saisir le nom du CDataframe:\n");

    if (dataframe_title[0] == '\0')
    {
        printf("\nLe nom que vous avez saisie pour le CDataframe n'est pas valide\n");
        return NULL;
    }

    DATAFRAME2* dataframe = create_cdataframe(dataframe_title);

    if (dataframe != NULL)
    {
        return dataframe;
    }
    else
        return NULL;
}

#pragma region menu_management

void afficher_menu()
{
    printf("\n");
    printf("    ***************************************************************************************************************\n");
    printf("    *                                                                                                             *\n");
    printf("    *                                          ****   CDATAFRAME   ****                                           *\n");
    printf("    *                                                                                                             *\n");
    printf("    *                                          =-    MENU GENERAL    -=                                           *\n");
    printf("    *                                                                                                             *\n");
    printf("    ***************************************************************************************************************\n");
    printf("    *                                                                                                             *\n");
    printf("    *  \033[4m1. Alimentation\033[0m                                          \033[4m2. Affichage\033[0m                                      *\n");
    printf("    *                                                                                                             *\n");
    printf("    *  X 11. Creation d'un CDataframe vide                        21. Afficher tout le CDataframe                 *\n");
    printf("    *                                                                                                             *\n");
    printf("    *    12. Remplissage du CDataframe a partir                   22. Afficher les lignes du CDataframe selon     *\n");
    printf("    *        de saisies utilisateurs                                  une eventuelle limite de l'utilisateur      *\n");
    printf("    *                                                                                                             *\n");
    printf("    *  X 13. Remplissage automatique du CDataframe                23. Afficher les colonnes du CDataframe selon   *\n");
    printf("    *                                                                 une eventuelle limite de l'utilisateur      *\n");
    printf("    *    14. Sauvegarder le CDataframe dans un fichier                                                            *\n");
    printf("    *                                                             24. Afficher le nombre de colonnes              *\n");
    printf("    *    15. Charger un CDataframe depuis un fichier                                                              *\n");
    printf("    *                                                             25. Afficher le nom et le type des colonnes     *\n");
    printf("    *                                                                                                             *\n");
    printf("    *                                                             26. Afficher le contenu d'une colonne           *\n");
    printf("    *                                                                                                             *\n");
    printf("    *                                                             27. Afficher le nombre de lignes                *\n");
    printf("    *                                                                                                             *\n");
    printf("    *                                                                                                             *\n");
    printf("    *  \033[4m3. Operations usuelles\033[0m                                   \033[4m4. Analyse et statistiques\033[0m                        *\n");
    printf("    *                                                                                                             *\n");
    printf("    *    31. Ajouter une ligne de valeurs au                      41. Nombre de cellules contenant une            *\n");
    printf("    *         CDataframe                                              valeur egale a \"x\"                          *\n");
    printf("    *                                                                                                             *\n");
    printf("    *    32. Supprimer une ligne de valeurs du                    42. Nombre de cellules contenant une            *\n");
    printf("    *         CDataframe                                              valeur superieure a \"x\"                     *\n");
    printf("    *                                                                                                             *\n");
    printf("    *    33. Ajouter une colonne au CDataframe                    43. Nombre de cellules contenant une            *\n");
    printf("    *                                                                 valeur inferieure a \"x\"                     *\n");
    printf("    *    34. Supprimer une colonne du CDataframe                                                                  *\n");
    printf("    *                                                                                                             *\n");
    printf("    *    35. Renommer le titre d'une colonne                  \033[4m5. Divers\033[0m                                           *\n");                                                   
    printf("    *                                                                                                             *\n");
    printf("    *    36. Trier une colonne                                 51. Effacer l'ecran et afficher le menu            *\n");
    printf("    *                                                                                                             *\n");
    printf("    *    37. Lire la valeur d'une cellule                      52. Afficher la version du programme               *\n");
    printf("    *                                                                                                             *\n");
    printf("    *    38. Modifier valeur d'une cellule                     53. Quitter le programme                           *\n");
    printf("    *                                                                                                             *\n");
    printf("    *    39. Verifier l'existence d'une valeur                                                                    *\n");
    printf("    *                                                                                                             *\n");
    printf("    ***************************************************************************************************************\n");
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
        process_user_menu_choice_main_section_2(sub_section_number);

        break;
    case 3:
        process_user_menu_choice_main_section_3(sub_section_number);
        break;
    case 4:
        process_user_menu_choice_main_section_4(sub_section_number);
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
    switch (sub_section_number)
    {
        case 11:
            printf("\nChoix 11 - Creation d'un CDataframe :\n");
            
            CDataframe2 = manage_creation_of_cdataframe();
            if (CDataframe2 != NULL)
                printf("\n Le CDataframe \"%s\" a ete cree avec succes\n", CDataframe2->title);
            else
                printf("\n Une erreur est survenue lors de la creation du CDataframe");
            break;
        case 12:

            break;

        case 13:
            
            printf("\nChoix 13 - Remplissage automatique du CDataframe :\n");

            if (populate_dataframe_automatically(CDataframe2))
                printf("\nLe dataframe a ete remplie avec plusieurs colonnes de differents types contenant diverses donnees\n");
            else
                printf("\n Un probleme est survenue lors du remplissage automatique du CDataframe\n");

            break;
        
        case 14:

            printf("\nChoix 14 - Sauvegarder le CDataframe dans un fichier :\n");

            if (save_dataframe_to_csv(CDataframe2, NOM_FICHIER_CSV, SEPARATEUR_CSV))
                printf("\nLe CDdataframe a ete sauvegarde avec succes\n");
            else
                printf("\n Un probleme est survenue lors de la sauvegarde du CDataframe dans le fichier CSV\n");

            break;

    default:
        break;
    }
}

int process_user_menu_choice_main_section_2(int sub_section_number)
{

}

int process_user_menu_choice_main_section_3(int sub_section_number)
{
    switch (sub_section_number)
    {
        case 31:
            
            printf("\nChoix 31 - Ajouter une ligne de valeurs au CDataframe :\n");
            add_row_manually(CDataframe2);
            break;

        case 38:

            printf("\nChoix 38 - Affichage du nom des colonnes:\n");
            int nombre_col = print_name_of_columns(CDataframe2);
            printf("\nLe(s) nom(s) de %d colonne(s) ont ete affiche(s)\n\n", nombre_col);
            break;

        default:
            break;
    }
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

#pragma endregion CDataframe 2

int res = 0;

int main()
{
    int choix_menu = -1; //7; // -1 = Choix manu, sinon indiquer la valeur choisit pr choix auto
    int go = 1;
    int res_choix_menu = 0;

    afficher_menu();
    
    // Boucle jusqu'à ce que la saisie soit valide
    while (go == 1)
    {
        //test();
        
        if (choix_menu == -1)
        {
            printf("\n\n");
            printf("Choisissez le nombre d'une commande et validez \"Entree\"\n\n");
            
            res_choix_menu = scanf("%d", &choix_menu);

            process_user_menu_choice(choix_menu);
            
            choix_menu = -1;
        }
    }
    
    // Libération de la mémoire occupée par les colonnes et le dataframe
    free_all_ressources(&CDataframe1);

    return 1;
}

void test()
{
    if (CDataframe2 == NULL)
    {
        CDataframe2 = create_cdataframe("Dataframe 2");
        populate_dataframe_automatically(CDataframe2);
    }

    res = show_cdataframe(CDataframe2, NO_LIMIT, 20);

    //add_row_manually(CDataframe2);

    /////////////////////////////////////////////////////////////////////////////////////////
    // Tri de la colonne INT par tri insertion
    printf("\nContenu de la colonne \"%s\" AVANT trie insertion:\n", CDataframe2->columns[0]->title);
    print_column(CDataframe2->columns[0], false, NO_LIMIT);

    // def sens du tri: 0 = du + petit au + grand
    CDataframe2->columns[0]->sort_dir = 1;
    //effectuer le tri
    sort_column_after_insertion_int(CDataframe2->columns[0]);

    printf("\nContenu de la colonne \"%s\" APRES trie insertion:\n", CDataframe2->columns[0]->title);
    print_col_by_index(CDataframe2->columns[0]);
    /////////////////////////////////////////////////////////////////////////////////////////

    /////////////////////////////////////////////////////////////////////////////////////////
    // Tri de la colonne INT par tri quicksort
    printf("\nContenu de la colonne \"%s\" AVANT trie quicksort:\n", CDataframe2->columns[0]->title);
    print_column(CDataframe2->columns[0], false, NO_LIMIT);

    quick_sort_column(CDataframe2->columns[0], 0, CDataframe2->columns[0]->size - 1, 0);

    printf("\nContenu de la colonne \"%s\" APRES trie quicksort:\n", CDataframe2->columns[0]->title);
    print_col_by_index(CDataframe2->columns[0]);
    /////////////////////////////////////////////////////////////////////////////////////////

    /////////////////////////////////////////////////////////////////////////////////////////
    // Tri de la colonne DOUBLE par quicksort
    printf("\nContenu de la colonne \"%s\" AVANT trie quicksort:\n", CDataframe2->columns[0]->title);
    print_column(CDataframe2->columns[0], false, NO_LIMIT);

    quick_sort_column(CDataframe2->columns[0], 0, CDataframe2->columns[0]->size - 1, 0);

    printf("\nContenu de la colonne \"%s\" APRES trie quicksort:\n", CDataframe2->columns[0]->title);
    print_col_by_index(CDataframe2->columns[0]);
    /////////////////////////////////////////////////////////////////////////////////////////

    sauvegarder_types_colonnes_dans_fichier(CDataframe2, NOM_FICHIER_CSV, SEPARATEUR_CSV);
}
//////////////////////////////////////////////////////////////////////////