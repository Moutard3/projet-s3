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

#include "global.h"
#include "liste.h"
#include "utils_sd.h"
#include "uninomiales.h"

/**
 * @brief Entrée du programme
 * @return EXIT_SUCCESS Arrêt normal du programme
 * @return EXIT_FAILURE Erreur d'argument dans l'appel du programme
 */
int main(int argc, char* argv[]) {
    int fileType = -1;
    char* filePath = "";

    t_enum_methodes methodes[6];
    int nbMethodes = 0;
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

        else if (strcmp(argv[i], "-m") == 0) {
            if (strcmp(argv[i + 1], "uni1") == 0) {
                methodes[nbMethodes++] = UNI1;
            } else if (strcmp(argv[i + 1], "uni2") == 0) {
                methodes[nbMethodes++] = UNI2;
            } else if (strcmp(argv[i + 1], "cm") == 0) {
                methodes[nbMethodes++] = CM;
            } else if (strcmp(argv[i + 1], "cp") == 0) {
                methodes[nbMethodes++] = CP;
            } else if (strcmp(argv[i + 1], "cs") == 0) {
                methodes[nbMethodes++] = CS;
            } else if (strcmp(argv[i + 1], "va") == 0) {
                methodes[nbMethodes++] = VA;
            }
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

    // -m absent
    if (nbMethodes == 0) {
        methodes[nbMethodes++] = CM;
        methodes[nbMethodes++] = CP;
        methodes[nbMethodes++] = CS;
        if (fileType == 1) {
            methodes[nbMethodes++] = UNI1;
            methodes[nbMethodes++] = UNI2;
            methodes[nbMethodes++] = VA;
        }
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
    //affiche_t_mat_char_star_dyn(matcsv, stdout);

    // Créer matrice des duels
    t_mat_int_dyn matduel;
    // -i
    if (fileType == 1) {
        matcsv.offset = 3;
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
        //affiche_t_mat_int_dyn(matduel, stdout);
    }

    for (int i = 0; i < nbMethodes; i++) {
        if (methodes[i] == UNI1) {
            int *votes = creer_tab_int(matcsv.nbCol-matcsv.offset);
            int indVainqueur, blanc;

            printf("\nUNINOMIALE SIMPLE:\n");
            uninomiale_simple(matcsv, votes, &indVainqueur, &blanc);
            printf("Nombre de votes nuls pour uninominal : %d\n", blanc);
            // Sans retirer les votes blancs des votes (comme dans res_uni1)
            printf("Mode de scrutin: %s, %d candidats, %d votants, vainqueur = %s, score = %d%%\n", "Uninomiale à un tour", matcsv.nbCol-matcsv.offset, matcsv.nbRows-1, matcsv.tab[0][indVainqueur+matcsv.offset], (votes[indVainqueur]*100)/(matcsv.nbRows-1));
            // En retirant les votes blancs des votes:
            // printf("Mode de scrutin: %s, %d candidats, %d votants, vainqueur = %s, score = %d%%\n", "Uninomiale à un tour", matcsv.nbCol-matcsv.offset, matcsv.nbRows-1, matcsv.tab[0][indVainqueur+matcsv.offset], (votes[indVainqueur]*100)/(matcsv.nbRows-1-blanc));
        } else if (methodes[i] == UNI2) {
            int *votesT1 = creer_tab_int(matcsv.nbCol-matcsv.offset), *votesT2 = creer_tab_int(2);
            int indVainqueur, indVainqueur1, indVainqueur2, blanc;

            printf("\nUNINOMIALE DOUBLE:\n");
            uninomiale_double(matcsv, votesT1, &indVainqueur1, &indVainqueur2, votesT2, &indVainqueur, &blanc);
            printf("Nombre de votes nuls pour uninominal : %d\n", blanc);
            printf("Mode de scrutin: %s, tour %d, %d candidats, %d votants, vainqueur = %s, score = %d%%\n", "Uninomiale à deux tour", 1, matcsv.nbCol-matcsv.offset, matcsv.nbRows-1, matcsv.tab[0][indVainqueur1+matcsv.offset], (votesT1[indVainqueur1]*100)/(matcsv.nbRows-1));
            printf("Mode de scrutin: %s, tour %d, %d candidats, %d votants, vainqueur = %s, score = %d%%\n", "Uninomiale à deux tour", 1, matcsv.nbCol-matcsv.offset, matcsv.nbRows-1, matcsv.tab[0][indVainqueur2+matcsv.offset], (votesT1[indVainqueur2]*100)/(matcsv.nbRows-1));
            printf("Mode de scrutin: %s, tour %d, %d candidats, %d votants, vainqueur = %s, score = %d%%\n", "Uninomiale à deux tour", 2, 2, matcsv.nbRows-1, matcsv.tab[0][indVainqueur+matcsv.offset], (votesT2[(indVainqueur == indVainqueur1)?(0):(1)]*100)/(matcsv.nbRows-1));
        }
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