#include <stdio.h>
#include <string.h>
#include "String_manager.h"

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
    char chaine[255];

    // Demander à l'utilisateur de saisir une chaine
    printf(invite_saisie);

    fgets(chaine, sizeof(chaine), stdin);

    // Supprimer le saut de ligne (\n) ajouté par fgets si présent
    chaine[strcspn(chaine, "\n")] = '\0';

    return chaine;
}
