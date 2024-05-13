#include <stdio.h>
#include "Alimentation.h"
#include "CDataframe.h"

#pragma region CDataframe 1

int remplir_dataframe_automatiquement(DATAFRAME1* dataframe)
{
    int ajouter_bloc_lignes_a_toutes_les_colonnes = 0;
    
    // Ajouter une colonne au dataframe
    ajouter_colonne(dataframe, "Colonne 1");

    // Ajouter une colonne au dataframe
    ajouter_colonne(dataframe, "Colonne 2");

    inserer_valeur_avec_gestion_memoire_data_colonnes(dataframe, 0, 10);
    
    inserer_valeur_avec_gestion_memoire_data_colonnes(dataframe, 0, 11);

    inserer_valeur_avec_gestion_memoire_data_colonnes(dataframe, 0, 12);

    // Ajouter une valeur à Colonne 2
    inserer_valeur_avec_gestion_memoire_data_colonnes(dataframe, 1, 20);
    inserer_valeur_avec_gestion_memoire_data_colonnes(dataframe, 1, 21);

    // Ajouter une colonne au dataframe
    ajouter_colonne(dataframe, "Colonne 3");

    // Ajouter quelques valeurs à Colonne 3
    inserer_valeur_avec_gestion_memoire_data_colonnes(dataframe, 2, 30);
    inserer_valeur_avec_gestion_memoire_data_colonnes(dataframe, 2, 31);

    // Ajouter une colonne au dataframe
    ajouter_colonne(dataframe, "Colonne 4");

    // Ajouter quelques valeurs à Colonne 4
    inserer_valeur_avec_gestion_memoire_data_colonnes(dataframe, 3, 40);
    inserer_valeur_avec_gestion_memoire_data_colonnes(dataframe, 3, 41);

        // Ajouter une colonne au dataframe
    ajouter_colonne(dataframe, "Colonne 5");

    // Ajouter quelques valeurs à Colonne 5
    inserer_valeur_avec_gestion_memoire_data_colonnes(dataframe, 4, 50);
    inserer_valeur_avec_gestion_memoire_data_colonnes(dataframe, 4, 51);

    ajouter_colonne(dataframe, "Colonne 6");
    
    // Ajouter quelques valeurs à Colonne 6
    inserer_valeur_avec_gestion_memoire_data_colonnes(dataframe, 5, 60);
    inserer_valeur_avec_gestion_memoire_data_colonnes(dataframe, 5, 61);
    inserer_valeur_avec_gestion_memoire_data_colonnes(dataframe, 5, 62);
    inserer_valeur_avec_gestion_memoire_data_colonnes(dataframe, 5, 63);

    return 1;
}

#pragma endregion Fin CDataframe 1

#pragma region CDataframe 2

int populate_dataframe_automatically(DATAFRAME2* dataframe)
{
    if (dataframe == NULL)
    {
        printf("\n Le dataframe n'existe pas, il est donc impossible de le remplir automatiquement\n");
        return 0;
    }
    
    add_column(dataframe, INT, "Col_INT");

    int i1 = 5;
    int i2 = 3;
    int i3 = 7;
    int i4 = 1;
    int i5 = 9;
    int i6 = 2;
    int i7 = 16;
    int i8 = 4;

    insert_value_with_memory_management_of_tabs_data_of_columns(dataframe, 0, &i1);
    insert_value_with_memory_management_of_tabs_data_of_columns(dataframe, 0, &i2);
    insert_value_with_memory_management_of_tabs_data_of_columns(dataframe, 0, &i3);
    insert_value_with_memory_management_of_tabs_data_of_columns(dataframe, 0, &i4);
    insert_value_with_memory_management_of_tabs_data_of_columns(dataframe, 0, &i5);
    insert_value_with_memory_management_of_tabs_data_of_columns(dataframe, 0, &i6);
    insert_value_with_memory_management_of_tabs_data_of_columns(dataframe, 0, &i7);
    insert_value_with_memory_management_of_tabs_data_of_columns(dataframe, 0, &i8);

    add_column(dataframe, DOUBLE, "Col_DOUBLE");

    double d1 = 4.761;
    double d2 = 1.21;
    double d3 = 2.761;
    double d4 = 7.21;
    double d5 = 29.761;
    double d6 = 9.21;
    double d7 = 3.761;
    double d8 = 1.11;

    insert_value_with_memory_management_of_tabs_data_of_columns(dataframe, 1, &d1);
    insert_value_with_memory_management_of_tabs_data_of_columns(dataframe, 1, &d2);
    insert_value_with_memory_management_of_tabs_data_of_columns(dataframe, 1, &d3);
    insert_value_with_memory_management_of_tabs_data_of_columns(dataframe, 1, &d4);
    insert_value_with_memory_management_of_tabs_data_of_columns(dataframe, 1, &d5);
    insert_value_with_memory_management_of_tabs_data_of_columns(dataframe, 1, &d6);
    insert_value_with_memory_management_of_tabs_data_of_columns(dataframe, 1, &d7);
    insert_value_with_memory_management_of_tabs_data_of_columns(dataframe, 1, &d8);

    add_column(dataframe, STRING, "Col_STRING");

    char s1[TAILLE_MAX_DATA_STRING] = "Hello";
    char s2[TAILLE_MAX_DATA_STRING] = "Bull";
    char s3[TAILLE_MAX_DATA_STRING] = "Ake";
    char s4[TAILLE_MAX_DATA_STRING] = "Zaho";
    char s5[TAILLE_MAX_DATA_STRING] = "Marlene";
    char s6[TAILLE_MAX_DATA_STRING] = "Eden";
    char s7[TAILLE_MAX_DATA_STRING] = "Bryan";
    char s8[TAILLE_MAX_DATA_STRING] = "Fudge";

    insert_value_with_memory_management_of_tabs_data_of_columns(dataframe, 2, &s1);
    insert_value_with_memory_management_of_tabs_data_of_columns(dataframe, 2, &s2);
    insert_value_with_memory_management_of_tabs_data_of_columns(dataframe, 2, &s3);
    insert_value_with_memory_management_of_tabs_data_of_columns(dataframe, 2, &s4);
    insert_value_with_memory_management_of_tabs_data_of_columns(dataframe, 2, &s5);
    insert_value_with_memory_management_of_tabs_data_of_columns(dataframe, 2, &s6);
    insert_value_with_memory_management_of_tabs_data_of_columns(dataframe, 2, &s7);
    insert_value_with_memory_management_of_tabs_data_of_columns(dataframe, 2, &s8);

    add_column(dataframe, STRUCTURE, "Col_STRUCTURE");

    return 1;
}

#pragma endregion Fin CDataframe 2

