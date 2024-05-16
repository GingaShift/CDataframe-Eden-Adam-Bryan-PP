#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "String_manager.h"
#include "divers.h"

int compare_chaines(const char* str1, const char* str2)
{
    while (*str1 && *str2)
    {
        if (tolower(*str1) != tolower(*str2))
            break;
        str1++;
        str2++;
    }
    if (*str1 == '\0' && *str2 == '\0')
        return 0;

    return 1;
}

char* saisie_chaine(char* invite_saisie)
{
    char* chaine[255];

    // Demander � l'utilisateur de saisir une chaine
    printf(invite_saisie);

    int res = scanf("%s", chaine); // Lire la saisie de l'utilisateur et la stocker dans le tableau input

    // Supprimer le saut de ligne (\n) ajout� par scanf si pr�sent
    chaine[strcspn(chaine, "\n")] = '\0';

    return chaine;
}

char obtenir_premiere_lettre_de_chaine(char* chaine)
{
    
    // V�rifier si la cha�ne est vide
    if (chaine == NULL || *chaine == '\0') {
        // Retourner un caract�re nul si la cha�ne est vide
        return '\0';
    }

    // Retourner le premier caract�re de la cha�ne
    return *chaine;
}

#pragma region Tests de type de donn�e contenu dans une string

// Fonction pour tester si une cha�ne peut �tre convertie en entier
bool string_is_int(const char* chaine)
{
    char* fin;
    strtol(chaine, &fin, 10);
    if (fin != chaine && *fin == '\0')
        return true;
    else
        return false;
}

// TODO: FAIRE LA SUITE SUR LE MODELE CI-DESSUS
bool string_is_uint(const char* chaine)
{
    char* fin;
    strtoul(chaine, &fin, 10);
    return fin != chaine && *fin == '\0';
}

//// Fonction pour savoir si une cha�ne est un nombre flottant
//bool string_is_float(const char* chaine)
//{
//    char* fin;
//    strtof(chaine, &fin);
//    return fin != chaine && *fin == '\0';
//}
//
//// Fonction pour savoir si une cha�ne est un double
//bool string_is_double(const char* chaine)
//{
//    char* fin;
//    strtod(chaine, &fin);
//    return fin != chaine && *fin == '\0';
//}
//
//// Fonction pour savoir si une cha�ne est un caract�re
//bool string_is_char(const char* chaine)
//{
//    return strlen(chaine) == 1;
//}
//
//// Fonction pour savoir si une cha�ne est une cha�ne de caract�res
//bool string_exists(const char* chaine)
//{
//    return strlen(chaine) > 0;
//}
//
//// Fonction pour tester le type de donn�es entr� par l'utilisateur
//bool test_if_string_can_be_casted(char string_to_cast[TAILLE_MAX], const char* type)
//{
//    // Savoir la string peut �tre convertie en un type "int"
//    if (strcmp(type, "int") == 0)
//    {
//        if (string_is_int(string_to_cast))
//            return true;
//        else
//            return false;
//    }
//    
//    // TODO: FAIRE LE RESTE SUR LE MODELE CI DESSUS
//    else if (strcmp(type, "float") == 0 || strcmp(type, "double") == 0) {
//        if (string_is_float(string_to_cast)) {
//            printf("Merci.\n");
//        }
//        else {
//            printf("Erreur : la valeur entr�e n'est pas un nombre flottant. Veuillez r�essayer.\n");
//        }
//    }
//    else if (strcmp(type, "char") == 0) {
//        if (string_is_char(string_to_cast)) {
//            printf("Merci.\n");
//        }
//        else {
//            printf("Erreur : la valeur entr�e n'est pas un caract�re. Veuillez r�essayer.\n");
//        }
//    }
//    else if (strcmp(type, "string") == 0) {
//        if (string_exists(string_to_cast)) {
//            printf("Merci.\n");
//        }
//        else {
//            printf("Erreur : la valeur entr�e n'est pas une cha�ne de caract�res. Veuillez r�essayer.\n");
//        }
//    }
//    else {
//        printf("Type non reconnu.\n");
//    }
//}
//
//#pragma endregion Tests de type de donn�e contenu dans une string
