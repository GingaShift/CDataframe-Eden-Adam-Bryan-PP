#pragma once
#include <stdio.h>

// D�finition d'une �num�ration pour repr�senter un type bool�en
typedef enum { false, true } bool;

void free_ressources(COLONNE** dataframe, int taille_dataframe);