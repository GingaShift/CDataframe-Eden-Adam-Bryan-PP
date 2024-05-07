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
        printf("\nErreur d'allocation de m�moire pour la nouvelle colonne.\n");
        return 0;
    }

    // Initialisation de la nouvelle colonne
    strncpy(nouvelle_colonne->titre, titre, sizeof(nouvelle_colonne->titre) - 1);
    nouvelle_colonne->titre[sizeof(nouvelle_colonne->titre) - 1] = '\0'; // Assure la terminaison de la cha�ne
    nouvelle_colonne->data = NULL;
    nouvelle_colonne->taille_physique = 0;
    nouvelle_colonne->taille_logique = 0;

    return nouvelle_colonne;
}

int inserer_valeur(COLONNE* colonne, int valeur, bool* bloc_lignes_ajoute_a_colonne)
{
    (*bloc_lignes_ajoute_a_colonne) = false;
    
    // V�rifier si le tableau data est vide
    if (colonne->data == NULL)
    {
        // Allouer de la m�moire pour un tableau de X entiers
        colonne->data = malloc(NOMBRE_CELLULES_PAR_BLOC_DATA_COLONNE * sizeof(int));

        if (colonne->data == NULL)
        {
            printf("\nErreur d'allocation m�moire lors de la cr�ation du tableau data de la colonne\n");
            return 0;
        }

        colonne->taille_physique = NOMBRE_CELLULES_PAR_BLOC_DATA_COLONNE;

        (*bloc_lignes_ajoute_a_colonne) = true;
    }
    // V�rifier si le tableau data est plein
    else if (colonne->taille_logique == colonne->taille_physique)
    {
        // Si le tableau de data est plein, augmenter la taille physique du tableau data par tranche de 256
        int nouvelle_taille = colonne->taille_physique + NOMBRE_CELLULES_PAR_BLOC_DATA_COLONNE;
        
        // Creation du nouveau tableau (compos� de l'ancien tableau auquel on ajoute le bloc de nouvelles lignes vierges) 
        int* nouveau_data = realloc(colonne->data, nouvelle_taille * sizeof(int));
        if (nouveau_data == NULL)
        {
            printf("\nErreur de r�allocation de m�moire lors de l'extension du tableau data de la colonne.\n");
            return 0;
        }
        
        // Assignation du tableau "agrandi"
        colonne->data = nouveau_data;

        // Mise � jour de la taille physique du tableau
        colonne->taille_physique = nouvelle_taille;

        // Savoir qu'il faudra mettre � jour toutes les autres colonnes � la sortie de la fonction afin de preserver la matrice du dataframe
        (*bloc_lignes_ajoute_a_colonne) = true;
    }

    // Ins�rer la valeur dans le tableau data et mettre � jour la taille logique
    colonne->data[colonne->taille_logique] = valeur;
    colonne->taille_logique++;
    
    return 1;
}

int liberer_ressources_colonne(COLONNE* colonne)
{
    // Lib�rer les donn�es de la colonne
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
        printf("\nLa colonne %s ne contient aucunes donn�es\n\n", colonne->titre);
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
    // Allocation de m�moire pour la colonne
    COLUMN* new_column = (COLUMN*)malloc(sizeof(COLUMN));
    if (new_column == NULL)
    {
        printf("Erreur d'allocation memoire lors de la creation de la colonne\n");
        return NULL;
    }

    // Allocation de m�moire pour le titre de la colonne
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

    // Retourne le pointeur vers la colonne cr��e
    return new_column;
}

int insert_value(COLUMN* col, void* value)
{
    // Retourne 0 si le pointeur de colonne ou la valeur est NULL
    if (col == NULL)
    {
        printf("\nLa colonne n'existe pas, impopssible d'y ajouter la valeur specifiee\n");
        return 0;
    }

    if (col->data == NULL)
    {
        col->data = malloc(NOMBRE_CELLULES_PAR_BLOC_DATA_COLONNE * sizeof(COL_TYPE*));
        if (col->data == NULL)
        {
            printf("\nErreur d'allocation m�moire lors de la cr�ation du tableau data de la colonne\n");
            return 0;
        }
        col->max_size = NOMBRE_CELLULES_PAR_BLOC_DATA_COLONNE;

        // TODO: faire malloc pour index
    }

    // V�rifie si le tableau de donn�es de la colonne est plein
    if (col->size == col->max_size)
    {
        // Si oui, r�allocation de m�moire pour augmenter la capacit� de la colonne en y ajoutant un bloc de donn�es
        col->max_size += NOMBRE_CELLULES_PAR_BLOC_DATA_COLONNE;
        
        col->data = realloc(col->data, col->max_size * sizeof(COL_TYPE*));
        if (col->data == NULL) {
            printf("\nErreur de r�allocation de m�moire lors de l'extension du tableau data de la colonne\n");
            return 0;
        }

        // TODO: faire realloc pour index

    }

    // Allocation de m�moire pour stocker la nouvelle valeur dans la colonne
    switch (col->column_type)
    {

        // TODO: Ajoutez les autres types

        case INT:

            col->data[col->size] = (int*)malloc(sizeof(int));
            if (col->data[col->size] == NULL)
            {
                printf("\nErreur d'allocation memoire pour la cellule du tableau de donnees\n");
                return 0;
            }

            // Renseigner la valeur pass�e en param ou mettre NULL si inexistante
            if (value != NULL)
                *((int*)col->data[col->size]) = *((int*)value);
            else
                col->data[col->size] = NULL;

            // TODO: renseigne l'index
            // col->index[]...

            break;

    default:
        // Type de colonne non pris en charge
        return 0;
    }

    // Incr�mente la taille logique de la colonne
    col->size++;

    // Retourne 1 pour indiquer que la valeur a �t� ins�r�e avec succ�s
    return 1;
}

#pragma endregion Fin CDataframe 2
