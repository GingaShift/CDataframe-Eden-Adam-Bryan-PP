#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CDataframe.h"

// Fonction servant à sauvegarder un DataFrame dans un fichier CSV
int save_dataframe_to_csv(DATAFRAME2* dataframe, const char* filename, char separator)
{
    if (!dataframe_has_data(dataframe))
        return 0;

    if (separator == NULL)
        separator = ',';

    // Ouvre le fichier en mode écriture
    FILE* file = fopen(filename, "w");

    if (file == NULL)
    {
        fprintf("\n Erreur lors de l'ouverture du fichier %s\n", filename);
        return 0;
    }

    // Écrire le type de la colonne dans le fichier CSV
    fprintf(file, "%s", dataframe->title);

    fprintf(file, "\n");

    // Sauvegarder le type des colonnes du dataframe
    for (int i = 0; i < dataframe->size; i++) {

        // Écrire le type de la colonne dans le fichier CSV
        fprintf(file, "%d", dataframe->columns[i]->column_type);

        // Si ce n'est pas la dernière colonne, ajouter une virgule
        if (i < dataframe->size - 1)
            fprintf(file, "%c", separator);
        else
            fprintf(file, "\n");
    }

    char cur_data[TAILLE_MAX_DATA_STRING];
    int nombre_col = dataframe->size - 1;
    int nombre_lignes = dataframe->columns[0]->max_size-1;

    // Écrit les données du DataFrame dans le fichier CSV, ligne par ligne
    for (int cur_ligne = 0; cur_ligne <= nombre_lignes; cur_ligne++)
    {
        for (int cur_col = 0; cur_col <= nombre_col; cur_col++)
        {
            // Si la colonne contient des données pour cette ligne, les afficher
            if (cur_ligne <= dataframe->columns[cur_col]->size - 1 && dataframe->columns[cur_col]->size > 0)
            {
                convert_value(dataframe->columns[cur_col], cur_ligne, cur_data, sizeof(cur_data));
                fprintf(file, "%s", cur_data);
            }
            else
                fprintf(file, "%s", "NULL");
            
            cur_data[0] = '\0';

            // Tant que la derniere col n'est pas atteinte, ajouter un séparateur
            if (cur_col < nombre_col)
                fprintf(file, "%c", separator);
            else
                // fin de la ligne, inserer un saut de ligne
                fprintf(file, "\n");
        }
    }
    // Ferme le fichier
    fclose(file);

    return 1;
}

// Fonction pour charger un DataFrame à partir d'un fichier CSV avec un séparateur spécifié
DATAFRAME2* load_dataframe_from_csv(const char* dataframe_title, const char* filename, char separator)
{
    FILE* file = fopen(filename, "r"); // Ouvre le fichier en mode lecture

    if (file == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier %s\n", filename);
        return NULL;
    }

    DATAFRAME2* dataframe;

    char line[TAILLE_MAX_DATA_STRING];
    int line_count = 0;

    while (fgets(line, sizeof(line), file))
    {
        char* token;
        if (line_count == 0)
        {
            // Lire les types de colonnes depuis la première ligne
            token = strtok(line, &separator);
            dataframe = create_cdataframe(token);
            if (dataframe == NULL)
            {
                printf("\n Erreur lors du chargement du CDataframe depuis le fichier csv \"%s\"", filename);
                printf("\n Le CDataframe n'a pas pu etre cree");
            }
        }
        if (line_count == 1)
        {
            // Lire les types de colonnes depuis la première ligne
            token = strtok(line, &separator);
            int col_index = 0;
            while (token != NULL)
            {
                ENUM_TYPE column_type = (ENUM_TYPE)atoi(token);
                COLUMN* column = create_column(column_type, "1");
                dataframe->columns[col_index++] = column;
                token = strtok(NULL, &separator);
            }
            dataframe->size = col_index;
        }
        else {
            // Lire les valeurs de données
            int col_index = 0;
            token = strtok(line, &separator);
            while (token != NULL) {
                insert_value_with_memory_management_of_tabs_data_of_columns (dataframe, line_count, token);
                token = strtok(NULL, &separator);
            }
        }
        line_count++;
    }

    fclose(file);
    return 1;
}
