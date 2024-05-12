#include <stdio.h>
#include <string.h>
#include "CDataframe.h"
#include "Main.h"
#include "Colonne.h"
#include "Divers.h"
#include "String_manager.h"

#pragma region CDataframe 1

DATAFRAME1* creer_cdataframe(bool* dataframe_exists, char* nom_dataframe)
{
    DATAFRAME1* nouveau_dataframe = (DATAFRAME1*)malloc(sizeof(DATAFRAME1));

    if (nouveau_dataframe == NULL) {
        printf("\nErreur lors de l'allocation de mémoire pour le dataframe.\n");
        return 0;
    }

    // Attribution du nom (si nom_dataframe est valide)
    if (nom_dataframe != NULL)
    {
        strncpy(nouveau_dataframe->titre, nom_dataframe, sizeof(nouveau_dataframe->titre) - 1);
        nouveau_dataframe->titre[sizeof(nouveau_dataframe->titre) - 1] = '\0'; // Assurer que la chaîne est terminée par un caractère nul
    }
    else
        // Si nom_dataframe est NULL, affecter une chaîne vide
        nouveau_dataframe->titre[0] = '\0';

    nouveau_dataframe->taille = 0;

    // Initialiser le tableau de pointeurs de colonnes à NULL
    nouveau_dataframe->colonnes = NULL;

    (*dataframe_exists) = true;

    return nouveau_dataframe;
}

int ajouter_colonne(DATAFRAME1* dataframe, const char* nom_colonne)
{
    // Ajout d'une colonne en utilisant la fonction creer_colonne
    COLONNE* nouvelle_colonne = creer_colonne(nom_colonne);
    if (nouvelle_colonne == NULL)
    {
        printf("\nErreur lors de la création de la colonne.\n");
        return 0;
    }

    // Agrandissement du tableau CDataframe pour ajouter la nouvelle colonne
    dataframe->taille++;
    //        *colonnes = realloc(*colonnes, (*taille_dataframe) * sizeof(COLONNE*));
    dataframe->colonnes = realloc(dataframe->colonnes, (dataframe->taille) * sizeof(COLONNE*));
    if (dataframe == NULL)
    {
        printf("\nErreur d'allocation mémoire lors de l'ajout d'une colonne au CDataframe.\n");
        free(nouvelle_colonne);
        return 0;
    }

    // Ajout de la colonne au dataframe
    // (*colonnes)[*taille_dataframe - 1] = nouvelle_colonne;
    dataframe->colonnes[dataframe->taille - 1] = nouvelle_colonne;

    return 1;
}

int renommer_colonne(DATAFRAME1* dataframe, int num_colonne, const char* nouveau_nom)
{
    // Vérifier si le numéro de colonne est valide
    if (num_colonne < 0 || num_colonne >= dataframe->taille)
    {
        printf("\nLe numéro de colonne %d est invalide.\n", num_colonne);
        return 0;
    }

    // Vérifier si le nouveau nom est déjà utilisé par une autre colonne
    for (int i = 0; i < dataframe->taille; ++i)
    {
        if (i != num_colonne && strcmp(dataframe->colonnes[i]->titre, nouveau_nom) == 0)
        {
            printf("\nLe nom \"%s\" est déjà utilisé par la colonne %d.\n", nouveau_nom, i);
            return 0;
        }
    }

    // Mettre à jour le nom de la colonne
    strncpy(dataframe->colonnes[num_colonne]->titre, nouveau_nom, sizeof(dataframe->colonnes[num_colonne]->titre) - 1);

    // Ajouter le char terminal
    dataframe->colonnes[num_colonne]->titre[sizeof(dataframe->colonnes[num_colonne]->titre) - 1] = '\0';

    return 1;
}

int supprimer_colonne(DATAFRAME1* dataframe, int num_col)
{
    if (dataframe == NULL)
    {
        printf("\nLe dataframe n'existe pas.\n");
        return 0;
    }

    if (num_col < 0 || num_col >= dataframe->taille)
    {
        printf("\nLa colonne numero %d n'existe pas.\n", num_col);
        return 0;
    }
    
    liberer_ressources_colonne(dataframe->colonnes[num_col]);

    dataframe->taille--;

    if (dataframe->taille == 1)
        return 1;

    for (int i = num_col; i <= dataframe->taille - 1; i++)
        dataframe->colonnes[i] = dataframe->colonnes[i + 1];

    return 1;
}

int nom_colonne_existe(DATAFRAME1* dataframe, char* nom_colonne, int taille_CDataframe)
{
    for (int i = 0; i < taille_CDataframe; i++)
    {
        const char* nom = dataframe->colonnes[i]->titre;

        if (compare_chaines(nom, nom_colonne) == 0)
            return 1;
    }
    return 0;
}

int inserer_valeur_avec_gestion_memoire_data_colonnes(DATAFRAME1* dataframe, int num_col, int valeur)
{
    bool nouveau_bloc_cellules_ajoute_a_colonne = false;

    // Ajouter valeur à colonne
    if (!inserer_valeur(dataframe->colonnes[num_col], valeur, &nouveau_bloc_cellules_ajoute_a_colonne))
        printf("\nUne erreur est survenue lors de l'ajout de la valeur dans la colonne\n");

    if (nouveau_bloc_cellules_ajoute_a_colonne == true)
        egaliser_taille_des_tabs_data_des_colonnes(dataframe);

    return 1;
}

int egaliser_taille_des_tabs_data_des_colonnes(DATAFRAME1* dataframe)
{
    // Si une seule colonne présente, ne rien faire
    if (dataframe->taille == 1)
        return 1;

    int taille_du_plus_grand_tab_data = 0;
    int nombre_blocs_a_ajouter = 0;
    int delta_taille = 0;

    // Parcourir toutes les colonnes et recherchee le tab data ayant la taille physique la + élevée
    // Cette taille devra être allouée, si ce n'est pas déjà le cas, à tous les autres tab data des colonnes
    for (int i = 0; i < dataframe->taille; ++i)
    {
        if (dataframe->colonnes[i]->taille_physique > taille_du_plus_grand_tab_data)
        {
            taille_du_plus_grand_tab_data = dataframe->colonnes[i]->taille_physique;
        }
    }

    // Examiner et ajuster eventuellement la taille des colonnes à cette taille max si besoin
    for (int i = 0; i < dataframe->taille; ++i)
    {
        COLONNE* colonne = dataframe->colonnes[i];

        if (colonne->taille_physique == taille_du_plus_grand_tab_data)
            continue;

        if (colonne->taille_physique < taille_du_plus_grand_tab_data)
        {
            // Calculer le nombre de blocs à allouer. Il peut y avoir un ou plusieurs bloc(s).
            // Ex: Si on vient de créer une col alors qu'il en existe déjà une de 512 lignes (2 blocs))
            delta_taille = taille_du_plus_grand_tab_data - colonne->taille_physique;
            nombre_blocs_a_ajouter = delta_taille / NOMBRE_CELLULES_PAR_BLOC_DATA_COLONNE;

            // Allouer le ou les bloc(s) mémoire nécessaire(s)
            int nouvelle_taille = colonne->taille_physique + (nombre_blocs_a_ajouter * NOMBRE_CELLULES_PAR_BLOC_DATA_COLONNE);

            int* nouveau_tab_data = realloc(colonne->data, nouvelle_taille * sizeof(int));
            if (nouveau_tab_data == NULL)
            {
                printf("\nErreur d'allocation de mémoire pour la colonne %s.\n", colonne->titre);
                return 0;
            }

            // Mettre à jour les données de la colonne
            colonne->taille_physique = nouvelle_taille;
            colonne->data = nouveau_tab_data;
        }
    }
}

int afficher_nombre_colonnes(DATAFRAME1* dataframe)
{
    if (dataframe == NULL) {
        printf("\nVeuillez d'abord creer un dataframe.\n");
        return 0;
    }

    printf("Nombre de colonnes presentes dans le CDataframe \"%s\" : %d\n", dataframe->titre, dataframe->taille);

    return 1;
}

int afficher_noms_colonnes(DATAFRAME1* dataframe)
{
    if (dataframe->taille == 0)
    {
        printf("\nLe CDataframe est vide ou non initialise.\n");
        return 0;
    }

    int nombre_col = 0;

    printf("\nNoms des colonnes :\n\n");

    for (int i = 0; i < dataframe->taille; i++) {
        COLONNE* colonne = dataframe->colonnes[i];
        printf(" [%d] = ", nombre_col);
        printf("%s\n", colonne->titre);
        nombre_col += 1;
    }

    return nombre_col;
}

int afficher_les_colonnes(DATAFRAME1* dataframe)
{
    for (int num_col = 0; num_col < dataframe->taille; num_col++)
    {
        afficher_colonne(dataframe->colonnes[num_col]);
    }
    return 1;
}

int afficher_cdataframe(DATAFRAME1* dataframe, int num_col_max, int num_ligne_max)
{
    if (dataframe == NULL)
    {
        printf("\n\n");
        printf("Veuillez d'abord creer et remplir le CDataframe\n\n");
        return 0;
    }

    // todo: Optimisation: Chercher ici la colonne qui contient le plus de données, et limiter l'affichage des données
    // à cette valeur de ligne au lieu d'afficher toutes les lignes inconditionnellement.
    // rappel: ecrire une fonction nommee "obtenir_num_lignes_max_contenant_donnees(DATAFRAME* dataframe)
    
    int largeur_colonne_nombre_col = 5;

    printf("\n\n");
        
    // Si aucune limites de cols précisée, alors afficher toutes les colonnes
    if (num_col_max == NO_LIMIT)
        num_col_max = dataframe->taille;

    // Si aucune limites de lignes précisée, alors afficher toutes les lignes
    if (num_ligne_max == NO_LIMIT)
        num_ligne_max = dataframe->colonnes[0]->taille_physique;

    // affichage de la ligne des noms de toutes les colonnes voulues
    for (int i = 0; i < num_col_max; i++)
    {
        if (i==0)
            printf(" Num:");
        
        printf("      \"%s\"   ", dataframe->colonnes[i]->titre);
    }

    printf("\n");

    // Traiter toutes les lignes de toutes les colonnes du dataframe en respectant d'eventuelles limites spécifiées
    for (int ligne_courante = 0; ligne_courante <= num_ligne_max; ligne_courante++)
    {
        if (ligne_courante == 0)
            printf("\n");
        else
            printf("\n\n");

        // Afficher une ligne contenant les données de toutes les colonnes à cet indice
        for (int col_courante = 0; col_courante < num_col_max; col_courante++)
        {
            // Affichage du num de ligne en début de ligne une seule et unique fois
            if (col_courante == 0)
            {
                printf(" [%02d]", ligne_courante);
                printf("    ");
            }
            else
                printf("              ");

            // Si la colonne contient encore des données pour cette ligne, les afficher
            if (ligne_courante <= dataframe->colonnes[col_courante]->taille_logique - 1)
                printf("  %*d", largeur_colonne_nombre_col, dataframe->colonnes[col_courante]->data[ligne_courante]);
            // Sinon afficher une val par défaut (à la place d'une valeur quelconque incohérente de la cellule lorsque celle-ci ne contient rien) 
            else
                printf("  %*d", largeur_colonne_nombre_col, VALEUR_PAR_DEFAUT_DATA_COLONNE);
        }
    }

    printf("\n\n\n");
    printf(" ");

    // Commentaire final
    switch (dataframe->taille)
    {
    case 0:
        printf("Il n'y a aucune colonne a afficher dans le CDataframe");
        break;
    case 1:
        printf("Les valeurs d'une colonne ont ete affichee pour ce CDataframe");
        break;
    default:
        printf("Les valeurs de %d colonnes ont ete affiches pour ce CDataframe", num_col_max);
        break;
    }

    printf("\n\n");

    return 1;
}

int obtenir_nombre_lignes_stockant_data(DATAFRAME1* dataframe)
{
    if (dataframe->taille == 0)
    {
        printf("\n La CDataframe ne contient aucune colonne");
        return 0;
    }

    if (dataframe->colonnes[0]->taille_logique == 0)
    {
        printf("\n La CDataframe ne contient aucune ligne avec des donnees");
        return 0;
    }

    printf("\n La CDataframe ne contient %s lignes", dataframe->colonnes[0]->taille_logique);
}

int obtenir_nombre_lignes(DATAFRAME1* dataframe)
{
    if (dataframe->taille == 0)
    {
        printf("\n La CDataframe ne contient aucune colonne");
        return 0;
    }
        
    if(dataframe->colonnes[0]->taille_physique == 0)
    {
        printf("\n La CDataframe ne contient aucune ligne");
        return 0;
    }

    printf("\n La CDataframe ne contient %s lignes", dataframe->colonnes[0]->taille_physique);

    return 1;
}

int modifier_valeur(DATAFRAME1* dataframe, int num_col, int num_ligne, int valeur)
{
    if (dataframe == NULL)
    {
        printf("\nLe dataframe n'existe pas.\n");
        return 0;
    }
    
    if (num_col > dataframe->taille - 1)
    {
        printf("La colonne num %d n'existe pas", num_col);
        return 0;
    }

    if (num_ligne > dataframe->colonnes[num_col]->taille_logique)
    {
        printf("La colonne num %d ne possede pas de valeur à la ligne %d, on ne peut donc pas la modifier", num_col, num_ligne);
        return 0;
    }

    // Modification de la valeur
    dataframe->colonnes[num_col]->data[num_ligne] = valeur;
}

int afficher_valeur(DATAFRAME1* dataframe, int num_col, int num_ligne)
{
    if (dataframe == NULL)
    {
        printf("\nLe dataframe n'existe pas.\n");
        return 0;
    }
    
    if (num_col < 0)
    {
        printf("\nLa ligne entree n'existe pas\n");
    }

    if (num_col >= dataframe->taille)
    {
        printf(" Dans la limite de la plage de colonne disponible ");
    }

    if (num_ligne >= dataframe->colonnes[num_col]->taille_logique)
    {
        printf("ERREUR, ce n'est pas réglementaire aux données enregistrées");
        return 0;
    }

    int valeur = dataframe->colonnes[num_col]->data[num_ligne];
    
    printf("\nValeur à la colonne %d, ligne %d : %d\n", num_col, num_ligne, valeur);

    return 1;
}

int ajouter_valeur_par_utilisateur(DATAFRAME1* dataframe, int num_col, int valeur)
{
    if (dataframe == NULL)
    {
        printf("\nLe dataframe n'existe pas\n");
        return 0;
    }

    if (num_col < 0 || num_col >= dataframe->taille)
    {
        printf("\nLa colonne spécifiée est invalide car elle n'existe pas dans le dataframe.\n");
        return 0;
    }

    if (inserer_valeur_avec_gestion_memoire_data_colonnes(dataframe, num_col, valeur))
    {
        printf("\nLa valeur a bien été ajoutée\n");
        return 1;
    }
    else
    {
        printf("\nUne erreur est survenue\n");
        return 0;
    }
}

void ajouter_ligne(DATAFRAME1* dataframe)
{
    // TODO:
    //S'il n'y a plus de lignes dispo, ajouter un new bloc de lignes
    

    int nouvelle_taille = dataframe->colonnes[0]->taille_logique + 1;

    // Remplissage des données:
    for (int i = 0; i < dataframe->taille; i++)
    {
        ///////////////////////////////////////////////////////////////
        // Copier les valeurs dans la nouvelle ligne
        // dataframe->colonnes[i]->data[nouvelle_taille - 1] = valeur[i];
        // REMPLACER PAR SAISIE UTILISATEUR (scanf)
        //
        // VERIFIER QUE L'UTILISATEUR A BIEN SAISIE LE TYPE ATTENDU POUR LA COLONNE EN COURS !
        // 
        ///////////////////////////////////////////////////////////////

        // Mettre à jour la taille de la colonne */
        dataframe->colonnes[i]->taille_logique = nouvelle_taille;
    }
}

#pragma endregion Fin CDataframe 1

#pragma region CDataframe 2

DATAFRAME2* create_cdataframe(char* dataframe_title)
{
    DATAFRAME2* new_dataframe = (DATAFRAME2*)malloc(sizeof(DATAFRAME2));

    if (new_dataframe == NULL) {
        printf("\nErreur lors de l'allocation de mémoire pour le dataframe.\n");
        return 0;
    }

    // Attribution du nom au dataframe si valide)
    if (dataframe_title != NULL)
    {
        strncpy(new_dataframe->title, dataframe_title, sizeof(new_dataframe->title) - 1);
        new_dataframe->title[sizeof(new_dataframe->title) - 1] = '\0'; // Assurer que la chaîne est terminée par un caractère nul
    }
    else
        // Si nom_dataframe est NULL, affecter une chaîne vide
        new_dataframe->title[0] = '\0';

    new_dataframe->size = 0;

    // Initialiser le tableau de pointeurs de colonnes à NULL
    new_dataframe->columns = NULL;

    return new_dataframe;
}

int add_column(DATAFRAME2* dataframe, ENUM_TYPE column_type, const char* column_title)
{
    // Ajout d'une colonne
    COLUMN* new_col = create_column(column_type, column_title);
    if (new_col == NULL)
    {
        printf("\nErreur lors de la création de la colonne.\n");
        return 0;
    }

    // Agrandissement du tableau CDataframe apres ajout de la nouvelle colonne
    dataframe->size++;

    // Note: Ne pas faire de malloc, meme s'il n'y a aucune colonne

    dataframe->columns = realloc(dataframe->columns, (dataframe->size) * sizeof(COLUMN*));
    if (dataframe == NULL)
    {
        printf("\nErreur d'allocation mémoire lors de l'ajout d'une colonne au CDataframe.\n");
        free(new_col);
        return 0;
    }

    // Ajout de la colonne au dataframe
    dataframe->columns[dataframe->size - 1] = new_col;

    return 1;
}

int rename_column(DATAFRAME2* dataframe, int column_num, char* new_name)
{
    // Vérifier si le numéro de colonne est valide
    if (column_num < 0 || column_num >= dataframe->size)
    {
        printf("\nLe numero de colonne \"%d\" est invalide\n", column_num);
        return 0;
    }

    int name_exists = 0;

    // Vérifier si le nouveau nom est déjà pris par une autre colonne
    for (int i = 0; i < dataframe->size; i++)
    {
        if (i != column_num - 1)
        {
            if (column_name_exists(dataframe, new_name))
            {
                printf("\nLe nom \"%s\" est deja utilise par la colonne %d.\n", new_name, i + 1);
                return 0;
            }
        }
    }
    
    // Mettre à jour le nom de la colonne
    strcpy(dataframe->columns[column_num]->title, new_name);

    return 1;
}

int delete_column(DATAFRAME2* dataframe, int num_col)
{
    if (dataframe->columns[num_col] == NULL)
        // Retourne si la colonne n'existe pas
        return 0;

    // Libération de la mémoire allouée pour le titre de la colonne
    free((dataframe->columns[num_col])->title);
    dataframe->columns[num_col]->title = NULL;

    // Libère la mémoire allouée pour chaque donnée de la colonne
    if (dataframe->columns[num_col]->data != NULL)
    {
        for (unsigned int i = 0; i < dataframe->columns[num_col]->size; i++)
        {
            free(dataframe->columns[num_col]->data[i]);
            dataframe->columns[num_col]->data[i] = NULL;
        }

        // Libération de la mémoire allouée pour le tableau de pointeurs des données
        free(dataframe->columns[num_col]->data);
        dataframe->columns[num_col]->data = NULL;
    
        // Libération de la mémoire allouée pour le tableau d'index
        /*for (unsigned int i = 0; i < dataframe->columns[num_col]->size; i++)
        {
            free(dataframe->columns[num_col]->index[i]);
            dataframe->columns[num_col]->index[i] = NULL;
        }*/
        
        free(dataframe->columns[num_col]->index);
        dataframe->columns[num_col]->index = NULL;
    }

    // Libération de la mémoire allouée pour la structure de la colonne elle-même
    free(dataframe->columns[num_col]);
    dataframe->columns[num_col] = NULL;

    dataframe->size--;

    if (dataframe->size == 1)
        return 1;

    // Réajustement des colonnes
    for (int i = num_col; i < dataframe->size; i++)
    {
        dataframe->columns[i] = dataframe->columns[i + 1];
        dataframe->columns[i + 1] = NULL;
    }
        
    return 1;
}

int column_name_exists(DATAFRAME2* dataframe, char* column_name)
{
    for (int i = 0; i < dataframe->size; i++)
    {
        if (compare_chaines(dataframe->columns[i]->title, column_name) == 0)
            return 1;
    }
    return 0;
}

int insert_value_with_memory_management_of_tabs_data_of_columns(DATAFRAME2* dataframe, int num_col, void* value)
{
    bool block_cells_added_to_column = false;

    // Ajouter valeur à colonne
    if (! insert_value(dataframe->columns[num_col], value, &block_cells_added_to_column))
    {
        printf("\nUne erreur est survenue lors de l'ajout de la valeur dans la colonne\n");
        return 0;
    }

    // Si un nouveau bloc de cells à été ajouté à cette col, toutes les autres cols doivent être de la même taille
    if (block_cells_added_to_column == true)
        equalize_size_of_tabs_data_of_columns(dataframe);

    return 1;
}

int equalize_size_of_tabs_data_of_columns(DATAFRAME2* dataframe)
{
    // Si une seule colonne présente, point besoin d'égaliser
    if (dataframe->size == 1)
        return 1;

    int size_of_highest_tab_data = 0;
    int number_of_blocks_to_add = 0;
    int delta_size = 0;

    // Parcourir toutes les colonnes et rechercher le tab data ayant la taille physique la + élevée
    // Cette taille devra être allouée, si ce n'est pas déjà le cas, à tous les autres tab data des colonnes
    for (int i = 0; i < dataframe->size; ++i)
    {
        if (dataframe->columns[i]->max_size > size_of_highest_tab_data)
        {
            size_of_highest_tab_data = dataframe->columns[i]->max_size;
        }
    }

    int total_number_of_cells = 0;

    // Examiner et ajuster eventuellement la taille des colonnes à cette taille max si besoin
    for (int i = 0; i < dataframe->size; ++i)
    {
        COLUMN* col = dataframe->columns[i];

        if (col->size == size_of_highest_tab_data)
            continue;
        
        total_number_of_cells = 0;

        if (col->size < size_of_highest_tab_data)
        {
            // Calculer le nombre de blocs à allouer. Il peut y avoir un ou plusieurs à allouer.
            // Ex: Si on vient de créer une col alors qu'il en existe déjà possédant 512 lignes, cela fera 2 blocs à ajouter d'un coup
            delta_size = size_of_highest_tab_data - col->size;
            number_of_blocks_to_add = delta_size / NOMBRE_CELLULES_PAR_BLOC_DATA_COLONNE;

            // Allouer le ou les bloc(s) mémoire nécessaire(s)
            total_number_of_cells = col->size + (number_of_blocks_to_add * NOMBRE_CELLULES_PAR_BLOC_DATA_COLONNE);

            //TODO: faire fct "allocate_memory_to_data(col, total_number_of_cells)
            // et y mettre le code ci-dessous. Ensuite utiliser cette fct au lieu du code suivant.
            // Factoriser egalement de la m maniere le m type de code qui est dans "insert_value".
            
            // Si la col ne contient aucune données, allouer de l'espace pour les data et l'index
            if (col->max_size == 0)
            {
                // creation du tab de données (vide)
                col->data = malloc(total_number_of_cells * sizeof(COL_TYPE*));
                if (col->data == NULL)
                {
                    printf("\nErreur d'allocation mémoire lors de la création du tab data de la colonne\n");
                    return 0;
                }

                // creation du tab d'index pour le tab de données (vide)
                col->index = malloc(total_number_of_cells * sizeof(unsigned long long int*));
                if (col->index == NULL)
                {
                    printf("\nErreur d'allocation mémoire lors de la création du tab d'index pour le tab data de la colonne\n");
                    return 0;
                }
                col->max_size = total_number_of_cells;
                continue;
            }

            // Si la col contient déjà des blocs, ajouter le nombre de blocs manquant
            if(col->max_size < size_of_highest_tab_data)
            {
                col->data = realloc(col->data, total_number_of_cells * sizeof(COL_TYPE*));
                if (col->data == NULL) {
                    printf("\nErreur de réallocation de mémoire lors de l'extension du tableau data de la colonne\n");
                    return 0;
                }

                // Réallocation de mémoire afin d'augmenter la capacité du tab d'index pour le tab de données
                col->index = realloc(col->index, total_number_of_cells * sizeof(unsigned long long int*));
                if (col->index == NULL) {
                    printf("\nErreur de réallocation de mémoire lors de l'extension du tab d'index pour le tab de données\n");
                    return 0;
                }
                col->max_size = total_number_of_cells;
            }
        }
    }
}

int print_number_of_columns(DATAFRAME2* dataframe)
{
    if (dataframe == NULL) {
        printf("\n veuillez d'abord initialiser un dataframe\n");
        return 0;
    }

    printf("Nombre de colonnes présentent dans le CDataframe : %d\n", dataframe->size);
    return 1;
}

int print_name_of_columns(DATAFRAME2* dataframe)
{
    if (dataframe == NULL || dataframe->size == 0) {
        printf("\nLe dataframe est vide ou non intialisé.\n");
        return 0;
    }

    int col_number = 0;

    printf("\noms des colonnes : \n\n");

    for (int i = 0; i < dataframe->size; i++) {
        COLUMN* column = dataframe->columns[i];
        printf("[%d] = %s\n", col_number, column->title);
        col_number += 1;
    }
    return 1;
}

int print_columns(DATAFRAME2* dataframe)
{
    if (dataframe == NULL || dataframe->size == 0)
    {
        printf("\nDataframe à initialisé.\n");
        return 0;
    }

    for (int i = 0; i < dataframe->size; i++)
        afficher_colonne(dataframe->columns[i]);

    return 1;
}

int get_number_of_rows_storing_data(DATAFRAME2* dataframe)
{
    if (dataframe->size == 0)
    {
        printf("\n La CDataframe ne contient aucune colonne");
        return 0;
    }

    if (dataframe->columns[0]->size == 0)
    {
        printf("\n La CDataframe ne contient aucune ligne avec des donnees");
        return 0;
    }

    printf("\n La CDataframe ne contient %s lignes", dataframe->columns[0]->size);
}

int get_number_of_rows(DATAFRAME2* dataframe)
{
    if (dataframe->size == 0)
    {
        printf("\n La CDataframe ne contient aucune colonne");
        return 0;
    }

    if (dataframe->columns[0]->max_size == 0)
    {
        printf("\n La CDataframe ne contient aucune ligne");
        return 0;
    }

    printf("\n La CDataframe ne contient %s lignes", dataframe->columns[0]->max_size);

    return 1;
}

int print_value(DATAFRAME2* dataframe, int num_col, int num_ligne)
{
    if (dataframe == NULL)
    {
        printf("\nLe dataframe n'existe pas.\n");
        return 0;
    }

    if (num_col < 0 || num_col >= dataframe->size)
    {
        printf("\nLe numéro de colonne entré est invalide.\n");
        return 0;
    }

    COLUMN* column = dataframe->columns[num_col];

    if (num_ligne < 0 || num_ligne >= column->size)
    {
        printf("\nLe numéro de ligne entré est invalide pour cette colonne.\n");
        return 0;
    }

    char value_str[TAILLE_MAX_DATA_STRING];
    if (! convert_value(column, num_ligne, value_str, sizeof(value_str)))
    {
        printf("\nErreur dans print_value lors de la conversion de la valeur a afficher\n");
        return 0;
    }

    return 1;
}

int change_value(DATAFRAME2* dataframe, int num_col, int num_row, void* value)
{
    if (dataframe == NULL)
    {
        printf("\nLe dataframe n'existe pas\n");
        return 0;
    }

    if (num_col > dataframe->size - 1)
    {
        printf("La colonne num %d n'existe pas", num_col);
        return 0;
    }

    if (num_row > dataframe->columns[num_col]->size)
    {
        printf("La colonne num %d ne possede pas de ligne %d, on ne peut donc pas la modifier", num_col, num_row);
        return 0;
    }

    if (value == NULL)
    {
        printf("La valeur à modifier n'est pas valide");
        return 0;
    }

    // Modification de la valeur
    //dataframe->columns[num_col]->data[num_row] = value;
    //*((int*)dataframe->columns[0]->data[0]) = value;

    switch (dataframe->columns[num_col]->column_type)
    {
        // modifier par la valeur passée en param en fonction du putain de type
        case UINT:
            *((unsigned int*)dataframe->columns[num_col]->data[num_row]) = *((unsigned int*)value);
            break;

        case INT:
            *((int*)dataframe->columns[num_col]->data[num_row]) = *((int*)value);
            break;

        case CHAR:
            *((char*)dataframe->columns[num_col]->data[num_row]) = *((char*)value);
            break;

        case FLOAT:
            *((float*)dataframe->columns[num_col]->data[num_row]) = *((float*)value);
            break;

        case DOUBLE:
            *((double*)dataframe->columns[num_col]->data[num_row]) = *((double*)value);
            break;

        case STRING:

            // Allocation de mémoire pour une chaîne de caractères
            dataframe->columns[num_col]->data[num_row] = malloc(strlen((char*)value) + 1); // +1 pour le caractère de fin de chaîne nulle

            if (dataframe->columns[num_col]->data[num_row] == NULL)
            {
                printf("\nErreur d'allocation mémoire pour la cellule de type STRING du tableau de données\n");
                return 0;
            }

            // Copie de la chaîne de caractères
            strcpy((char*)dataframe->columns[num_col]->data[num_row], (char*)value);

            break;

    case STRUCTURE:
    {
        // Taille de la structure
        size_t struct_size;
        dataframe->columns[num_col]->data[num_row] = malloc(struct_size);
        if (dataframe->columns[num_col]->data[num_row] == NULL) {
            printf("\nErreur d'allocation mémoire pour la cellule de type STRUCTURE du tableau de données\n");
            return 0;
        }

        // Copie de la structure
        memcpy(dataframe->columns[num_col]->data[num_row], value, struct_size);

        break;
    }

    default:

        // Type de colonne non pris en charge
        printf("\nErreur: Ce type de colonne n'est pas reconnu\n");
        return 0;
    }
}

int delete_cdataframe(DATAFRAME2* dataframe)
// Supprimer completement un dataframe et récuperer tout l'espace mémoire alloué
{
    for (int i = 0; i < dataframe->size; i++)
    {
        for (int j = 0; j < dataframe->columns[0]->size; j++)
        { 
            // Liberer le contenu de la cell
            free(dataframe->columns[i]->data[j]);

            // Liberer le contenu de l'index
            free(dataframe->columns[i]->index[j]);
        }

        // Liberer la memoire du tab data
        free(dataframe->columns[i]->data);

        // Liberer la memoire de l'index
        dataframe->columns[i]->index;

        // Liberer l'espace alloué à la colonne
        free(dataframe->columns[i]);
    }

    // Libèrer l'espace alloué pour le tableau de pointeurs de colonnes
    free(dataframe->columns);

    // Libèrer l'espace alloué au dataframe
    free(dataframe);

    return 1;
}

void add_row(DATAFRAME2* dataframe)
{
    int new_size = dataframe->columns[0]->size + 1;

    // Allocation de mémoire pour la nouvelle ligne dans chaque colonne
    for (int i = 0; i < dataframe->size; i++)
    {
        COLUMN* colonne = dataframe->columns[i];
         
        // Réallocation de la mémoire pour les données de la colonne
        COL_TYPE** new_data = realloc(colonne->data, new_size * sizeof(COL_TYPE*));
        if (new_data == NULL)
        {
            printf("Erreur d'allocation de mémoire pour la colonne %s lors de l'ajout d'une nouvelle ligne.\n", colonne->title);
            return;
        }

        // Mise à jour de la taille de la colonne et du tab data
        colonne->size = new_size;
        colonne->data = new_data;

        // Allocation de mémoire pour la nouvelle valeur dans la colonne
        COL_TYPE* new_value = malloc(sizeof(COL_TYPE));
        if (new_value == NULL)
        {
            printf("Erreur d'allocation de mémoire pour la nouvelle valeur dans la colonne %s.\n", colonne->title);
            return;
        }

        // Demander à l'utilisateur de saisir la valeur en fonction du type de la colonne
        switch (colonne->column_type)
        {
        case UINT:
            printf("Saisissez une valeur entière non signée pour la colonne %s : ", colonne->title);
            scanf("%u", &(new_value->uint_value));
            break;
        case INT:
            printf("Saisissez une valeur entière pour la colonne %s : ", colonne->title);
            scanf("%d", &(new_value->int_value));
            break;
        case CHAR:
            printf("Saisissez un caractère pour la colonne %s : ", colonne->title);
            scanf(" %c", &(new_value->char_value)); // Utilisez " %c" pour ignorer les espaces vides et les retours chariot résiduels
            break;
        case STRING:
            printf("Saisissez une chaîne de caractères pour la colonne %s : ", colonne->title);
            new_value->string_value = malloc((256) * sizeof(char)); // Vous devrez définir MAX_STRING_LENGTH
            if (new_value->string_value == NULL)
            {
                printf("Erreur d'allocation de mémoire pour la chaîne de caractères dans la colonne %s.\n", colonne->title);
                return;
            }
            scanf("%s", new_value->string_value);
            break;
            // Ajoutez ici d'autres cas pour les autres types de colonnes (FLOAT, DOUBLE, STRUCTURE, etc.) si nécessaire
        default:
            printf("Type de colonne non pris en charge pour la saisie de valeur.\n");
            return;
        }

        // Assigner la nouvelle valeur à la colonne
        colonne->data[new_size - 1] = new_value;
    }
}

void delete_row(DATAFRAME2* dataframe, int index_ligne)
{
    if (index_ligne < 0 || index_ligne >= dataframe->columns[0]->size)
    {
        printf("Indice de ligne invalide.\n");
        return;
    }

    // Parcours de chaque colonne pour libérer la mémoire de la ligne à l'index donné
    for (int i = 0; i < dataframe->size; i++)
    {
        COLUMN* colonne = dataframe->columns[i];

        // Libération de la mémoire de la ligne à l'index donné dans la colonne actuelle
        free(colonne->data[index_ligne]);

        // Déplacement des éléments suivants vers le haut pour remplir le trou laissé par la suppression de la ligne
        for (int j = index_ligne + 1; j < colonne->size; j++)
        {
            colonne->data[j - 1] = colonne->data[j];
        }

        // Réduction de la taille de la colonne
        colonne->size--;
    }
}
 
#pragma endregion Fin CDataframe 2