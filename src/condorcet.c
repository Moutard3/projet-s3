/**
 * @file condorcet.c
 * @brief 
 * @author Alexandre Saillet
 * @date CR 04/01/2019
 * @date LU 06/01/2019
 */

#include "condorcet.h"

void chercherVainqueurCondorcet(liste larcs, int *indVainqueur, int nbCandidats) {
    for (int i = 0; i < nbCandidats; i++) {
        int nbArcSortant = 0;
        for (int j = 0; j < nbEltList(larcs); j++) {
            Elementliste e;
            pickEltList(larcs, &e, j);

            if (e.orig == i) {
                nbArcSortant++;
            }
        }
        if (nbArcSortant == nbCandidats-1) {
            *indVainqueur = i;
            break;
        }
    }
}

void chercherVainqueurMinimax(t_mat_int_dyn matduel, int *indVainqueur) {
    int max = matduel.tab[0][0];
    for (int i = 0; i < matduel.nbRows; i++) {
        int min = matduel.tab[i][0];
        for (int j = 0; j < matduel.nbCol; j++) {
            if (min > matduel.tab[i][j] && i != j) {
                min = matduel.tab[i][j];
            }
        }
        if (max < min) {
            max = min;
            *indVainqueur = i;
        }
    }
}

void chercherVainqueurPaires(liste larcs, int *indVainqueur, int nbCandidats) {
    liste lcirc;
    createList(&lcirc);

    bubbleSortList(&larcs);

    for (int i = 0; i < nbEltList(larcs); i++) {
        Elementliste e;
        pickEltList(larcs, &e, i);
        addTailList(&lcirc, e);
        if (circuits(lcirc, nbCandidats)) {
            delTailList(&lcirc);
        }
    }

    chercherVainqueurCondorcet(lcirc, indVainqueur, nbCandidats);
}
