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



#pragma region CDataframe 1

DATAFRAME1* gestion_creation_cdataframe(bool* dataframe_exists);

#pragma endregion CDataframe 1

#pragma region CDataframe 2

DATAFRAME2* manage_creation_of_cdataframe(bool* dataframe_exists);

#pragma endregion CDataframe 2

#pragma region menu_management

void process_user_menu_choice(int sub_section_number);

int process_user_menu_choice_main_section_1(int sub_section_number);

int process_user_menu_choice_main_section_2(int sub_section_number);

int process_user_menu_choice_main_section_3(int sub_section_number);

int process_user_menu_choice_main_section_4(int sub_section_number);

int process_user_menu_choice_main_section_5(int sub_section_number);

#pragma endregion menu_management
