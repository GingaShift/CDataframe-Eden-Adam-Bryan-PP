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

#define VAL_CHOIX_LIBRE_DANS_MENU = -1

int res = 0;

int major_version = 1;
int minor_version = 0;
int rev_version = 0;

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
    printf("    *  X 11. Creation d'un CDataframe vide                      X 21. Afficher le CDataframe                      *\n");
    printf("    *                                                                                                             *\n");
    printf("    *    12. Ajouter une colonne au CDataframe                  X 22. Afficher les lignes du CDataframe selon     *\n");
    printf("    *                                                                 une eventuelle limite de l'utilisateur      *\n");
    printf("    *    13. Remplir une colonne du CDataframe                                                                    *\n");
    printf("    *                                                           X 23. Afficher le nombre de colonnes              *\n");
    printf("    *    14. Ajouter une ligne de valeurs au CDataframe                                                           *\n");
    printf("    *                                                           X 24. Afficher le nom et le type des colonnes     *\n");
    printf("    *  X 15. Remplissage automatique du CDataframe                                                                *\n");
    printf("    *                                                             25. Afficher le contenu d'une colonne           *\n");
    printf("    *    16. Sauvegarder le CDataframe dans un fichier                                                            *\n");
    printf("    *                                                             26. Afficher le nombre de lignes                *\n");
    printf("    *    17. Charger un CDataframe depuis un fichier                                                              *\n");
    printf("    *                                                                                                             *\n");
    printf("    *                                                                                                             *\n");
    printf("    *  \033[4m3. Operations usuelles\033[0m                                   \033[4m4. Analyse et statistiques\033[0m                        *\n");
    printf("    *                                                                                                             *\n");
    printf("    *    31. Supprimer une colonne du CDataframe                  41. Nombre de cellules contenant une            *\n");
    printf("    *                                                                 valeur egale a \"x\"                          *\n");
    printf("    *    32. Supprimer une ligne de valeurs du                                                                    *\n");
    printf("    *        CDataframe                                           42. Nombre de cellules contenant une            *\n");
    printf("    *                                                                 valeur superieure a \"x\"                     *\n");
    printf("    *    33. Trier une colonne                                                                                    *\n");
    printf("    *                                                             43. Nombre de cellules contenant une            *\n");
    printf("    *    34. Lire la valeur d'une cellule                             valeur inferieure a \"x\"                     *\n");
    printf("    *                                                                                                             *\n");
    printf("    *    36. Modifier la valeur d'une cellule                                                                     *\n");
    printf("    *                                                          \033[4m5. Divers\033[0m                                          *\n");                                                   
    printf("    *    37. Verifier l'existence d'une valeur                                                                    *\n");
    printf("    *                                                           X 51. Reinitialiser l'ecran et afficher le menu   *\n");
    printf("    *                                                                                                             *\n");
    printf("    *                                                           X 52. Afficher les informations legales           *\n");
    printf("    *                                                                                                             *\n");
    printf("    *                                                           X 53. Quitter le programme                        *\n");
    printf("    *                                                                                                             *\n");
    printf("    ***************************************************************************************************************\n");
}

int process_user_menu_choice(int sub_section_number)
{
    // Controler le fait que user ait fait un choix compris dans une certaine plage seulement

    // Extraire le num de section principale choisie (toujours le premier num)
    int main_section_number = obtenir_premier_chiffre(sub_section_number);

    switch (main_section_number)
    {
        case 1:
            return process_user_menu_choice_main_section_1(sub_section_number);
        case 2:
            return process_user_menu_choice_main_section_2(sub_section_number);
        case 3:
            return process_user_menu_choice_main_section_3(sub_section_number);
        case 4:
            return process_user_menu_choice_main_section_4(sub_section_number);
        case 5:
            return process_user_menu_choice_main_section_5(sub_section_number);
        default:
            printf("\n\nVotre choix n'est pas valide\n");
            return -1;
    }
}

#pragma region menu_management_sub_menu_1

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

        return -1;

    case 12:


    case 13:


    case 14:

        printf("\nChoix 14 - Sauvegarder le CDataframe dans un fichier :\n");

        if (save_dataframe_to_csv(CDataframe2, NOM_FICHIER_CSV, SEPARATEUR_CSV))
            printf("\nLe CDdataframe a ete sauvegarde avec succes\n");
        else
            printf("\n Un probleme est survenue lors de la sauvegarde du CDataframe dans le fichier CSV\n");

        return -1;

    case 15:
        printf("\nChoix 13 - Remplissage automatique du CDataframe :\n");

        if (populate_dataframe_automatically(CDataframe2))
            printf("\nLe dataframe a ete remplie avec plusieurs colonnes de differents types contenant diverses donnees\n");
        else
            printf("\n Un probleme est survenue lors du remplissage automatique du CDataframe\n");

        return -1;

    default:
        break;
    }
}

// Code...

#pragma endregion menu_management_sub_menu_1

#pragma region menu_management_sub_menu_2

int process_user_menu_choice_main_section_2(int sub_section_number)
{
    switch (sub_section_number)
    {
        case 21:
            printf("\n 21. Afficher le CDataframe \"%s\" :\n", CDataframe2->title);
            return cmd_afficher_cdataframe();
        case 22:
            printf("\n 22. Afficher les lignes du CDataframe \"%s\" selon une eventuelle limite de l'utilisateur :\n", CDataframe2->title);
            return cmd_afficher_lignes_selon_limites_utilisateurs(CDataframe2);
        case 23:
            printf("\n 23. Afficher le nombre de colonnes du CDataframe \"%s\" :\n", CDataframe2->title);
            return cmd_afficher_nombre_de_colonnes(CDataframe2);
        case 24:
            printf("\n 24. Afficher le nom et le type des colonnes du CDataframe \"%s\" :\n", CDataframe2->title);
            return cmd_afficher_nom_et_type_des_colonnes(CDataframe2);
        default:
            break;
    }
}

int cmd_afficher_cdataframe()
{
    show_cdataframe(CDataframe2, NO_LIMIT, NO_LIMIT);
    return -1;
}

int cmd_afficher_lignes_selon_limites_utilisateurs(DATAFRAME2* dataframe)
{
    int ret = 0;
    int num_col_max_to_show = 0;
    int num_ligne_max_to_show = 0;

    if (dataframe == NULL)
    {
        printf("Veuillez d'abord creer ET remplir le CDataframe\n\n");
        return -1;
    }

    if (dataframe->size == 0)
    {
        printf("\n Le CDataframe %s ne contient aucune colonne\n", dataframe->title);
        printf("\n Appuyez sur une touche puis sur \"Entree\"  pour continuer\n");
        ret = getchar();
        return -1;
    }

    // Saisie du nombre de col max à afficher
    do {
        printf("\n Entrez le nombre max de colonnes a afficher :\n");
        printf("\n Pour afficher toutes les lignes, entrez la valeur \"-1\" :\n");
        printf("\n Note: Le CDataframe courant contient %d colonnes :\n", dataframe->size);

        scanf("%d", &num_col_max_to_show);

        // Vérifier si le choix est valide, sinon prevenir
        if (num_col_max_to_show == NO_LIMIT)
            ret = 1;
        if (num_col_max_to_show > dataframe->size)
            printf("\n Choix invalide. Veuillez entrer un num de colonne compris entre 1 et %d:\n", dataframe->size);
        else if (num_col_max_to_show <= 1)
        {
            printf("\n Le nombre doit être positif ou egal a -1 mais pas negatif ni egal a zero");
            printf("\n Veuillez entrer un nombre de colonnes max correspondant a cela et qui ne soit pas superieur a %d:\n", dataframe->size);

        }
        else
            ret = 1;
    } while (ret != 1); // Continuer tant que les valeurs entrees sont erronnees

    // Saisie du nombre de lignes max à afficher
    int nombre_lignes_total = get_number_of_rows(CDataframe2);
    
    if (nombre_lignes_total == 0)
    {
        printf("\n Le CDataframe %s ne contient aucune lignes\n", dataframe->title);
        printf("\n Appuyez sur une touche puis sur \"Entree\" pour continuer\n");
        ret = getchar();
        return -1;
    }

    do {
        printf("\n Entrez le nombre de lignes max a afficher :\n");
        printf("\n Note: Le CDataframe courant contient %d lignes :\n", nombre_lignes_total);

        scanf("%d", &num_ligne_max_to_show);

        // Vérifier si le choix est valide, sinon prevenir
        if (num_ligne_max_to_show > nombre_lignes_total)
        {
            printf("\n Choix invalide, le nombre de lignes a afficher ne doit pas exceder %d", nombre_lignes_total);
            printf("\n Veuillez entrer un nombre de lignes max compris entre 1 et %d:\n", nombre_lignes_total);
        }
        else if (num_ligne_max_to_show <= 1)
        {
            printf("\n Le nombre de lignes a afficher doit être positif ou egal a -1 mais pas negatif ni egal a zero");
            printf("\n Veuillez entrer un nombre de lignes max correspondant a cela et qui ne soit pas superieur a %d:\n", nombre_lignes_total);
        }
        else
            ret = 1;
    } while (ret != 1); // Continuer tant que les valeurs sont erronnees

    show_cdataframe(CDataframe2, num_col_max_to_show, num_ligne_max_to_show);
    
    return -1;
}

int cmd_afficher_nombre_de_colonnes(DATAFRAME2* dataframe)
{
    print_number_of_columns(dataframe);
    return -1;
}

int cmd_afficher_nom_et_type_des_colonnes(DATAFRAME2* dataframe)
{
    print_name_and_type_of_columns(dataframe);
    return -1;
}

#pragma endregion menu_management_sub_menu_2

#pragma region menu_management_sub_menu_3

int process_user_menu_choice_main_section_3(int sub_section_number)
{
    switch (sub_section_number)
    {
    case 31:

        printf("\nChoix 31 - Ajouter une ligne de valeurs au CDataframe :\n");
        add_row_manually(CDataframe2);
        return -1;

    case 38:

        printf("\nChoix 38 - Affichage du nom des colonnes:\n");
        int nombre_col = print_name_and_type_of_columns(CDataframe2);
        printf("\nLe(s) nom(s) de %d colonne(s) ont ete affiche(s)\n\n", nombre_col);
        return -1;

    default:
        break;
    }
}

// Code...

#pragma endregion menu_management_sub_menu_3

#pragma region menu_management_sub_menu_4

int process_user_menu_choice_main_section_4(int sub_section_number)
{

}

// Code...

#pragma endregion menu_management_sub_menu_4

#pragma region menu_management_sub_menu_5

int process_user_menu_choice_main_section_5(int sub_section_number)
{
    switch (sub_section_number)
    {
    case 51:
        printf("\n Choix 51 - Reinitialiser l'ecran et afficher le menu :\n");
        return cmd_reini_ecran();
    case 52:
        printf("\n Choix 52 - Afficher les informations legales :\n");
        return cmd_afficher_informations_sur_programme();
    case 53:
        printf("\n Choix 53 - Quitter le programme :\n");
        return cmd_quitter_programme();
    default:
        break;
    }
}

int cmd_reini_ecran()
{
    printf("\n\n Etes vous sur de vouloir reinitialiser l'ecran ? (o/n)\n");

    char choix[2]; // Tableau de caractères pour stocker le choix de l'utilisateur
    int ret;

    do {
        printf("Entrez votre choix (o/n) : ");
        ret = scanf("%1s", choix); // Lire une chaîne de caractères de longueur 1 (o ou n)

        // Vérifier si le choix est valide
        if (strcmp(choix, "o") == 0) {
            // Effacer l'écran et afficher le menu
            system("cls");
            afficher_menu();
            return -1;
        }
        else if (strcmp(choix, "n") == 0) {
            // Sortir et laisser l'utilisateur choisir librement une autre commande dans le menu
            return -1;
        }
        else {
            printf("Choix invalide. Veuillez entrer 'o' ou 'n' :\n");
        }
    } while (ret != EOF); // Continuer tant que scanf ne retourne pas EOF (fin de fichier)
}

int cmd_afficher_informations_sur_programme()
{
    system("cls");
    printf("\n");
    printf("\n*******************************************************************");
    printf("\n                                                                   ");
    printf("\n        ====----      Programme CDtaframe        ====----          ");
    printf("\n                                                                   ");
    printf("\n*******************************************************************");
    printf("\n");
    printf("\n Nom du projet : CDataframe\n");
    printf("\n Version %d.%d.%d\n", major_version, minor_version, rev_version);
    printf("\n Auteurs : Eden Elfassy - Bryan Tewouda - Adam Assayag");
    printf("\n\n Date de creation : Mars 2024");
    printf("\n\n Description : Gestion d'un dataframe \"quasiment parfait\"");
    printf("\n\n Copyright (c) 2024 - Eden Elfassy - Bryan Tewouda - Adam Assayag");
    printf("\n Tous droits reserves");
    printf("\n\n\n");

    return -1;
}

int cmd_quitter_programme()
{
    printf("\n\n Etes vous sur de vouloir quitter le programme ? (o/n)\n");

    // Tableau de caractères pour stocker le choix de l'utilisateur
    char choix[2];
    int ret;

saisie_reponse:

    // le char doit être unique et seules deux valeurs sont possibles: "o" ou "n"
    ret = scanf("%1s", choix);

    // Vérifier si le choix est valide
    if (strcmp(choix, "o") == 0)
    {
        // quitter le prog
        exit(0);
    }
    else if (strcmp(choix, "n") == 0)
        // Sortir et laisser user choisir librement une autre commande dans le menu
        return -1;
    else
    {
        printf("Choix invalide. Veuillez entrer 'o' ou 'n' :\n");
        goto saisie_reponse;
    }
}

void test()
{
    
    //add_row_manually(CDataframe2);

    /////////////////////////////////////////////////////////////////////////////////////////
    // Tri de la colonne INT par tri insertion
    printf("\nContenu de la colonne \"%s\" AVANT trie insertion:\n", CDataframe2->columns[0]->title);
    print_column(CDataframe2->columns[0], false, NO_LIMIT);

    //effectuer le tri
    // def sens du tri: 0 = du + petit au + grand
    CDataframe2->columns[0]->sort_dir = 0;
    //sort_column_after_insertion_int(CDataframe2->columns[0]);
    quick_sort_column(CDataframe2->columns[0], 0, CDataframe2->columns[0]->size - 1, CDataframe2->columns[0]->sort_dir);

    printf("\nContenu de la colonne \"%s\" APRES trie insertion:\n", CDataframe2->columns[0]->title);
    print_col_by_index(CDataframe2->columns[0]);

    res = show_cdataframe(CDataframe2, NO_LIMIT, 20);
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

#pragma endregion menu_management_sub_menu_5

#pragma endregion menu_management

#pragma endregion CDataframe 2

int main()
{
    int choix_menu = -1; //7; // -1 = Choix manu, sinon indiquer la valeur choisit pr choix auto
    int go = 1;
    int res_choix_menu = 0;

    afficher_menu();
    
    // Boucle jusqu'à ce que la saisie d'une commande soit effectuée
    while (go == 1)
    {
        ///////////////////////////////////////////////////////////////////
        // CREATION ET ALIMENTATION AUTO DU CDATAFRAME - POUR TESTS SEULEMENT, NE SURTOUT PAS OUBLIE DE VIRER !!!
        if (CDataframe2 == NULL)
        {
            CDataframe2 = create_cdataframe("Dataframe 2");
            populate_dataframe_automatically(CDataframe2);
        }
        //test();
        ///////////////////////////////////////////////////////////////////


        switch (choix_menu)
        {
            case -1:
                printf("\n\n");
                printf(" Saisissez le nombre de la commande voulue et appuyez sur \"Entree\"\n\n");

                res_choix_menu = scanf("%d", &choix_menu);

                choix_menu = process_user_menu_choice(choix_menu);

                break;
            
            default:
            break;
        }
    }
    
    // Libération de la mémoire occupée par les colonnes et le dataframe
    free_all_ressources(&CDataframe1);

    return 1;
}

//////////////////////////////////////////////////////////////////////////