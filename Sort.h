#pragma once
#include <stdio.h>
#include "Colonne.h"

#pragma endregion Tri QuickSort

int partition_uint(COLUMN* column, int left, int right, int sort_dir);

int partition_int(COLUMN* column, int left, int right, int sort_dir);

int partition_char(COLUMN* column, int left, int right, int sort_dir);

int partition_float(COLUMN* column, int left, int right, int sort_dir);

int partition_double(COLUMN* column, int left, int right, int sort_dir);

int partition_string(COLUMN* column, int left, int right, int sort_dir);

// STRUCTURE

int quick_sort_column(COLUMN* column, int left, int right, int sort_dir);

int quick_sort_column_uint(COLUMN* column, int left, int right, int sort_dir);

int quick_sort_column_int(COLUMN* column, int left, int right, int sort_dir);

int quick_sort_column_char(COLUMN* column, int left, int right, int sort_dir);

int quick_sort_column_float(COLUMN* column, int left, int right, int sort_dir);

int quick_sort_column_double(COLUMN* column, int left, int right, int sort_dir);

int quick_sort_column_string(COLUMN* column, int left, int right, int sort_dir);
 
// STRUCTURE

#pragma endregion Tri QuickSort

#pragma endregion Tri insertion

int sort_column_after_insertion(COLUMN* column, int sort_dir);

int sort_column_after_insertion_uint(COLUMN* col, int sort_dir);

int sort_column_after_insertion_int(COLUMN* column, int sort_dir);

int sort_column_after_insertion_char(COLUMN* col, int sort_dir);

int sort_column_after_insertion_float(COLUMN* col, int sort_dir);

int sort_column_after_insertion_double(COLUMN* col, int sort_dir);

int sort_column_after_insertion_string(COLUMN* col, int sort_dir);

// STRUCTURE

#pragma endregion Tri insertion

int sort_column(COLUMN* col, int sort_dir);