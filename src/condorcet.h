/**
 * @file condorcet.h
 * @brief Méthodes de vote condorcet
 * @author Alexandre Saillet
 * @date CR 04/01/2019
 * @date LU 09/01/2019
 */

#ifndef PROJET_S3_CONDORCET_H
#define PROJET_S3_CONDORCET_H

#include "global.h"
#include "circuit.h"
#include "utils_sd.h"

void chercherVainqueurCondorcet(liste larcs, int *indVainqueur, int nbCandidats);
void chercherVainqueurMinimax(t_mat_int_dyn matduel, int *indVainqueur);
void chercherVainqueurPaires(liste larcs, int *indVainqueur, int nbCandidats);

#endif //PROJET_S3_CONDORCET_H
