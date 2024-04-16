#include <stdio.h>
#include "Colonne.h"
#include "Analyses_et_stats.h"

int stats_sur_valeur(COLONNE** CDataframe, int taille_dataframe, int valeur, OPERATEURS_DE_COMPARAISON operateur_de_comparaison)
{
    int total = 0;

    for (int i = 0; i < taille_dataframe; i++) {

        for (int j = 0; j < CDataframe[i]->taille_logique; j++) {

            switch (operateur_de_comparaison.Operateur)
            {
                case SUPERIEUR:
                    if (CDataframe[i]->data[j] > valeur)
                        total++;
                    break;
                case EGAL:
                    if (CDataframe[i]->data[j] == valeur)
                        total++;
                    break;
                case INFERIEUR:
                    if (CDataframe[i]->data[j] < valeur)
                        total++;
                    break;
                default:
                    break;
            }
        }
    }
    return total;
}
