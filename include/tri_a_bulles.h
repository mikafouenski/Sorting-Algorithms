void tri_a_bulles(int* t, int arraysize) {
    int i = 0, j;
    while(i < arraysize -1) {
        j = arraysize - 1;
        while(j > i) {
            if (t[j] < t[j - 1])
                permute(j, j - 1, t);
            j = j - 1;
        }
        i++;
    }
}
