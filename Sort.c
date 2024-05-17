#include <stdio.h>
#include "Colonne.h"

#pragma region Tri QuickSort

// Utilisé conjointement avec quick_sort_column
int partition_uint(COLUMN* column, int left, int right, int sort_dir)
{
    unsigned int pivot = column->data[column->index[right]]->uint_value;

    int i = left - 1;

    for (int j = left; j <= right - 1; j++)
    {
        // Condition remplie ? Nbre actuel est-il plus petit que le nombre pivot (ou plus grand selon la valeur donnée à sort_dir) ?
        if ((sort_dir == 0 && column->data[column->index[j]]->uint_value <= pivot) ||
            (sort_dir == 1 && column->data[column->index[j]]->uint_value >= pivot))
        {
            // Si oui, permuter
            i++;

            // Échanger tab[i] et tab[j] si la condition est remplie (selon la valeur de donnée à sort_dir)
            int temp = column->index[i];
            column->index[i] = column->index[j];
            column->index[j] = temp;
        }
    }

    // Échanger tab[i + 1] et tab[droite]
    unsigned long long int temp = column->index[i + 1];
    column->index[i + 1] = column->index[right];
    column->index[right] = temp;

    return i + 1;
}

int partition_int(COLUMN* column, int left, int right, int sort_dir)
{
    int pivot = column->data[column->index[right]]->int_value;
    
    int i = left - 1;

    for (int j = left; j <= right - 1; j++)
    {
        // Condition remplie ? Nbre actuel est-il plus petit que le nombre pivot (ou plus grand selon la valeur donnée à sort_dir) ?
        if ((sort_dir == 0 && column->data[column->index[j]]->int_value <= pivot) ||
            (sort_dir == 1 && column->data[column->index[j]]->int_value >= pivot))
        {
            // Si oui, permuter
            i++;

            // Échanger tab[i] et tab[j] si la condition est remplie (selon la valeur de donnée à sort_dir)
            int temp = column->index[i];
            column->index[i] = column->index[j];
            column->index[j] = temp;
        }
    }

    // Échanger tab[i + 1] et tab[droite]
    unsigned long long int temp = column->index[i + 1];
    column->index[i + 1] = column->index[right];
    column->index[right] = temp;

    return i + 1;
}

int partition_char(COLUMN* column, int left, int right, int sort_dir)
{
    int pivot = column->data[column->index[right]]->char_value;

    int i = left - 1;

    for (int j = left; j <= right - 1; j++)
    {
        // Condition remplie ? Char actuel est-il plus petit que le nombre pivot (ou plus grand selon la valeur donnée à sort_dir) ?
        if ((sort_dir == 0 && column->data[column->index[j]]->char_value <= pivot) ||
            (sort_dir == 1 && column->data[column->index[j]]->char_value >= pivot))
        {
            // Si oui, permuter
            i++;

            // Échanger tab[i] et tab[j] si la condition est remplie (selon la valeur de donnée à sort_dir)
            int temp = column->index[i];
            column->index[i] = column->index[j];
            column->index[j] = temp;
        }
    }

    // Échanger tab[i + 1] et tab[droite]
    unsigned long long int temp = column->index[i + 1];
    column->index[i + 1] = column->index[right];
    column->index[right] = temp;

    return i + 1;
}

int partition_float(COLUMN* column, int left, int right, int sort_dir)
{
    float pivot = column->data[column->index[right]]->float_value;

    int i = left - 1;

    for (int j = left; j <= right - 1; j++)
    {
        // Condition remplie ? Nbre actuel est-il plus petit que le nombre pivot (ou plus grand selon la valeur donnée à sort_dir) ?
        if ((sort_dir == 0 && column->data[column->index[j]]->float_value <= pivot) ||
            (sort_dir == 1 && column->data[column->index[j]]->float_value >= pivot))
        {
            // Si oui, permuter
            i++;

            // Échanger tab[i] et tab[j] si la condition est remplie (selon la valeur de donnée à sort_dir)
            int temp = column->index[i];
            column->index[i] = column->index[j];
            column->index[j] = temp;
        }
    }

    // Échanger tab[i + 1] et tab[droite]
    unsigned long long int temp = column->index[i + 1];
    column->index[i + 1] = column->index[right];
    column->index[right] = temp;

    return i + 1;
}

int partition_double(COLUMN* column, int left, int right, int sort_dir)
{
    double pivot = column->data[column->index[right]]->double_value;

    int i = left - 1;

    for (int j = left; j <= right - 1; j++)
    {
        // Condition remplie ? Nbre actuel est-il plus petit que le nombre pivot (ou plus grand selon la valeur donnée à sort_dir) ?
        if ((sort_dir == 0 && column->data[column->index[j]]->double_value <= pivot) ||
            (sort_dir == 1 && column->data[column->index[j]]->double_value >= pivot))
        {
            // Si oui, permuter
            i++;

            // Échanger tab[i] et tab[j] si la condition est remplie (selon la valeur de donnée à sort_dir)
            int temp = column->index[i];
            column->index[i] = column->index[j];
            column->index[j] = temp;
        }
    }

    // Échanger tab[i + 1] et tab[droite]
    unsigned long long int temp = column->index[i + 1];
    column->index[i + 1] = column->index[right];
    column->index[right] = temp;

    return i + 1;
}

int partition_string(COLUMN* column, int left, int right, int sort_dir)
{
    char pivot = column->data[column->index[right]]->string_value;

    int i = left - 1;

    for (int j = left; j <= right - 1; j++)
    {
        // Condition remplie ? Nbre actuel est-il plus petit que le nombre pivot (ou plus grand selon la valeur donnée à sort_dir) ?
        if ((sort_dir == 0 && column->data[column->index[j]]->string_value <= pivot) ||
            (sort_dir == 1 && column->data[column->index[j]]->string_value >= pivot))
        {
            // Si oui, permuter
            i++;

            // Échanger tab[i] et tab[j] si la condition est remplie (selon la valeur de donnée à sort_dir)
            int temp = column->index[i];
            column->index[i] = column->index[j];
            column->index[j] = temp;
        }
    }

    // Échanger tab[i + 1] et tab[droite]
    unsigned long long int temp = column->index[i + 1];
    column->index[i + 1] = column->index[right];
    column->index[right] = temp;

    return i + 1;
}


// STRUCTURE

///////////////////////////////////////////////////////////////////////////////////////////////////
// Tri "QuickSort": A utiliser si le tableau n'a pas encore été trié
// sort_dir = 0: Tri du plus petit au plus grand
// sort_dir = 1: Tri du plus grand au plus petit
// Lors de l'appel de la fonction: gauche = 0 et droite = (taille logique de la col - 1)
///////////////////////////////////////////////////////////////////////////////////////////////////
int quick_sort_column(COLUMN* column, int left, int right, int sort_dir)
{
    switch (column->column_type)
    {
        case NULLVAL:
            printf("\nLe type n'est pas valide, impossible d'effectuer le tri quicksort\n");
            return 0;
        case UINT:
            quick_sort_column_uint(column, left, right, sort_dir);
            break;
        case INT:
            quick_sort_column_int(column, left, right, sort_dir);
            break;
        case CHAR:
            quick_sort_column_char(column, left, right, sort_dir);
            break;
        case FLOAT:
            quick_sort_column_float(column, left, right, sort_dir);
            break;
        case DOUBLE:
            quick_sort_column_double(column, left, right, sort_dir);
            break;
        case STRING:
            quick_sort_column_string(column, left, right, sort_dir);
            break;
        case STRUCTURE:
            //quick_sort_column_structure(colonne, gauche, droite, sort_dir);
            break;
        default:
            printf("\nCe type n'est pas reconnu\n");
            return 0;
    }
    column->index_size += 1;
    return 1;
}

int quick_sort_column_uint(COLUMN* column, int left, int right, int sort_dir)
{
    if (left < right)
    {
        // Effectuer le partitionnement
        unsigned int pi = partition_int(column, left, right, sort_dir);

        // Trier les sous-tableaux avant et après le pivot
        quick_sort_column_uint(column, left, pi - 1, sort_dir);
        quick_sort_column_int(column, pi + 1, right, sort_dir);
    }
}

int quick_sort_column_int(COLUMN* column, int left, int right, int sort_dir)
{
    if (left < right)
    {
        // Effectuer le partitionnement
        int pi = partition_int(column, left, right, sort_dir);

        // Trier les sous-tableaux avant et après le pivot
        quick_sort_column_int(column, left, pi - 1, sort_dir);
        quick_sort_column_int(column, pi + 1, right, sort_dir);
    }
}

int quick_sort_column_char(COLUMN* column, int left, int right, int sort_dir)
{
    if (left < right)
    {
        // Effectuer le partitionnement
        int pi = partition_char(column, left, right, sort_dir);

        // Trier les sous-tableaux avant et après le pivot
        quick_sort_column_char(column, left, pi - 1, sort_dir);
        quick_sort_column_char(column, pi + 1, right, sort_dir);
    }
}

int quick_sort_column_float(COLUMN* column, int left, int right, int sort_dir)
{
    if (left < right)
    {
        // Effectuer le partitionnement
        float pi = partition_float(column, left, right, sort_dir);

        // Trier les sous-tableaux avant et après le pivot
        quick_sort_column_float(column, left, pi - 1, sort_dir);
        quick_sort_column_float(column, pi + 1, right, sort_dir);
    }
}

int quick_sort_column_double(COLUMN* column, int left, int right, int sort_dir)
{
    if (left < right)
    {
        // Effectuer le partitionnement
        double pi = partition_double(column, left, right, sort_dir);

        // Trier les sous-tableaux avant et après le pivot
        quick_sort_column_double(column, left, pi - 1, sort_dir);
        quick_sort_column_double(column, pi + 1, right, sort_dir);
    }
}

int quick_sort_column_string(COLUMN* column, int left, int right, int sort_dir)
{
    if (left < right)
    {
        // Effectuer le partitionnement
        char pi = partition_double(column, left, right, sort_dir);

        // Trier les sous-tableaux avant et après le pivot
        quick_sort_column_string(column, left, pi - 1, sort_dir);
        quick_sort_column_string(column, pi + 1, right, sort_dir);
    }
}


// STRUCTURE

#pragma endregion Tri QuickSort

#pragma region Tri insertion

// Tri "Insertion": Le tab data a été trié, on lui ajoute une nouvelle valeur qui va être à trier parmi celles déjà triées
// sort_dir = 0: Tri du plus petit au plus grand
// sort_dir = 1: Tri du plus grand au plus petit
int sort_column_after_insertion(COLUMN* column, int sort_dir)
{
    switch (column->column_type)
    {
    case NULLVAL:
        printf("\nLe type n'est pas valide, impossible d'effectuer le tri par insertion\n");
        return 0;
    case UINT:
        sort_column_after_insertion_uint(column, sort_dir);
        break;
    case INT:
        sort_column_after_insertion_int(column, sort_dir);
        break;
    case CHAR:
        sort_column_after_insertion_char(column, sort_dir);
        break;
    case FLOAT:
        sort_column_after_insertion_float(column, sort_dir);
        break;
    case DOUBLE:
        sort_column_after_insertion_double(column, sort_dir);
        break;
    case STRING:
        sort_column_after_insertion_string(column, sort_dir);
        break;
    case STRUCTURE:
        
        break;
    default:
        printf("\nCe type n'est pas reconnu\n");
        return 0;
    }
    column->index_size += 1;
    return 1;
}

int sort_column_after_insertion_uint(COLUMN* col, int sort_dir)
{
    unsigned int taille = col->size;
    unsigned long long int* index = col->index;
    COL_TYPE** data = col->data;

    for (unsigned int i = 1; i < taille; i++) {
        unsigned long long int k = index[i];
        int j = i - 1;

        COL_TYPE* k_value = data[k];
        // si val suivante est > à val courante (ou < en fonction du mode de tri choisi), update les index pour trier ces valeurs via leur index
        while (j >= 0 && ((col->sort_dir == 0 && data[index[j]]->uint_value > k_value->uint_value) ||
            (col->sort_dir == 1 && data[index[j]]->uint_value < k_value->uint_value)))
        {
            index[j + 1] = index[j];
            j--;
        }
        // continuer le tri
        index[j + 1] = k;
    }
}

int sort_column_after_insertion_int(COLUMN* col, int sort_dir)
{
    unsigned int taille = col->size;
    unsigned long long int* index = col->index;
    COL_TYPE** data = col->data;

    for (unsigned int i = 1; i < taille; i++) {
        unsigned long long int k = index[i];
        int j = i - 1;

        COL_TYPE* k_value = data[k];
        // si val suivante est > à val courante (ou < en fonction du mode de tri choisi), update les index pour trier ces valeurs via leur index
        while (j >= 0 && ((col->sort_dir == 0 && data[index[j]]->int_value > k_value->int_value) ||
                          (col->sort_dir == 1 && data[index[j]]->int_value < k_value->int_value)))
        {
            index[j + 1] = index[j];
            j--;
        }
        // continuer le tri
        index[j + 1] = k;
    }
}

int sort_column_after_insertion_char(COLUMN* col, int sort_dir)
{
    unsigned int taille = col->size;
    unsigned long long int* index = col->index;
    COL_TYPE** data = col->data;

    for (unsigned int i = 1; i < taille; i++) {
        unsigned long long int k = index[i];
        int j = i - 1;

        COL_TYPE* k_value = data[k];
        // si val suivante est > à val courante (ou < en fonction du mode de tri choisi), update les index pour trier ces valeurs via leur index
        while (j >= 0 && ((col->sort_dir == 0 && data[index[j]]->char_value > k_value->char_value) ||
            (col->sort_dir == 1 && data[index[j]]->char_value < k_value->char_value)))
        {
            index[j + 1] = index[j];
            j--;
        }
        // continuer le tri
        index[j + 1] = k;
    }
}

int sort_column_after_insertion_float(COLUMN* col, int sort_dir)
{
    unsigned int taille = col->size;
    unsigned long long int* index = col->index;
    COL_TYPE** data = col->data;

    for (unsigned int i = 1; i < taille; i++) {
        unsigned long long int k = index[i];
        int j = i - 1;

        COL_TYPE* k_value = data[k];
        // si val suivante est > à val courante (ou < en fonction du mode de tri choisi), update les index pour trier ces valeurs via leur index
        while (j >= 0 && ((col->sort_dir == 0 && data[index[j]]->float_value > k_value->float_value) ||
            (col->sort_dir == 1 && data[index[j]]->float_value < k_value->float_value)))
        {
            index[j + 1] = index[j];
            j--;
        }
        // continuer le tri
        index[j + 1] = k;
    }
}

int sort_column_after_insertion_double(COLUMN* col, int sort_dir)
{
    unsigned int taille = col->size;
    unsigned long long int* index = col->index;
    COL_TYPE** data = col->data;

    for (unsigned int i = 1; i < taille; i++) {
        unsigned long long int k = index[i];
        int j = i - 1;

        COL_TYPE* k_value = data[k];
        // si val suivante est > à val courante (ou < en fonction du mode de tri choisi), update les index pour trier ces valeurs via leur index
        while (j >= 0 && ((col->sort_dir == 0 && data[index[j]]->double_value > k_value->double_value) ||
            (col->sort_dir == 1 && data[index[j]]->double_value < k_value->double_value)))
        {
            index[j + 1] = index[j];
            j--;
        }
        // continuer le tri
        index[j + 1] = k;
    }
}

int sort_column_after_insertion_string(COLUMN* col, int sort_dir)
{
    unsigned int taille = col->size;
    unsigned long long int* index = col->index;
    COL_TYPE** data = col->data;

    for (unsigned int i = 1; i < taille; i++)
    {
        unsigned long long int k = index[i];
        int j = i - 1;

        char* k_value = (char*)col->data[k];

        // Tri par insertion selon la direction du tri (0 pour ascendant, 1 pour descendant)
        while (j >= 0 && ((col->sort_dir == 0 && strcmp((char*)col->data[col->index[j]], k_value) > 0) ||
                          (col->sort_dir == 1 && strcmp((char*)col->data[col->index[j]], k_value) < 0)))
        {
            index[j + 1] = index[j];
            j--;
        }
        index[j + 1] = k;
    }

    return 0; // Si tout s'est bien passé, retourner 0
}

// STRUCTURE

#pragma endregion Tri insertion

int sort_column(COLUMN* column, int sort_dir)
{
    /*Colonne jamais triée :
    valid_index = 0 (val par défaut)
        Lors  d'ajout d'une valeur, appeler "quicksort"
        valid_index passe alors à 1 (colonne correctement triée)

        quick_sort_column

        Si colonne correctement triée : valid_index = 1
        On ajoute une new valeur alors valid_index passe à - 1 (col partiellement trié)
        On doit donc de nouveau effectuer un tri mais par insertion, cette fois
        On effectue un tri tri "insertion"
        ceci fait, set valid_index à 1 (colonne correctement triée)

        sort_column_after_insertion

        */
    

}

