#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Colonne.h"

void free_ressources(COLONNE** dataframe, int taille_dataframe)
{
    for (int i = 0; i < taille_dataframe; i++) {
        free(dataframe[i]);
    }

    free(dataframe);
}

int main()
{
    // Creer le CDataframe vide
    COLONNE** CDataframe = NULL;
    int taille_CDataframe = 0;

    // Ajouter une colonne au dataframe
    ajouter_colonne(&CDataframe, &taille_CDataframe, "Colonne 1");

    // Ajouter des données à cette colonne
    CDataframe[0]->data[0] = 10;
    CDataframe[0]->data[1] = 20;
    CDataframe[0]->taille_physique = 2;
    CDataframe[0]->taille_logique = 2;

    // Ajouter une colonne au dataframe
    ajouter_colonne(&CDataframe, &taille_CDataframe, "Colonne 2");

    // Ajouter des données à la colonne
    CDataframe[1]->data[0] = 100;
    CDataframe[1]->data[1] = 200;
    CDataframe[1]->taille_physique = 2;
    CDataframe[1]->taille_logique = 2;

    // Afficher colonnes du CDataframe
    afficher_colonne(CDataframe, 0, taille_CDataframe);
    
    afficher_colonne(CDataframe, 1, taille_CDataframe);

    // Recherche d'une valeur dans la colonne
    /*int indice = rechercher_valeur(CDataframe, 0, 20);
    if (indice != -1) {
        printf("La valeur 20 a été trouvée à l'indice %d dans la colonne.\n", indice);
    }
    else {
        printf("La valeur 20 n'a pas été trouvée dans la colonne.\n");
    }*/

    // Libération de la mémoire occupée par les colonnes et le dataframe
    free_ressources(CDataframe, taille_CDataframe);

    return 0;
}