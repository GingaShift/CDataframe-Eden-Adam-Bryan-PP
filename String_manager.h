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

#pragma region Tests de type de donnée contenu dans une string

bool string_is_int(const char* chaine);

bool string_is_uint(const char* chaine);

//bool string_is_float(const char* chaine);
//
//bool string_is_double(const char* chaine);
//
//bool string_is_char(const char* chaine);
//
//bool string_exists(const char* chaine);
//
//bool test_if_string_can_be_casted(char string_to_cast[TAILLE_MAX], const char* type);

#pragma endregion Tests de type de donnée contenu dans une string
