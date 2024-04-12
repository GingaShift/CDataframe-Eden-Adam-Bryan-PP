#pragma once
#include <stdbool.h>
#include "Colonne.h"

#define NOMBRE_DE_COLONNES_PAR_BLOC 3

/////////////////////////////////////////////////////////////
//                  ALIMENTATION 
/////////////////////////////////////////////////////////////

typedef struct SCDataframe
{
    COLONNE* CDataframe;
    int nombre_colonnes;
} SCDATAFRAME;

static SCDATAFRAME* SCDataframe;

SCDATAFRAME* CreerStructCDataframe();

COLONNE* CreerCDataframe();

// todo: RemplissageCDataframeParSaisieUtilisateur()

// todo: RemplissageEnDurDuCDataframe()

/////////////////////////////////////////////////////////////
//                  AFFICHAGE 
/////////////////////////////////////////////////////////////

// todo: AfficherCDataframe()

// todo: AfficherLignesCDataframe(int NombreLignes)

// todo: AfficherColonnesCDataframe(int NombreColonnes)

void AfficherUneColonneDuCDataframe(COLONNE CDataframe[], int NumCol);

/////////////////////////////////////////////////////////////
//             OPERATIONS USUELLES 
/////////////////////////////////////////////////////////////

bool AjouterLigneDeValeurDansCDataframe(char NomCol, int Valeur);

// todo: SupprimerLigneValeurCDataframe()

int AjouterColonneAuCDataframe(COLONNE* CDataframe, char* Nom, int nombre_colonnes);

// todo: SupprimerColonneDuCDataframe()

bool RenommerColonneDuCDataframe(char* AncienNomCol, char* NouveauNomCol, COLONNE* CDataframe);

int RechercherValeurDansCDataframe(COLONNE* CDataframe, int valeur);

bool RechercherValeurDansUneColonneDuCDataframe(COLONNE* CDataframe, int Valeur, char* NomCol, int* Ligne);

// todo: RemplacerValeurDuCDataframe()

void AfficherNomsColonnes(COLONNE* CDataframe);

/////////////////////////////////////////////////////////////
//             ANALYSES ET STATISTIQUES 
/////////////////////////////////////////////////////////////

// todo: AfficherNombreLignes()

// todo: AfficherNombreColonnes()

// todo: TrouverNombreCellulesContenantValeur()

// todo: TrouverNombreCellulesContenantValeursSuperieures()

// todo: TrouverNombreCellulesContenantValeursInferieures()
