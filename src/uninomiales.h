/**
 * @file uninomiales.h
 * @brief Méthodes unimoniales
 * @author Alexandre Saillet
 * @date CR: 04/01/2019
 * @date LU: 04/01/2019
 */

#ifndef PROJET_S3_UNINOMIALES_H
#define PROJET_S3_UNINOMIALES_H

#include "utils_sd.h"

void uninomiale_simple(t_mat_char_star_dyn matcsv, int *votes, int *indVainqueur);
void uninomiale_double(t_mat_char_star_dyn matcsv, int *votes, int *indVainqueur);

#endif //PROJET_S3_UNINOMIALES_H
