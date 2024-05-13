#pragma once
#include <stdio.h>

const char NOM_FICHIER_CSV[] = "save_dataframe.csv";
const char SEPARATEUR_CSV = ',';

int sauvegarder_types_colonnes_dans_fichier(DATAFRAME2* dataframe, const char* nom_fichier, char* separateur);

int save_dataframe_to_csv(DATAFRAME2* dataframe, const char* filename, char* separateur);

DATAFRAME2* load_dataframe_from_csv(const char* dataframe_title, const char* filename, char separator);