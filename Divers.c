#include <stdio.h>
#include "Divers.h"

int obtenir_premier_chiffre(int nombre)
{
    // Si le nombre est négatif, le convertir en positif
    if (nombre < 0)
    {
        nombre = -nombre;
    }

    // Extraire le premier chiffre en itérant jusqu'à ce que le nombre soit inférieur à 10
    while (nombre >= 10)
    {
        nombre /= 10;
    }

    // Le chiffre restant est le premier chiffre
    return nombre;
}

void vider_tampon()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}