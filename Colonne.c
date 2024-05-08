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
    {
        printf("[%d] : %d\n", i, colonne->data[i]);
    }
    
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

    // Retourne le pointeur vers la colonne créée
    return new_column;
}

int insert_value(COLUMN* col, void* value, bool* bloc_lignes_ajoute_a_colonne)
{
    (*bloc_lignes_ajoute_a_colonne) = false;
    
    // Retourne 0 si le pointeur de colonne ou la valeur est NULL
    if (col == NULL)
    {
        printf("\nLa colonne n'existe pas, impossible d'y ajouter la valeur specifiee\n");
        return 0;
    }

    if (col->data == NULL)
    {
        // creation du tab de données (vide)
        col->data = malloc(NOMBRE_CELLULES_PAR_BLOC_DATA_COLONNE * sizeof(COL_TYPE*));
        if (col->data == NULL)
        {
            printf("\nErreur d'allocation mémoire lors de la création du tab data de la colonne\n");
            return 0;
        }

        // creation du tab d'index pour le tab de données (vide)
        col->index = malloc(NOMBRE_CELLULES_PAR_BLOC_DATA_COLONNE * sizeof(unsigned long long int*));
        if (col->index == NULL)
        {
            printf("\nErreur d'allocation mémoire lors de la création du tab d'index pour le tab data de la colonne\n");
            return 0;
        }

        col->max_size = NOMBRE_CELLULES_PAR_BLOC_DATA_COLONNE;

        (*bloc_lignes_ajoute_a_colonne) = true;
    }

    // Vérifie si le tableau de données de la colonne est plein
    if (col->size == col->max_size)
    {
        // Si oui, réallocation de mémoire pour augmenter la capacité de la colonne en y ajoutant un bloc de données
        col->max_size += NOMBRE_CELLULES_PAR_BLOC_DATA_COLONNE;
        
        col->data = realloc(col->data, col->max_size * sizeof(COL_TYPE*));
        if (col->data == NULL) {
            printf("\nErreur de réallocation de mémoire lors de l'extension du tableau data de la colonne\n");
            return 0;
        }

        // Réallocation de mémoire afin d'augmenter la capacité du tab d'index pour le tab de données
        col->index = realloc(col->index, col->max_size * sizeof(unsigned long long int*));
        if (col->index == NULL) {
            printf("\nErreur de réallocation de mémoire lors de l'extension du tab d'index pour le tab de données\n");
            return 0;
        }

        (*bloc_lignes_ajoute_a_colonne) = true;
    }

    // Allocation de mémoire pour stocker la nouvelle valeur dans la colonne
    switch (col->column_type)
    {
        // TODO: Ajoutez les autres cas des autres types:
        // UINT, INT, CHAR, FLOAT, DOUBLE, STRING, STRUCTURE

    case UINT:

        col->data[col->size] = (int*)malloc(sizeof(int));
        if (col->data[col->size] == NULL)
        {
            printf("\nErreur d'allocation memoire pour la cellule du tableau de donnees\n");
            return 0;
        }

        // Renseigner la valeur passée en param et l'index ou mettre NULL si inexistante
        if (value != NULL)
            *((unsigned int*)col->data[col->size]) = *((unsigned int*)value);
        else
            col->data[col->size] = NULL;

        // Renseigner l'index.
        col->index[col->size] = col->size;

        break;

        case INT:

            col->data[col->size] = (int*)malloc(sizeof(int));
            if (col->data[col->size] == NULL)
            {
                printf("\nErreur d'allocation memoire pour la cellule du tableau de donnees\n");
                return 0;
            }

            // Renseigner la valeur passée en param et l'index ou mettre NULL si inexistante
            if (value != NULL)
                *((int*)col->data[col->size]) = *((int*)value);
            else
                col->data[col->size] = NULL;

            // Renseigner l'index
            col->index[col->size] = col->size;

            break;

    default:
        // Type de colonne non pris en charge
        return 0;
    }

    // Incrémente la taille logique de la colonne
    col->size++;

    // Retourne 1 pour indiquer que la valeur a été insérée avec succès
    return 1;
}


// Convertir une valeur en chaîne de caractères
void convert_value(COLUMN* col, unsigned long long int num_ligne, char* str, int size)
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

    // Utilisation de sprintf pour convertir la valeur en chaîne de caractères
    switch (col->column_type)
    {
    case UINT:

        snprintf(str, size, "%u", *((unsigned int*)col->data[num_ligne]));
        
        break;

    case INT:

        // Ori Efrei:
        snprintf(str, size, "%d", *((int*)col->data[num_ligne]));

        // Autre version possible:
        //snprintf(str, size, "%d", col->data[num_ligne]->int_value);

        break;

    case CHAR:

        snprintf(str, size, "%c", col->data[num_ligne]->char_value);
        break;

    case FLOAT:

        snprintf(str, size, "%f", col->data[num_ligne]->float_value);
        break;

    case DOUBLE:

        snprintf(str, size, "%lf", col->data[num_ligne]->double_value);
        break;

    case STRING:

        snprintf(str, size, "%s", col->data[num_ligne]->string_value);
        break;

    case STRUCTURE:

        // Adresse de la structure
        snprintf(str, size, "%p", col->data[num_ligne]->struct_value);
        break;

    default:
        // Type de colonne non pris en charge
        snprintf(str, size, "Unsupported type");
    }
}

#pragma endregion Fin CDataframe 2
