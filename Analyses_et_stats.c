#include "CDataframe.h"
#include "Analyses_et_stats.h"

int stats_sur_valeur(DATAFRAME* dataframe, int valeur, OPERATEURS_DE_COMPARAISON operateur_de_comparaison)
{
    int total = 0;

    for (int i = 0; i < dataframe->taille; i++) {

        for (int j = 0; j < dataframe->colonnes[i]->taille_logique; j++) {

            switch (operateur_de_comparaison.Operateur)
            {
                case SUPERIEUR:
                    if (dataframe->colonnes[i]->data[j] > valeur)
                        total++;
                    break;
                case EGAL:
                    if (dataframe->colonnes[i]->data[j] == valeur)
                        total++;
                    break;
                case INFERIEUR:
                    if (dataframe->colonnes[i]->data[j] < valeur)
                        total++;
                    break;
                default:
                    break;
            }
        }
    }
    return total;
}
