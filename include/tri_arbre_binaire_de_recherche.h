struct Noeud
{
    int donnee;
    struct Noeud *fils_G;
    struct Noeud *fils_D;
};

void insertion(struct Noeud **noeud, int m)
{
    if (*noeud == NULL)
    {
        *noeud = malloc(sizeof(struct Noeud));
        (*noeud) -> donnee = m;
        (*noeud) -> fils_G = NULL;
        (*noeud) -> fils_D = NULL;
    }
    else
    {
        if (m < (*noeud) -> donnee)
            insertion(&((*noeud) -> fils_G), m);
        else
            insertion(&((*noeud) -> fils_D), m);
    }
}

/*int* parcourt(struct Noeud *noeud)
{
    int* array;
    int i = 0;
    if (noeud != NULL)
    {
        parcourt(noeud -> fils_G);
        array[i] = noeud -> donnee;
        i++;
        printf(" %d", noeud -> donnee);
        parcourt(noeud -> fils_D);
    }
    return array;
}*/

void tri_arbre_binaire_de_recherche(int* array, int arraysize) {
    struct Noeud *tree;
    int i;
    for (i = 0; i < arraysize; ++i) insertion(&tree, array[i]); 
    /*array = parcourt(tree);*/
}
