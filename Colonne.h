#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Divers.h">

#define NOMBRE_CELLULES_PAR_BLOC_DATA_COLONNE 256
#define VALEUR_PAR_DEFAUT_DATA_COLONNE 0
#define NOMBRE_CHAR_MAX_NOM_COLONNE 255

#pragma region CDataframe 1

typedef struct Colonne
{
    char titre[NOMBRE_CHAR_MAX_NOM_COLONNE];
    int* data;
    int taille_physique;
    int taille_logique;
} COLONNE;

COLONNE* creer_colonne(const char* nom);

int inserer_valeur(COLONNE* colonne, int valeur, bool* block_cells_added_to_column);

int liberer_ressources_colonne(COLONNE* colonne);

int afficher_colonne(COLONNE* colonne);

#pragma endregion CDataframe 1

#pragma region CDataframe 2

enum enum_type
{
    NULLVAL = 0, UINT, INT, CHAR, FLOAT, DOUBLE, STRING, STRUCTURE
};
typedef enum enum_type ENUM_TYPE;

union column_type
{
    unsigned int uint_value;
    signed int int_value;
    char char_value;
    float float_value;
    double double_value;
    char* string_value;
    void* struct_value;
};
typedef union column_type COL_TYPE;

typedef struct Column
{
    // Titre de la colonne
    char* title;

    // Taille logique du tab de données (Nombre de données stockées à l'instant T)
    unsigned int size;

    // Taille physique du tab de données (Nombre total de cells dispo)
    unsigned int max_size;

    // Type de données de la colonne
    ENUM_TYPE column_type;

    // Tableau de pointeurs sur les données
    COL_TYPE** data;

    // Tableau d'entiers permettant le trie de la colonne
    unsigned long long int* index;
};
typedef struct Column COLUMN;

COLUMN* create_column(ENUM_TYPE column_type, char* column_title);

int insert_value(COLUMN* col, void* value, bool* block_cells_added_to_column);

int convert_value(COLUMN* col, unsigned long long int num_ligne, char* str, int size);

int print_column(COLUMN* col, bool show_column_title, int number_of_rows_to_show);

int print_col_by_index(COLUMN* colonne);

const char* enum_to_string(ENUM_TYPE value);

#pragma endregion CDataframe 2
