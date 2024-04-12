#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "CDataframe.h"
#include "Colonne.h"

/////////////////////////////////////////////////////////////
//                  ALIMENTATION 
/////////////////////////////////////////////////////////////

SCDATAFRAME* CreerStructCDataframe()
{
    SCDATAFRAME* SCDataframe = malloc(sizeof(SCDATAFRAME));

    // Vérification de l'allocation de mémoire du CDataframe
    if (SCDataframe == NULL) {
        printf("Erreur lors de la création du SCDataframe\n");
        exit(EXIT_FAILURE);
    }

    SCDataframe->CDataframe = CreerCDataframe();

    SCDataframe->nombre_colonnes = -1;

    return SCDataframe;
}

COLONNE* CreerCDataframe()
{
    // Allouer dynamiquement un tableau de colonnes de la taille spécifiée
    COLONNE* CDataframe = malloc(sizeof(COLONNE));

    // Vérification de l'allocation mémoire du CDataframe
    if (CDataframe == NULL) {
        printf("Erreur lors de la création du CDataframe\n");
        exit(EXIT_FAILURE);
    }

    return CDataframe;
}

// todo: RemplissageCDataframeParSaisieUtilisateur()

// todo: RemplissageEnDurDuCDataframe()

/////////////////////////////////////////////////////////////
//                  AFFICHAGE 
/////////////////////////////////////////////////////////////

// todo: AfficherCDataframe()

// todo: AfficherLignesCDataframe(int NombreLignes)

// todo: AfficherColonnesCDataframe(int NombreColonnes)

void AfficherUneColonneDuCDataframe(COLONNE* CDataframe, int NumCol)
{
    COLONNE col;

    col = CDataframe[NumCol];

    AfficherColonne(col);
}

/////////////////////////////////////////////////////////////
//             OPERATIONS USUELLES 
/////////////////////////////////////////////////////////////

bool AjouterLigneDeValeurDansCDataframe(char NomCol, int Valeur)
{
    // todo

    return 0;
}

// todo: SupprimerLigneValeurCDataframe()

int AjouterColonneAuCDataframe(COLONNE* CDataframe, char* NomColonne, int nombre_colonnes)
{
    // Declarer une nouvelle colonne dans le CDataframe
    CDataframe = realloc(CDataframe, sizeof(COLONNE));

    // Creer la colonne
    COLONNE col = CreerColonne(NomColonne);

    // Ajouter cette colonne au CDataframe 
    nombre_colonnes++;

    CDataframe[nombre_colonnes] = col;

    // Assurer le suivi du nombre de colonnes du CDataframe
    return nombre_colonnes;
}

// todo: SupprimerColonneDuCDataframe()

bool RenommerColonneDuCDataframe(char* AncienNomCol, char* NouveauNomCol, COLONNE* CDataframe)
{
    int NombreColonnes = sizeof(CDataframe) / sizeof(CDataframe[0]);

    // Parcourir les colonnes du CDataframe afin de localiser celle à renommer via son nom actuel 
    for (int i = 0; i <= NombreColonnes; i++)
    {
        COLONNE col = CDataframe[i];

        int res = strcmp(CDataframe[i].nom, AncienNomCol);

        // S'il s'agit du nom de la colonne recherché, res == 0
        if (res == 0)
        {
            // Avant de renommer la colonne, s'assurer que le nom n'existe pas déjà pour une autre colonne
            // To do...

            strcpy(CDataframe[i].nom, NouveauNomCol);

            return true;
        }
    }
    return false;
}

int RechercherValeurDansCDataframe(COLONNE* CDataframe, int valeur)
{
    // todo

    return 0;
}

bool RechercherValeurDansUneColonneDuCDataframe(COLONNE* CDataframe, int Valeur, char* NomCol, int* Ligne)
{
    // todo

    return 0;
}

// todo: RemplacerValeurDuCDataframe()

void AfficherNomsColonnes(COLONNE* CDataframe)
{
    // todo

}

/////////////////////////////////////////////////////////////
//             ANALYSES ET STATISTIQUES 
/////////////////////////////////////////////////////////////

// todo: AfficherNombreLignes()

// todo: AfficherNombreColonnes()

// todo: TrouverNombreCellulesContenantValeur()

// todo: TrouverNombreCellulesContenantValeursSuperieures()

// todo: TrouverNombreCellulesContenantValeursInferieures()

