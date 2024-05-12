#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CDataframe.h"

// Fonction destin�e � sauvegarder les types de chaque colonne dans un fichier CSV
void sauvegarder_types_colonnes_dans_fichier_csv(DATAFRAME2* dataframe, const char* nom_fichier)
{
    FILE* fichier = fopen(nom_fichier, "w");
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
            fprintf(fichier, ", ");
        }
    }

    fclose(fichier);
}

// Fonction servant � sauvegarder un DataFrame dans un fichier CSV
void save_to_csv(DATAFRAME2* dataframe, const char* filename)
{
    FILE* file = fopen(filename, "w"); // Ouvre le fichier en mode �criture

    if (file == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier %s\n", filename);
        return;
    }

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
                fprintf(file, ",");
            }
        }
        fprintf(file, "\n");
    }

    fclose(file); // Ferme le fichier
}

void convertir_val_num_en_lib_type_colonne()
{

}