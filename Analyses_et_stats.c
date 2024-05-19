#include "CDataframe.h"
#include "Analyses_et_stats.h"
#include "Divers.h"

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

// Tente de déterminer le type sur lequel pointe le pointeur générique passé en parametre
ENUM_TYPE get_value_type(void* valptr)
{
    if (valptr == NULL)
        return NULLVAL;

    // Essayer de convertir en entier non signé
    if (sscanf((char*)valptr, "%u") == 1)
        return UINT;

    // Essayer de convertir en entier
    if (sscanf((char*)valptr, "%d") == 1)
        return INT;

    // Essayer de convertir en double
    if (sscanf((char*)valptr, "%lf") == 1)
        return DOUBLE;

    // Essayer de convertir en float
    if (sscanf((char*)valptr, "%f") == 1)
        return FLOAT;

    // Essayer de convertir en char
    if (sscanf((char*)valptr, "%c") == 1)
        return CHAR;

    // Si aucune des conversions n'a réussi, il pourrait s'agir d'une chaîne de caractères
    return STRING;
}

int stats_on_value(DATAFRAME2* dataframe, void* pointer_on_value, ENUM_TYPE value_type, OPERATEURS_DE_COMPARAISON comparison_operator)
{
    unsigned int uint_val = 0;
    int int_val = 0;
    char char_val = '\0';
    float float_val = 0.0f;
    double double_val = 0.0;
    char* string_val = NULL;
    //MyStruct val_structure = { 0 }; // Initialisez avec des valeurs par défaut appropriées

    // En fonction de cela, convertir la valeur sur laquelle on souhaite faire des stats dans son type
    // Caster la variable dans le type correspondant
    switch (value_type)
    {
    case UINT:
        uint_val = *(unsigned int*)(pointer_on_value);
        break;
    case INT:
        int_val = *(int*)(pointer_on_value);
        break;
    case CHAR:
        char_val = *(char*)(pointer_on_value);
        break;
    case FLOAT:
        float_val = *(float*)(pointer_on_value);
        break;
    case DOUBLE:
        double_val = *(double*)(pointer_on_value);
        break;
    case STRING:
        string_val = (char*)(pointer_on_value);
        break;
    case STRUCTURE:
        //val_structure = *(MyStruct*)(valptr);  // MyStruct est un type de structure défini par l'utilisateur
        break;
    default:
        break;
    }

    // Parcourir chaque col du dataframe. Si la col en cours correspond au type de la valeur, 
    // on la prend en compte dans la recherche, sinon on passe à la suivante
    int total_occ = 0;

    for (int i = 0; i < dataframe->size; i++)
    {
        COLUMN* col = dataframe->columns[i];

        // Type de col correspond au type de la valeur ?
        // Si oui, comptabiliser le nombre d'occurrences de la valeur dans la col
        // Si non, abandonner l'examen de cette col et passer à la suivante
        if (col->column_type != value_type)
            continue;

        for (int j = 0; j < col->size; j++)
        {
            COL_TYPE* data = col->data[j];

            switch (col->column_type)
            {
            case UINT:
                switch (comparison_operator.Operateur)
                {
                    case SUPERIEUR:
                        if (data->uint_value > uint_val)
                            total_occ++;
                        break;
                    case EGAL:
                        if (data->uint_value == uint_val)
                            total_occ++;
                        break;
                    case INFERIEUR:
                        if (data->uint_value < uint_val)
                            total_occ++;
                        break;
                    default:
                        break;
                }
                break;
            case INT:
                switch (comparison_operator.Operateur)
                {
                case SUPERIEUR:
                    if (data->int_value > int_val)
                        total_occ++;
                    break;
                case EGAL:
                    if (data->int_value == int_val)
                        total_occ++;
                    break;
                case INFERIEUR:
                    if (data->int_value < int_val)
                        total_occ++;
                    break;
                default:
                    break;
                }
                break;
            case CHAR:
                switch (comparison_operator.Operateur)
                {
                case EGAL:
                    if (tolower(data->char_value) == tolower(pointer_on_value))
                        total_occ++;
                    break;
                default:
                    break;
                }
                break;
            case FLOAT:
                switch (comparison_operator.Operateur)
                {
                case SUPERIEUR:
                    if (data->float_value > float_val)
                        total_occ++;
                    break;
                case EGAL:
                    if (data->float_value == float_val)
                        total_occ++;
                    break;
                case INFERIEUR:
                    if (data->float_value < float_val)
                        total_occ++;
                    break;
                default:
                    break;
                }
                break;
            case DOUBLE:
                switch (comparison_operator.Operateur)
                {
                case SUPERIEUR:
                    if (data->double_value > double_val)
                        total_occ++;
                    break;
                case EGAL:
                    if (data->double_value == double_val)
                        total_occ++;
                    break;
                case INFERIEUR:
                    if (data->double_value < double_val)
                        total_occ++;
                    break;
                default:
                    break;
                }
                break;
            case STRING:
                switch (comparison_operator.Operateur)
                {
                    case SUPERIEUR:
                        if (strlen(data->string_value) > strlen((char*)&pointer_on_value))
                            total_occ++;
                        break;
                    case EGAL:
                        if (strlen(data->string_value) == strlen((char*)&pointer_on_value))
                            if(strcmp(data->string_value, (char*)&pointer_on_value) == 0)
                                total_occ++;
                        break;
                    case INFERIEUR:
                        if (strlen(data->string_value) < strlen((char*)&pointer_on_value))
                            total_occ++;
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

    return total_occ;
}

#pragma endregion Fin CDataframe 2

