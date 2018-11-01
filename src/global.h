/**
 * @file global.h
 * @brief 
 * @author Vincent Dugat
 * @date 2018
 */

#ifndef PROJET_S3_GLOBAL_H
#define PROJET_S3_GLOBAL_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

/// Arc pondéré
typedef struct s_arc_p{
    int orig; ///< Origine de l'arc
    int dest; ///< Destination de l'arc
    int poids; ///< Poids de l'arc
} t_arc_p; ///< Définit le type t_arc_p comme struct s_arc_p

#endif //PROJET_S3_GLOBAL_H
