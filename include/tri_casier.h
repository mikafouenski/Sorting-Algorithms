int getMax(int* array, int arraysize) {
    int max = 0;
    int i;
    for (i = 0; i < arraysize; ++i)
        if (array[i] > max)
            max = array[i];
    return max;
}

void counting_sort(int *array, int taille, int min, int max)
{
    int i, j, z;
    int range = max - min + 1;
    int *count = malloc(range * sizeof(*array));
 
    for(i = 0; i < range; i++) count[i] = 0;
    for(i = 0; i < taille; i++) count[ array[i] - min ]++;
 
    for(i = min, z = 0; i <= max; i++) {
        for(j = 0; j < count[i - min]; j++) {
            array[z++] = i;
        }
    }

    free(count);
}

void tri_casier(int* array, int arraysize) {
    int minValue = 0;
    int maxValue = getMax(array, arraysize);
    counting_sort(array, arraysize, minValue, maxValue);
}
