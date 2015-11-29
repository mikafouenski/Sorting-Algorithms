void ajouter(int* array, int x, int size)
{
    int i = size;
    int parent = (i - 1) / 2;
    array[size] = x;
    
    while (i >= 1 && array[parent] < x)
    {
        permute(i, parent, array);
        i = parent;
        parent = (i - 1) / 2;
    }
}

void suppression(int* array, int size)
{
    int i = 0;
    int d = 2;
    int g = 1;
    int max;
    permute(0, size - 1, array);
    while(g < size - 1)
    {
        if (d < size - 1 && array[d] > array[g])
        {
            max = d;
        }
        else
            max = g;
        if (array[i] < array[max])
        {
            permute(i, max, array);
        }
        else break;

        i = max;
        g = 2 * i + 1;
        d = 2 * i + 2;
    }
}

void creation(int* array, int size)
{
    int i;
    for (i = 1; i < size; ++i)
    {
        ajouter(array, array[i], i);
    }
}

void tri_par_tas(int* array, int arraysize)
{
    int i;
    creation(array, arraysize);
    
    for (i = arraysize; i > 1; --i)
    {
        suppression(array, i);
    }
}
