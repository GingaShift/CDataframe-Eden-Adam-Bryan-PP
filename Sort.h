#pragma once
#include <stdio.h>
#include "Colonne.h"

#pragma endregion Tri QuickSort

int quick_sort_column(COLUMN* colonne, int gauche, int droite, int sort_dir);

int partition(COLUMN* colonne, int gauche, int droite, int sort_dir);

#pragma endregion Tri QuickSort

#pragma endregion Tri insertion
void sort_column_after_insertion(COLUMN* colonne, int sort_dir);

#pragma endregion Tri insertion
