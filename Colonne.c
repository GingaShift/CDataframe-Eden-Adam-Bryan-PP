#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Colonne.h"
#include "Main.h"
#include "Divers.h"

#pragma region CDataframe 1

COLONNE* creer_colonne(const char* titre)
{
    COLONNE* nouvelle_colonne = malloc(sizeof(COLONNE));
    if (nouvelle_colonne == NULL) {
        printf("\nErreur d'allocation de mémoire pour la nouvelle colonne.\n");
        return 0;
    }

    // Initialisation de la nouvelle colonne
    strncpy(nouvelle_colonne->titre, titre, sizeof(nouvelle_colonne->titre) - 1);
    nouvelle_colonne->titre[sizeof(nouvelle_colonne->titre) - 1] = '\0'; // Assure la terminaison de la chaîne
    nouvelle_colonne->data = NULL;
    nouvelle_colonne->taille_physique = 0;
    nouvelle_colonne->taille_logique = 0;

    return nouvelle_colonne;
}

int inserer_valeur(COLONNE* colonne, int valeur, bool* bloc_cellules_ajoute_a_colonne)
{
    (*bloc_cellules_ajoute_a_colonne) = false;
    
    // Vérifier si le tableau data est vide
    if (colonne->data == NULL)
    {
        // Allouer de la mémoire pour un tableau de X entiers
        colonne->data = malloc(NOMBRE_CELLULES_PAR_BLOC_DATA_COLONNE * sizeof(int));

        if (colonne->data == NULL)
        {
            printf("\nErreur d'allocation mémoire lors de la création du tableau data de la colonne\n");
            return 0;
        }

        colonne->taille_physique = NOMBRE_CELLULES_PAR_BLOC_DATA_COLONNE;

        (*bloc_cellules_ajoute_a_colonne) = true;
    }
    // Vérifier si le tableau data est plein
    else if (colonne->taille_logique == colonne->taille_physique)
    {
        // Si le tableau de data est plein, augmenter la taille physique du tableau data par tranche de 256
        int nouvelle_taille = colonne->taille_physique + NOMBRE_CELLULES_PAR_BLOC_DATA_COLONNE;
        
        // Creation du nouveau tableau (composé de l'ancien tableau auquel on ajoute le bloc de nouvelles lignes vierges) 
        int* nouveau_data = realloc(colonne->data, nouvelle_taille * sizeof(int));
        if (nouveau_data == NULL)
        {
            printf("\nErreur de réallocation de mémoire lors de l'extension du tableau data de la colonne.\n");
            return 0;
        }
        
        // Assignation du tableau "agrandi"
        colonne->data = nouveau_data;

        // Mise à jour de la taille physique du tableau
        colonne->taille_physique = nouvelle_taille;

        // Savoir qu'il faudra mettre à jour toutes les autres colonnes à la sortie de la fonction afin de preserver la matrice du dataframe
        (*bloc_cellules_ajoute_a_colonne) = true;
    }

    // Insérer la valeur dans le tableau data et mettre à jour la taille logique
    colonne->data[colonne->taille_logique] = valeur;
    colonne->taille_logique++;
    
    return 1;
}

int liberer_ressources_colonne(COLONNE* colonne)
{
    // Libérer les données de la colonne
    if (colonne->data != NULL)
        free(colonne->data);
    else
        return 0;

    free(colonne);

    return 1;
}

int afficher_colonne(COLONNE* colonne)
{
    if (colonne == NULL)
    {
        printf("\nLa colonne n'existe pas\n");
        return 0;
    }

    if (colonne->taille_logique == 0)
    {
        printf("\nLa colonne %s ne contient aucunes données\n\n", colonne->titre);
        return 1;
    }

    printf("\nVoici le contenu de la colonne \"%s\" :\n\n", colonne->titre);
    
    for (int i = 0; i < colonne->taille_logique; i++)
        printf("[%d] : %d\n", i, colonne->data[i]);
    
    return 1;
}

#pragma endregion Fin CDataframe 1

#pragma region CDataframe 2

COLUMN* create_column(ENUM_TYPE column_type, char* column_title)
{
    // Allocation de mémoire pour la colonne
    COLUMN* new_column = (COLUMN*)malloc(sizeof(COLUMN));
    if (new_column == NULL)
    {
        printf("Erreur d'allocation memoire lors de la creation de la colonne\n");
        return NULL;
    }

    // Allocation de mémoire pour le titre de la colonne
    new_column->title = (char*)malloc(strlen(column_title) + 1);
    if (new_column->title == NULL)
    {
        printf("Erreur lors de l'allocation memoire du titre de la nouvelle colonne\n");
        return NULL;
    }
    strcpy(new_column->title, column_title);

    // Ini de la taille logique de la colonne
    new_column->size = 0;
    
    // Ini de la taille physique de la colonne
    new_column->max_size = 0;
    
    // Autres ini
    new_column->column_type = column_type;
    new_column->data = NULL;
    new_column->index = NULL;
    new_column->valid_index = 0;
    new_column->index_size = 0;
    new_column->sort_dir = 0;

    // Retourne le pointeur vers la colonne créée
    return new_column;
}

int insert_value(COLUMN* col, void* value, bool* block_cells_added_to_column)
{
    (*block_cells_added_to_column) = false;

    // Retourne 0 si le pointeur de colonne ou la valeur est NULL
    if (col == NULL)
    {
        printf("\nLa colonne n'existe pas, impossible d'y ajouter la valeur specifiee\n");
        return 0;
    }

    if (value == NULL)
    {
        printf("\nLa valeur n'existe pas, ajout impossible.\n");
        return 0;
    }

    int total_number_of_cells = 0;

    if (col->max_size == 0)
    {
        total_number_of_cells = NOMBRE_CELLULES_PAR_BLOC_DATA_COLONNE;

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

        (*block_cells_added_to_column) = true;
    }

    // Vérifie si le tableau de données de la colonne est plein.
    // Si oui, réallocation de mémoire pour augmenter la capacité de la colonne en y ajoutant un bloc de données
    if (col->size == col->max_size)
    {
        total_number_of_cells += col->max_size + NOMBRE_CELLULES_PAR_BLOC_DATA_COLONNE;
        
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

        (*block_cells_added_to_column) = true;
    }

    // Traitement si valeur NULL
    if (value == NULL)
    {
        col->data[col->size] = NULL;
        
        // Renseigner l'index.
        col->index[col->size] = col->size;

        // Augmenter la taille de l'index
        col->index_size += 1;

        // Incrémente la taille logique de la colonne
        col->size++;
        
        return 1;
    }

    // Allocation de mémoire pour stocker le pointeur sur la nouvelle valeur dans la cell de la colonne
    switch (col->column_type)
    {
        case UINT:

            // Allocation de mémoire pour la cell qui va contenir un pointeur sur un type "unsigned int"
            col->data[col->size] = (unsigned int*)malloc(sizeof(unsigned int));
            if (col->data[col->size] == NULL)
            {
                printf("\nErreur d'allocation memoire pour la cellule de type UINT du tableau de donnees\n");
                return 0;
            }

            // Renseigner la valeur passée en param
            *((unsigned int*)col->data[col->size]) = *((unsigned int*)value);

            break;

        case INT:

            col->data[col->size] = (int*)malloc(sizeof(int));
            if (col->data[col->size] == NULL)
            {
                printf("\nErreur d'allocation memoire pour la cellule de type INT du tableau de donnees\n");
                return 0;
            }

            // Renseigner la valeur passée en param
            *((int*)col->data[col->size]) = *((int*)value);

            break;

        case CHAR:

            col->data[col->size] = (char*)malloc(sizeof(char));
            if (col->data[col->size] == NULL)
            {
                printf("\nErreur d'allocation memoire pour la cellule de type CHAR du tableau de donnees\n");
                return 0;
            }

            // Renseigner la valeur passée en param
            *((char*)col->data[col->size]) = *((char*)value);
            
            break;

        case FLOAT:

            col->data[col->size] = (float*)malloc(sizeof(float));
            if (col->data[col->size] == NULL)
            {
                printf("\nErreur d'allocation memoire pour la cellule de type FLOAT du tableau de donnees\n");
                return 0;
            }

            // Renseigner la valeur passée en param
            *((float*)col->data[col->size]) = *((float*)value);

            break;

        case DOUBLE:

            col->data[col->size] = (double*)malloc(sizeof(double));
            if (col->data[col->size] == NULL)
            {
                printf("\nErreur d'allocation memoire pour la cellule de type DOUBLE du tableau de donnees\n");
                return 0;
            }

            // Renseigner la valeur passée en param
            *((double*)col->data[col->size]) = *((double*)value);

            break;

        case STRING:

            // Allocation de mémoire pour une chaîne de caractères
            col->data[col->size] = malloc(strlen((char*)value) + 1); // +1 pour le caractère de fin de chaîne nulle
            
            if (col->data[col->size] == NULL)
            {
                printf("\nErreur d'allocation mémoire pour la cellule de type STRING du tableau de données\n");
                return 0;
            }

            // Copie de la chaîne de caractères
            strcpy((char*)col->data[col->size], (char*)value);
             
            break;
            
        case STRUCTURE:
        {
            col->data[col->size] = (void*)malloc(sizeof(value));
            if (col->data[col->size] == NULL)
            {
                printf("\nErreur d'allocation mémoire pour la cellule de type STRUCTURE du tableau de données\n");
                return 0;
            }

            // Renseigner la valeur passée en param
            col->data[col->size] = value;
        
            break;
         }

    default:
        // Type de colonne non pris en charge
        return 0;
    }

    // Renseigner l'index associé à cette valeur
    col->index[col->size] = col->size;

    // Augmenter la taille de l'index
    col->index_size += 1;

    // Incrémente la taille logique de la colonne
    col->size++;

    // Retourne 1 pour indiquer que la valeur a été insérée avec succès
    return 1;
}

// Convertir une valeur en chaîne de caractères
int convert_value(COLUMN* col, unsigned long long int num_ligne, char* str, int size)
{
    // Retourne si le pointeur de colonne est NULL ou si la position est invalide
    if (col == NULL)
    {
        printf("\nLa colonne n'existe pas, operation de conversion impossible\n");
        return 0;
    }

    if (str == NULL)
    {
        printf("\nla string de destination passee en parametre n'existe pas, operation de conversion impossible\n");
        return 0;
    }

    if (num_ligne >= col->size)
    {
        printf("\nLe numero de cellule est invalide car il ne contient pas de donnee, operation de conversion impossible\n");
        return 0;
    }

    if (col->data[num_ligne] == NULL)
    {
        snprintf(str, size, "%s", "NULL");
        return 1;
    }

    // Utilisation de sprintf pour convertir la valeur en chaîne de caractères
    switch (col->column_type)
    {
        case UINT:

            //snprintf(str, size, "%u", *((unsigned int*)col->data[num_ligne]));
            snprintf(str, size, "%u", *((unsigned int*)col->data[col->index[num_ligne]]));
            break;

        case INT:

            // ori non trié: snprintf(str, size, "%d", *((int*)col->data[num_ligne]));
            
            // col trié sur index:
            snprintf(str, size, "%d", *((int*)col->data[col->index[num_ligne]]));

            // Autre version possible:
            //snprintf(str, size, "%d", col->data[col->index[num_ligne]]->int_value);

            break;

        case CHAR:
            //snprintf(str, size, "%c", col->data[num_ligne]->char_value);
            snprintf(str, size, "%c", col->data[col->index[num_ligne]]->char_value);
            break;

        case FLOAT:
            snprintf(str, size, "%.5f", *((float*)col->data[col->index[num_ligne]]));
            break;

        case DOUBLE:
            //snprintf(str, size, "%lf", *((double*)col->data[num_ligne]));
            snprintf(str, size, "%.3lf", *((double*)col->data[col->index[num_ligne]]));
            break;

        case STRING:
            snprintf(str, size, "%s", (char*)col->data[col->index[num_ligne]]);
            break;

        case STRUCTURE:

            // Adresse de la structure
            snprintf(str, size, "%p", col->data[col->index[num_ligne]]->struct_value);
            break;

        default:
            // Type de colonne non pris en charge
            snprintf(str, size, "Unsupported type");
        }

    return 1;
}

int print_column(COLUMN* col, bool show_column_title, int number_of_rows_to_show)
{
    // Retourne si le pointeur de colonne est NULL ou si la position est invalide
    if (col == NULL)
    {
        printf("\n La colonne n'existe pas\n");
        return 0;
    }

    if (col->size == 0)
    {
        printf("\n La colonne ne contient pas de données\n");
        return 0;
    }

    if (number_of_rows_to_show == NO_LIMIT)
        number_of_rows_to_show = col->size;
    
    if (number_of_rows_to_show > col->size)
    {
        printf("\n Impossible de mener a bien votre requete car le nombre de cellules que vous souhaitez afficher pour la colonne \"%s\" est %d or le nombre de cellules disponibles est plus petit: %d\n", col->title, number_of_rows_to_show, col->size);
        return 0;
    }

    if (show_column_title)
    {
        printf("\n Contenu de la colonne \"%s\" :\n", col->title);
    }
    
    char* str[TAILLE_MAX_DATA_STRING];

    for (int i = 0; i < number_of_rows_to_show; i++)
    {
        convert_value(col, i, str, sizeof(str));
        // Ne jamais afficher l'index, seulement le num sequentiel de la boucle for, tout simplement
        printf("\n   [%d] %s", i, str);
        str[0] = "\0";
    }

    if (number_of_rows_to_show == 1)
        printf("\n\n Une cellule a ete affichee pour la colonne \"%s\"", col->title);
    else if (number_of_rows_to_show > 1)
        printf("\n\n %d cellules ont ete affichees pour la colonne \"%s\"", number_of_rows_to_show, col->title);

    return 1;
}

int print_col_by_index(COLUMN* col)
{
    // Vérifier si la colonne est vide
    if (col->size == 0)
    {
        printf("La colonne est vide.\n");
        return 0;
    }
    
    // Parcourir le tableau index et afficher les valeurs correspondantes dans l'ordre
    for (int i = 0; i < col->size; i++)
    {
        // Récupérer l'index de la valeur actuelle
        unsigned long long int index = col->index[i];

        // Afficher la valeur correspondante dans le tableau data
        switch (col->column_type)
        {
            case INT:
                printf("   [%d] %d ", i, col->data[index]->int_value);
                break;
            case UINT:
                printf("   [%d] %u ", i, col->data[index]->uint_value);
                break;
            case CHAR:
                printf("   [%d] %c ", i, col->data[index]->char_value);
                break;
            case FLOAT:
                printf("   [%d] %f ", i, col->data[index]->float_value);
                break;
            case DOUBLE:
                printf("   [%d] %lf ", i, col->data[index]->double_value);
                break;
            case STRING:
                printf("   [%d] %s ", i, col->data[index]->string_value);
                break;
            case STRUCTURE:
                printf("   [%d] %s ", i, col->data[index]->struct_value);
                break;
            default:
                printf("Type de donnees non geree");
        }
    
        printf("\n");
    }

    return 1;
}

const char* enum_to_string(ENUM_TYPE value)
{
    switch (value)
    {
        case NULLVAL: return "NULLVAL";
        case UINT: return "UINT";
        case INT: return "INT";
        case CHAR: return "CHAR";
        case FLOAT: return "FLOAT";
        case DOUBLE: return "DOUBLE";
        case STRING: return "STRING";
        case STRUCTURE: return "STRUCTURE";
        default: return "Unknown";
    }
}

#pragma endregion Fin CDataframe 2
