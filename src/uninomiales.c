/**
 * @file uninomiales.c
 * @brief 
 * @author Alexandre Saillet
 * @date CR: 04/01/2019
 * @date LU: 09/01/2019
 */

#include "uninomiales.h"

/**
 * @brief Effectue un vote uninomiale à un tour
 * @param[in] matcsv : Matrice des ballots
 * @param[out] votes : Tableau des nombres de votes
 * @param[out] indVainqueur : Indicde du vainqueur (relatif au tableau votes)
 * @param[out] blanc : Nombre de votes blanc
 */
void uninomiale_simple(t_mat_char_star_dyn matcsv, int *votes, int *indVainqueur, int *blanc) {
    int nbCandidats = matcsv.nbCol-matcsv.offset;

    // Initialisation du tableau des votes
    init_tab_int(votes, nbCandidats, 0);

    // Compte des votes
    int skipped = 0;
    for (int i = 1; i < matcsv.nbRows; i++) {
        int k = matcsv.offset;
        bool skip = false;
        for (int j = matcsv.offset+1; j < matcsv.nbCol; j++) {
            if ((int) strtol(matcsv.tab[i][j], NULL, 10) == (int) strtol(matcsv.tab[i][k], NULL, 10)) {
                skip = true;
            }
            if ((int) strtol(matcsv.tab[i][j], NULL, 10) < (int) strtol(matcsv.tab[i][k], NULL, 10)) {
                k = j;
                skip = false;
            }
        }
        if (!skip) {
            votes[k - matcsv.offset]++;
        } else {
            // En comptant les votes blancs dans les votes:
            votes[k - matcsv.offset]++;
            skipped++;
        }
    }

    // Détermination du vainqueur
    int k = 0;
    for (int i = 0; i < nbCandidats; i++) {
        if (votes[i] > votes[k]) k = i;
    }
    *indVainqueur = k;
    *blanc = skipped;

    //affiche_tab_int(votes, nbCandidats, stdout);
}

/**
 * @brief Effectue un vote uninomiale à deux tours
 * @param matcsv : Matrice des ballots
 * @param votesT1 : Tableau du nombre de votes au tour un
 * @param indVainqueur1 : Indice du vainqueur un au tour un (relatif au tableau votesT1)
 * @param indVainqueur2 : Indice du vainqueur deux au tour un (relatif au tableau votesT1)
 * @param votesT2 : Tableau du nombre de votes au tour deux
 * @param indVainqueur : Indice du vainqueur du vote ( = vainqueur du tour 2, relatif au tableau votesT2)
 * @param blanc : Nombre de votes blancs au tour 1
 */
void uninomiale_double(t_mat_char_star_dyn matcsv, int *votesT1, int *indVainqueur1, int *indVainqueur2, int *votesT2, int *indVainqueur, int *blanc) {
    // Détermine le 1er vainqueur
    uninomiale_simple(matcsv, votesT1, indVainqueur1, blanc);

    // Si <= 50% : second tour
    if (votesT1[*indVainqueur1] <= 50) {
        // Détermine le 2nd vainqueur
        *indVainqueur2 = ((*indVainqueur1 == 0) ? (1) : (0));
        for (int i = 0; i < matcsv.nbCol-matcsv.offset; i++) {
            if (i != *indVainqueur1) {
                if (votesT1[i] > votesT1[*indVainqueur2]) *indVainqueur2 = i;
            }
        }

        // Compte les votes du second tour
        votesT2[0] = 0;
        votesT2[1] = 0;

        for (int i = 1; i < matcsv.nbRows; i++) {
            ((int) strtol(matcsv.tab[i][*indVainqueur1+matcsv.offset], NULL, 10) < (int) strtol(matcsv.tab[i][*indVainqueur2+matcsv.offset], NULL, 10)) ? (votesT2[0]++) : (votesT2[1]++);
        }

        (votesT2[0] > votesT2[1]) ? (*indVainqueur = *indVainqueur1) : (*indVainqueur = *indVainqueur2);
    } else {
        *indVainqueur = *indVainqueur1;
    }

    /*
    affiche_tab_int(votesT1, matcsv.nbCol-matcsv.offset, stdout);
    affiche_tab_int(votesT2, 2, stdout);
    */
}