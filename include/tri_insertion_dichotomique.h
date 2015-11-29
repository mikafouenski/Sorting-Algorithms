int position_dicho(int i, int* t) {
    int gauche = 0, droite = i, millieu;
    while(gauche < droite) {
        millieu = (droite + gauche) / 2;
        if (t[millieu] < t[i])
            gauche = millieu + 1;
        else
            droite = millieu;
    }
    return gauche;
}

void translation_dicho(int p, int i, int* t) {
    int j;
    for (j = i - 1; p <= j; --j)
        t[j + 1] = t[j];
}

void tri_insertion_dichotomique(int* t, int arraysize) {
    int i, p, x;
    for (i = 1; i < arraysize; ++i) {
        p = position_dicho(i, t);
        x = t[i];
        translation_dicho(p, i, t);
        t[p] = x;
    }
}
