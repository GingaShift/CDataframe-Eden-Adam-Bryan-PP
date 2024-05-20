#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "String_manager.h"
#include "divers.h"

/// <summary>
/// compare two strings
/// </summary>
/// <param name="str1">first string to compare</param>
/// <param name="str2">second string to compare</param>
/// <returns>result of the  comparison</returns>
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

/// <summary>
/// input a string
/// </summary>
/// <param name="invite_saisie">caption to prompt the user</param>
/// <returns>inputted string</returns>
char* saisie_chaine(char* invite_saisie)
{
    char* chaine[255];

    // Demander à l'utilisateur de saisir une chaine
    printf(invite_saisie);

    int res = scanf("%s", chaine); // Lire la saisie de l'utilisateur et la stocker

    // Supprimer le saut de ligne (\n) ajouté par scanf si présent
    chaine[strcspn(chaine, "\n")] = '\0';

    return chaine;
}

/// <summary>
/// get the first lettre of a string
/// </summary>
/// <param name="chaine">specified string where to get the first letter</param>
/// <returns>the first letter of the specified string</returns>
char obtenir_premiere_lettre_de_chaine(char* chaine)
{
    
    // Vérifier si la chaîne est vide
    if (chaine == NULL || *chaine == '\0') {
        // Retourner un caractère nul si la chaîne est vide
        return '\0';
    }

    // Retourner le premier caractère de la chaîne
    return *chaine;
}

#pragma region Tests de type de donnée contenu dans une string