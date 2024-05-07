#include "CDataframe.h"
#include "Analyses_et_stats.h"

//OPERATEURS_DE_COMPARAISON egal = { EGAL };
//OPERATEURS_DE_COMPARAISON superieur = { SUPERIEUR };
//OPERATEURS_DE_COMPARAISON inferieur = { INFERIEUR };

// Exemple d'appel:
//stats_sur_valeur(CDataframe, taille_CDataframe, 10, egal);

int stats_sur_valeur(DATAFRAME1* dataframe, int valeur, OPERATEURS_DE_COMPARAISON operateur_de_comparaison)
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
