#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Colonne.h"
#include "CDataframe.h"
#include "Divers.h"
#include "Alimentation.h"
#include "Analyses_et_stats.h"
#include "Main.h"
#include "String_manager.h"

//OPERATEURS_DE_COMPARAISON egal = { EGAL };
//OPERATEURS_DE_COMPARAISON superieur = { SUPERIEUR };
//OPERATEURS_DE_COMPARAISON inferieur = { INFERIEUR };
//stats_sur_valeur(CDataframe, taille_CDataframe, 10, egal);  

int ajouter_ligne_de_valeur(int valeur)
{

}

// Todo: A implémenter et à inserer dans CDataframe
int supprimer_ligne_de_valeur(int num_ligne)
{

}

// Todo: A tester et à inserer dans Colonne
int modifier_valeur(COLONNE** dataframe, int taille_dataframe, int num_col, int num_ligne, int valeur)
{
    // Parcourir toutes les colonnes du dataframe
    for (int i = 0; i < taille_dataframe; ++i) {
        
        COLONNE* colonne = dataframe[i];

        // gerer num_col et num_ligne...
        // todo

        // Ajouter la nouvelle valeur à la colonne
        colonne->data[colonne->taille_logique] = valeur;
        colonne->taille_logique++;
    }
}

int afficher_cdataframe(COLONNE** dataframe, int taille_dataframe, bool dataframe_exists, int nombre_col)
{   
    printf("Premiere ligne\n");
    printf("Deuxieme ligne\n");

    printf("Ma ligne modifiee\n");

    printf("\033[4F"); // Cette séquence ANSI déplace le curseur vers le haut de 4 caractères

    printf("\033[5C"); // Cette séquence déplace le curseur vers la droite de 5 caractères

    printf("\033[6D"); // Cette séquence déplace le curseur vers la gauche de 6 caractères

    return FAILED;

    
    if (! dataframe_exists)
    {
        printf("Veuillez d'abord creer le CDataframe et le remplir\n\n");
        return FAILED;
    }
    
    printf("\n\n");

    // affichage de la ligne des noms de toutes les colonnes voulues
    for(int i=0; i < taille_dataframe; i++)
    {
        printf("Colonne num = %d - nom = %s : ", i, dataframe[i]->nom);
        printf("      ");

        if (i = nombre_col)
            break;
    }

    printf("\n\n");

    for (int i = 0; i < taille_dataframe; i++)
    {
        // Ecrire d'abord la fonction suivante:
        // afficher_valeur(COLONNE *col, int num_ligne)

        
        printf("      ");
    }

    // Commentaire final
    switch (taille_dataframe)
    {
        case 0:
            printf("Il n'y a aucune colonne a afficher dans le CDataframe");
            break;
        case 1:
            printf("Une colonne a ete affichee pour ce CDataframe");
            break;
        default:
            printf("%d colonnes ont ete affiches pour ce CDataframe", taille_dataframe);
            break;
    }

    printf("\n\n");

    return SUCCESS;
}

int main()
{
    
    // Creation et ini du CDataframe
    int taille_CDataframe = -1;
    COLONNE** CDataframe = NULL;
    bool CDataframe_exists = false;

    // a mettre dans fonction "afficher_menu_general"
    printf("\n");
    printf("************************************************************************\n");
    printf("*                                                                      *\n");
    printf("*                     =-    MENU GENERAL    -=                         *\n");    
    printf("*                                                                      *\n");
    printf("************************************************************************\n");
    printf("\n");
    printf("1. Creer le CDataframe");
    printf("                  ");
    printf("2. Charger un CDataframe\n\n");
    printf("3. Creer une colonne");
    printf("                    ");
    printf("4. Afficher le nom des colonnes\n\n");
    printf("5. Gestion des donnees (Ajout, Suppr, Stats, Autre...)\n\n");
    printf("6. Afficher CDataframe\n\n");
    printf("0. Quitter le programme\n\n");
    
    int choix = 0;
    int go = 1;
    int nombre_col = 0;

    // Boucle jusqu'à ce que la saisie soit valide
    while (go == 1)
    {
        printf("\nChoisissez un des numeros du menu puis validez en appuyant sur la touche Entree\n\n");
        scanf("%d", &choix);

        // a mettre dans fonction "manager_choix_menu_general" et creer aussi une fonction "manager_choix_menu_gestion_des_donnees"
        switch (choix)
        {
            case 0:
                //system("cls");
                go = 0;
                break;
            case 1:
                // si le dataframe n'existe pas
                if (! CDataframe_exists)
                {
                    CDataframe = creer_cdataframe(&taille_CDataframe, &CDataframe_exists);
                    
                    // dataframe vide créé avec succès
                    if (CDataframe == NULL && taille_CDataframe == 0)
                    {
                        printf("\nLe CDataframe a ete cree avec succes\n\n");

                        // si le CDataframe a été créé, taille_CDataframe passe de -1 à 0. taille_CDataframe = 0 signifie qu'il a été créé via creer_cdataframe
                        taille_CDataframe == 0;

                        // Peupler le CDataframe artificiellement - Test seulement
                        populate_dataframe_artificially(&CDataframe, &taille_CDataframe);
                    }
                }
                else if (taille_CDataframe >= 0)
                    printf("\nLe CDataframe a deja ete cree\n");
                break;
            case 2:
                printf("\nLe chargement d'un CDataframe sera bientot disponible...\n");
                break;
            case 3:
                printf("\nLe chargement d'un CDataframe sera bientot disponible...\n");
                break;
            case 4:
                nombre_col = afficher_noms_colonnes(CDataframe, taille_CDataframe);
                printf("\n\n  %d colonne(s) trouvees(s)\n\n", nombre_col);
                break;
            case 5:
                printf("\nLa gestion des données sera bientot disponible...\n");
                break;
            case 6:
                CDataframe = creer_cdataframe(&taille_CDataframe, &CDataframe_exists);
                populate_dataframe_artificially(&CDataframe, &taille_CDataframe);
                afficher_cdataframe(CDataframe, taille_CDataframe, CDataframe_exists, taille_CDataframe);
                break;
        default:
            break;
        }
    }
    
    // Libération de la mémoire occupée par les colonnes et le dataframe
    free_ressources(CDataframe, taille_CDataframe);

    return 0;
}
