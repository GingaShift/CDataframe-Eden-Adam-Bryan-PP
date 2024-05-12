#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CDataframe.h"

// Fonction destin�e � sauvegarder les types de chaque colonne dans un fichier CSV
void sauvegarder_types_colonnes_dans_fichier(DATAFRAME2* dataframe, const char* filename, char* separateur)
{
    FILE* fichier = fopen(filename, "w");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    // Parcourir chaque colonne du DataFrame
    for (int i = 0; i < dataframe->size; i++) {
        
        // �crire le type de la colonne dans le fichier CSV
        fprintf(fichier, "%d", dataframe->columns[i]->column_type);

        // Si ce n'est pas la derni�re colonne, ajouter une virgule
        if (i < dataframe->size - 1) {
            fprintf(fichier, separateur);
        }
    }

    fclose(fichier);
}

// Fonction servant � sauvegarder un DataFrame dans un fichier CSV
void save_dataframe_to_csv(DATAFRAME2* dataframe, const char* filename, char* separateur)
{
    FILE* file = fopen(filename, "w"); // Ouvre le fichier en mode �criture

    if (file == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier %s\n", filename);
        return;
    }

    // Sauvegarder le type des colonnes du dataframe
    sauvegarder_types_colonnes_dans_fichier(dataframe, filename, separateur);

    char cur_data = "";

    // �crit les donn�es du DataFrame dans le fichier CSV
    for (int i = 0; i < dataframe->size; i++)
    {
        for (int j = 0; j < dataframe->columns; j++)
        {
            // Parcourir l'ensemble des lignes du dataframe, et stocker chaque donn�e trouv�e dans chaque col composant cette ligne, au fur et � mesure

            // (Utiliser convert)
            //fprintf(file, "%s", dataframe->data[i * dataframe->columns + j]);
            
            // Tant que la derniere col n'est pas atteinte, ajouter un s�parateur, sinon aller se faire voir
            if (j < dataframe->size - 1)
            {
                fprintf(file, separateur);
            }
        }
        fprintf(file, "\n");
    }

    fclose(file); // Ferme le fichier
}

// Fonction pour charger un DataFrame � partir d'un fichier CSV avec un s�parateur sp�cifi�
DATAFRAME2* load_dataframe_from_csv(const char* dataframe_title, const char* filename, char separator)
{

    FILE* file = fopen(filename, "r"); // Ouvre le fichier en mode lecture

    if (file == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier %s\n", filename);
        return NULL;
    }

    // Compte le nombre de lignes et de colonnes dans le fichier CSV
    int rows = 0;
    int cols = 0;
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        rows++;
        char* token = strtok(buffer, &separator);
        int col_count = 0;
        while (token != NULL)
        {
            col_count++;
            token = strtok(NULL, &separator);
        }
        if (cols == 0) {
            cols = col_count;
        }
        else if (cols != col_count) {
            fprintf(stderr, "Erreur : Les lignes du fichier CSV n'ont pas le m�me nombre de colonnes\n");
            fclose(file);
            return NULL;
        }
    }

    // R�initialise la position du curseur de fichier au d�but
    fseek(file, 0, SEEK_SET);

    // Alloue de la m�moire pour le DataFrame
    DATAFRAME2* dataframe = create_cdataframe(dataframe_title);
    
    dataframe->size = rows;
    /*dataframe->cols = cols;
    dataframe->data = (char**)malloc(rows * cols * sizeof(char*));
    if (dataframe->data == NULL) {
        printf("\nErreur lors de l'allocation de m�moire pour le DataFrame\n");
        fclose(file);
        free(dataframe);
        return NULL;
    }*/

    // Lit les donn�es du fichier CSV et les stocke dans le DataFrame
    int row = 0;
    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        int col = 0;
        char* token = strtok(buffer, &separator);
        while (token != NULL) {
            dataframe->columns[col] = strdup(token);
            col++;
            token = strtok(NULL, &separator);
        }
        row++;
    }

    fclose(file); // Ferme le fichier

    return dataframe;
}
