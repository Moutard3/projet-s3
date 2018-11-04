/**
 * @file elementliste.c
 * @brief 
 * @author Alexandre Saillet
 * @date 01/11/2018
 */

#include "elementliste.h"

/**
 * @brief Permet de saisir un élément d'une liste
 * @param[out] e : Element de la liste saisi
 */
void saisie_element(Elementliste *e) {
    printf("Nouvel élément !\n");
    printf("Origine: ");
    scanf("%d", &e->orig);
    printf("Destination: ");
    scanf("%d", &e->dest);
    printf("Poids: ");
    scanf("%d", &e->poids);
}

/**
 * @brief Copie un élément vers un autre
 * @param[out] cible : Elément vers lequel copier
 * @param[in] source : Elément à copier
 */
void copie_element(Elementliste *cible, Elementliste source) {
    cible->orig = source.orig;
    cible->dest = source.dest;
    cible->poids = source.poids;
}

/**
 * @brief Affiche un élément vers un fichier
 * @param[in] e : Elément à afficher
 * @param[in] fp : Fichier où afficher
 */
void afficher_element(Elementliste e,FILE *fp) {
    fprintf(fp, "(%d, %d, %d) ", e.orig, e.dest, e.poids);
}

/**
 * @brief Compare l'égalité de deux éléments
 * @param[in] e1 : Elément 1
 * @param[in] e2 : Elément 2
 * @return bool true=égaux, false=pas égaux
 */
bool cmp_elements(Elementliste e1,Elementliste e2) {
    return (e1.orig == e2.orig && e1.dest == e2.dest && e1.poids == e2.poids);
}