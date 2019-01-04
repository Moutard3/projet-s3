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

/*
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))
*/

/// Arc pondéré
typedef struct s_arc_p{
    int orig; ///< Origine de l'arc
    int dest; ///< Destination de l'arc
    int poids; ///< Poids de l'arc
} t_arc_p; ///< Définit le type t_arc_p comme struct s_arc_p

/// pour encapsuler des tableaux dynamiques d'entiers avec la dimension.
typedef struct s_tab_dyn{
    int * tab; ///< Le tableau dynamique
    int dim; ///< La dimension du tableau
} t_tab_int_dyn; ///< Définit le type t_tab_int_dyn comme struct s_tab_dyn

/// pour encapsuler des matrices dynamiques d'entiers avec les lignes et colonnes.
typedef struct s_mat_dyn{
    int ** tab; ///< La matrice dynamique
    int nbRows; ///< Le nombre de lignes
    int nbCol; ///< Le nombre de colonnes
} t_mat_int_dyn; ///< Définit le type t_mat_int_dyn comme struct s_mat_dyn

/// pour encapsuler des matrices dynamiques de chaînes avec les lignes, colonnes et nb colonnes avant les candidats.
typedef struct s_mat_char_dyn{
    char *** tab; ///< Matrice dynamique
    int nbRows; ///< Nombre de lignes
    int nbCol; ///< Nombre de colonnes
    int offset; ///< Nombre de colonnes avant celles des candidats
} t_mat_char_star_dyn; ///< Définit le type t_mat_char_star_dyn comme struct s_mat_char_dyn


#endif //PROJET_S3_GLOBAL_H
