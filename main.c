#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "float.h"
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
    printf("    *    12. Ajouter une colonne au CDataframe                  X 22. Afficher les lignes et colonnes selon       *\n");
    printf("    *                                                                 une eventuelle limite de l'utilisateur      *\n");
    printf("    *    13. Remplir une colonne du CDataframe                                                                    *\n");
    printf("    *                                                           X 23. Afficher le nombre de colonnes              *\n");
    printf("    *    14. Ajouter une ligne de valeurs au CDataframe                                                           *\n");
    printf("    *                                                           X 24. Afficher le nom et le type des colonnes     *\n");
    printf("    *  X 15. Remplissage automatique du CDataframe                                                                *\n");
    printf("    *                                                           X 25. Afficher le contenu d'une colonne           *\n");
    printf("    *    16. Sauvegarder le CDataframe dans un fichier                                                            *\n");
    printf("    *                                                           X 26. Afficher le nombre de lignes du CDataframe  *\n");
    printf("    *    17. Charger un CDataframe depuis un fichier                                                              *\n");
    printf("    *                                                                                                             *\n");
    printf("    *                                                                                                             *\n");
    printf("    *  \033[4m3. Operations usuelles\033[0m                                   \033[4m4. Analyse et statistiques\033[0m                        *\n");
    printf("    *                                                                                                             *\n");
    printf("    *    31. Trier une colonne                                    41. Nombre de cellules contenant une            *\n");
    printf("    *                                                                 valeur egale a \"x\"                          *\n");
    printf("    *    32. Lire la valeur d'une cellule                                                                         *\n");
    printf("    *                                                             42. Nombre de cellules contenant une            *\n");
    printf("    *    33. Modifier la valeur d'une cellule                         valeur superieure a \"x\"                     *\n");
    printf("    *                                                                                                             *\n");
    printf("    *    34. Verifier l'existence d'une valeur                    43. Nombre de cellules contenant une            *\n");
    printf("    *                                                                 valeur inferieure a \"x\"                     *\n");
    printf("    *    35. Supprimer une colonne du CDataframe                                                                  *\n");
    printf("    *                                                                                                             *\n");
    printf("    *    36. Supprimer une ligne de valeurs du                 \033[4m5. Divers\033[0m                                          *\n");                                                   
    printf("    *        CDataframe                                                                                           *\n");
    printf("    *                                                           X 51. Reinitialiser l'ecran et afficher le menu   *\n");
    printf("    *    37. Supprimer le CDataframe                                                                              *\n");
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
            printf("\n 11 - Creation d'un CDataframe vide :\n");
            return cmd_creation_cdataframe(CDataframe2);
        case 12:
            printf("\n 12 - Ajouter une colonne au CDataframe \"%s\" :\n", CDataframe2->title);
            return cmd_ajouter_colonne_au_cdataframe(CDataframe2);
        case 13:
            printf("\n 13 - Remplir une colonne du CDataframe \"%s\" :\n", CDataframe2->title);
            return cmd_remplir_une_colonne_du_cdataframe(CDataframe2);
        case 14:
            printf("\n 14 - Ajouter une ligne de valeur au CDataframe \"%s\" :\n", CDataframe2->title);
            return cmd_ajouter_une_ligne_au_cdataframe(CDataframe2);
        case 15:
            printf("\n 15 - Remplissage automatique du CDataframe :\n");
            return cmd_remplissage_automatique_du_cdataframe(CDataframe2);
        case 16:
            printf("\n 16 - Sauvegarder le CDataframe dans un fichier :\n");
            return cmd_sauvegarder_cdataframe_dans_fichier(CDataframe2);
        case 17:
            printf("\n 17 - Charger un CDataframe depuis un fichier :\n");
            return cmd_charger_cdataframe_depuis_fichier(CDataframe2);
        default:
            break;
    }
}

int cmd_creation_cdataframe(DATAFRAME2* dataframe)
{
    dataframe = manage_creation_of_cdataframe();
    if (dataframe != NULL)
        printf("\n Le CDataframe \"%s\" a ete cree avec succes\n", CDataframe2->title);
    else
        printf("\n Une erreur est survenue lors de la creation du CDataframe");

    return -1;
}

int cmd_ajouter_colonne_au_cdataframe(DATAFRAME2* dataframe)
{
    // Ask user to input col name
    int col_type = -1;
    char* col_name[TAILLE_MAX_STRING];

    // Ask user to input col name
    printf("\n Veuillez entrer le nom de la colonne a ajouter :");

    scanf("%s", &col_name);
    
    if (col_name[0] == '\0')
    {
        printf("\n Le nom de la colonne est invalide, operation annulee");
        printf("\n Appuyez sur une touche pour continuer\n");
        int ret = getchar();
        return -1;
    }
    else
    {
        printf("\n Le nom de votre nouvelle colonne est : %s\n", col_name);
    }
    
    // Ask user to input col type
    printf("\n Veuillez choisir le type de la colonne a ajouter :");
    printf("\n (UINT = 1, INT = 2, CHAR = 3, FLOAT = 5, DOUBLE = 6, STRING = 7, STRUCTURE = 8)");
    printf("\n\n Si vous souhaitez annuler l'opération, entrez la valeur zéro");

    scanf("%d", &col_type);

    if (col_type == 0)
    {
        printf("\n Le type de la colonne est invalide, operation annulee");
        printf("\n Appuyez sur une touche pour continuer\n");
        int ret = getchar();
        return -1;
    }
    else
    {
        printf("\n Le type de votre nouvelle colonne est : %s\n", enum_to_string(col_type));
    }

    add_column(dataframe, col_type, col_name);

    return -1;
}

int cmd_remplir_une_colonne_du_cdataframe(DATAFRAME2* dataframe)
{
    // Faire verif de base df + col
    if (dataframe == NULL)
    {
        printf("\n Veuillez d'abord creer ET remplir le CDataframe\n\n");
        return -1;
    }

    if (dataframe->size == 0)
    {
        printf("\n Le CDataframe \"%s\" ne contient aucune colonne\n", dataframe->title);
        printf("\n Appuyez sur une touche puis sur \"Entree\"  pour continuer\n");
        int ret = getchar();
        return -1;
    }

    // Ask user to choose num col to fill 
    int nombre_col_total = dataframe->size;
    int num_col_to_fill = 0;
    int user_saisie_col_num = 0;
    int user_saisie_val = 0;
    int user_continue_saisie_nouvelle_val = 0;
    char choix[2];

    unsigned int uint_value = 0;
    signed int   int_value = 0;
    char         char_value = '\0';
    float        float_value = 0.0f;
    double       double_value = 0.0;
    char* string_value = "";    // chaîne vide

    // Ask user to input col num:
    user_saisie_col_num = 1;
    do {
        printf("\n Le CDataframe \"%s\" contient %d colonne(s) au total", dataframe->title, nombre_col_total);
        printf("\n\n Elles sont numerote de 0 a %d\n", (dataframe->size - 1));
        printf("\n\n Entrez le numero de la colonne a remplir :\n");

        scanf("%d", &num_col_to_fill);

        // Vérifier si le choix est valide, sinon prevenir
        if (num_col_to_fill > nombre_col_total)
        {
            printf("\n Choix invalide, le numero de colonne a remplir ne doit pas exceder %d", nombre_col_total);
            printf("\n Veuillez entrer un numero de colonne compris entre 0 et %d:\n", nombre_col_total);
        }
        else if (num_col_to_fill < 0)
        {
            printf("\n Veuillez entrer un numero de colonne POSITIF compris entre 0 et %d:\n", nombre_col_total);
        }
        else
            user_saisie_col_num = 1;
    } while (user_saisie_col_num == 1); // Continuer tant que le num de col à remplir est erronée

    do {
        // Demander à user d'entrer la prochaine valeur à ajouter à la colonne
        printf("\n Veuillez saisir une valeur de type %s : ", enum_to_string(dataframe->columns[num_col_to_fill]->column_type));
        
        
        //////////////////////////////////////////////////////////////////////////////////////////////
        // mettre un switch pour gerer tous les types possibles
        scanf("%d", &int_value);
        //////////////////////////////////////////////////////////////////////////////////////////////


        // Verifier que la valeur entrée corresponde bien au type de la col considérée
        if (check_if_valid_value(&int_value, dataframe->columns[num_col_to_fill]->column_type))
        {
            insert_value_with_memory_management_of_tabs_data_of_columns(dataframe, num_col_to_fill, &int_value);
            printf("\n La valeur a ete ajoute a la colonne \"%s\"", dataframe->columns[num_col_to_fill]->title);
        }
        else
            printf("\n Impossible d'ajouter cette valeur car elle ne correspond pas au type attendu");

        user_saisie_val = 1;

        // boucler tant que l'utilisateur souhaite continuer à entrer des valeurs dans cette col
        do {
            printf("\n\n  Saisir une nouvelle valeur ? (o/n) : ");
            scanf("%1s", choix);

            // Vérifier si le choix est valide
            if (strcmp(choix, "o") == 0)
                user_saisie_val = 1;
            else if (strcmp(choix, "n") == 0)
                user_continue_saisie_nouvelle_val = 0;
            else
                printf("\n\n  Saisir une nouvelle valeur ? (o/n) : ");
        
        // Continuer tant que user souhaite saisir une valeur
        } while (user_saisie_val == 1);

        // Continuer la saisie d'une nouvelle valeur
    } while (user_continue_saisie_nouvelle_val == 1);

    return -1;
}

int cmd_ajouter_une_ligne_au_cdataframe(DATAFRAME2* dataframe)
{
    if (dataframe == NULL)
    {
        printf("\n Veuillez d'abord creer ET remplir le CDataframe\n\n");
        return -1;
    }

    if (dataframe->size == 0)
    {
        printf("\n Le CDataframe \"%s\" ne contient aucune colonne\n", dataframe->title);
        printf("\n Appuyez sur une touche puis sur \"Entree\"  pour continuer\n");
        int ret = getchar();
        return -1;
    }

    if (add_a_row_manually(CDataframe2))
        printf("\n La ligne a ete ajoutee avec succes");
    else
        printf("\n Un probleme est survenu mors de l'ajout de la ligne");

    return -1;
}

int cmd_remplissage_automatique_du_cdataframe(DATAFRAME2* dataframe)
{
    if (dataframe == NULL)
    {
        printf("\n Veuillez d'abord creer le CDataframe\n");
        return 0;
    }

    if (dataframe->size == 0)
    {
        printf("\n Veuillez d'abord creer et remplir au moins une colonne dans le CDataframe \"%s\"\n", dataframe->title);
        return 0;
    }

    if (populate_dataframe_automatically(CDataframe2))
        printf("\n Le dataframe a ete remplie avec plusieurs colonnes de differents types contenant diverses donnees\n");
    else
        printf("\n Un probleme est survenue lors du remplissage automatique du CDataframe\n");

    return -1;
}

int cmd_sauvegarder_cdataframe_dans_fichier(DATAFRAME2* dataframe)
{
    if (dataframe == NULL)
    {
        printf("\n Veuillez d'abord creer le CDataframe\n");
        return 0;
    }

    if (dataframe->size == 0)
    {
        printf("\n Veuillez d'abord creer et remplir au moins une colonne dans le CDataframe \"%s\"\n", dataframe->title);
        return 0;
    }
    
    if (save_dataframe_to_csv(CDataframe2, NOM_FICHIER_CSV, SEPARATEUR_CSV))
        printf("\nLe CDdataframe a ete sauvegarde avec succes\n");
    else
        printf("\n Un probleme est survenue lors de la sauvegarde du CDataframe dans le fichier CSV\n");

    return -1;
}

int cmd_charger_cdataframe_depuis_fichier(DATAFRAME2* dataframe)
{
    if (dataframe == NULL)
    {
        printf("\n Veuillez d'abord creer le CDataframe\n");
        return 0;
    }

    if (dataframe->size == 0)
    {
        printf("\n Veuillez d'abord creer et remplir au moins une colonne dans le CDataframe \"%s\"\n", dataframe->title);
        return 0;
    }

    if (load_dataframe_from_csv(CDataframe2, NOM_FICHIER_CSV, SEPARATEUR_CSV))
        printf("\nLe CDdataframe a ete sauvegarde avec succes\n");
    else
        printf("\n Un probleme est survenue lors de la sauvegarde du CDataframe dans le fichier CSV\n");

    return -1;
}

#pragma endregion menu_management_sub_menu_1

#pragma region menu_management_sub_menu_2

int process_user_menu_choice_main_section_2(int sub_section_number)
{
    switch (sub_section_number)
    {
        case 21:
            printf("\n 21 - Afficher le CDataframe \"%s\" :\n", CDataframe2->title);
            return cmd_afficher_cdataframe();
        case 22:
            printf("\n 22 - Afficher les lignes et colonnes du CDataframe \"%s\" selon une eventuelle limite de l'utilisateur :\n", CDataframe2->title);
            return cmd_afficher_lignes_et_colonnes_selon_limites_utilisateurs(CDataframe2);
        case 23:
            printf("\n 23 - Afficher le nombre de colonnes du CDataframe \"%s\" :\n", CDataframe2->title);
            return cmd_afficher_nombre_de_colonnes(CDataframe2);
        case 24:
            printf("\n 24 - Afficher le nom et le type des colonnes du CDataframe \"%s\" :\n", CDataframe2->title);
            return cmd_afficher_noms_et_types_des_colonnes(CDataframe2);
        case 25:
            printf("\n 25 - Afficher le contenu d'une colonne du CDataframe \"%s\" :\n", CDataframe2->title);
            return cmd_afficher_contenu_de_colonne(CDataframe2);
        case 26:
            printf("\n 26 - Afficher le nombre de lignes du CDataframe \"%s\" :\n", CDataframe2->title);
            return cmd_afficher_nombre_lignes(CDataframe2);
        default:
            break;
    }
}

int cmd_afficher_cdataframe()
{
    show_cdataframe(CDataframe2, NO_LIMIT, NO_LIMIT);
    return -1;
}

int cmd_afficher_lignes_et_colonnes_selon_limites_utilisateurs(DATAFRAME2* dataframe)
{
    int ret = 0;
    int num_col_max_to_show = 0;
    int num_ligne_max_to_show = 0;

    if (dataframe == NULL)
    {
        printf("\n Veuillez d'abord creer le CDataframe\n");
        return 0;
    }

    if (dataframe->size == 0)
    {
        printf("\n Veuillez d'abord creer et remplir au moins une colonne dans le CDataframe \"%s\"\n", dataframe->title);
        return 0;
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
        printf("\n Le CDataframe \"%s\" contient %d colonnes :\n", dataframe->title, dataframe->size);
        printf("\n Pour afficher toutes les colonnes, entrez la valeur \"-1\" :\n");

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
        printf("\n Le CDataframe \"%s\" ne contient aucune ligne\n", dataframe->title);
        printf("\n Appuyez sur une touche puis sur \"Entree\" pour continuer\n");
        ret = getchar();
        return -1;
    }

    do {
        printf("\n Le CDataframe \"%s\" contient %d lignes :\n", dataframe->title, nombre_lignes_total);
        printf("\n Entrez le nombre de lignes max a afficher :\n");
        printf("\n Pour afficher toutes les lignes, entrez la valeur \"-1\" :\n");

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

int cmd_afficher_noms_et_types_des_colonnes(DATAFRAME2* dataframe)
{
    if (dataframe == NULL)
    {
        printf("\n Veuillez d'abord creer ET remplir le CDataframe\n\n");
        return -1;
    }

    if (dataframe->size == 0)
    {
        printf("\n Le CDataframe \"%s\" ne contient aucune colonne\n", dataframe->title);
        printf("\n Appuyez sur une touche puis sur \"Entree\"  pour continuer\n");
        int ret = getchar();
        return -1;
    }

    int nombre_col = print_name_and_type_of_columns(CDataframe2);

    if (nombre_col == 1)
    {
        printf("\n Le nom de %d colonne(s) ont ete affiche(s)\n\n", nombre_col);
    }
    else if (nombre_col > 1)
    {
        printf("\n Les noms de %d colonnes ont ete affiches\n\n", nombre_col);
    }
    return -1;
}

int cmd_afficher_contenu_de_colonne(DATAFRAME2* dataframe)
{
    if (dataframe == NULL)
    {
        printf("\n Veuillez d'abord creer ET remplir le CDataframe\n\n");
        return -1;
    }

    if (dataframe->size == 0)
    {
        printf("\n Le CDataframe \"%s\" ne contient aucune colonne\n", dataframe->title);
        printf("\n Appuyez sur une touche puis sur \"Entree\"  pour continuer\n");
        int ret = getchar();
        return -1;
    }

    // Check if cols exist
    int nombre_col_total = dataframe->size;
    int num_col_to_show = 0;
    int val_correcte = 0;

    // Ask user to input col num:
    do {
        printf("\n Le CDataframe \"%s\" contient %d colonne(s) au total", dataframe->title, nombre_col_total);
        printf("\n Elles sont numerote de 0 à %d\n", nombre_col_total);
        printf("\n Entrez le numero de la colonne a afficher :\n");

        scanf("%d", &num_col_to_show);

        // Vérifier si le choix est valide, sinon prevenir
        if (num_col_to_show > nombre_col_total)
        {
            printf("\n Choix invalide, le numero de colonne a afficher ne doit pas exceder %d", nombre_col_total);
            printf("\n Veuillez entrer un numero de colonne compris entre 0 et %d:\n", nombre_col_total);
        }
        else if (num_col_to_show < 0)
        {
            printf("\n Veuillez entrer un numero de colonne compris entre 0 et %d:\n", nombre_col_total);
            printf("\n Sinon je ne pourrais rien faire pour vous...");
        }
        else
            val_correcte = 1;
    } while (val_correcte != 1); // Continuer tant que le num de col à afficher est erronée

    print_column(dataframe->columns[num_col_to_show], true, NO_LIMIT);

    return -1;
}

int cmd_afficher_nombre_lignes(DATAFRAME2* dataframe)
{
    if (dataframe == NULL)
    {
        printf("\n Veuillez d'abord creer un CDataframe\n");
        return -1;
    }

    int ret = 0;

    if (dataframe->size == 0)
    {
        printf("\n Le CDataframe %s ne contient aucunes colonnes, donc aucunes lignes\n", dataframe->title);
        printf("\n Appuyez sur une touche puis sur \"Entree\"  pour continuer\n");
        ret = getchar();
        return -1;
    }

    // Obtenir le nombre de lignes max à afficher
    int total_number_of_rows = get_number_of_rows(CDataframe2);

    if (total_number_of_rows == 0)
        printf("\n Le CDataframe \"%s\" ne contient aucune ligne\n", dataframe->title);
    else if (total_number_of_rows == 1)
        printf("\n Le CDataframe \"%s\" contient une seule et unique ligne\n", dataframe->title);
    else if (total_number_of_rows > 0)
        printf("\n Le CDataframe \"%s\" contient %d lignes\n", dataframe->title, total_number_of_rows);

    // get_number_of_rows
    return -1;
}

#pragma endregion menu_management_sub_menu_2

#pragma region menu_management_sub_menu_3

int process_user_menu_choice_main_section_3(int sub_section_number)
{
    switch (sub_section_number)
    {
    case 31:
        printf("\n 31 - Trier une colonne :\n");
        return cmd_trier_une_colonne(CDataframe2);
    case 32:
        printf("\n 32 - Lire la valeur d'une cellule :\n");
        return cmd_lire_valeur_cellule(CDataframe2);
    case 33:
        printf("\n 33 - Modifier la valeur d'une cellule :\n");
        return cmd_modifier_valeur_cellule(CDataframe2);
    case 34:
        printf("\n 34 - Verifier l'existence d'une valeur :\n");
        //return cmd_verifier_existence_valeur(CDataframe2);
    case 35:
        printf("\n 35 - Supprimer une colonne du CDataframe :\n");
        //return cmd_supprimer_colonne_du_cdataframe(CDataframe2);
    case 36:
        printf("\n 36 - Supprimer une ligne de valeurs du CDataframe :\n");
        //return cmd_supprimer_ligne_du_cdataframe(CDataframe2);
    case 37:
        printf("\n 36 - Supprimer le CDataframe :\n");
        //return cmd_supprimer_cdataframe(CDataframe2);
    default:
        break;
    }
}

int cmd_trier_une_colonne(DATAFRAME2* dataframe)
{
    if (dataframe == NULL)
    {
        printf("\n Veuillez d'abord creer ET remplir le CDataframe pour pouvoir effectuer un tri\n\n");
        return -1;
    }

    if (dataframe->size == 0)
    {
        printf("\n Impossible d'effectuer un tri car le CDataframe \"%s\" ne contient aucune colonne\n", dataframe->title);
        printf("\n Appuyez sur une touche puis sur \"Entree\"  pour continuer\n");
        int ret = getchar();
        return -1;
    }

    // Show all col names and type 

    // Ask user which col to sort

    // Ask user wich way to sort

    // sort_column
}

int cmd_lire_valeur_cellule(DATAFRAME2* dataframe)
{
    if (dataframe == NULL)
    {
        printf("\n Veuillez d'abord creer ET remplir le CDataframe pour pouvoir lire la valeur d'une cellule\n\n");
        return -1;
    }

    if (dataframe->size == 0)
    {
        printf("\n Impossible de lire une valeur dans une cellule d'une colonne car le CDataframe \"%s\" ne contient aucune colonne\n", dataframe->title);
        printf("\n Appuyez sur une touche puis sur \"Entree\"  pour continuer\n");
        int ret = getchar();
        return -1;
    }

    // Show all col names and type 

    // Ask user which col 

    // Ask user which line

    // print_value(dataframe, )
}

int cmd_modifier_valeur_cellule(DATAFRAME2* dataframe)
{
    if (dataframe == NULL)
    {
        printf("\n Veuillez d'abord creer ET remplir le CDataframe pour pouvoir modifier la valeur d'une cellule\n\n");
        return -1;
    }

    if (dataframe->size == 0)
    {
        printf("\n Impossible de modifier une valeur dans une cellule d'une colonne car le CDataframe \"%s\" ne contient aucune colonne\n", dataframe->title);
        printf("\n Appuyez sur une touche puis sur \"Entree\"  pour continuer\n");
        int ret = getchar();
        return -1;
    }

    // Ask user which col 

    // Ask user which line

    // Check if value got the right type

    // change_value
}

#pragma endregion menu_management_sub_menu_3

#pragma region menu_management_sub_menu_4

int process_user_menu_choice_main_section_4(int sub_section_number)
{
    switch (sub_section_number)
    {
    case 41:
        printf("\n 41 - Nombre de cellules contenant une valeur egale a \"x\" :\n");
        //return cmd_nombre_cellules_contenant_valeur_egale_a_x(CDataframe2);
    case 42:
        printf("\n 42 - Nombre de cellules contenant une valeur superieure a \"x\" :\n");
        //return cmd_nombre_cellules_contenant_valeur_superieure_a_x(CDataframe2);
    case 43:
        printf("\n 42 - Nombre de cellules contenant une valeur inferieure a \"x\" :\n");
        //return cmd_nombre_cellules_contenant_valeur_inferieure_a_x(CDataframe2);
    default:
        break;
    }
}

// Implementer cmd ici

#pragma endregion menu_management_sub_menu_4

#pragma region menu_management_sub_menu_5

int process_user_menu_choice_main_section_5(int sub_section_number)
{
    switch (sub_section_number)
    {
    case 51:
        printf("\n Choix 51 - Reinitialiser l'ecran et afficher le menu :\n");
        return cmd_reini_ecran_et_afficher_menu();
    case 52:
        printf("\n Choix 52 - Afficher les informations legales :\n");
        return cmd_afficher_informations_legales();
    case 53:
        printf("\n Choix 53 - Quitter le programme :\n");
        return cmd_quitter_programme();
    default:
        break;
    }
}

int cmd_reini_ecran_et_afficher_menu()
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

int cmd_afficher_informations_legales()
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
    int choix[2];
    int ret;

    // Saisie du nombre de col max à afficher
    do
    {
        // le char doit être unique et seules deux valeurs sont possibles: "o" ou "n"
        ret = scanf("%1s", choix);

        // Vérifier si le choix est valide
        if (strcmp(choix, "o") == 0)
            ret = 1;
        else if (strcmp(choix, "n") == 0)
            // Sortir et laisser user choisir librement une autre commande dans le menu
            return -1;
        else
            printf("Choix invalide. Veuillez entrer 'o' ou 'n' :\n");
           
    } while (ret != 1); // Continuer tant que les valeurs entrees sont erronnees

    // Libération de la mémoire occupée par les colonnes et le dataframe
    free_all_ressources(&CDataframe1);

    // Liberation des ressources
    free_ressources(CDataframe2);
    
    // quitter le prog
    exit(0);
}

#pragma endregion menu_management_sub_menu_5

#pragma endregion menu_management

void test()
{
    OPERATEURS_DE_COMPARAISON oc_egal = {EGAL};

    // UINT = 1, INT = 2, CHAR = 3, FLOAT = 5, DOUBLE = 6, STRING = 7, STRUCTURE = 8

    int i = 5;

    void* valptr = &i;

    stats_on_value(CDataframe2, valptr, INT, oc_egal);
    
    //add_row_manually(CDataframe2);

    /////////////////////////////////////////////////////////////////////////////////////////
    // Tri de la colonne INT par tri
    int num_col = 5;  // UINT = 0, INT = 1, CHAR = 2, FLOAT = 3, DOUBLE = 4, STRING = 5, STRUCTURE = 6
    printf("\nContenu de la colonne \"%s\" AVANT trie :\n", CDataframe2->columns[num_col]->title);
    print_column(CDataframe2->columns[num_col], false, NO_LIMIT);

    //effectuer le tri
    // def sens du tri: 0 = du + petit au + grand
    CDataframe2->columns[num_col]->sort_dir = 0;
    sort_column_after_insertion(CDataframe2->columns[num_col], CDataframe2->columns[num_col]->sort_dir);
    //quick_sort_column(CDataframe2->columns[num_col], 0, CDataframe2->columns[num_col]->size - 1, CDataframe2->columns[num_col]->sort_dir);

    printf("\n\nContenu de la colonne \"%s\" APRES trie :\n\n", CDataframe2->columns[num_col]->title);
    print_col_by_index(CDataframe2->columns[num_col]);

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

int check_if_valid_value(void* value, ENUM_TYPE type)
{
    // TODO: Terminer l'implémentation
    
    switch (type)
    {
    case INT:
        if (*(int*)value < INT_MIN || *(int*)value > INT_MAX)
            // Out of range
            return 0;
        break;
    case FLOAT:
        if (*(float*)value < FLT_MIN || *(float*)value > FLT_MAX)
            // Out of range
            return 0;
        break;
    case DOUBLE:
        if (*(double*)value < DBL_MIN || *(double*)value > DBL_MAX)
            // Out of range
            return 0;
        break;
    default:
        break;
    }
    return 1;
}

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
                printf(" Saisissez le code de la commande voulue et appuyez sur \"Entree\"\n\n");

                res_choix_menu = scanf("%d", &choix_menu);

                choix_menu = process_user_menu_choice(choix_menu);

                break;
            
            default:
                break;
        }
    }
    
    return 1;
}