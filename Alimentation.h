#pragma once
#include "CDataframe.h"
#include "Colonne.h"

int ajouter_colonne(DATAFRAME* dataframe, const char* nom_colonne);

int populate_dataframe_artificially(DATAFRAME* dataframe);