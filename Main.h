#pragma once
#include "CDataframe.h"

#pragma region CDataframe 1

int free_all_ressources(DATAFRAME1* dataframe);

DATAFRAME1* gestion_creation_cdataframe(bool* dataframe_exists);

#pragma endregion Fin CDataframe 1

#pragma region CDataframe 2

int free_ressources(DATAFRAME2* dataframe);

DATAFRAME2* manage_creation_of_cdataframe();

#pragma region menu_management

int process_user_menu_choice(int sub_section_number);

#pragma region menu_management_sub_menu_1

int process_user_menu_choice_main_section_1(int sub_section_number);

#pragma endregion menu_management_sub_menu_1

#pragma region menu_management_sub_menu_2

int process_user_menu_choice_main_section_2(int sub_section_number);

int cmd_afficher_cdataframe();

int cmd_afficher_lignes_selon_limites_utilisateurs(DATAFRAME2* dataframe);

int cmd_afficher_nombre_de_colonnes(DATAFRAME2* dataframe);

#pragma endregion menu_management_sub_menu_2

#pragma region menu_management_sub_menu_3

int process_user_menu_choice_main_section_3(int sub_section_number);

#pragma endregion menu_management_sub_menu_3

#pragma region menu_management_sub_menu_4

int process_user_menu_choice_main_section_4(int sub_section_number);

#pragma endregion menu_management_sub_menu_4

#pragma region menu_management_sub_menu_5

int process_user_menu_choice_main_section_5(int sub_section_number);

int cmd_reini_ecran();

int cmd_afficher_informations_sur_programme();

int cmd_quitter_programme();

#pragma endregion menu_management_sub_menu_5

#pragma endregion menu_management

void test();

#pragma endregion Fin CDataframe 2