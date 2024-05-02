#include <stdio.h>
#include <string.h>
#include "CDataframe.h"
#include "Main.h"
#include "Colonne.h"
#include "Divers.h"
#include "String_manager.h"

int ajouter_colonne(DATAFRAME* dataframe, const char* nom_colonne)
{
    // Ajout d'une colonne en utilisant la fonction creer_colonne
    COLONNE* nouvelle_colonne = creer_colonne(nom_colonne);
    if (nouvelle_colonne == NULL)
    {
        printf("\nErreur lors de la création de la colonne.\n");
        return 1;
    }

    // Agrandissement du tableau CDataframe pour ajouter la nouvelle colonne
    dataframe->taille++;
    //        *colonnes = realloc(*colonnes, (*taille_dataframe) * sizeof(COLONNE*));
    dataframe->colonnes = realloc(dataframe->colonnes, (dataframe->taille) * sizeof(COLONNE*));
    if (dataframe == NULL)
    {
        printf("\nErreur d'allocation mémoire lors de l'ajout d'une colonne au CDataframe.\n");
        free(nouvelle_colonne);
        return 1;
    }

    // Ajout de la colonne au dataframe
    // (*colonnes)[*taille_dataframe - 1] = nouvelle_colonne;
    dataframe->colonnes[dataframe->taille - 1] = nouvelle_colonne;

    return 0;
}

int obtenir_nombre_lignes(DATAFRAME* dataframe)
{
    if (dataframe->taille == 0)
        return 0;

    return dataframe->colonnes[0]->taille_physique;
}

int egaliser_taille_des_tabs_data_des_colonnes(DATAFRAME* dataframe)
{
    // Si une seule colonne présente, ne rien faire
    if (dataframe->taille == 1)
        return 0;

    int taille_du_plus_grand_tab_data = 0;
    int nombre_blocs_a_ajouter = 0;
    int delta_taille = 0;

    // Parcourir toutes les colonnes et recherchee le tab data ayant la taille physique la + élevée
    // Cette taille devra être allouée, si ce n'est pas déjà le cas, à tous les autres tab data des colonnes
    for (int i = 0; i < dataframe->taille; ++i)
    {
        if (dataframe->colonnes[i]->taille_physique > taille_du_plus_grand_tab_data)
        {
            taille_du_plus_grand_tab_data = dataframe->colonnes[i]->taille_physique;
        }
    }

    // Examiner et ajuster eventuellement la taille des colonnes à cette taille max si besoin
    for (int i = 0; i < dataframe->taille; ++i)
    {
        COLONNE* colonne = dataframe->colonnes[i];

        if (colonne->taille_physique == taille_du_plus_grand_tab_data)
            continue;

        if (colonne->taille_physique < taille_du_plus_grand_tab_data)
        {
            // Calculer le nombre de blocs à allouer. Il peut y avoir un ou plusieurs bloc(s).
            // Ex: Si on vient de créer une col alors qu'il en existe déjà une de 512 lignes (2 blocs))
            delta_taille = taille_du_plus_grand_tab_data - colonne->taille_physique;
            nombre_blocs_a_ajouter = delta_taille / NOMBRE_LIGNES_PAR_BLOC_DATA_COLONNE;

            // Allouer le ou les bloc(s) mémoire nécessaire(s)
            int nouvelle_taille = colonne->taille_physique + (nombre_blocs_a_ajouter * NOMBRE_LIGNES_PAR_BLOC_DATA_COLONNE);

            int* nouveau_tab_data = realloc(colonne->data, nouvelle_taille * sizeof(int));
            if (nouveau_tab_data == NULL)
            {
                printf("\nErreur d'allocation de mémoire pour la colonne %s.\n", colonne->titre);
                return 1;
            }

            // Mettre à jour les données de la colonne
            colonne->taille_physique = nouvelle_taille;
            colonne->data = nouveau_tab_data;
        }
    }
}

int inserer_valeur_avec_gestion_memoire_data_colonnes(DATAFRAME* dataframe, int num_col, int valeur)
{
    bool nouveau_bloc_lignes_ajoute_a_colonne = false;

    // Ajouter valeur à colonne
    if(! inserer_valeur(dataframe->colonnes[num_col], valeur, &nouveau_bloc_lignes_ajoute_a_colonne))
        printf("\nUne erreur est survenue lors de l'ajout de la valeur dans la colonne\n");

    if (nouveau_bloc_lignes_ajoute_a_colonne == true)
        egaliser_taille_des_tabs_data_des_colonnes(dataframe);

    return 0;
}

int nom_colonne_existe(COLONNE** colonne, char* nom_colonne, int taille_CDataframe)
{
    for (int i = 0; i < taille_CDataframe; i++)
    {
        const char* nom = colonne[i]->titre;

        if (compare_chaines(nom, nom_colonne) == 0)
            return 0;
    }
    return 1;
}

DATAFRAME* creer_cdataframe(bool* dataframe_exists, char* nom_dataframe)
{
    DATAFRAME* nouveau_dataframe = (DATAFRAME*)malloc(sizeof(DATAFRAME));
    
    if (nouveau_dataframe == NULL) {
        printf("\nErreur lors de l'allocation de mémoire pour le dataframe.\n");
        exit(EXIT_FAILURE);
    }
    
    // Attribution du nom (si nom_dataframe est valide)
    if (nom_dataframe != NULL)
    {
        strncpy(nouveau_dataframe->titre, nom_dataframe, sizeof(nouveau_dataframe->titre) - 1);
        nouveau_dataframe->titre[sizeof(nouveau_dataframe->titre) - 1] = '\0'; // Assurer que la chaîne est terminée par un caractère nul
    }
    else
    {
        // Si nom_dataframe est NULL, affecter une chaîne vide
        nouveau_dataframe->titre[0] = '\0';
    }

    nouveau_dataframe->taille = 0;
    
    // Initialiser le tableau de pointeurs de colonnes à NULL
    nouveau_dataframe->colonnes = NULL;
    
    (*dataframe_exists) = true;

    return nouveau_dataframe;
    
    //// Declaration du dataframe
    //DATAFRAME dataframe;

    //// Ini dataframe
    //dataframe.taille = 0;
    //
    //// Attribution du nom (si nom_dataframe est valide)
    //if (nom_dataframe != NULL)
    //{
    //    strncpy(dataframe.titre, nom_dataframe, sizeof(dataframe.titre) - 1);
    //    dataframe.titre[sizeof(dataframe.titre) - 1] = '\0'; // Assurer que la chaîne est terminée par un caractère nul
    //}
    //else
    //{
    //    // Si nom_dataframe est NULL, affecter une chaîne vide
    //    dataframe.titre[0] = '\0';
    //}

    //dataframe.colonnes = NULL;

    //// Modifier le pointeur de booléen pour indiquer que la dataframe a été créée
    //(*dataframe_exists) = true;

    //// Retourner le dataframe créé
    //return dataframe;
}

int afficher_les_colonnes(COLONNE** dataframe, int taille_dataframe)
{
    for (int num_col = 0; num_col < taille_dataframe; num_col++)
    {
        afficher_colonne(dataframe, taille_dataframe, num_col);
    }
}

int afficher_noms_colonnes(DATAFRAME* dataframe)
{
    if (dataframe->taille == 0)
    {
        printf("\nLe CDataframe est vide ou non initialise.\n");
        return 1;
    }

    int nombre_col = 0;

    printf("\nNoms des colonnes :\n\n");

    for (int i = 0; i < dataframe->taille; i++) {
        COLONNE* colonne = dataframe->colonnes[i];
        printf(" [%d] = ", nombre_col);
        printf("%s\n", colonne->titre);
        nombre_col += 1;
    }

    return nombre_col;
}

int afficher_cdataframe(DATAFRAME* dataframe, int num_col_max, int num_ligne_max)
{
    if (dataframe == NULL)
    {
        printf("\n\n");
        printf("Veuillez d'abord creer et remplir le CDataframe\n\n");
        return 1;
    }

    // todo: Optimisation: Chercher ici la colonne qui contient le plus de données, et limiter l'affichage des données
    // à cette valeur de ligne au lieu d'afficher toutes les lignes inconditionnellement.
    // rappel: ecrire une fonction nommee "obtenir_num_lignes_max_contenant_donnees(DATAFRAME* dataframe)
    
    int largeur_colonne_nombre_col = 5;

    printf("\n\n");
        
    // Si aucune limites de cols précisée, alors afficher toutes les colonnes
    if (num_col_max == 0)
        num_col_max = dataframe->taille;

    // Si aucune limites de lignes précisée, alors afficher toutes les lignes
    if (num_ligne_max == 0)
        num_ligne_max = dataframe->colonnes[0]->taille_physique;

    // affichage de la ligne des noms de toutes les colonnes voulues
    for (int i = 0; i < num_col_max; i++)
    {
        if (i==0)
            printf(" Num:");
        
        printf("      \"%s\"   ", dataframe->colonnes[i]->titre);
    }

    printf("\n");

    // Traiter toutes les lignes de toutes les colonnes du dataframe en respectant d'eventuelles limites spécifiées
    for (int ligne_courante = 0; ligne_courante <= num_ligne_max; ligne_courante++)
    {
        if (ligne_courante == 0)
            printf("\n");
        else
            printf("\n\n");

        // Afficher une ligne contenant les données de toutes les colonnes à cet indice
        for (int col_courante = 0; col_courante < num_col_max; col_courante++)
        {
            // Affichage du num de ligne en début de ligne une seule et unique fois
            if (col_courante == 0)
            {
                printf(" [%02d]", ligne_courante);
                printf("    ");
            }
            else
                printf("              ");

            // Si la colonne contient encore des données pour cette ligne, les afficher
            if (ligne_courante <= dataframe->colonnes[col_courante]->taille_logique - 1)
                printf("  %*d", largeur_colonne_nombre_col, dataframe->colonnes[col_courante]->data[ligne_courante]);
            // Sinon afficher une val par défaut (à la place d'une valeur quelconque incohérente de la cellule lorsque celle-ci ne contient rien) 
            else
                printf("  %*d", largeur_colonne_nombre_col, VALEUR_PAR_DEFAUT_DATA_COLONNE);
        }
    }

    printf("\n\n\n");
    printf(" ");

    // Commentaire final
    switch (dataframe->taille)
    {
    case 0:
        printf("Il n'y a aucune colonne a afficher dans le CDataframe");
        break;
    case 1:
        printf("Les valeurs d'une colonne ont ete affichee pour ce CDataframe");
        break;
    default:
        printf("Les valeurs de %d colonnes ont ete affiches pour ce CDataframe", num_col_max);
        break;
    }

    printf("\n\n");

    return 0;
}

int modifier_valeur(DATAFRAME* dataframe, int num_col, int num_ligne, int valeur)
{
    if (num_col > dataframe->taille - 1)
    {
        printf("La colonne num %d n'existe pas", num_col);
        return 1;
    }

    if (num_ligne > dataframe->colonnes[num_col]->taille_logique)
    {
        printf("La colonne num %d ne possede pas de valeur à la ligne %d, on ne peut donc pas la modifier", num_col, num_ligne);
        return 1;
    }

    // Modification de la valeur
    dataframe->colonnes[num_col]->data[num_ligne] = valeur;
}

int renommer_colonne(DATAFRAME* dataframe, int num_colonne, const char* nouveau_nom)
{
    // Vérifier si le numéro de colonne est valide
    if (num_colonne < 0 || num_colonne >= dataframe->taille)
    {
        printf("\nLe numéro de colonne %d est invalide.\n", num_colonne);
        return 1;
    }

    // Vérifier si le nouveau nom est déjà utilisé par une autre colonne
    for (int i = 0; i < dataframe->taille; ++i)
    {
        if (i != num_colonne && strcmp(dataframe->colonnes[i]->titre, nouveau_nom) == 0)
        {
            printf("\nLe nom \"%s\" est déjà utilisé par la colonne %d.\n", nouveau_nom, i);
            return 1;
        }
    }

    // Mettre à jour le nom de la colonne
    strncpy(dataframe->colonnes[num_colonne]->titre, nouveau_nom, sizeof(dataframe->colonnes[num_colonne]->titre) - 1);

    // Ajouter le char terminal
    dataframe->colonnes[num_colonne]->titre[sizeof(dataframe->colonnes[num_colonne]->titre) - 1] = '\0';

    return 0;
}

int afficher_valeur(DATAFRAME* dataframe, int num_col, int num_ligne)
{
    if (dataframe == NULL)
    {
        printf("\nLe dataframe n'existe pas.\n");
        return 1;
    }
    
    if (num_col < 0)
    {
        printf("\nLa ligne entree n'existe pas\n");
    }

    if (num_col >= dataframe->taille)
    {
        printf(" Dans la limite de la plage de colonne disponible ");
    }

    if (num_ligne >= dataframe->colonnes[num_col]->taille_logique)
    {
        printf("ERREUR, ce n'est pas réglementaire aux données enregistrées");
        return 1;
    }

    int valeur = dataframe->colonnes[num_col]->data[num_ligne];
    
    printf("\nValeur à la colonne %d, ligne %d : %d\n", num_col, num_ligne, valeur);

}

int remplacer_valeur(DATAFRAME* dataframe, int num_col, int num_ligne, int new_val)
{
    if (dataframe == NULL)
    {
        printf("\nLe dataframe n'existe pas.\n");
        return 1;
    }

    if (num_col < 0)
    {
        printf("\nLa ligne entree n'existe pas\n");
        return 1;
    }

    if (num_col >= dataframe->taille)
    {
        printf(" Dans la limite de la plage de colonne disponible ");
        return 1;
    }

    if (num_ligne >= dataframe->colonnes[num_col]->taille_logique)
    {
        printf("ERREUR, ce n'est pas réglementaire aux données enregistrées");
        return 1;
    }

    dataframe->colonnes[num_col]->data[num_ligne] = new_val;
    
    return 0;
}

int supprimer_colonne_du_cdataframe(DATAFRAME* dataframe, int num_col)
{
    if (dataframe == NULL)
    {
        printf("\nLe dataframe n'existe pas.\n");
        return 0;
    }

    if (num_col < 0 || num_col >= dataframe->taille)
    {
        printf("\nLa colonne numero %d n'existe pas.\n", num_col);
        return 0;
    }
    
    if (! supprimer_colonne(dataframe->colonnes[num_col]))
        printf("Une erreur est survenue lors de la suppression de la colonne");

    dataframe->taille--;

    if (dataframe->taille == 1)
        return 1;

    for (int i = num_col; i <= dataframe->taille - 1; i++)
        dataframe->colonnes[i] = dataframe->colonnes[i + 1];
    
    return 1;
}



