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

int stats_sur_valeur(DATAFRAME1* dataframe, int valeur, OPERATEURS_DE_COMPARAISON operateur_de_comparaison);