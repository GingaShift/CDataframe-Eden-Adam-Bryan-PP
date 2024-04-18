#pragma once
#include <stdio.h>

// Définition d'une énumération pour représenter un type booléen
typedef enum { false, true } bool;

void free_ressources(COLONNE** dataframe, int taille_dataframe);