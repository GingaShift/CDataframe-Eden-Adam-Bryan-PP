#include <stdio.h>
#include "Colonne.h"

#pragma endregion Tri QuickSort

// Utilisé conjointement avec quick_sort_column
int partition_int(COLUMN* colonne, int gauche, int droite, int sort_dir)
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
    unsigned long long int temp = colonne->index[i + 1];
    colonne->index[i + 1] = colonne->index[droite];
    colonne->index[droite] = temp;

    return i + 1;
}

int partition_float(COLUMN* colonne, int gauche, int droite, int sort_dir)
{
    float pivot = colonne->data[colonne->index[droite]]->float_value;

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
    unsigned long long int temp = colonne->index[i + 1];
    colonne->index[i + 1] = colonne->index[droite];
    colonne->index[droite] = temp;

    return i + 1;
}

int partition_double(COLUMN* colonne, int gauche, int droite, int sort_dir)
{
    double pivot = colonne->data[colonne->index[droite]]->double_value;

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
    unsigned long long int temp = colonne->index[i + 1];
    colonne->index[i + 1] = colonne->index[droite];
    colonne->index[droite] = temp;

    return i + 1;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Tri "QuickSort": A utiliser si le tableau n'a pas encore été trié
// sort_dir = 0: Tri du plus petit au plus grand
// sort_dir = 1: Tri du plus grand au plus petit
// Lors de l'appel de la fonction: gauche = 0 et droite = (taille logique de la col - 1)
///////////////////////////////////////////////////////////////////////////////////////////////////
int quick_sort_column(COLUMN* colonne, int gauche, int droite, int sort_dir)
{
    switch (colonne->column_type)
    {
        case NULLVAL:
            printf("\nLe type n'est pas valide, impossible d'effectuer le tri quicksort\n");
            return 0;
        case UINT:
            //quick_sort_column_uint(colonne, gauche, droite, sort_dir);
            break;
        case INT:
            quick_sort_column_int(colonne, gauche, droite, sort_dir);
            break;
        case CHAR:
            //quick_sort_column_char(colonne, gauche, droite, sort_dir);
            break;
        case FLOAT:
            quick_sort_column_float(colonne, gauche, droite, sort_dir);
            break;
        case DOUBLE:
            //quick_sort_column_double(colonne, gauche, droite, sort_dir);
            break;
        case STRING:
            //quick_sort_column_string(colonne, gauche, droite, sort_dir);
            break;
        case STRUCTURE:
            //quick_sort_column_structure(colonne, gauche, droite, sort_dir);
            break;
        default:
            printf("\nCe type n'est pas reconnu\n");
            return 0;
    }
    return 1;
}

int quick_sort_column_int(COLUMN* colonne, int gauche, int droite, int sort_dir)
{
    if (gauche < droite)
    {
        // Effectuer le partitionnement
        int pi = partition_int(colonne, gauche, droite, sort_dir);

        // Trier les sous-tableaux avant et après le pivot
        quick_sort_column_int(colonne, gauche, pi - 1, sort_dir);
        quick_sort_column_int(colonne, pi + 1, droite, sort_dir);
    }
}

int quick_sort_column_float(COLUMN* colonne, int gauche, int droite, int sort_dir)
{
    if (gauche < droite)
    {
        // Effectuer le partitionnement
        float pi = partition_float(colonne, gauche, droite, sort_dir);

        // Trier les sous-tableaux avant et après le pivot
        quick_sort_column_float(colonne, gauche, pi - 1, sort_dir);
        quick_sort_column_float(colonne, pi + 1, droite, sort_dir);
    }
}

int quick_sort_column_double(COLUMN* colonne, int gauche, int droite, int sort_dir)
{
    if (gauche < droite)
    {
        // Effectuer le partitionnement
        double pi = partition_double(colonne, gauche, droite, sort_dir);

        // Trier les sous-tableaux avant et après le pivot
        quick_sort_column_double(colonne, gauche, pi - 1, sort_dir);
        quick_sort_column_double(colonne, pi + 1, droite, sort_dir);
    }
}

#pragma endregion Tri QuickSort

#pragma endregion Tri insertion

// Tri "Insertion": Le tab data a été trié, on lui ajoute une nouvelle valeur qui va être à trier parmi celles déjà triées
// sort_dir = 0: Tri du plus petit au plus grand
// sort_dir = 1: Tri du plus grand au plus petit
int sort_column_after_insertion(COLUMN* colonne, int sort_dir)
{
    switch (colonne->column_type)
    {
    case NULLVAL:
        printf("\nLe type n'est pas valide, impossible d'effectuer le tri par insertion\n");
        return 0;
    case UINT:
        break;
    case INT:
        sort_column_after_insertion_int(colonne, sort_dir);
        break;
    case CHAR:
        
        break;
    case FLOAT:
        
        break;
    case DOUBLE:
        
        break;
    case STRING:
        
        break;
    case STRUCTURE:
        
        break;
    default:
        printf("\nCe type n'est pas reconnu\n");
        return 0;
    }

}

int sort_column_after_insertion_int(COLUMN* column)
{
    unsigned int taille = column->size;
    unsigned long long int* index = column->index;
    COL_TYPE** data = column->data;

    for (unsigned int i = 1; i < taille; i++) {
        unsigned long long int k = index[i];
        int j = i - 1;

        COL_TYPE* k_value = data[k];
        // si val suivante est > à val courante (ou < en fonction du mode de tri choisi), update les index pour trier ces valeurs via leur index
        while (j >= 0 && ((column->sort_dir == 0 && data[index[j]]->int_value > k_value->int_value) ||
                          (column->sort_dir == 1 && data[index[j]]->int_value < k_value->int_value)))
        {
            index[j + 1] = index[j];
            j--;
        }
        // continuer le tri
        index[j + 1] = k;
    }
}

#pragma endregion Tri insertion

