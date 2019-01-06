/**
 * @file condorcet.c
 * @brief 
 * @author Alexandre Saillet
 * @date CR 04/01/2019
 * @date LU 04/01/2019
 */

#include "condorcet.h"

void chercherVainqueurCondorcet(t_mat_int_dyn matduel, int *indVainqueur) {
    for (int i = 0; i < matduel.nbRows; i++) {
        bool estVainqueur = true;
        for (int j = 0; j < matduel.nbRows; j++) {
            if (i != j) {
                if (matduel.tab[j][i] > matduel.tab[i][j]) {
                    estVainqueur = false;
                }
            }
        }
        if (estVainqueur) {
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