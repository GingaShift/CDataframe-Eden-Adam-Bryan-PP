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

    // Demander à l'utilisateur de saisir une chaine
    printf(invite_saisie);

    int res = scanf("%s", chaine); // Lire la saisie de l'utilisateur et la stocker

    // Supprimer le saut de ligne (\n) ajouté par scanf si présent
    chaine[strcspn(chaine, "\n")] = '\0';

    return chaine;
}

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

// Fonction pour tester si une chaîne peut être convertie en entier
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
