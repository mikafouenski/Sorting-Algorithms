void tri_selection_permutation(int* array, int arraysize) {
    int i = 0, min, j;
    while(i < arraysize - 1) {
        min = i;
        j = i + 1;
        while(j < arraysize) {
            if (array[j] < array[min]) min = j;
            j++;
        }
        permute(i, min, array);
        i++;
    }
}
