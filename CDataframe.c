#include <stdio.h>
#include "Colonne.h"

//int afficher_nbr_colonne(COLONNE** CDataframe, int taille_dataframe) {
//    if (taille_dataframe == 0) {
//        printf("Il n'y a pas encore de colonne dans le CDataframe\n")
//            return 0;
//    }
//
//
//    printf("Nombre de colonnes présentes : %d\n", taille_dataframe);
//    return taille_dataframe;
//}

int obtenir_nombre_colonnes(int taille_dataframe)
{
    return taille_dataframe;
}


//int afficher_nbr_lignes(COLONNE** CDataframe, int taille_dataframe) {
//    if (taille_dataframe == 0) {
//        printf("Il n'y a pas encore de ligne dans le CDataframe\n") {
//            return 0;
//        }
//
//        int nbr_lignes = dataframe[0]->taille_physique;
//        printf("Nombre de lignes présentes : %d\n", nbr_lignes);
//        return nbr_lignes
//    }
//}

int obtenir_nombre_lignes(COLONNE** dataframe, int taille_dataframe)
{
    if (taille_dataframe == 0)
        return 0;

    return dataframe[0]->taille_physique;
}





