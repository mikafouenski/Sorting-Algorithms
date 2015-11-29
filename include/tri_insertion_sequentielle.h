int position_par_sequence(int i, int* array) {
    int p = 0;
    while(array[p] < array[i])
        p++;
    return p;
}

void translation_sequen(int p, int i, int* array) {
    int j;
    for (j = i - 1; p <= j; --j)
        array[j + 1] = array[j];
}

void tri_insertion_sequentielle(int* array, int arraysize) {
    int i, p, x;
    for (i = 1; i < arraysize; ++i) {
        p = position_par_sequence(i, array);
        x = array[i];
        translation_sequen(p, i, array);
        array[p] = x;
    }
}
