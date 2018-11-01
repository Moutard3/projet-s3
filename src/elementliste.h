/**
 * @file elementliste.h
 * @brief Element d'une liste statique
 * @author Vincent Dugat
 * @date 2018
 */

#ifndef PROJET_S3_ELEMENTLISTE_H
#define PROJET_S3_ELEMENTLISTE_H

#include "global.h" // définit le type t_arc_p

typedef t_arc_p Elementliste; ///< Définit les éléments de la liste comme des arcs pondérés
void saisie_element(Elementliste *e);
void copie_element(Elementliste *cible, Elementliste source);
void afficher_element(Elementliste e,FILE *fp);
bool cmp_elements(Elementliste e1,Elementliste e2);

#endif //PROJET_S3_ELEMENTLISTE_H
