#if defined __STRICT_ANSI__ && !defined _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <time.h> /* alarme */
#include <sys/times.h> /* pour le temps processeur */
#include <stdlib.h> /*malloc, ...*/
#include <stdio.h> /* printf, .. */
#include <sys/wait.h> /* wait */
#include <unistd.h> /* fork, ... */
#include <signal.h> /* handler */

#include "permute.h" /* juste la fonction permute */

#include "tri_a_bulles.h"
#include "tri_casier.h"
#include "tri_insertion_sequentielle.h"
#include "tri_insertion_dichotomique.h"
#include "tri_rapide.h"
#include "tri_selection_permutation.h"
#include "tri_fusion.h"
#include "tri_par_tas.h"
#include "tri_arbre_binaire_de_recherche.h"
#include "tri_insertion_sequentielle_liste_chainee.h"

typedef struct tms sTms;

typedef struct{
    sTms sdebut, sfin;
}temps_exec;

typedef void(*Pfonction[10])(int*,int);

int arrayOfArraysize[15] = {100, 500, 5000, 10000, 50000, 100000, 200000, 300000, 400000, 500000, 600000, 700000, 800000, 900000, 1000000};
char* nomsTri[10] = {"tri_a_bulles", "tri_casier", "tri_insertion_sequentielle", "tri_rapide", "tri_selection_permutation", 
                    "tri_fusion", "tri_par_tas", "tri_insertion_dichotomique", "tri_insertion_sequentielle_liste_chainee", "tri_arbre_binaire_de_recherche"};

Pfonction functArray = {tri_a_bulles, tri_casier, tri_insertion_sequentielle, tri_rapide, tri_selection_permutation, 
                        tri_fusion, tri_par_tas, tri_insertion_dichotomique, tri_insertion_sequentielle_liste_chainee, tri_arbre_binaire_de_recherche};

char* resultsArray[10] = {"results/tri_a_bulles.csv", "results/tri_casier.csv", "results/tri_insertion_sequentielle.csv", "results/tri_rapide.csv", "results/tri_selection_permutation.csv",
                        "results/tri_fusion.csv", "results/tri_par_tas.csv", "results/tri_insertion_dichotomique.csv", 
                        "results/tri_insertion_sequentielle_liste_chainee.csv", "results/tri_arbre_binaire_de_recherche.csv"};
/**
 * Fonction de handler pour l'alarme
 * In : void
 * Out : Affiche "Timeout"
 **/
void captSigAlarm() {
    printf("Timeout !\n"); /* affiche le timeout du tris */
    exit(0);
}

/**
 * Fonction définissant le handler pour SIGALRM
 * In : Le signal et des option pour le handler
 * Out : int 0 Pour tout va bien et -1 sinon
 **/
int signal_perso (int sig, int options)
{
    int r;
    struct sigaction s;
    s.sa_handler = captSigAlarm;
    sigemptyset (&s.sa_mask);
    s.sa_flags = options;
    r = sigaction (sig, &s, NULL);
    return r;
}

/**
 * Fonction Pour afficher un tableau.
 * In : un tableau de int et sa taille.
 * Out : Affiche le tableau.
 **/
void display(int* array, int arraysize) {
    int i;
    for (i = 0; i < arraysize; ++i)
        printf("%d", array[i]);
    printf("\n");
}

/**
 * Fonction qui remplit un tableau de chiffre aléatoire.
 * In : un tableau de int et sa taille.
 * Out : un tableau avec des nombre aléatoire dedans.
 **/
void random_perso(int* array, int arraysize) {
    int i;
    srand(time(NULL));
    for(i = 0 ; i < arraysize ; ++i)
        array[i] = (rand() % arraysize);
}

/**
 * Fonction qui enregistre des temps en csv
 * In : une matrice et le numéro de tri
 * Out : un fichier csv contenant les temps du tri t
 **/
void resultat(long int tab[15][20], int t)
{
    int i, j;
    FILE *fichier = NULL;

    fichier = fopen(resultsArray[t], "w+");
    fprintf(fichier, ", ");
    for(i = 0; i < 15; ++i)
        fprintf(fichier, "%d, ", arrayOfArraysize[i]);
    fprintf(fichier, "\n");

    for (i = 0; i < 20; ++i) {
        fprintf(fichier, "%s, ", nomsTri[t]);
        for (j = 0; j < 15; ++j)
            fprintf(fichier, "%ld, ", tab[j][i]);
        fprintf(fichier, "\n");
    }
    fprintf(fichier, "\n");
}

/**
 * Fonction qu’exécute le fils
 * In : Le tableau de taille de tableau et le numéro du tri a lancer
 * Out : void
 **/
void traitement_fils(int* arrayOfArraysize, int tri)
{
    int i, j, arraysize;
    int* array;
    temps_exec temps;

    long int tableauResultat[15][20]; /* Matrice qui va contenir les résultats */
    alarm(300); /* lance de décompte des 300 secondes*/
    signal_perso(SIGALRM, SA_RESTART);  /*crée le handler pour SIGALRM */

    for (j = 0; j < 20; ++j) {
        /* le faire 20 fois */
        for (i = 0; i < 15; ++i) {
            /* 15 tailles */
            arraysize = arrayOfArraysize[i]; /* change la taille du tableau */
            array = (int*)malloc(arraysize * sizeof(int)); /* alloue le tableau */
            random_perso(array, arraysize); /* met des chiffres comprit entre 0 et la taille du tableau dans le tableau */
            times(&temps.sdebut); /* commence le compteur */
            (functArray[tri])(array, arraysize); /* le tris est ICI ! */
            times(&temps.sfin); /* arrête le compteur */
            tableauResultat[i][j] = (temps.sfin.tms_utime - temps.sdebut.tms_utime) * 10; /* Sauvegarde le temps */
            printf("%s, taille %d, %ld millisecondes\n", nomsTri[tri], arrayOfArraysize[i], (temps.sfin.tms_utime - temps.sdebut.tms_utime) * 10/*(fin - debut) * 1.0 / CLOCKS_PER_SEC*/); /* affiche le temps de tris */ 
        }
    }
    resultat(tableauResultat, tri);
    free(array); /* libère le tableau */
}


int main(/*int argc, char const *argv[]*/)
{
    int i, status = 0, wpid, fils;

    for (i = 0; i < 10; ++i) {
        /* 10 tris */
        fils = fork(); /* crée un fils */
        if (fils == 0) {
            /* on est dans le fils */
            traitement_fils(arrayOfArraysize, i);
            exit(0); /* fin du fils */
        }
    }
    /* le père attend tout les fils */
    while ((wpid = wait(&status)) > 0);
    return 0;
}
