/**
 * @file main.c
 * @brief 
 * @author Vincent Dugat
 * @author Alexandre Saillet
 * @date CR: 01/11/2018
 * @date LU: 06/01/2019
 */

#include <stdio.h>
#include <stdbool.h>

#include "global.h"
#include "liste.h"
#include "utils_sd.h"
#include "uninomiales.h"
#include "condorcet.h"

void lireArguments(int argc, char* argv[], int *nbMethodes, t_enum_methodes *methodes, int *fileType, char **filePath) {
    for (int i = 1; i < argc; i++) {
        // -i ou -d déjà présent
        if ((strcmp(argv[i], "-i") == 0 || strcmp(argv[i], "-d") == 0) && *fileType != -1) {
            fprintf(stderr, "Les arguments -i et -d sont incompatibles et doivent être uniques.\n");
            exit(EXIT_FAILURE);
        }

        // -i
        if (strcmp(argv[i], "-i") == 0) {
            *fileType = 1;
            *filePath = argv[i+1];
        }

        // -d
        else if (strcmp(argv[i], "-d") == 0) {
            for (int j = 0; j < *nbMethodes; j++) {
                if (methodes[j] == UNI1 || methodes[j] == UNI2 || methodes[j] == VA) {
                    fprintf(stderr, "Une des méthodes nécessite des ballots, -d est donc incompatible, utilisez -i.\n");
                    exit(EXIT_FAILURE);
                }
            }
            *fileType = 2;
            *filePath = argv[i+1];
        }

        // TODO: -l
        else if (strcmp(argv[i], "-l") == 0) {

        }

        else if (strcmp(argv[i], "-m") == 0) {
            if (strcmp(argv[i + 1], "uni1") == 0) {
                if (*fileType == 2) {
                    fprintf(stderr, "La méthode uninomiale à un tour nécessite des ballots, -d est donc incompatible, utilisez -i.\n");
                    exit(EXIT_FAILURE);
                }
                methodes[(*nbMethodes)++] = UNI1;
            } else if (strcmp(argv[i + 1], "uni2") == 0) {
                if (*fileType == 2) {
                    fprintf(stderr, "La méthode uninomiale à deux tours nécessite des ballots, -d est donc incompatible, utilisez -i.\n");
                    exit(EXIT_FAILURE);
                }
                methodes[(*nbMethodes)++] = UNI2;
            } else if (strcmp(argv[i + 1], "cm") == 0) {
                methodes[(*nbMethodes)++] = CM;
            } else if (strcmp(argv[i + 1], "cp") == 0) {
                methodes[(*nbMethodes)++] = CP;
            } else if (strcmp(argv[i + 1], "cs") == 0) {
                methodes[(*nbMethodes)++] = CS;
            } else if (strcmp(argv[i + 1], "va") == 0) {
                if (*fileType == 2) {
                    fprintf(stderr, "La méthode vote alternatif nécessite des ballots, -d est donc incompatible, utilisez -i.\n");
                    exit(EXIT_FAILURE);
                }
                methodes[(*nbMethodes)++] = VA;
            }
        }
    }
}

void verifArguments(int fileType, const char* filePath) {
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
}

void remplirMethodes(int fileType, t_enum_methodes *methodes, int *nbMethodes) {
    methodes[(*nbMethodes)++] = CM;
    methodes[(*nbMethodes)++] = CP;
    methodes[(*nbMethodes)++] = CS;
    if (fileType == 1) {
        methodes[(*nbMethodes)++] = UNI1;
        methodes[(*nbMethodes)++] = UNI2;
        methodes[(*nbMethodes)++] = VA;
    }
}

void creerMatCsv(char* filePath, t_mat_char_star_dyn *matcsv) {
    FILE* filep = fopen(filePath, "r");
    // Le fichier n'a pas pu être ouvert
    if (!filep) {
        fprintf(stderr, "Le fichier %s n'est pas accessible en lecture.\n", filePath);
        exit(EXIT_FAILURE);
    }

    // Lit le CSV
    creer_t_mat_char_dyn(matcsv);
    csv_to_t_tab_mat_str_dyn(filep, matcsv, '\t');

    fclose(filep);
}

void creerMatDuel(int fileType, t_mat_char_star_dyn *matcsv, t_mat_int_dyn *matduel) {
    // -i
    if (fileType == 1) {
        matcsv->offset = 3;
        creer_t_mat_int_dyn(matduel, matcsv->nbCol-matcsv->offset, matcsv->nbCol-matcsv->offset);
        init_mat_int(matduel->tab, matduel->nbRows, matduel->nbCol, 0);

        for (int i = 1; i < matcsv->nbRows; i++) {
            for (int j = matcsv->offset; j < matcsv->nbCol; j++) {
                for (int k = matcsv->offset; k < matcsv->nbCol; k++) {
                    if (k != j && strtol(matcsv->tab[i][j], NULL, 10) < strtol(matcsv->tab[i][k], NULL, 10)) {
                        matduel->tab[j-matcsv->offset][k-matcsv->offset]++;
                    }
                }
            }
        }
    }
    // -d
    else {
        matcsv->offset = 0;
        creer_t_mat_int_dyn(matduel, matcsv->nbCol-matcsv->offset, matcsv->nbCol-matcsv->offset);
        int a=0, b=0;
        for (int i = 1; i < matcsv->nbRows; i++) {
            for (int j = matcsv->offset; j < matcsv->nbCol; j++) {
                matduel->tab[a][b++] = (int) strtol(matcsv->tab[i][j], NULL, 10);
            }
            a++;
            b=0;
        }
    }
}

void creerArcsDuel(liste *larcs, t_mat_int_dyn matduel) {
    createList(larcs);
    for (int i = 0; i < matduel.nbRows; i++) {
        for (int j = 0; j < matduel.nbCol; j++) {
            if (matduel.tab[i][j] > matduel.tab[j][i]) {
                Elementliste e;
                e.orig = i;
                e.dest = j;
                e.poids = matduel.tab[i][j];
                addFrontList(larcs, e);
            }
        }
    }
}

void genererGraphPython(char* baseFilePath, char* destFilePath, liste larcs) {
    FILE* pyTestFile = fopen(baseFilePath, "r");
    FILE* pyGraphFile = fopen(destFilePath, "w");
    if (!pyTestFile) {
        fprintf(stderr, "\nVérifiez que le fichier pollTests.py est bien présent à côté de l'executable.\n\n");
    } else if (!pyGraphFile) {
        fclose(pyTestFile);
        fprintf(stderr, "\nImpossible de créer le fichier pollGraph.py à côté de l'executable.\n\n");
    } else {
        char line[255];
        while( fgets(line, 255, pyTestFile) ) {
            if (strcmp(line, "# ajouter les arcs ici\n") != 0) {
                fprintf(pyGraphFile, "%s", line);
            } else {
                for (int i = 0; i < nbEltList(larcs); i++) {
                    Elementliste e;
                    pickEltList(larcs, &e, i);
                    fprintf(pyGraphFile, "G.add_edges_from([(%d,%d)],weight=%d)\n", e.orig, e.dest, e.poids);
                }
            }
        }

        fclose(pyTestFile);
        fclose(pyGraphFile);
    }
}

/**
 * @brief Permet de tester la lecture d'un CSV
 */
void test_lecture_csv() {
    t_mat_char_star_dyn tabmots;
    creer_t_mat_char_dyn(&tabmots);

    FILE* filep = fopen("file.csv", "r");
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

    printf("\n\nDelFront\n");
    delFrontList(&p);
    dumpList(p, stdout);

    printf("\nDelTail\n");
    delTailList(&p);
    dumpList(p, stdout);
}

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

    lireArguments(argc, argv, &nbMethodes, methodes, &fileType, &filePath);
    verifArguments(fileType, filePath);
    if (nbMethodes == 0) {
        remplirMethodes(fileType, methodes, &nbMethodes);
    }

    t_mat_char_star_dyn matcsv;
    creerMatCsv(filePath, &matcsv);
    //affiche_t_mat_char_star_dyn(matcsv, stdout);

    t_mat_int_dyn matduel;
    creerMatDuel(fileType, &matcsv, &matduel);
    affiche_t_mat_int_dyn(matduel, stdout);

    liste larcs;
    creerArcsDuel(&larcs, matduel);
    //dumpList(larcs, stdout);

    char* baseFilePath = "../../pollTests.py";
    char* destFilePath = "../../pollGraph.py";
    genererGraphPython(baseFilePath, destFilePath, larcs);

    for (int i = 0; i < nbMethodes; i++) {
        if (methodes[i] == UNI1) {
            int *votes = creer_tab_int(matcsv.nbCol-matcsv.offset);
            int indVainqueur, blanc;

            //printf("\nUNINOMIALE SIMPLE:\n");
            uninomiale_simple(matcsv, votes, &indVainqueur, &blanc);
            printf("Nombre de votes nuls pour uninominal : %d\n", blanc);
            // Sans retirer les votes blancs des votes (comme dans res_uni1)
            printf("Mode de scrutin: %s, %d candidats, %d votants, vainqueur = %s, score = %d%%\n", "Uninomiale à un tour", matduel.nbRows, matcsv.nbRows-1, matcsv.tab[0][indVainqueur+matcsv.offset], (votes[indVainqueur]*100)/(matcsv.nbRows-1));
            // En retirant les votes blancs des votes:
            // printf("Mode de scrutin: %s, %d candidats, %d votants, vainqueur = %s, score = %d%%\n", "Uninomiale à un tour", matcsv.nbCol-matcsv.offset, matcsv.nbRows-1, matcsv.tab[0][indVainqueur+matcsv.offset], (votes[indVainqueur]*100)/(matcsv.nbRows-1-blanc));

            free(votes);
        } else if (methodes[i] == UNI2) {
            int *votesT1 = creer_tab_int(matcsv.nbCol-matcsv.offset), *votesT2 = creer_tab_int(2);
            int indVainqueur, indVainqueur1, indVainqueur2, blanc;

            //printf("\nUNINOMIALE DOUBLE:\n");
            uninomiale_double(matcsv, votesT1, &indVainqueur1, &indVainqueur2, votesT2, &indVainqueur, &blanc);
            printf("Nombre de votes nuls pour uninominal : %d\n", blanc);
            printf("Mode de scrutin: %s, tour %d, %d candidats, %d votants, vainqueur = %s, score = %d%%\n", "Uninomiale à deux tour", 1, matduel.nbRows, matcsv.nbRows-1, matcsv.tab[0][indVainqueur1+matcsv.offset], (votesT1[indVainqueur1]*100)/(matcsv.nbRows-1));
            printf("Mode de scrutin: %s, tour %d, %d candidats, %d votants, vainqueur = %s, score = %d%%\n", "Uninomiale à deux tour", 1, matduel.nbRows, matcsv.nbRows-1, matcsv.tab[0][indVainqueur2+matcsv.offset], (votesT1[indVainqueur2]*100)/(matcsv.nbRows-1));
            printf("Mode de scrutin: %s, tour %d, %d candidats, %d votants, vainqueur = %s, score = %d%%\n", "Uninomiale à deux tour", 2, 2, matcsv.nbRows-1, matcsv.tab[0][indVainqueur+matcsv.offset], (votesT2[(indVainqueur == indVainqueur1)?(0):(1)]*100)/(matcsv.nbRows-1));

            free(votesT1);
            free(votesT2);
        } else if (methodes[i] == CM) {
            int indVainqueur;

            if(!circuits(larcs, matduel.nbRows)) {
                chercherVainqueurCondorcet(larcs, &indVainqueur, matduel.nbRows);
            } else {
                chercherVainqueurMinimax(matduel, &indVainqueur);
            }

            printf("Mode de scrutin : %s, %d candidats, %d votants, vainqueur = %s\n", "Condorcet minimax",  matduel.nbRows, matcsv.nbRows-1, matcsv.tab[0][indVainqueur+matcsv.offset]);
        } else if (methodes[i] == CP) {
            int indVainqueur;

            if(!circuits(larcs, matduel.nbRows)) {
                chercherVainqueurCondorcet(larcs, &indVainqueur, matduel.nbRows);
            } else {
                chercherVainqueurPaires(larcs, &indVainqueur, matduel.nbRows);
            }

            printf("Mode de scrutin : %s, %d candidats, %d votants, vainqueur = %s\n", "Condorcet paires",  matduel.nbRows, matcsv.nbRows-1, matcsv.tab[0][indVainqueur+matcsv.offset]);
        } else if (methodes[i] == CS) {

        } else if (methodes[i] == VA) {

        }
    }

    for (int i=0; i<matcsv.nbRows; i++) {
        for (int j=0; j<matcsv.nbCol; j++) {
            free(matcsv.tab[i][j]);
        }
        free(matcsv.tab[i]);
    }
    free(matcsv.tab);
    for (int i=0; i<matduel.nbRows; i++) {
        free(matduel.tab[i]);
    }
    free(matduel.tab);

    return 0;
}
