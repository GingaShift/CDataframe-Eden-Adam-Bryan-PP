#include <stdio.h>
#include <stdbool.h>
#include "Colonne.h"
#include "CDataframe.h"

bool ret = false;

int main()
{
    // D�claration et allocation de la m�moire pour la structure principale SCDataframe
    SCDataframe = CreerStructCDataframe();

    // V�rification si l'allocation a r�ussi
    if (SCDataframe == NULL)
    {
        // Gestion de l'�chec de l'allocation m�moire
        printf("Erreur : Impossible d'allouer de la m�moire pour SCDataframe.\n");
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

    // Apr�s utilisation, lib�rez la m�moire allou�e pour SCDataframe
    free(SCDataframe);

    return 0;
}