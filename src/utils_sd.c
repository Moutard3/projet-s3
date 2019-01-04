/**
 * @file utils_sd.c
 * @brief 
 * @author Alexandre Saillet
 * @date CR: 02/11/2018
 * @date LU: 04/01/2019
 */

#include <malloc.h>
#include "utils_sd.h"

/**
 * @brief Crée un tableau d'entiers
 * @param[in] dim : Dimension du tableau
 * @return int* tableau
 */
int * creer_tab_int(int dim) {
    return malloc(dim*sizeof(int));
}

/**
 * @brief Crée une matrice d'entiers
 * @param[in] nbRows : Nombre de lignes
 * @param[in] nbCol : Nombre de colonnes
 * @return int** matrice
 */
int ** creer_mat_int(int nbRows,int nbCol) {
    int** tab = malloc(nbRows*sizeof(int*));
    for (int i=0; i<nbRows; i++) {
        tab[i] = creer_tab_int(nbCol);
    }
    return tab;
}

/**
 * @brief Affiche un tableau d'entiers dans un fichier
 * @param[in] tab : Le tableau d'entiers
 * @param[in] dim : La dimension du tableau
 * @param[in] logfp : Le fichier où afficher
 */
void affiche_tab_int(int *tab,int dim, FILE *logfp) {
    for (int i=0; i<dim; i++) {
        fprintf(logfp, "%d\t", *(tab+i));
    }
}

/**
 * @brief Affiche une matrice d'entiers dans un fichier
 * @param[in] duels_mat : La matrice
 * @param[in] nbRows : Le nombre de lignes
 * @param[in] nbCol : Le nombre de colonnes
 * @param[in] logfp : Le fichier où afficher
 */
void affiche_mat_int(int **duels_mat,int nbRows,int nbCol,FILE *logfp) {
    for (int i=0; i<nbRows; i++) {
        affiche_tab_int(*(duels_mat+i), nbCol, logfp);
        fprintf(logfp, "\n");
    }
}


/**
 * @brief Crée un t_tab_int_dyn
 * @param[out] stTab : Le t_tab_int_dyn
 * @param[in] dim : La dimension
 */
void creer_t_tab_int_dyn(t_tab_int_dyn *stTab,int dim) {
    stTab->tab = creer_tab_int(dim);
    stTab->dim = dim;
}

/**
 * @brief Crée un t_mat_int_dyn
 * @param[out] stTab : Le t_mat_int_dyn
 * @param[in] nbRows : Le nombre de lignes
 * @param[in] nbCol : Le nombre de colonnes
 */
void creer_t_mat_int_dyn(t_mat_int_dyn *stTab,int nbRows,int nbCol) {
    stTab->tab = creer_mat_int(nbRows, nbCol);
    stTab->nbCol = nbCol;
    stTab->nbRows = nbRows;
}

/**
 * @brief Crée un t_mat_char_dyn
 * @param[out] s_tabmots : Le t_mat_char_star_dyn
 */
void creer_t_mat_char_dyn(t_mat_char_star_dyn * s_tabmots) {
    s_tabmots->nbCol = 0;
    s_tabmots->nbRows = 0;
    s_tabmots->offset = 0;
    s_tabmots->tab = malloc(sizeof(char**));
}

/**
 * @brief Affiche un t_tab_int_dyn dans un fichier
 * @param[in] t_tab : Le t_tab_int_dyn à afficher
 * @param[in] logfp : Le ficher où afficher
 */
void affiche_t_tab_int_dyn(t_tab_int_dyn t_tab, FILE *logfp) {
    for (int i=0; i<t_tab.dim; i++) {
        affiche_tab_int(t_tab.tab, t_tab.dim, logfp);
    }
}

/**
 * @brief Affiche un t_mat_int_dyn dans un fichier
 * @param[in] t_tab : Le t_mat_int_dyn à afficher
 * @param[in] logfp : Le fichier où afficher
 */
void affiche_t_mat_int_dyn(t_mat_int_dyn t_tab, FILE *logfp) {
    affiche_mat_int(t_tab.tab, t_tab.nbRows, t_tab.nbCol, logfp);
}

/**
 * @brief Affiche un t_mat_char_star_dyn dans un fichier
 * @param[in] t_tabmots : Le t_mat_char_star_dyn à afficher
 * @param[in] logfp : Le fichier où afficher
 */
void affiche_t_mat_char_star_dyn(t_mat_char_star_dyn t_tabmots, FILE *logfp) {
    for (int i=0; i<t_tabmots.nbRows; i++) {
        for (int j=0; j<t_tabmots.nbCol; j++) {
            fprintf(logfp, "%s\t", t_tabmots.tab[i][j]);
        }
        fprintf(logfp, "\n");
    }
}


/**
 * @brief Initialise un tableau d'entiers avec une valeur
 * @param[out] tab : Le tableau d'entiers
 * @param[in] dim : La dimension du tableau
 * @param[in] valeur : La valeur avec laquelle initialiser
 */
void init_tab_int(int *tab,int dim,int valeur) {
    for (int i=0; i<dim; i++) {
        *(tab+i) = valeur;
    }
}

/**
 * @brief Initialise une matrice d'entiers avec une valeur
 * @param[out] mat : La matrice d'entiers
 * @param[in] nbRows : Le nombre de lignes
 * @param[in] nbCol : Le nombre de colonnes
 * @param[in] valeur : La valeur avec laquelle initialiser
 */
void init_mat_int(int **mat,int nbRows,int nbCol,int valeur) {
    for (int i=0; i<nbRows; i++) {
        init_tab_int(*(mat+i), nbCol, valeur);
    }
}

/**
 * Alloue la place nécessaire dans un t_tab_mat_str_dyn d'après le contenu d'un CSV et le remplis avec ce dernier.
 * La ligne 0 du tableau sera la ligne d'en-tête du CSV.
 * @brief Initialise un t_tab_mat_str_dyn avec un CSV
 * @param[in] csvfp : Le fichier CSV
 * @param[out] tabmots : Le t_tab_mat_str_dyn
 * @param[in] separator : Le séparateur entre les colonnes du CSV
 * @param[in] offset : Le nombre de colonne avec celle des candidats
 */
void csv_to_t_tab_mat_str_dyn(FILE *csvfp, t_mat_char_star_dyn * tabmots, char separator) {
    char line[1024];
    bool firstline = true;
    while (fgets(line, 1024, csvfp)) {
        tabmots->tab = realloc(tabmots->tab, sizeof(char **) * ++tabmots->nbRows);
        tabmots->tab[tabmots->nbRows-1] = malloc(sizeof(char *) * tabmots->nbCol);
        //printf("Ligne %d : %s\n", tabmots->nbRows, line);

        char snl[3];
        snl[0] = separator;
        snl[1] = '\n';
        snl[2] = 0;
        int i = 0;
        for (char *tok = strtok(line, snl); tok != NULL; tok = strtok(NULL, snl))
        {
            if (firstline) {
                tabmots->tab[0] = realloc(tabmots->tab[0], sizeof(char *) * ++tabmots->nbCol);
            }
            tabmots->tab[tabmots->nbRows-1][i++] = strdup(tok);
            //printf("%s : %s\n", tabmots->tab[0][i-1], tabmots->tab[tabmots->nbRows-1][i-1]);
        }
        firstline=false;
        //printf("\n");
    }
}