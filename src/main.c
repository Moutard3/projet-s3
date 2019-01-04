/**
 * @file main.c
 * @brief 
 * @author Vincent Dugat
 * @author Alexandre Saillet
 * @date CR: 01/11/2018
 * @date LU: 04/01/2019
 */

#include <stdio.h>
#include <stdbool.h>

#include "liste.h"
#include "utils_sd.h"

/**
 * @brief Entrée du programme
 * @return EXIT_SUCCESS Arrêt normal du programme
 * @return EXIT_FAILURE Erreur d'argument dans l'appel du programme
 */
int main(int argc, char* argv[]) {
    int fileType = -1;
    char* filePath = "";
    for (int i = 1; i < argc; i++) {
        // -i ou -d déjà présent
        if ((strcmp(argv[i], "-i") == 0 || strcmp(argv[i], "-d") == 0) && fileType != -1) {
            fprintf(stderr, "Les arguments -i et -d sont incompatibles et doivent être uniques.\n");
            exit(EXIT_FAILURE);
        }

        // -i
        if (strcmp(argv[i], "-i") == 0) {
            fileType = 1;
            filePath = argv[i+1];
        }

        // -d
        else if (strcmp(argv[i], "-d") == 0) {
            fileType = 2;
            filePath = argv[i+1];
        }

        // TODO: -l
        else if (strcmp(argv[i], "-l") == 0) {

        }

        // TODO: -m
        else if (strcmp(argv[i], "-m") == 0) {

        }
    }

    // NI -i NI -d
    if (fileType == -1) {
        fprintf(stderr, "L'argument -i ou -d doit être présent.\n");
        exit(EXIT_FAILURE);
    }

    // -i ou -d en dernier argument
    if (filePath == NULL) {
        fprintf(stderr, "La valeur de -i ou -d ne peut être nulle.\n");
        exit(EXIT_FAILURE);
    }

    FILE* filep = fopen(filePath, "r");
    // Le fichier n'a pas pu être ouvert
    if (!filep) {
        fprintf(stderr, "Le fichier %s n'est pas accessible en lecture.\n", filePath);
        exit(EXIT_FAILURE);
    }


    // Lit le CSV
    t_mat_char_star_dyn matcsv;
    creer_t_mat_char_dyn(&matcsv);
    csv_to_t_tab_mat_str_dyn(filep, &matcsv, '\t');
    affiche_t_mat_char_star_dyn(matcsv, stdout);

    // Créer matrice des duels
    t_mat_int_dyn matduel;
    // -i
    if (fileType == 1) {
        matcsv.offset = 5;
        // TODO
    }
    // -d
    else {
        matcsv.offset = 0;
        creer_t_mat_int_dyn(&matduel, matcsv.nbRows-1, matcsv.nbCol-matcsv.offset);
        int a=0, b=0;
        for (int i = 1; i < matcsv.nbRows; i++) {
            for (int j = matcsv.offset; j < matcsv.nbCol; j++) {
                matduel.tab[a][b++] = (int) strtol(matcsv.tab[i][j], NULL, 10);
                //printf("%s == %ld == %d == (%d,%d)=%d\n", matcsv.tab[i][j], strtol(matcsv.tab[i][j], NULL, 10), (int)strtol(matcsv.tab[i][j], NULL, 10), a, b-1, matduel.tab[a][b-1]);
            }
            a++;
            b=0;
        }
        printf("\n");
        affiche_t_mat_int_dyn(matduel, stdout);
    }
}

/**
 * @brief Permet de tester la lecture d'un CSV
 */
void test_lecture_csv() {
    t_mat_char_star_dyn tabmots;
    creer_t_mat_char_dyn(&tabmots);

    FILE* filep = fopen("../../file.csv", "r");
    if (filep) {
        printf("Fichier\n");
        csv_to_t_tab_mat_str_dyn(filep, &tabmots, '\t');
        printf("Lu\n");
        affiche_t_mat_char_star_dyn(tabmots, stdout);
        printf("Affiché\n");

        fclose(filep);
    } else {
        printf("Erreur\n");
    }
}

/**
 * @brief Permet de tester les listes (de liste.c)
 */
void test_liste() {
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
}