#pragma once
#include "CDataframe.h"

#pragma region code_main

#pragma region CDataframe 1

int free_all_ressources(DATAFRAME1* dataframe);

#pragma endregion Fin CDataframe 1

#pragma region CDataframe 2

int free_ressources(DATAFRAME2* dataframe);

#pragma endregion Fin CDataframe 2

#pragma region code_main

//////////////////////////////////////////////////////////////////

#pragma region gestion_choix_menu

#pragma region CDataframe 1

DATAFRAME1* gestion_creation_cdataframe(bool* dataframe_exists);

#pragma endregion CDataframe 1

#pragma region CDataframe 2

#pragma endregion CDataframe 2

#pragma endregion gestion_choix_menu
