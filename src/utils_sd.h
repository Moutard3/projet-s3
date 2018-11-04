/**
 * @file utils_sd.h
 * @brief Fonctions utilitaires en rapport avec les structures de données.
 * @author Alexandre Saillet
 * @date CR: 02/11/2018
 * @date LU: 04/11/2018
 */

#ifndef PROJET_S3_UTILS_SD_H
#define PROJET_S3_UTILS_SD_H

#include "global.h"

int * creer_tab_int(int dim); // juste un malloc de dim cases
int ** creer_mat_int(int nbRows,int nbCol); // malob 2D
void affiche_tab_int(int *tab,int dim, FILE *logfp);

void creer_t_mat_int_dyn(t_mat_int_dyn *stTab,int nbRows,int nbCol); // utilise la struct
void creer_t_tab_int_dyn(t_tab_int_dyn *stTab,int dim); // idem
void creer_t_mat_char_dyn(t_mat_char_star_dyn * s_tabmots);
void affiche_t_tab_int_dyn(t_tab_int_dyn t_tab, FILE *logfp);
void affiche_t_mat_char_star_dyn(t_mat_char_star_dyn t_tabmots, FILE *logfp);
void affiche_t_mat_int_dyn(t_mat_int_dyn t_tab, FILE *logfp);
void affiche_mat_int(int **duels_mat,int nbRows,int nbCol,FILE *logfp);

void init_tab_int(int *tab,int dim,int valeur);// initialise avec une valeur
void init_mat_int(int **mat,int nbRows,int nbCol,int valeur); // idem

void csv_to_t_tab_mat_str_dyn(FILE *csvfp, t_mat_char_star_dyn * tabmots, char separator, int offset);

#endif //PROJET_S3_UTILS_SD_H
