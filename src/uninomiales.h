/**
 * @file uninomiales.h
 * @brief Méthodes de vote unimoniales
 * @author Alexandre Saillet
 * @date CR: 04/01/2019
 * @date LU: 09/01/2019
 */

#ifndef PROJET_S3_UNINOMIALES_H
#define PROJET_S3_UNINOMIALES_H

#include "utils_sd.h"

void uninomiale_simple(t_mat_char_star_dyn matcsv, int *votes, int *indVainqueur, int *blanc);
void uninomiale_double(t_mat_char_star_dyn matcsv, int *votesT1, int *indVainqueur1, int *indVainqueur2, int *votesT2, int *indVainqueur, int *blanc);

#endif //PROJET_S3_UNINOMIALES_H
