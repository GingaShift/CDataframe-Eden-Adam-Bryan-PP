#include <stdio.h>
#include "Colonne.h"

#pragma endregion Tri QuickSort

// Tri "QuickSort": A utiliser si le tableau n'a pas encore été trié
// sort_dir = 0: Tri du plus petit au plus grand
// sort_dir = 1: Tri du plus grand au plus petit
// Lors de l'appel de la fonction: gauche = 0 et droite = (taille logique de la col - 1)
void quick_sort_column(COLUMN* colonne, int gauche, int droite, int sort_dir)
{
    if (gauche < droite)
    {
        // Effectuer le partitionnement
        int pi = partition(colonne, gauche, droite, sort_dir);

        // Trier les sous-tableaux avant et après le pivot
        quick_sort_column(colonne, gauche, pi - 1, sort_dir);
        quick_sort_column(colonne, pi + 1, droite, sort_dir);
    }
}

// Utilisé conjointement avec quick_sort_column
int partition(COLUMN* colonne, int gauche, int droite, int sort_dir)
{
    int pivot = colonne->data[colonne->index[droite]]->int_value;
    int i = gauche - 1;

    for (int j = gauche; j <= droite - 1; j++)
    {
        // Condition remplie ? Nbre actuel est-il plus petit que le nombre pivot (ou plus grand selon la valeur donnée à sort_dir) ?
        if ((sort_dir == 0 && colonne->data[colonne->index[j]]->int_value <= pivot) ||
            (sort_dir == 1 && colonne->data[colonne->index[j]]->int_value >= pivot))
        {
            // Si oui, permuter
            i++;

            // Échanger tab[i] et tab[j] si la condition est remplie (selon la valeur de donnée à sort_dir)
            int temp = colonne->index[i];
            colonne->index[i] = colonne->index[j];
            colonne->index[j] = temp;
        }
    }

    // Échanger tab[i + 1] et tab[droite]
    int temp = colonne->index[i + 1];
    colonne->index[i + 1] = colonne->index[droite];
    colonne->index[droite] = temp;

    return i + 1;
}

#pragma endregion Tri QuickSort

#pragma endregion Tri insertion

// Tri "Insertion": Le tab data a été trié, on lui ajoute une nouvelle valeur qui va être à trier parmi celles déjà triées
// sort_dir = 0: Tri du plus petit au plus grand
// sort_dir = 1: Tri du plus grand au plus petit
void sort_column_after_insertion(COLUMN* colonne, int sort_dir)
{
    int taille = colonne->size;
    COL_TYPE** data = colonne->data;
    unsigned long long int* index = colonne->index;

    for (int i = 1; i < taille; i++) {
        unsigned long long int k = i;
        COL_TYPE* temp_data = data[i];

        int j = i - 1;

        if (sort_dir == 0) {
            // Tri du plus petit au plus grand
            while (j >= 0 && data[j]->int_value > temp_data->int_value) {
                data[j + 1] = data[j];
                index[j + 1] = index[j];
                j--;
            }
        }
        else {
            // Tri du plus grand au plus petit
            while (j >= 0 && data[j]->int_value < temp_data->int_value) {
                data[j + 1] = data[j];
                index[j + 1] = index[j];
                j--;
            }
        }

        data[j + 1] = temp_data;
        index[j + 1] = k;
    }
}

#pragma endregion Tri insertion

