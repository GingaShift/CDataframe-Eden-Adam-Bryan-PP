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

    add_column(dataframe, UINT, "Col_UINT");

    unsigned int ui1 = 21;
    unsigned int ui2 = 14;
    unsigned int ui3 = 7;
    unsigned int ui4 = 11;
    unsigned int ui5 = 9;
    unsigned int ui6 = 2;
    unsigned int ui7 = 16;
    unsigned int ui8 = 4;

    insert_value_with_memory_management_of_tabs_data_of_columns(dataframe, 0, &ui1);
    insert_value_with_memory_management_of_tabs_data_of_columns(dataframe, 0, &ui2);
    insert_value_with_memory_management_of_tabs_data_of_columns(dataframe, 0, &ui3);
    insert_value_with_memory_management_of_tabs_data_of_columns(dataframe, 0, &ui4);
    insert_value_with_memory_management_of_tabs_data_of_columns(dataframe, 0, &ui5);
    insert_value_with_memory_management_of_tabs_data_of_columns(dataframe, 0, &ui6);
    insert_value_with_memory_management_of_tabs_data_of_columns(dataframe, 0, &ui7);
    insert_value_with_memory_management_of_tabs_data_of_columns(dataframe, 0, &ui8);


    add_column(dataframe, INT, "Col_INT");

    int i1 = 5;
    int i2 = 3;
    int i3 = 7;
    int i4 = 1;
    int i5 = 9;
    int i6 = 2;
    int i7 = 16;
    int i8 = 4;

    insert_value_with_memory_management_of_tabs_data_of_columns(dataframe, 1, &i1);
    insert_value_with_memory_management_of_tabs_data_of_columns(dataframe, 1, &i2);
    insert_value_with_memory_management_of_tabs_data_of_columns(dataframe, 1, &i3);
    insert_value_with_memory_management_of_tabs_data_of_columns(dataframe, 1, &i4);
    insert_value_with_memory_management_of_tabs_data_of_columns(dataframe, 1, &i5);
    insert_value_with_memory_management_of_tabs_data_of_columns(dataframe, 1, &i6);
    insert_value_with_memory_management_of_tabs_data_of_columns(dataframe, 1, &i7);
    insert_value_with_memory_management_of_tabs_data_of_columns(dataframe, 1, &i8);


    add_column(dataframe, CHAR, "Col_CHAR");

    char c1 = 'C';
    char c2 = 'Y';
    char c3 = 'M';
    char c4 = 'A';
    char c5 = 'F';
    char c6 = 'W';
    char c7 = 'B';
    char c8 = 'J';

    insert_value_with_memory_management_of_tabs_data_of_columns(dataframe, 2, &c1);
    insert_value_with_memory_management_of_tabs_data_of_columns(dataframe, 2, &c2);
    insert_value_with_memory_management_of_tabs_data_of_columns(dataframe, 2, &c3);
    insert_value_with_memory_management_of_tabs_data_of_columns(dataframe, 2, &c4);
    insert_value_with_memory_management_of_tabs_data_of_columns(dataframe, 2, &c5);
    insert_value_with_memory_management_of_tabs_data_of_columns(dataframe, 2, &c6);
    insert_value_with_memory_management_of_tabs_data_of_columns(dataframe, 2, &c7);
    insert_value_with_memory_management_of_tabs_data_of_columns(dataframe, 2, &c8);


    add_column(dataframe, FLOAT, "Col_FLOAT");

    float f1 = 3.14;
    float f2 = 7.89;
    float f3 = 1.23;
    float f4 = 4.56;
    float f5 = 6.78;
    float f6 = 9.01;
    float f7 = 2.34;
    float f8 = 8.12;

    insert_value_with_memory_management_of_tabs_data_of_columns(dataframe, 3, &f1);
    insert_value_with_memory_management_of_tabs_data_of_columns(dataframe, 3, &f2);
    insert_value_with_memory_management_of_tabs_data_of_columns(dataframe, 3, &f3);
    insert_value_with_memory_management_of_tabs_data_of_columns(dataframe, 3, &f4);
    insert_value_with_memory_management_of_tabs_data_of_columns(dataframe, 3, &f5);
    insert_value_with_memory_management_of_tabs_data_of_columns(dataframe, 3, &f6);
    insert_value_with_memory_management_of_tabs_data_of_columns(dataframe, 3, &f7);
    insert_value_with_memory_management_of_tabs_data_of_columns(dataframe, 3, &f8);


    add_column(dataframe, DOUBLE, "Col_DOUBLE");

    double d1 = 4.761;
    double d2 = 1.21;
    double d3 = 2.761;
    double d4 = 7.21;
    double d5 = 29.761;
    double d6 = 9.21;
    double d7 = 3.761;
    double d8 = 1.11;

    insert_value_with_memory_management_of_tabs_data_of_columns(dataframe, 4, &d1);
    insert_value_with_memory_management_of_tabs_data_of_columns(dataframe, 4, &d2);
    insert_value_with_memory_management_of_tabs_data_of_columns(dataframe, 4, &d3);
    insert_value_with_memory_management_of_tabs_data_of_columns(dataframe, 4, &d4);
    insert_value_with_memory_management_of_tabs_data_of_columns(dataframe, 4, &d5);
    insert_value_with_memory_management_of_tabs_data_of_columns(dataframe, 4, &d6);
    insert_value_with_memory_management_of_tabs_data_of_columns(dataframe, 4, &d7);
    insert_value_with_memory_management_of_tabs_data_of_columns(dataframe, 4, &d8);


    add_column(dataframe, STRING, "Col_STRING");

    char* s1 = "Hello";
    char* s2 = "Bull";
    char* s3 = "Ake";
    char* s4 = "Zaho";
    char* s5 = "Marlene";
    char* s6 = "Eden";
    char* s7 = "Bryan";
    char* s8 = "Adam";

    insert_value_with_memory_management_of_tabs_data_of_columns(dataframe, 5, s1);
    insert_value_with_memory_management_of_tabs_data_of_columns(dataframe, 5, s2);
    insert_value_with_memory_management_of_tabs_data_of_columns(dataframe, 5, s3);
    insert_value_with_memory_management_of_tabs_data_of_columns(dataframe, 5, s4);
    insert_value_with_memory_management_of_tabs_data_of_columns(dataframe, 5, s5);
    insert_value_with_memory_management_of_tabs_data_of_columns(dataframe, 5, s6);
    insert_value_with_memory_management_of_tabs_data_of_columns(dataframe, 5, s7);
    insert_value_with_memory_management_of_tabs_data_of_columns(dataframe, 5, s8);


    add_column(dataframe, STRUCTURE, "Col_STRUCTURE");
    // TODO

    return 1;
}

#pragma endregion Fin CDataframe 2

