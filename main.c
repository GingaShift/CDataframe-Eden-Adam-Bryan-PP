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

int afficher_cdataframe_old(COLONNE** dataframe, int taille_dataframe)
{   
    if (dataframe == NULL)
    {
        printf("\n\n");
        printf("Veuillez d'abord creer le CDataframe et le remplir\n\n");
        return FAILED;
    }
    
    printf("\n\n");

    // affichage de la ligne des noms de toutes les colonnes voulues
    for(int i=0; i < taille_dataframe; i++)
    {
        printf("Col %d - \"%s\"  ||  ", i, dataframe[i]->titre);
    }
    
    printf("\n");

    int largeur_nombre = 5;
    int ligne_courante = 0;

    // Traiter toutes les colonnes du dataframe
    for (int ligne_courante = 0; ligne_courante <= dataframe[0]->taille_physique; ligne_courante++)
    {
        if (ligne_courante==0)
            printf("\n");
        else
            printf("\n\n");

        // Afficher une ligne contenant les données de toutes les colonnes à cet indice
        for (int col_courante = 0; col_courante < taille_dataframe; col_courante++)
        {
            // Affichage du num de ligne en début de ligne une seule et unique fois
            if (col_courante == 0)
            { 
                printf(" [%d]", ligne_courante);
                printf("    ");
            }
            else
                printf("              ");
                        
            // Si la colonne contient encore des données pour cette ligne, les afficher
            if (ligne_courante <= dataframe[col_courante]->taille_logique - 1)
                printf("  %*d", largeur_nombre, dataframe[col_courante]->data[ligne_courante]);
            // Sinon afficher une val par défaut (à la place d'une valeur quelconque incohérente de la cellule lorsque celle-ci ne contient rien) 
            else
                printf("  %*d", largeur_nombre, VALEUR_PAR_DEFAUT_DATA_COLONNE);
        }
    }
    
    printf("\n\n\n");
    printf(" ");

    // Commentaire final
    switch (taille_dataframe)
    {
        case 0:
            printf("Il n'y a aucune colonne a afficher dans le CDataframe");
            break;
        case 1:
            printf("Les valeurs d'une colonne ont ete affichee pour ce CDataframe");
            break;
        default:
            printf("Les valeurs des %d colonnes ont ete affiches pour ce CDataframe", taille_dataframe);
            break;
    }

    printf("\n\n");

    return SUCCESS;
}

void afficher_menu()
{
    printf("\n");
    printf(" ****************************************************************************\n");
    printf(" *                                                                          *\n");
    printf(" *                         =-    MENU GENERAL    -=                         *\n");
    printf(" *                                                                          *\n");
    printf(" ****************************************************************************\n");
    printf(" *                                                                          *\n");
    printf(" *  1. Creer le CDataframe");
    printf("             ");
    printf(" 2. Charger un CDataframe            *");
    printf("\n");
    printf(" *                                                                          *");
    printf("\n");
    printf(" *  3. Creer une colonne");
    printf("               ");
    printf(" 4. Afficher le nom des colonnes     *");
    printf("\n");
    printf(" *                                                                          *");
    printf("\n");
    printf(" *  5. Gestion donnees (Remplir)");
    printf("       ");
    printf(" 6. Afficher le CDataframe           *");
    printf("\n");
    printf(" *                                                                          *");
    printf("\n");
    printf(" *                                                                          *");
    printf("\n");
    printf(" *                       0. Quitter le programme                            *");
    printf("\n");
    printf(" *                                                                          *");
    printf("\n");
    printf(" *                                                                          *");
    printf("\n");
    printf(" ****************************************************************************\n");
}



int main()
{
    // Declaration du CDataframe
    int taille_CDataframe_old = -1;
    COLONNE** CDataframe_old = NULL;
    
    DATAFRAME CDataframe_new;

    bool CDataframe_exists = false;
    
    // TEST SEULEMENT : REMETTRE A 0
    int choix = 6; //-1;
    int go = 1;
    int nombre_col = 0;
    int res_choix_menu = -1;

    afficher_menu();
    
    printf("\n\n");
    printf("INSTRUCTIONS:");
    printf("\n");
    printf("Choisissez un des numeros du menu puis validez en appuyant sur la touche Entree\n\n");
    printf("NOTE IMPORTANTE:");
    printf("\n");
    printf("Pour une demo rapide, choisissez dans l'ordre l'entree 1, puis 5,\nensuite 4 et enfin 6\n\n");

    // Boucle jusqu'à ce que la saisie soit valide
    while (go == 1)
    {
        printf("\n");
        printf(" - Choisissez une des entrees du menu puis validez :\n\n");

        //res_choix_menu = scanf("%d", &choix);

        // a mettre dans fonction "manager_choix_menu_general" et creer aussi une fonction "manager_choix_menu_gestion_des_donnees"
        switch (choix)
        {
            case 0:
                //system("cls");
                go = 0;
                break;
            
            case 1:
                printf("\nChoix 1 - Creation du CDataframe:\n");
                
                // si le dataframe n'existe pas
                if (! CDataframe_exists)
                {
                    CDataframe_old = creer_cdataframe_old(&taille_CDataframe_old, &CDataframe_exists);
                    
                    // dataframe vide créé avec succès
                    if (CDataframe_old == NULL && taille_CDataframe_old == 0)
                    {
                        printf("\nLe CDataframe a ete cree avec succes\n\n");

                        // si le CDataframe a été créé, taille_CDataframe passe de -1 à 0. taille_CDataframe = 0 signifie qu'il a été créé via creer_cdataframe
                        taille_CDataframe_old == 0;
                    }
                }
                else if (taille_CDataframe_old >= 0)
                    printf("\nLe CDataframe a deja ete cree\n");
                break;
            case 2:
                printf("\nChoix 2 - Chargement du CDataframe:\n");
                printf("\nLe chargement d'un CDataframe sera bientot disponible...\n\n");
                break;
            case 3:
                printf("\nChoix 3 - Creation d'une colonne:\n");
                printf("\nLa creation d'une colonne sera bientot disponible...\n\n");
                break;
            case 4:
                printf("\nChoix 4 - Affichage du nom des colonnes:\n");
                nombre_col = afficher_noms_colonnes(CDataframe_old, taille_CDataframe_old);
                printf("\nLe(s) nom(s) de %d colonne(s) ont ete affiche(s)\n\n", nombre_col);
                break;
            case 5:
                printf("\nChoix 5 - Gestion des donnees:\n");
                if (! CDataframe_exists)
                {
                    printf("Veuillez d'abord creer un CDataframe\n\n");
                    break;
                }
                // Peupler le CDataframe artificiellement - Test seulement - 
                populate_dataframe_artificially_old(&CDataframe_old, &taille_CDataframe_old);
                
                printf("\nLa gestion des donnees sera bientot disponible dans son entierete...\n");
                printf("\nCependant, trois colonnes ont ete ajoutees. Elles contiennent egalement quelques donnees pour cette demo\n");
                printf("Vous pouvez visualiser ces colonnes dans le detail en choisissant l'entree de menu \"6\"\n\n");

                break;

            case 6:
                
                ////////////////////////////////////////////////////////////////////////
                // A virer
                CDataframe_old = creer_cdataframe_old(&taille_CDataframe_old, &CDataframe_exists);
                
                CDataframe_new = creer_cdataframe_new(&CDataframe_exists, "CDataframe1");
                              
                // Peupler le CDataframe artificiellement - Test seulement - 
                //populate_dataframe_artificially_old(&CDataframe_old, &taille_CDataframe_old);
                populate_dataframe_artificially_new(&CDataframe_new);

                // Fin A virer
                ////////////////////////////////////////////////////////////////////////

                printf("\nChoix 6 - Affichage du CDataframe:");
                
                if (!CDataframe_exists)
                {
                    printf("\n Impossible d'afficher le CDataframe car il n'existe pas.");
                    printf("\n Veuillez le creer ou le charger a partir d'une source.");
                    break;
                }

                int res = afficher_cdataframe_old(CDataframe_old, taille_CDataframe_old);

                choix = -1;

                break;
        default:
            break;
        }
    }
    
    // Libération de la mémoire occupée par les colonnes et le dataframe
    free_ressources(CDataframe_old, taille_CDataframe_old);

    return 0;
}
