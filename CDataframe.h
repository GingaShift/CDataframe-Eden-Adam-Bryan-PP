#pragma once
#include <stdio.h>
#include "Colonne.h"
#include "Divers.h"

#define NOMBRE_CHAR_MAX_NOM_DATAFRAME 256
#define TAILLE_MAX_DATA_STRING 256
#define NOMBRE_TYPE_COL 8

#pragma region CDataframe 1

typedef struct Dataframe1
{
    char titre[NOMBRE_CHAR_MAX_NOM_DATAFRAME];
    int taille;
    COLONNE** colonnes;
} DATAFRAME1;

DATAFRAME1* creer_cdataframe(bool* dataframe_exists, const char* nom_dataframe);

int ajouter_colonne(DATAFRAME1* dataframe, const char* nom_colonne);

int renommer_colonne(DATAFRAME1* dataframe, int num_colonne, const char* nouveau_nom);

int supprimer_colonne(DATAFRAME1* dataframe, int num_col);

int nom_colonne_existe(DATAFRAME1* dataframe, char* nom_colonne, int taille_CDataframe);

int inserer_valeur_avec_gestion_memoire_data_colonnes(DATAFRAME1* dataframe, int num_col, int valeur);

int egaliser_taille_des_tabs_data_des_colonnes(DATAFRAME1* dataframe);

int afficher_nombre_colonnes(DATAFRAME1* dataframe);

int afficher_noms_colonnes(DATAFRAME1* dataframe);

int afficher_les_colonnes(DATAFRAME1* dataframe);

int afficher_cdataframe(DATAFRAME1* dataframe, int num_col_max, int int_num_ligne_max);

int obtenir_nombre_lignes(DATAFRAME1* dataframe);

int modifier_valeur(DATAFRAME1* dataframe, int num_col, int num_ligne, int valeur);

int afficher_valeur(DATAFRAME1* dataframe, int num_col, int num_ligne);

int ajouter_valeur_par_utilisateur(DATAFRAME1* dataframe, int num_col, int valeur);

void ajouter_ligne(DATAFRAME1* dataframe);

#pragma endregion Fin CDataframe 1

#pragma region CDataframe 2

typedef struct Dataframe2
{
    char title[NOMBRE_CHAR_MAX_NOM_DATAFRAME];
    int size;
    COLUMN** columns;
} DATAFRAME2;

DATAFRAME2* create_cdataframe(char* dataframe_title);

int add_column(DATAFRAME2* dataframe, ENUM_TYPE column_type, const char* column_title);

int rename_column(DATAFRAME2* dataframe, int column_num, char* new_name);

int delete_column(DATAFRAME2* dataframe, int num_col);

int column_name_exists(DATAFRAME2* dataframe, char* column_name);

int insert_value_with_memory_management_of_tabs_data_of_columns(DATAFRAME2* dataframe, int num_col, void* value);

int equalize_size_of_tabs_data_of_columns(DATAFRAME2* dataframe);

int print_number_of_columns(DATAFRAME2* dataframe);

int print_name_and_type_of_columns(DATAFRAME2* dataframe);

int print_columns(DATAFRAME2* dataframe);

int show_cdataframe(DATAFRAME2* dataframe, int num_col_max_to_show, int num_ligne_max_to_show);

int get_number_of_rows_storing_data(DATAFRAME2* dataframe);

int get_number_of_rows(DATAFRAME2* dataframe);

int print_value(DATAFRAME2* dataframe, int num_col, int num_ligne);

int change_value(DATAFRAME2* dataframe, int num_col, int num_row, void* value);

int delete_cdataframe(DATAFRAME2** dataframe);

int add_data_manually_in_column(DATAFRAME2* dataframe, int num_col);

int add_a_row_manually(DATAFRAME2* dataframe);

int delete_row(DATAFRAME2* dataframe, int index_ligne);

int dataframe_has_data(DATAFRAME2* dataframe);

#pragma endregion Fin CDataframe 2