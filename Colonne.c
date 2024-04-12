#include <stdio.h>
#include <stdbool.h>
#include "Colonne.h"

COLONNE CreerColonne(char* nom)
{
    COLONNE col;

    strcpy(col.nom, nom);

    bool ret = IniValeursColonne(&col);

    col.taille_logique = 0;
    col.taille_physique = NOMBRE_LIGNES_PAR_COLONNE;

    return col;
}

bool IniValeursColonne(COLONNE* col)
{
    int nombre_lignes = sizeof(col->data) / sizeof(col->data[0]);

    for (int i = 0; i < nombre_lignes; i++)
    {
        col->data[i] = VALEUR_PAR_DEFAUT_DATA_COLONNE;
    }

    return true;
}

void AfficherColonne(COLONNE col)
{
    printf("Nom de la colonne: %s \n", col.nom);

    printf("Taille physique: %d \n", col.taille_physique);

    printf("Taille logique: %d \n", col.taille_logique);

    printf("Contenu du tableau de data: \n");

    int nombre_lignes = sizeof(col.data) / sizeof(col.data[0]);

    for (int i = 0; i < nombre_lignes; i++)
    {
        printf("Valeurs de la ligne %d = %d \n", i, col.data[i]);
    }
}

void InsererValeurDansColonne()
{

}

void RechercherValeurDansColonne(COLONNE col, int valeur)
{

}


