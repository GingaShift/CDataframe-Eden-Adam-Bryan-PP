#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "String_manager.h"
#include "divers.h"

#define TAILLE_MAX_STRING 256

int compare_chaines(const char* str1, const char* str2);

char* saisie_chaine(char* invite_saisie);

char obtenir_premiere_lettre_de_chaine(char* chaine);

