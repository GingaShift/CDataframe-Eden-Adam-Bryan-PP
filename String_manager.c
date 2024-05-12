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
