/**
 * @file main.c
 * @brief 
 * @author Vincent Dugat
 * @author Alexandre Saillet
 * @date 01/11/2018
 */

#include <stdio.h>
#include <stdbool.h>

#include "liste.h"

/**
 * @brief Entrée du programme
 * @return EXIT_SUCCESS Arrêt normal du programme
 */
int main() {
    liste p;
    Elementliste e1, e2, e;

    /*
    saisie_element(&e1);
    saisie_element(&e2);
     */

    e1.orig = 1;
    e1.dest = 2;
    e1.poids = 15;

    e2.orig = 2;
    e2.dest = 1;
    e2.poids = 35;

    createList(&p); // initialisation à vide

    printf("liste créée\n");
    if (emptyList(p))
        printf("elle est vide\n");
    else
        printf("elle n'est pas vide et c'est un pb\n");

    /* Remplissage de la liste */
    addTailList(&p, e1);
    addTailList(&p, e2);
    //saisie_element(&e2);
    e2.orig = 3;
    e2.dest = 1;
    e2.poids = 37;
    addTailList(&p, e2);
    //saisie_element(&e2);
    e2.orig = 1;
    e2.dest = 3;
    e2.poids = 5;
    addTailList(&p, e2);

    printf("4 éléments entrés dans la liste\n");

    /* on affiche */
    printf("** ");
    dumpList(p, stdout);
    printf("** \n");

    printf("Tri :\n");
    bubbleSortList(&p);
    dumpList(p, stdout);

    addFrontList(&p, e2);
    printf("** \n");
    dumpList(p, stdout);
    printf("Nb elt=%d\n", nbEltList(p));
    pickEltList(p, &e, 2);
    printf("Element :");
    afficher_element(e, stdout);
    printf("\nbelong ? %d\n", belongEltList(p, e1));
    afficher_element(e, stdout);

    return EXIT_SUCCESS;
}

