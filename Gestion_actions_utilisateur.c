#include "CDataframe.h"
#include "String_manager.h"

DATAFRAME* gestion_creation_cdataframe(bool* dataframe_exists)
{
	printf("\nChoix 1 - Creation du CDataframe:\n");

	// Deamnder le nom du CDataframe
	char* chaine = saisie_chaine("\nVeuillez saisir le nom du CDataframe:\n");

	DATAFRAME* dataframe = creer_cdataframe(dataframe_exists, chaine);
	
	if (dataframe != NULL)
		printf("\nLe CDataframe a ete cree avec succes\n\n");

	return dataframe;
}