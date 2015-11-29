struct Chainon {
    int donnee;
    struct Chainon *p_suivant;
};

struct Chainon *insertion_dans_liste(struct Chainon *liste, int valeur)
{
    struct Chainon *p_nouvelle = malloc(sizeof *liste);
    if (p_nouvelle == NULL)
    {
        exit(EXIT_FAILURE);
    }
    else
    {
        struct Chainon *p_tmp = NULL;
        struct Chainon *p_liste = liste;
        p_nouvelle -> donnee = valeur;

        while(p_liste != NULL && p_liste -> donnee <= valeur)
        {
            p_tmp = p_liste;
            p_liste = p_liste -> p_suivant;
        }
        p_nouvelle -> p_suivant =  p_liste;

        if (p_tmp != NULL)
        {
            p_tmp -> p_suivant = p_nouvelle;
        }
        else
        {
            liste = p_nouvelle;
        }
    }
    return liste;
}

/*void affichage(Chainon **liste)
{
    while(liste != NULL)
    {
        printf("%d ", liste -> donnee);
        liste = liste -> p_suivant;
    }
    printf("\n");
}*/

void liberer(struct Chainon **liste)
{
    while(*liste != NULL)
    {
        struct Chainon *p_tmp = (*liste) -> p_suivant;
        free(*liste), *liste = NULL;
        *liste = p_tmp;
    }
}

void tri_insertion_sequentielle_liste_chainee(int* array, int arraysize)
{
    struct Chainon *liste = NULL;
    int i;
    for (i = 0; i < arraysize; ++i)
    {
        liste = insertion_dans_liste(liste, array[i]);
    }

    for (i = 0; liste != NULL; ++i)
    {
        array[i] = liste -> donnee;
        liste = liste -> p_suivant;
    }

    liberer(&liste);
}
