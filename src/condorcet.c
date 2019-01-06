/**
 * @file condorcet.c
 * @brief 
 * @author Alexandre Saillet
 * @date CR 04/01/2019
 * @date LU 04/01/2019
 */

#include "condorcet.h"

void chercherVainqueurCondorcet(liste larcs, t_mat_int_dyn matduel, int *indVainqueur) {
    for (int k = 0; k < matduel.nbRows; k++) {
        bool estVainqueur = true;
        for (int j = 0; j < matduel.nbRows; j++) {
            if (k != j) {
                Elementliste e;
                e.orig = k;
                e.dest = j;
                e.poids = matduel.tab[k][j];

                if (!belongEltList(larcs, e)) {
                    estVainqueur = false;
                }
            }
        }
        if (estVainqueur) {
            *indVainqueur = k;
        }
    }
}