#include "CDataframe.h"
#include "Analyses_et_stats.h"

//OPERATEURS_DE_COMPARAISON egal = { EGAL };
//OPERATEURS_DE_COMPARAISON superieur = { SUPERIEUR };
//OPERATEURS_DE_COMPARAISON inferieur = { INFERIEUR };

// Exemple d'appel:
//stats_sur_valeur(CDataframe, taille_CDataframe, 10, egal);

#pragma region CDataframe 1

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

#pragma endregion Fin CDataframe 1

#pragma region CDataframe 2

int stats_on_value(DATAFRAME2* dataframe, void* valeur, OPERATEURS_DE_COMPARAISON operateur_de_comparaison)
{
    // Déduire tout d'abord le type de la valeur sur lequel pointe le pointeur

    ENUM_TYPE type_valeur;
    type_valeur = INT;

    int total = 0;

    for (int i = 0; i < dataframe->size; i++)
    {
        COLUMN* colonne = dataframe->columns[i];

        for (int j = 0; j < colonne->size; j++)
        {
            COL_TYPE* data = colonne->data[j];

            switch (colonne->column_type)
            {
                case UINT:
                    switch (operateur_de_comparaison.Operateur)
                    {
                        case SUPERIEUR:
                            if (data->uint_value > valeur)
                                total++;
                            break;
                        case EGAL:
                            if (data->uint_value == valeur)
                                total++;
                            break;
                        case INFERIEUR:
                            if (data->uint_value < valeur)
                                total++;
                            break;
                    default:
                        break;
                }
                break;

            case INT:
                switch (operateur_de_comparaison.Operateur)
                {
                    case SUPERIEUR:
                        if (data->int_value > valeur)
                            total++;
                        break;
                    case EGAL:
                        if (data->int_value == valeur)
                            total++;
                        break;
                    case INFERIEUR:
                        if (data->int_value < valeur)
                            total++;
                        break;
                    default:
                        break;
                }
                break;

            case CHAR:
                switch (operateur_de_comparaison.Operateur)
                {
                    case EGAL:
                        if (tolower(data->char_value) == tolower(valeur))
                            total++;
                        break;
                    default:
                        break;
                }
                break;

            case STRING:
                switch (operateur_de_comparaison.Operateur)
                {
                    case SUPERIEUR:
                        if (strlen(data->string_value) > strlen((char*)&valeur))
                            total++;
                        break;
                    case EGAL:
                        if (strlen(data->string_value) == strlen((char*)&valeur))
                            total++;
                        break;
                    case INFERIEUR:
                        if (strlen(data->string_value) < strlen((char*)&valeur))
                            total++;
                        break;
                    default:
                        break;
                }
                break;

            default:
                break;
            }
        }
    }

    return total;
}

#pragma endregion Fin CDataframe 2

