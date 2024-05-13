#pragma once
#include <stdio.h>
#include "Colonne.h"

#pragma endregion Tri QuickSort

int partition_int(COLUMN* colonne, int gauche, int droite, int sort_dir);

int quick_sort_column(COLUMN* colonne, int gauche, int droite, int sort_dir);

// UINT

int quick_sort_column_int(COLUMN* colonne, int gauche, int droite, int sort_dir);

// CHAR

// FLOAT - A tester
int quick_sort_column_float(COLUMN* colonne, int gauche, int droite, int sort_dir);

// DOUBLE
int quick_sort_column_double(COLUMN* colonne, int gauche, int droite, int sort_dir);


// STRING
// 
// STRUCTURE


#pragma endregion Tri QuickSort

#pragma endregion Tri insertion

int sort_column_after_insertion(COLUMN* column);

int sort_column_after_insertion_int(COLUMN* column);

#pragma endregion Tri insertion
