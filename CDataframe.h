#pragma once
#include <stdio.h>
#include "Colonne.h"

int obtenir_nombre_colonnes(int taille_dataframe);

int obtenir_nombre_lignes(COLONNE** dataframe, int taille_dataframe);

int ajouter_bloc_lignes_aux_colonnes(COLONNE** dataframe, int taille_dataframe, int* num_colonne_a_ignorer);

int inserer_valeur_avec_gestion_memoire_data_colonnes(COLONNE*** dataframe, int* taille_dataframe, int num_col, int valeur);

int nom_colonne_existe(COLONNE** dataframe, const char* nom_colonne, int taille_CDataframe);