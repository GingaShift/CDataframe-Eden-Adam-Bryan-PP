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

int cmd_creation_cdataframe(DATAFRAME2* dataframe);

int cmd_ajouter_colonne_au_cdataframe(DATAFRAME2* dataframe);

int cmd_remplir_une_colonne_du_cdataframe(DATAFRAME2* dataframe);

int cmd_ajouter_une_ligne_au_cdataframe(DATAFRAME2* dataframe);

int cmd_remplissage_automatique_du_cdataframe(DATAFRAME2* dataframe);

int cmd_sauvegarder_cdataframe_dans_fichier(DATAFRAME2* dataframe);

int cmd_charger_cdataframe_depuis_fichier(DATAFRAME2* dataframe);

#pragma endregion menu_management_sub_menu_1

#pragma region menu_management_sub_menu_2

int process_user_menu_choice_main_section_2(int sub_section_number);

int cmd_afficher_cdataframe();

int cmd_afficher_lignes_et_colonnes_selon_limites_utilisateurs(DATAFRAME2* dataframe);

int cmd_afficher_nombre_de_colonnes(DATAFRAME2* dataframe);

int cmd_afficher_noms_et_types_des_colonnes(DATAFRAME2* dataframe);

int cmd_afficher_contenu_de_colonne(DATAFRAME2* dataframe);

int cmd_afficher_nombre_lignes(DATAFRAME2* dataframe);

#pragma endregion menu_management_sub_menu_2

#pragma region menu_management_sub_menu_3

int process_user_menu_choice_main_section_3(int sub_section_number);

int cmd_trier_une_colonne(DATAFRAME2* dataframe);

int cmd_lire_valeur_cellule(DATAFRAME2* dataframe);

int cmd_modifier_valeur_cellule(DATAFRAME2* dataframe);

int cmd_renommer_une_colonne(DATAFRAME2* dataframe);

int cmd_ne_jamais_lancer_cette_commande();

int cmd_supprimer_colonne_du_cdataframe(DATAFRAME2* dataframe);

int cmd_supprimer_ligne_du_cdataframe(DATAFRAME2* dataframe);

int cmd_supprimer_cdataframe(DATAFRAME2** dataframe);

#pragma endregion menu_management_sub_menu_3

#pragma region menu_management_sub_menu_4

int process_user_menu_choice_main_section_4(int sub_section_number);

int cmd_nombre_cellules_contenant_valeur_egale_a_x(DATAFRAME2* dataframe);

#pragma endregion menu_management_sub_menu_4

#pragma region menu_management_sub_menu_5

int process_user_menu_choice_main_section_5(int sub_section_number);

int cmd_reini_ecran_et_afficher_menu();

int cmd_afficher_informations_legales();

int cmd_quitter_programme();

#pragma endregion menu_management_sub_menu_5

#pragma endregion menu_management

void test();

int check_if_valid_value(void* value, ENUM_TYPE type);

#pragma endregion Fin CDataframe 2