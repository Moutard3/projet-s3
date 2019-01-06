/**
 * @file condorcet.h
 * @brief 
 * @author Alexandre Saillet
 * @date CR 04/01/2019
 * @date LU 04/01/2019
 */

#ifndef PROJET_S3_CONDORCET_H
#define PROJET_S3_CONDORCET_H

#include "global.h"
#include "circuit.h"

void chercherVainqueurCondorcet(liste larcs, t_mat_int_dyn matduel, int *indVainqueur);

#endif //PROJET_S3_CONDORCET_H
