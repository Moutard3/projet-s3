/**
 * @file uninomiales.c
 * @brief 
 * @author Alexandre Saillet
 * @date CR: 04/01/2019
 * @date LU: 04/01/2019
 */

#include "uninomiales.h"

void uninomiale_simple(t_mat_char_star_dyn matcsv, int *votes, int *indVainqueur) {
    int nbCandidats = matcsv.nbCol-matcsv.offset;

    // Initialisation du tableau des votes
    for (int i = 0; i < nbCandidats; i++) {
        votes[i] = 0;
    }

    // Compte des votes
    for (int i = 1; i < matcsv.nbRows; i++) {
        int k = matcsv.offset;
        for (int j = matcsv.offset; j < matcsv.nbCol; j++) {
            if (MIN((int) strtol(matcsv.tab[i][j], NULL, 10), (int) strtol(matcsv.tab[i][k], NULL, 10)) == (int) strtol(matcsv.tab[i][j], NULL, 10)) k = j;
        }
        votes[k-matcsv.offset]++;
    }

    // Détermination du vainqueur
    int k = 0;
    for (int i = 0; i < nbCandidats; i++) {
        if (MAX(votes[i], votes[k]) == votes[i]) k = i;
    }
    *indVainqueur = k;

    //affiche_tab_int(votes, nbCandidats, stdout);
}

void uninomiale_double(t_mat_char_star_dyn matcsv, int *votes, int *indVainqueur) {
    int indVainUn;
    // Détermine le 1er vainqueur
    uninomiale_simple(matcsv, votes, &indVainUn);

    // Si <= 50% second tour
    if (votes[indVainUn] <= 50) {
        // Détermine le 2nd vainqueur
        int indVainDeux = indVainUn == 0 ? 1 : 0;
        for (int i = 0; i < matcsv.nbCol-matcsv.offset; i++) {
            if (i != indVainUn) {
                if (MAX(votes[i], votes[indVainDeux]) == votes[i]) indVainDeux = i;
            }
        }
        //printf("indVainDeux %d\n", indVainDeux);
    }


}