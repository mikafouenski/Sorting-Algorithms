void permute(int i, int j, int* array) {
    int tmp = array[i];
    array[i] = array[j];
    array[j] = tmp;
}
