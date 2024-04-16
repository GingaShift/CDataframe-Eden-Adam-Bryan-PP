#pragma once

typedef enum {
    SUPERIEUR,
    EGAL,
    INFERIEUR
} OPERATEURS_COMPARAISON;

typedef struct {
    OPERATEURS_COMPARAISON Operateur;
} OPERATEURS_DE_COMPARAISON;

int stats_sur_valeur(COLONNE** CDataframe, int taille_dataframe, int valeur, OPERATEURS_DE_COMPARAISON operateur_de_comparaison);