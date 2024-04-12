#include <stdio.h>
#include <stdbool.h>
#include "Colonne.h"
#include "CDataframe.h"

bool ret = false;

int main()
{
    // Déclaration et allocation de la mémoire pour la structure principale SCDataframe
    SCDataframe = CreerStructCDataframe();

    // Vérification si l'allocation a réussi
    if (SCDataframe == NULL)
    {
        // Gestion de l'échec de l'allocation mémoire
        printf("Erreur : Impossible d'allouer de la mémoire pour SCDataframe.\n");
        return 0;
    }

    SCDataframe->nombre_colonnes = AjouterColonneAuCDataframe(SCDataframe->CDataframe, "Col zero", SCDataframe->nombre_colonnes);

    // Creer 1 nouvelle colonne
    //COLONNE c0 = CreerColonne("Colonne 0 de Eden");

    // Assigner en lieu et place de l'ancienne col 0
    //SCDataframe->CDataframe[0] = c0;

    // Afficher les colonnes voulues
    AfficherUneColonneDuCDataframe(SCDataframe->CDataframe, 0);

    char* NomColAModifier = "Col zero";
    char* NewNomCol = "Colonne zero modified";

    RenommerColonneDuCDataframe(NomColAModifier, NewNomCol, SCDataframe->CDataframe);

    AfficherUneColonneDuCDataframe(SCDataframe->CDataframe, 0);

    // Ajouter le nombre de colonnes en param (NombreDeColonnesDansCDataframe)
    RechercherValeurDansCDataframe(SCDataframe->CDataframe, 10);

    // Après utilisation, libérez la mémoire allouée pour SCDataframe
    free(SCDataframe);

    return 0;
}