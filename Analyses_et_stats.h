#pragma once
#include "CDataframe.h"

typedef enum
{
    SUPERIEUR,
    EGAL,
    INFERIEUR
} OPERATEURS_COMPARAISON;

typedef struct
{
    OPERATEURS_COMPARAISON Operateur;
} OPERATEURS_DE_COMPARAISON;

#pragma region CDataframe 1

int stats_sur_valeur(DATAFRAME1* dataframe, int valeur, OPERATEURS_DE_COMPARAISON operateur_de_comparaison);

#pragma endregion Fin CDataframe 1

#pragma region CDataframe 2

int stats_on_value(DATAFRAME2* dataframe, void* valeur, OPERATEURS_DE_COMPARAISON operateur_de_comparaison);

#pragma endregion Fin CDataframe 2