#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
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
char* dataframe_title;

OPERATEURS_DE_COMPARAISON oc_egal = { EGAL };
OPERATEURS_DE_COMPARAISON oc_superieur = { SUPERIEUR };
OPERATEURS_DE_COMPARAISON oc_inferieur = { INFERIEUR };

int free_ressources(DATAFRAME2* dataframe)
{
    delete_cdataframe(dataframe);
    
    CDataframe2 = NULL;
}

DATAFRAME2* manage_creation_of_cdataframe()
{
    // Demander le nom du CDataframe
    char* dataframe_title = saisie_chaine("\n Veuillez saisir le nom du CDataframe : ");

    if (dataframe_title[0] == '\0')
    {
        printf("\nLe nom que vous avez saisie pour le CDataframe n'est pas valide\n");
        printf("\nL'operation est annule, vous n'avez pas cree de CDataframe\n");
        vider_tampon();
        getchar();
        return NULL;
    }

    DATAFRAME2* dataframe = create_cdataframe(dataframe_title);

    if (dataframe != NULL)
        return dataframe;
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
    printf("    *    11. Creation d'un CDataframe vide                        21. Afficher le CDataframe                      *\n");
    printf("    *                                                                                                             *\n");
    printf("    *    12. Ajouter une colonne au CDataframe                    22. Afficher les lignes et colonnes selon       *\n");
    printf("    *                                                                 une eventuelle limite de l'utilisateur      *\n");
    printf("    *    13. Remplir une colonne du CDataframe                                                                    *\n");
    printf("    *                                                             23. Afficher le nombre de colonnes              *\n");
    printf("    *    14. Ajouter une ligne de valeurs au CDataframe                                                           *\n");
    printf("    *                                                             24. Afficher le nom et le type des colonnes     *\n");
    printf("    *    15. Remplissage automatique du CDataframe                                                                *\n");
    printf("    *                                                             25. Afficher le contenu d'une colonne           *\n");
    printf("    *    16. Sauvegarder le CDataframe dans un fichier                                                            *\n");
    printf("    *                                                             26. Afficher le nombre de lignes du CDataframe  *\n");
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
    printf("    *    34. Renommer une colonne                                 43. Nombre de cellules contenant une            *\n");
    printf("    *                                                                 valeur inferieure a \"x\"                     *\n");
    printf("    *    35. Supprimer une colonne du CDataframe                                                                  *\n");
    printf("    *                                                                                                             *\n");
    printf("    *    36. Supprimer une ligne de valeurs du               \033[4m5. Divers\033[0m                                            *\n");                                                   
    printf("    *        CDataframe                                                                                           *\n");
    printf("    *                                                             51. Reinitialiser l'ecran et afficher le menu   *\n");
    printf("    *    37. Supprimer le CDataframe                                                                              *\n");
    printf("    *                                                             52. Afficher les informations legales           *\n");
    printf("    *    38. Ne jamais lancer cette commande                                                                      *\n");
    printf("    *                                                             53. Quitter le programme                        *\n");
    printf("    *                                                                                                             *\n");
    printf("    ***************************************************************************************************************\n");
}

int process_user_menu_choice(int sub_section_number)
{
    // Controler le fait que user ait fait un choix compris dans une certaine plage seulement

    // Extraire le num de section principale choisie (toujours le premier num)
    int main_section_number = obtenir_premier_chiffre(sub_section_number);

    if (CDataframe2 != NULL)
        dataframe_title = CDataframe2->title;
    else
        dataframe_title = "";

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
            printf("\n\n Votre choix n'est pas valide\n");
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
            return cmd_creation_cdataframe();
        case 12:
            printf("\n 12 - Ajouter une colonne au CDataframe \"%s\" :\n", dataframe_title);
            return cmd_ajouter_colonne_au_cdataframe(CDataframe2);
        case 13:
            printf("\n 13 - Remplir une colonne du CDataframe \"%s\" :\n", dataframe_title);
            return cmd_remplir_une_colonne_du_cdataframe(CDataframe2);
        case 14:
            printf("\n 14 - Ajouter une ligne de valeur au CDataframe \"%s\" :\n", dataframe_title);
            return cmd_ajouter_une_ligne_au_cdataframe(CDataframe2);
        case 15:
            printf("\n 15 - Remplissage automatique du CDataframe :\n");
            return cmd_remplissage_automatique_du_cdataframe(CDataframe2);
        case 16:
            printf("\n 16 - Sauvegarder le CDataframe dans un fichier :\n");
            return cmd_sauvegarder_cdataframe_dans_fichier(CDataframe2, NOM_FICHIER_CSV, SEPARATEUR_CSV);
        case 17:
            printf("\n 17 - Charger un CDataframe depuis un fichier :\n");
            return cmd_charger_cdataframe_depuis_fichier(&CDataframe2, NOM_FICHIER_CSV, SEPARATEUR_CSV);
        default:
            break;
    }
}

int cmd_creation_cdataframe()
{
    CDataframe2 = manage_creation_of_cdataframe();
    
    if (CDataframe2 != NULL)
        printf("\n Le CDataframe \"%s\" a ete cree avec succes\n", CDataframe2->title);
    else
        printf("\n Une erreur est survenue lors de la creation du CDataframe");

    return -1;
}

int cmd_ajouter_colonne_au_cdataframe(DATAFRAME2* dataframe)
{
    if (!dataframe_has_data(dataframe))
        return -1;

    // Ask user to input col name
    int col_type = -1;
    char col_name[NOMBRE_CHAR_MAX_NOM_COLONNE];

    // Ask user to input col name
    printf("\n Veuillez entrer le nom de la colonne a ajouter : ");
    int ret = scanf("%255s", col_name);

    if (col_name[0] == '\0')
    {
        printf("\n Le nom de la colonne est invalide, operation annulee");
        printf("\n Appuyez sur une touche pour continuer\n");
        vider_tampon();
        ret = getchar();
        return -1;
    }
    else
        printf("\n Le nom de votre nouvelle colonne est : \"%s\"\n", col_name);
    
    printf("\n Appuyez sur une touche pour continuer\n");
    vider_tampon();
    ret = getchar();

    // Ask user to input col type
    printf("\n Veuillez choisir le type de la colonne a ajouter :\n");
    printf("\n (UINT = 1, INT = 2, CHAR = 3, FLOAT = 5, DOUBLE = 6, STRING = 7, STRUCTURE = 8)");
    printf("\n\n (Si vous souhaitez annuler l'operation d'ajout de colonne, entrez la valeur \"-1\")\n");
    printf("\n\n A vous de jouer maintenant : ");

    ret = scanf("%d", &col_type);

    if (col_type == 0)
    {
        printf("\n\n l'opération d'ajout de colonne a ete annulee");
        printf("\n Appuyez sur une touche pour continuer\n");
        vider_tampon();
        ret = getchar();
        return -1;
    }
    else if (col_type < 0 || col_type > NOMBRE_TYPE_COL)
    {
        printf("\n Le type de la colonne est invalide, operation annulee");
        printf("\n Appuyez sur une touche pour continuer\n");
        vider_tampon();
        ret = getchar();
        return -1;
    }
    else
    {
        printf("\n Le type de votre nouvelle colonne est :\"%s\"\n", enum_to_string(col_type));
        printf("\n Appuyez sur une touche pour l'ajouter au CDataframe \"%s\"...\n", dataframe->title);
        vider_tampon();
        getchar();
    }

    if (add_column(dataframe, col_type, col_name))
        printf("\n La nouvelle colonne \"%s\" de type :\"%s\" a bien ete ajoute au CDataframe \"%s\"\n", col_name, enum_to_string(col_type), dataframe->title);
    else
        printf("\n Un probleme est survenu lors de l'ajout de la nouvelle colonne\n");

    printf("\n Le CDataframe \"%s\" contient maintenant %d colonne(s), voici leur aspect: \n", dataframe->title);

    print_name_and_type_of_columns(dataframe);
    
    printf("\n Appuyez sur une touche pour continuer\n");
    
    vider_tampon();

    getchar();

    return -1;
}

int cmd_remplir_une_colonne_du_cdataframe(DATAFRAME2* dataframe)
{
    int ret = 0;
    
    // Faire verif de base df + col
    if (dataframe == NULL)
    {
        printf("\n Veuillez d'abord creer ET remplir le CDataframe\n\n");
        return -1;
    }

    if (dataframe->size == 0)
    {
        printf("\n Le CDataframe \"%s\" ne contient aucune colonne\n", dataframe->title);
        printf("\n Appuyez sur une touche pour continuer\n");
        vider_tampon();
        ret = getchar();
        return -1;
    }

    // Ask user to choose num col to fill 
    int nombre_col_total = dataframe->size;
    int num_col_to_fill = 0;
    int ask_user_to_input_col_num = 0;
    int ask_user_if_want_to_add_new_val = 0;
    int user_continue_to_add_new_val = 0;
    char choix[2];

    // Ask user to input col num:
    ask_user_to_input_col_num = 1;
    
    do {
        printf("\n Le CDataframe \"%s\" contient %d colonne(s) au total", dataframe->title, nombre_col_total);
        printf("\n\n Elles sont numerote de 0 a %d et se presentent comme suit : \n", (dataframe->size - 1));
        print_name_and_type_of_columns(dataframe);
        printf("\n\n Entrez le numero de la colonne a remplir : ");

        ret = scanf("%d", &num_col_to_fill);

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
            ask_user_to_input_col_num = 0;

    } while (ask_user_to_input_col_num == 1); // Continuer tant que le num de col à remplir est erronée


    // A ce stade, la colonne a été selectionnée, on va la remplir avec des données

    ret = 0;
    //  AJOUT DE DONNEES
    do {
        // Saisir et ajouter la nouvelle valeur à la colonne
        if (add_data_manually_in_column(dataframe, num_col_to_fill))
            ret = 1;
        else
            printf("\n Une erreur est survenue lors de l'ajout de la donnee dans le CDataframe \"%s\"", dataframe->title);

        // Si donnée ajoutée avec succès, demander si on souhaite voir le resultat.
        if (ret == 1)
        {
            printf("\n\n  Souhaitez-vous voir le resultat ? (o/n) ");
            ret = scanf("%1s", choix);
            // Si oui, afficher le CDataframe en limitant le nombre de lignes celui de la nouvelle valeur pour ne pas polluer l'écran
            if (strcmp(choix, "o") == 0)
                show_cdataframe(dataframe, NO_LIMIT, dataframe->columns[num_col_to_fill]->size);
        }
        
        ask_user_if_want_to_add_new_val = 1;

        // boucler tant que l'utilisateur souhaite continuer à entrer des valeurs dans cette col
        do {
            printf("\n\n  Saisir une nouvelle valeur ? (o/n) : ");
            ret = scanf("%1s", choix);

            // Vérifier le choix
            if (strcmp(choix, "o") == 0)
            {
                ask_user_if_want_to_add_new_val = 0;
                user_continue_to_add_new_val = 1;
            }
            else if (strcmp(choix, "n") == 0)
            {
                ask_user_if_want_to_add_new_val = 0;
                user_continue_to_add_new_val = 0;
            }
            else
                printf("\n\n  Veuillez entrer uniquement le choix suivant : \"o\" ou \"n\")");

        // User n'a pas repondu par "o" ou "n" : Continuer de demander s'il souhaite saisir une nouvelle valeur
        } while (ask_user_if_want_to_add_new_val == 1);

        // Continuer la saisie d'une nouvelle valeur
    } while (user_continue_to_add_new_val == 1);

    printf("\n\n  Ajout de nouvelles valeurs dans une colonne termines\n");

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
        vider_tampon();
        int ret = getchar();
        return -1;
    }

    if (add_a_row_manually(CDataframe2))
        printf("\n\n La ligne a ete ajoutee avec succes");
    else
        printf("\n\n Un probleme est survenu mors de l'ajout de la ligne");

    return -1;
}

int cmd_remplissage_automatique_du_cdataframe(DATAFRAME2* dataframe)
{
    if (dataframe == NULL)
    {
        printf("\n Veuillez d'abord creer le CDataframe\n");
        return 0;
    }

    if (populate_dataframe_automatically(CDataframe2))
        printf("\n Le dataframe a ete remplie avec plusieurs colonnes de differents types contenant diverses donnees\n");
    else
        printf("\n Un probleme est survenue lors du remplissage automatique du CDataframe\n");

    return -1;
}

int cmd_sauvegarder_cdataframe_dans_fichier(DATAFRAME2* dataframe, char nom_fichier_csv, const char separateur)
{
    if (dataframe == NULL)
    {
        printf("\n Veuillez d'abord creer ET remplir le CDataframe\n\n");
        return -1;
    }

    int ret;

    if (dataframe->size == 0)
    {
        printf("\n Le CDataframe \"%s\" ne contient aucune colonne\n", dataframe->title);
        printf("\n Appuyez sur une touche puis sur \"Entree\"  pour continuer\n");
        ret = getchar();
        return -1;
    }
    
    if (save_dataframe_to_csv(CDataframe2, NOM_FICHIER_CSV, SEPARATEUR_CSV))
        printf("\n Le CDdataframe \"%s\" a ete sauvegarde avec succes dans le fichier \"%s\"\n", dataframe->title, NOM_FICHIER_CSV);
    else
        printf("\n Un probleme est survenue lors de la sauvegarde du CDataframe \"%s\" dans le fichier CSV \"%s\"\n", dataframe->title, NOM_FICHIER_CSV);

    vider_tampon();
    ret = getchar();

    return -1;
}

int cmd_charger_cdataframe_depuis_fichier(DATAFRAME2** dataframe_ptr, char nom_fichier_csv, const char separateur)
{
    if (dataframe_ptr == NULL)
        return 0;

    DATAFRAME2* dataframe = *dataframe_ptr;

    dataframe = load_dataframe_from_csv("dataframe", NOM_FICHIER_CSV, SEPARATEUR_CSV);
    
    if (true)
        printf("\nLe CDdataframe a ete charge avec succes\n");
    else
        printf("\n Un probleme est survenue lors du chargement du CDataframe dans le fichier CSV\n");

    return -1;
}

#pragma endregion menu_management_sub_menu_1

#pragma region menu_management_sub_menu_2

int process_user_menu_choice_main_section_2(int sub_section_number)
{
    if (CDataframe2 == NULL)
    {
        printf("\n Veuillez d'abord creer le CDataframe\n");
        return -1;
    }

    if (CDataframe2->size == 0)
    {
        printf("\n Veuillez d'abord creer et remplir au moins une colonne dans le CDataframe \"%s\"\n", dataframe_title);
        return -1;
    }
    
    switch (sub_section_number)
    {
        case 21:
            printf("\n 21 - Afficher le CDataframe \"%s\" :\n", dataframe_title);
            return cmd_afficher_cdataframe(CDataframe2);
        case 22:
            printf("\n 22 - Afficher les lignes et colonnes du CDataframe \"%s\" selon une eventuelle limite de l'utilisateur :\n", dataframe_title);
            return cmd_afficher_lignes_et_colonnes_selon_limites_utilisateurs(CDataframe2);
        case 23:
            printf("\n 23 - Afficher le nombre de colonnes du CDataframe \"%s\" :\n", dataframe_title);
            return cmd_afficher_nombre_de_colonnes(CDataframe2);
        case 24:
            printf("\n 24 - Afficher le nom et le type des colonnes du CDataframe \"%s\" :\n", dataframe_title);
            return cmd_afficher_noms_et_types_des_colonnes(CDataframe2);
        case 25:
            printf("\n 25 - Afficher le contenu d'une colonne du CDataframe \"%s\" :\n", dataframe_title);
            return cmd_afficher_contenu_de_colonne(CDataframe2);
        case 26:
            printf("\n 26 - Afficher le nombre de lignes du CDataframe \"%s\" :\n", dataframe_title);
            return cmd_afficher_nombre_lignes(CDataframe2);
        default:
            break;
    }
}

int cmd_afficher_cdataframe(DATAFRAME2* dataframe)
{
    show_cdataframe(dataframe, NO_LIMIT, NO_LIMIT);
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
        vider_tampon();
        ret = getchar();
        return -1;
    }

    // Saisie du nombre de col max à afficher
    do {
        printf("\n Entrez le nombre max de colonnes a afficher :\n");
        printf("\n Le CDataframe \"%s\" contient %d colonnes :\n", dataframe->title, dataframe->size);
        printf("\n Pour afficher toutes les colonnes, entrez la valeur \"-1\" : ");

        scanf("%d", &num_col_max_to_show);

        // Vérifier si le choix est valide, sinon prevenir
        if (num_col_max_to_show == NO_LIMIT)
            ret = 1;
        if (num_col_max_to_show > dataframe->size)
            printf("\n Choix invalide. Veuillez entrer un num de colonne compris entre 1 et %d:\n", dataframe->size);
        else if (num_col_max_to_show <= 1)
        {
            printf("\n Le nombre doit etre positif ou egal a -1 mais pas negatif ni egal a zero");
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
        vider_tampon();
        ret = getchar();
        return -1;
    }

    do {
        printf("\n Le CDataframe \"%s\" contient %d lignes :\n", dataframe->title, nombre_lignes_total);
        printf("\n Entrez le nombre de lignes max a afficher :\n");
        printf("\n Pour afficher toutes les lignes, entrez la valeur \"-1\" : ");

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
        vider_tampon();
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
        vider_tampon();
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
        vider_tampon();
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
        printf("\n 34 - Renommer une colonne :\n");
        return cmd_renommer_une_colonne(CDataframe2);
    case 35:
        printf("\n 35 - Supprimer une colonne du CDataframe : \"%s\" \n", dataframe_title);
        return cmd_supprimer_colonne_du_cdataframe(CDataframe2);
    case 36:
        printf("\n 36 - Supprimer une ligne de valeurs du CDataframe \"%s\" \n", dataframe_title);
        return cmd_supprimer_ligne_du_cdataframe(CDataframe2);
    case 37:
        printf("\n 37 - Supprimer le CDataframe : \"%s\" \n", dataframe_title);
        return cmd_supprimer_cdataframe(&CDataframe2);
    case 38:
        printf("\n 38 - Ne jamais lancer cette commande :\n");
        return cmd_ne_jamais_lancer_cette_commande();
    default:
        break;
    }
    return -1;
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
        printf("\n Appuyez sur une touche puis sur \"Entree\" pour continuer\n");
        vider_tampon();
        int ret = getchar();
        return -1;
    }

    // Show all col name and type 
    print_name_and_type_of_columns(dataframe);

    int ask_num_col = 1;
    int num_col = 0;

    do
    {
        // Demander le num de col à trier
        printf("\n Choisissez le numero d'une colonne et appuyez sur la touche \"Entree\" :\n\n");
        int ret = scanf("%1d", &num_col);

        if (num_col > dataframe->size || num_col < 0)
            printf("\n Le numero de colonne est invalide, veuillez le saisir de nouveau");
        else
            ask_num_col = 0;
        
    } while (ask_num_col == 1);

    printf("\n Choisissez le sens du tri (0 = du + petit au + grand || 1 = du + grand au + petit et appuyez sur la touche \"Entree\"\n\n");
    int sort_dir = 0;
    int ret = scanf("%1d", &sort_dir);

    dataframe->columns[num_col]->sort_dir = sort_dir;

    if (! sort_column(dataframe->columns[num_col], sort_dir))
    {
        printf("\n Un probleme est survenu lors de l'operation de tri\n");
        return -1;
    } 

    printf("\n La colonne \"%s\" du CDataframe \"%s\" a ete triee selon votre critere :\n\n", dataframe->columns[num_col]->title, dataframe->title);

    print_col_by_index(dataframe->columns[num_col]);

    char choix[2];

    printf("\n Voulez-vous voir le resultat global (avec toutes les autres colonnes) dans le CDataframe \"%s\" (o/n) ? \n\n", dataframe->title);
    ret = scanf("%1s", &choix);

    if (strcmp(choix, "o") == 0)
        ret = show_cdataframe(CDataframe2, NO_LIMIT, dataframe->columns[num_col]->size);

    return -1;
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
        printf("\n Impossible de lire la valeur dans une cellule d'une colonne car le CDataframe \"%s\" ne contient aucune colonne\n", dataframe->title);
        printf("\n Appuyez sur une touche puis sur \"Entree\"  pour continuer\n");
        vider_tampon();
        int ret = getchar();
        return -1;
    }

    int num_col = 0;
    int num_ligne = 0;
    int ask_user_to_input_value = 0;
    int nombre_de_lignes = 0;

    nombre_de_lignes = dataframe->columns[0]->max_size;

    // Show all col names and type 
    printf("\n Voici les colonnes disponibles...\n");
    print_name_and_type_of_columns(dataframe);

    ask_user_to_input_value = 1;
    // Demander à l'utilisateur de selectionner une colonne pour la lecture de la donnée
    do
    {
        printf("\n\n Veuillez saisir un numero de COLONNE hebergeant la donnee a lire et qui soit compris entre 0 et %d (ou \"-1\" pour abandonner) : ", dataframe->size);
        vider_tampon();
        int ret = scanf("  %d", &num_col);

        if (num_col > dataframe->size || num_col < -1)
        {
            printf("\n Numero de colonne fallacieux");
        }
        else if (num_col == -1)
            return -1;
        else
            ask_user_to_input_value = 0;

    } while (ask_user_to_input_value == 1);

    // Demander à l'utilisateur de selectionner une ligne pour la lecture de la donnée
    do
    {
        printf("\n\n Veuillez saisir un numero de LIGNE hebergeant la donnee a lire et qui soit compris entre 0 et %d (ou \"-1\" pour abandonner) : ", nombre_de_lignes);
        vider_tampon();
        int ret = scanf("  %d", &num_ligne);

        if (num_ligne > dataframe->size || num_ligne < -1)
        {
            printf("\n Numero de ligne erratique");
        }
        else if (num_ligne == -1)
            return -1;
        else
            ask_user_to_input_value = 0;

    } while (ask_user_to_input_value == 1);

    print_value(dataframe, num_col, num_ligne);

    return -1;
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
        vider_tampon();
        int ret = getchar();
        return -1;
    }

    int num_col = 0;
    int num_ligne = 0;
    int ask_user_to_input_value = 0;
    int nombre_de_lignes = 0;

    nombre_de_lignes = dataframe->columns[0]->max_size;

    // Show all col names and type 
    printf("\n Voici les colonnes disponibles...\n");
    print_name_and_type_of_columns(dataframe);

    ask_user_to_input_value = 1;
    // Demander à l'utilisateur de selectionner une colonne pour la lecture de la donnée
    do
    {
        printf("\n\n Veuillez saisir un numero de COLONNE hebergeant la donnee a modifier et qui soit compris entre 0 et %d (ou \"-1\" pour abandonner) : \n", dataframe->size);
        int ret = scanf("  %d", &num_col);

        if (num_col > dataframe->size || num_col < -1)
        {
            printf("\n Numero de colonne aberrant");
        }
        else if (num_col == -1)
            return -1;
        else
            ask_user_to_input_value = 0;

    } while (ask_user_to_input_value == 1);

    ask_user_to_input_value = 0;

    // Demander à l'utilisateur de selectionner une ligne pour la lecture de la donnée
    do
    {
        printf("\n\n Veuillez saisir un numero de LIGNE hebergeant la donnee a modifier et qui soit compris entre 0 et %d (ou \"-1\" pour abandonner) : \n", nombre_de_lignes);
        int ret = scanf("  %d", &num_ligne);

        if (num_ligne > dataframe->size || num_ligne < -1)
        {
            printf("\n Numero de ligne deplorable");
        }
        else if (num_ligne == -1)
            return -1;
        else
            ask_user_to_input_value = 0;

    } while (ask_user_to_input_value == 1);

    // Recuperer la valeur à modifier
    int ret = 0;
    int success = 0;

    ENUM_TYPE col_type = dataframe->columns[num_col]->column_type;

    switch (col_type)
    {
    case UINT:
        unsigned int uint_value = 0;
        printf("\n Saisissez une valeur entière non signée (UINT) a ajouter dans la colonne %s : ", dataframe->columns[num_col]->title);
        ret = scanf("%u", &uint_value);

        // Verifier que la valeur entrée corresponde bien au type de la col considérée
        if (!check_if_valid_value(&uint_value, col_type))
            printf("\n Ajout impossible: La valeur saisie n'est pas valide en tant que \"%s\"", enum_to_string(col_type));
        // Check if value got the right type
        change_value(dataframe, num_col, num_ligne, &uint_value);
        break;
    case INT:
        int int_value = 0;
        printf("\n Saisissez une valeur entière signée (INT) a ajouter dans la colonne %s : ", dataframe->columns[num_col]->title);
        ret = scanf("%d", &int_value);

        // Verifier que la valeur entrée corresponde bien au type de la col considérée
        if (!check_if_valid_value(&int_value, col_type))
            printf("\n Ajout impossible: La valeur saisie n'est pas valide en tant que \"%s\"", enum_to_string(col_type));
        // Check if value got the right type
        change_value(dataframe, num_col, num_ligne, &int_value);
        break;
    case CHAR:
        char char_value = '\0';
        printf("\n Saisissez une valeur (CHAR) a ajouter dans la colonne %s : ", dataframe->columns[num_col]->title);
        ret = scanf("%c", &char_value);

        // Verifier que la valeur entrée corresponde bien au type de la col considérée
        if (!check_if_valid_value(&char_value, col_type))
            printf("\n Ajout impossible: La valeur saisie n'est pas valide en tant que \"%s\"", enum_to_string(col_type));
        // Check if value got the right type
        change_value(dataframe, num_col, num_ligne, &char_value);
        break;
    case FLOAT:
        float float_value = 0.0f;
        printf("\n Saisissez une valeur (FLOAT) a ajouter dans la colonne %s : ", dataframe->columns[num_col]->title);
        ret = scanf("%f", &float_value);

        // Verifier que la valeur entrée corresponde bien au type de la col considérée
        if (!check_if_valid_value(&float_value, col_type))
            printf("\n Ajout impossible: La valeur saisie n'est pas valide en tant que \"%s\"", enum_to_string(col_type));
        // Check if value got the right type
        change_value(dataframe, num_col, num_ligne, &float_value);
        break;
    case DOUBLE:
        double double_value = 0.0;
        printf("\n Saisissez une valeur (DOUBLE) a ajouter dans la colonne %s : ", dataframe->columns[num_col]->title);
        ret = scanf("%lf", &double_value);

        // Verifier que la valeur entrée corresponde bien au type de la col considérée
        if (!check_if_valid_value(&double_value, col_type))
            printf("\n Ajout impossible: La valeur saisie n'est pas valide en tant que \"%s\"", enum_to_string(col_type));
        // Check if value got the right type
        change_value(dataframe, num_col, num_ligne, &double_value);
        break;
    case STRING:
        char string_value[TAILLE_MAX_DATA_STRING];
        printf("\n Saisissez une valeur (STRING) a ajouter dans la colonne %s : ", dataframe->columns[num_col]->title);
        ret = scanf("%255s", string_value);

        // Verifier que la valeur entrée corresponde bien au type de la col considérée
        if (!check_if_valid_value(string_value, col_type))
            printf("\n Ajout impossible: La valeur saisie n'est pas valide en tant que \"%s\"", enum_to_string(col_type));
        // Check if value got the right type
        change_value(dataframe, num_col, num_ligne, &string_value);
        break;
    case STRUCTURE:
        void* pstructure;
        printf("\n\n     TODO...");
        break;
    default:
        break;
    }
    
    return -1;
}

int cmd_renommer_une_colonne(DATAFRAME2* dataframe)
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
        vider_tampon();
        int ret = getchar();
        return -1;
    }

    int num_col = 0;
    int nombre_col_total = 0;
    char col_new_name[NOMBRE_CHAR_MAX_NOM_COLONNE];
    int saisir_col_num = 1;

    nombre_col_total = dataframe->size;

    print_name_and_type_of_columns(dataframe);

    // Ask for col number
    do {
        printf("\n\n Entrez le numero de la colonne a renommer :\n");
        scanf("%d", &num_col);

        // Vérifier si le choix est valide, sinon prevenir
        if (num_col > nombre_col_total)
        {
            printf("\n Choix invalide, le numero de colonne a remplir ne doit pas exceder %d", nombre_col_total);
            printf("\n Veuillez entrer un numero de colonne compris entre 0 et %d:\n", nombre_col_total);
        }
        else if (num_col < 0)
        {
            printf("\n Veuillez entrer un numero de colonne POSITIF compris entre 0 et %d:\n", nombre_col_total);
        }
        else
            saisir_col_num = 0;
    } while (saisir_col_num == 1); // Continuer tant que le num de col à remplir est erronée
        
    // Stocker l'ancien nom de la col avant modification
    char* col_old_name = strdup(dataframe->columns[num_col]->title);

    printf("\n Veuillez saisir le nouveau nom de la colonne \"%s\" : ", col_old_name);
    scanf("%255s", col_new_name);

    if (rename_column(dataframe, num_col, &col_new_name))
        printf("\n La colonne %d anciennement nommee \"%s\" a ete renomme en \"%s\"\n", num_col, col_old_name, col_new_name);
    else
        printf("\n Un probleme est survenu lors du renommage de la colonne\n");
    
    return -1;
}

int cmd_ne_jamais_lancer_cette_commande()
{
    system("cls");

    printf("\n\n\n\n\n\n\n\n\n\n                                        Serieusement ??? (Appuyez sur \"Entree\")");
    vider_tampon();
    getchar();

    printf("\n\n\n\n\n\n\n\n\n\n                                        Qu'est-ce que VOUS ne COMPRENEZ PAS dans...");
    vider_tampon();
    getchar();

    system("cls");

    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n                                        Ne \"JAMAIS\" lancer cette commande ! ! !");
    vider_tampon();
    getchar();

    system("cls");

    printf("\n\n\n\n\n\n\n\n\n\n                                             A la fin du compte a rebours, ton ordinateur n'existera plus...");
    printf("\n\n\n\n\n\n\n\n\n\n                                                            FALLAIT PAS BRAVER L'INTERDIT !");
    printf("\n\n\n\n\n\n\n\n\n\n                                        Maintenant, appuie pour la derniere fois sur une touche, si t'es un bonhomme...");
    vider_tampon();
    getchar();
    
    for (int i = 50000; i >= 0; i--)
        printf("                      !!!!!!!!!!!!!!!!!!!!!!!!                                %d                                !!!!!!!!!!!!!!!!!!!!!!!!                                        \n", i);

    system("cls");
    printf("\n\n\n\n\n\n\n\n\n\n                                        DESTRUCTION DE L'ORDINATEUR EN COURS...");
    printf("\n\n\n\n\n\n\n\n\n\n                                              DITES-LUI \"AU-REVOIR !\"");
    vider_tampon();
    getchar();

    for (int i = 100; i >= 0; i--)
    {
        system("cls");
        afficher_menu();
    }
    
    system("cls");

    for (int i = 0; i <= 11591; i++)
    {
        printf("*");
    }
    vider_tampon();
    getchar();

    system("cls");
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n                                                                 ! ! !        BOUM        ! ! !");

    vider_tampon();
    getchar();

    system("cls");

    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n                                                                 Avoues, t'y as vraiment cru...");
    vider_tampon();
    getchar();

    system("cls");

    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n                                                                 T'avais raison, HA HA HA ! ! !");
    vider_tampon();
    getchar();

    system("cls");

    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n                                                                 On rigole bien, non ?");
    vider_tampon();
    getchar();

    system("cls");

    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n                                                                 Je te rends ton ordi, maintenant...");
    vider_tampon();
    getchar();

    afficher_menu();

    return -1;
}

int cmd_supprimer_colonne_du_cdataframe(DATAFRAME2* dataframe)
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
        vider_tampon();
        int ret = getchar();
        return -1;
    }

    printf("\n Voici les colonnes disponibles :\n");
    print_name_and_type_of_columns(dataframe);

    printf("\n Veuillez entrer le numero de la colonne a supprimer : \n");

    int num_col = 0;
    int saisir_num_col = 1;

    do
    {
        int ret = scanf("  %d", &num_col);
        
        if (num_col > dataframe->size || num_col < -1)
            printf("\n\n Veuillez saisir un numero pour la colonne a supprimer qui soit compris entre 0 et %d ou -1 pour abandonner la suppression de la colonne\n", dataframe->size);
        else if (num_col == -1)
            return -1;
        else
            saisir_num_col = 0;

    } while (saisir_num_col == 1);

    if (delete_column(dataframe, num_col))
    {
        printf("\n La suppression de la colonne %d a ete effectue avec succes\n", num_col);
        printf("\n Voici le nouvel aspect du CDataframe \"%s\" :\n", dataframe->title);
        printf("\n Appuyez sur une touche quelconque pour le decouvrir...\n");
        vider_tampon();
        int ret = getchar();
        print_name_and_type_of_columns(dataframe);
    }
    else
        printf("\n Un probleme est survenu lors de la suppression de la colonne\n");

    return -1;
}

int cmd_supprimer_ligne_du_cdataframe(DATAFRAME2* dataframe)
{
    if (!dataframe_has_data(dataframe))
        return -1;

    int num_ligne_a_supprimer;
    int nombre_lignes;
    int ask_user_to_input_line_num = 0;
    int ret = 0;

    nombre_lignes = dataframe->columns[0]->max_size;
    
    ask_user_to_input_line_num = 1;

    do {
        printf("\n Le CDataframe \"%s\" contient %d ligne(s) au total", dataframe->title, nombre_lignes);
        printf("\n\n Entrez le numero de la ligne a supprimer ou \"-1\" pour abandonner l'operation: ");

        ret = scanf("%d", &num_ligne_a_supprimer);

        // Vérifier si le choix est valide, sinon prevenir
        if (num_ligne_a_supprimer == -1)
        {
            printf("\n Veuillez entrer un numero de ligne POSITIF compris entre 0 et %d:\n", nombre_lignes);
            return -1;
        }
        else if (num_ligne_a_supprimer > nombre_lignes)
        {
            printf("\n Choix invalide, le numero de ligne a supprimer ne doit pas exceder %d", nombre_lignes);
            printf("\n Veuillez entrer un numero de ligne compris entre 0 et %d:\n", nombre_lignes);
        }
        else if(num_ligne_a_supprimer < 0)
            printf("\n Veuillez entrer un numero de ligne POSITIF compris entre 0 et %d:\n", nombre_lignes);
        else
            ask_user_to_input_line_num = 0;

    } while (ask_user_to_input_line_num == 1);

    if (delete_row(dataframe, num_ligne_a_supprimer))
        printf("La ligne de valeurs numero \"%d\" du CDataframe \"%s\" a ete supprimee avec succes", num_ligne_a_supprimer, dataframe->title);
    else
        printf("Erreur lors de la tentative de suppression de la ligne de valeurs numero \"%d\" du CDataframe \"%s\"", num_ligne_a_supprimer, dataframe->title);

    return -1;
}

int cmd_supprimer_cdataframe(DATAFRAME2** dataframe_ptr)
{
    if (dataframe_ptr == NULL)
        return 1;

    DATAFRAME2* dataframe = *dataframe_ptr;
    
    if (dataframe == NULL)
    {
        printf("\n Veuillez d'abord creer un CDataframe\n");
        return -1;
    }

    char choix[2];
    int ret = 0;
    int quit = 0;

    printf("\n\n ****************************************** ");
    printf("\n           ***   ATTENTION   ***            ");
    printf("\n ****************************************** ");

    printf("\n\n Etes-vous sur de vouloir supprimer le CDataframe \"%s\" (o/n) ? \n\n", dataframe->title);
    
    ret = scanf("%1s", &choix);

    do
    {
        // Vérifier si le choix est valide
        if (strcmp(choix, "o") == 0)
        {
            // Effacer l'écran et afficher le menu
            system("cls");
            afficher_menu();

            // Tenter de supprimer le CDataframe
            if (delete_cdataframe(&dataframe))
            { 
                CDataframe2 = NULL;
                printf("\n Le CDataframe a ete supprime avec succes\n");
                quit = 1;
            }
            else
                printf("\n Un probleme est survenu lors de la suppression du CDataframe\n");
        }
        else if (strcmp(choix, "n") == 0)
        {
            // Sortir et laisser l'utilisateur choisir librement une autre commande dans le menu
            printf("\n Le CDataframe n'a PAS ete supprime, retour au menu general\n");
            quit = 1;
        }
        else
        {
            printf("\n Le CDataframe n'a PAS ete supprime, retour au menu general\n");
            quit = 1;
        }
    } while (quit == 0);
    
    return -1;
}

#pragma endregion menu_management_sub_menu_3

#pragma region menu_management_sub_menu_4

int process_user_menu_choice_main_section_4(int sub_section_number)
{
    switch (sub_section_number)
    {
    case 41:
        printf("\n 41 - Nombre de cellules contenant une valeur egale a \"x\" :\n");
        return cmd_nombre_cellules_contenant_valeur_egale_a_x(CDataframe2);
    case 42:
        printf("\n 42 - Nombre de cellules contenant une valeur superieure a \"x\" :\n");
        return cmd_nombre_cellules_contenant_valeur_superieure_a_x(CDataframe2);
    case 43:
        printf("\n 42 - Nombre de cellules contenant une valeur inferieure a \"x\" :\n");
        return cmd_nombre_cellules_contenant_valeur_inferieure_a_x(CDataframe2);
    default:
        break;
    }
}

int cmd_nombre_cellules_contenant_valeur_egale_a_x(DATAFRAME2* dataframe)
{
    OPERATEURS_DE_COMPARAISON comparison_operator = oc_egal;

    if (rechercher_nombre_occurences_dans_cdataframe(dataframe, comparison_operator))
        printf("\n La recherche statistique s'est terminee avec succes");
    else
        printf("\n Un probleme est survenu lors de la recherche statistique");
    
    return -1;
}

int cmd_nombre_cellules_contenant_valeur_superieure_a_x(DATAFRAME2* dataframe)
{
    OPERATEURS_DE_COMPARAISON comparison_operator = oc_superieur;

    if (rechercher_nombre_occurences_dans_cdataframe(dataframe, comparison_operator))
        printf("La recherche statistique s'est terminee avec succes");
    else
        printf("Un probleme est survenu lors de la recherche statistique");

    return -1;
}

int cmd_nombre_cellules_contenant_valeur_inferieure_a_x(DATAFRAME2* dataframe)
{
    OPERATEURS_DE_COMPARAISON comparison_operator = oc_inferieur;

    if (rechercher_nombre_occurences_dans_cdataframe(dataframe, comparison_operator))
        printf("La recherche statistique s'est terminee avec succes");
    else
        printf("Un probleme est survenu lors de la recherche statistique");

    return -1;
}

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

    char choix[2];
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

    return -1;
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
    free_ressources(&CDataframe2);
    
    // quitter le prog
    exit(0);
}

#pragma endregion menu_management_sub_menu_5

#pragma endregion menu_management

void test()
{
    // UINT = 1, INT = 2, CHAR = 3, FLOAT = 5, DOUBLE = 6, STRING = 7, STRUCTURE = 8
    
    /////////////////////////////////////////////////////////////////////////////////////////
    // Tri de la colonne INT par tri
    int num_col = 5;  // UINT = 0, INT = 1, CHAR = 2, FLOAT = 3, DOUBLE = 4, STRING = 5, STRUCTURE = 6
    printf("\n Contenu de la colonne \"%s\" AVANT trie :\n", CDataframe2->columns[num_col]->title);
    print_column(CDataframe2->columns[num_col], false, NO_LIMIT);

    //effectuer le tri (sens du tri: 0 = du + petit au + grand, 1 = inverse)
    CDataframe2->columns[num_col]->sort_dir = 1;
    sort_column(CDataframe2->columns[num_col], CDataframe2->columns[num_col]->sort_dir);

    printf("\n\nContenu de la colonne \"%s\" APRES trie :\n\n", CDataframe2->columns[num_col]->title);
    print_col_by_index(CDataframe2->columns[num_col]);

    res = show_cdataframe(CDataframe2, NO_LIMIT, 20);
}

int check_if_valid_value(void* value, ENUM_TYPE type)
{
    switch (type)
    {
    case UINT:
        // All possible int values
        return 1;
    case INT:
        if (*(int*)value < INT_MIN || *(int*)value > INT_MAX)
            // Out of range
            return 0;
        break;
    case CHAR:
        // All possible int values
        return 1;
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
    case STRING:
        // Verifier que la chaine ne soit ni NULL ni vide
        char* string_value = (char*)value;
        if (string_value == NULL || strlen(string_value) == 0)
            return 0;
        break;
    case STRUCTURE:
        // TODO
        return 1;
    default:
        break;
    }
    return 1;
}

int rechercher_nombre_occurences_dans_cdataframe(DATAFRAME2* dataframe, OPERATEURS_DE_COMPARAISON comparison_operator)
{
    // Entrer le type de valeur à rechercher
    ENUM_TYPE value_type;
    int int_value_type = 0;
    int nombre_occurences_valeur = 0;
    int ret = 0;

    // Demander le type de valeur à rechercher
    printf("\n Veuillez choisir le type de valeur a rechercher :\n");
    printf("\n (UINT = 1, INT = 2, CHAR = 3, FLOAT = 5, DOUBLE = 6, STRING = 7, STRUCTURE = 8)");
    printf("\n\n (Si vous souhaitez annuler l'operation de recherche statistique entrez la valeur \"-1\")\n");
    vider_tampon();
    ret = scanf("%d", &value_type);

    if (value_type == -1)
    {
        printf("\n\n l'opération de recherche statistique a bien ete annulee");
        return -1;
    }
    else if (value_type <= 0 || value_type > NOMBRE_TYPE_COL)
    {
        printf("\n Le type de valeur est invalide, operation annulee");
        return -1;
    }
    else
        printf("\n Le type de valeur a rechercher est : \"%s\"", enum_to_string(value_type));
        
    printf("\n\n Entrez la valeur a rechercher : ");
    
    // Entrer la valeur à rechercher
    switch (value_type)
    {
    case UINT:
        unsigned int uint_value = 0;
        vider_tampon();
        ret = scanf("%u", &uint_value);

        // Verifier que la valeur entrée corresponde bien au type de la col considérée
        if (check_if_valid_value(&uint_value, value_type))
        {
            void* valptr = &uint_value;
            nombre_occurences_valeur = stats_on_value(CDataframe2, valptr, value_type, comparison_operator);
        }
        else
            printf("La valeur saisie n'est pas du type %s", enum_to_string(value_type));
        break;
    case INT:
        int int_value = 0;
        vider_tampon();
        ret = scanf("%d", &int_value);

        // Verifier que la valeur entrée corresponde bien au type de la col considérée
        if (check_if_valid_value(&int_value, value_type))
        {
            void* valptr = &int_value;
            nombre_occurences_valeur = stats_on_value(CDataframe2, valptr, value_type, comparison_operator);
        }
        else
            printf("La valeur saisie n'est pas du type %s", enum_to_string(value_type));
        break;
    case CHAR:
        char char_value = '\0';
        vider_tampon();
        ret = scanf("%c", &char_value);

        // Verifier que la valeur entrée corresponde bien au type de la col considérée
        if (check_if_valid_value(&char_value, value_type))
        {
            void* valptr = &char_value;
            nombre_occurences_valeur = stats_on_value(CDataframe2, valptr, value_type, comparison_operator);
        }
        else
            printf("La valeur saisie n'est pas du type %s", enum_to_string(value_type));
        break;
    case FLOAT:
        float float_value = 0.0f;
        vider_tampon(); 
        ret = scanf("%f", &float_value);

        // Verifier que la valeur entrée corresponde bien au type de la col considérée
        if (check_if_valid_value(&float_value, value_type))
        {
            void* valptr = &float_value;
            nombre_occurences_valeur = stats_on_value(CDataframe2, valptr, value_type, comparison_operator);
        }
        else
            printf("La valeur saisie n'est pas du type %s", enum_to_string(value_type));
        break;
    case DOUBLE:
        double double_value = 0.0;
        vider_tampon();
        ret = scanf("%lf", &double_value);

        // Verifier que la valeur entrée corresponde bien au type de la col considérée
        if (check_if_valid_value(&double_value, value_type))
        {
            void* valptr = &double_value;
            nombre_occurences_valeur = stats_on_value(CDataframe2, valptr, value_type, comparison_operator);
        }
        else
            printf("La valeur saisie n'est pas du type %s", enum_to_string(value_type));
        break;
    case STRING:
        char string_value[TAILLE_MAX_DATA_STRING];
        vider_tampon();
        ret = scanf("%255s", string_value);

        // Verifier que la valeur entrée corresponde bien au type de la col considérée
        if (check_if_valid_value(&string_value, value_type))
        {
            void* valptr = &string_value;
            nombre_occurences_valeur = stats_on_value(CDataframe2, valptr, value_type, comparison_operator);
        }
        else
            printf("La valeur saisie n'est pas du type %s", enum_to_string(value_type));
        break;
    case STRUCTURE:
        //void* pstructure;
        printf("\n\n     Bientot disponible...");
    default:
        break;
    }

    switch (nombre_occurences_valeur)
    {
    case 0:
        printf("\n Il n'y a aucune occurence pour cette valeur dans le CDataframe \"%s\"", dataframe->title);
        break;
    case 1:
        printf("\n Une seule et unique occurence a ete trouve pour cette valeur dans le CDataframe \"%s\"", dataframe->title);
        break;
    default:
        printf("\n %d occurences ont ete trouve pour cette valeur dans le Cdataframe \"%s\"", nombre_occurences_valeur, dataframe->title);
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
        // TESTS SEULEMENT, NE SURTOUT PAS OUBLIE DE COMMENTER !!!
        if (CDataframe2 == NULL)
        {
            CDataframe2 = create_cdataframe("Dataframe 2");
            populate_dataframe_automatically(CDataframe2);
        }
        // test();
        ///////////////////////////////////////////////////////////////////
        
        switch (choix_menu)
        {
            case -1:
                printf("\n\n");
                printf(" Saisissez le code de la commande et appuyez sur \"Entree\"\n\n");

                res_choix_menu = scanf("%d", &choix_menu);

                choix_menu = process_user_menu_choice(choix_menu);

                break;
            
            default:
                break;
        }
    }
    
    return 1;
}