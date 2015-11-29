void placer_pivot(int g, int d, int* array, int *p)
{
    int i;
    int pivot = array[g];
    *p = g;
    for (i = g + 1; i <= d; i++)
    {
        if (array[i] < pivot) {
            (*p)++;
            if (i != *p) permute(i, *p, array);
        }
    }
    permute(*p, g, array);
}

void tri_rapide_back(int g, int d, int* array)
{
    int p;
    if (g < d) {
        placer_pivot(g, d, array, &p);
        tri_rapide_back(g, p - 1, array);
        tri_rapide_back(p + 1, d, array);
    }
}

void tri_rapide(int* array, int arraysize) {
    int debut = 0;
    tri_rapide_back(debut, arraysize - 1, array);
}
