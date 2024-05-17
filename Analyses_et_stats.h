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

int stats_on_value(DATAFRAME2* dataframe, void* pointer_on_value, ENUM_TYPE value_type, OPERATEURS_DE_COMPARAISON comparison_operator);

ENUM_TYPE get_value_type(void* valeur);

#pragma endregion Fin CDataframe 2