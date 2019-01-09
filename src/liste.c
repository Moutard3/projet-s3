/**
 * @file liste.c
 * @brief 
 * @author Alexandre Saillet
 * @date CR 01/11/2018
 * @date LU 06/01/2019
 */

#include "liste.h"

/**
 * @brief Renvoie le nombre d'éléments dans une liste
 * @param[in] lst : Liste
 * @return int nombre d'éléments
 */
int nbEltList(liste lst) {
    return lst.nbElt;
}

/**
 * @brief Initialise une liste
 * @param[in] p : Liste
 */
void createList(liste *p) {
    p->Tete = 0;
    p->nbElt = 0;
}

/**
 * @brief Ajoute un élément au début d'une liste
 * @param[in] p : Liste
 * @param[in] e : Element à ajouter
 */
void addFrontList(liste *p, Elementliste e) {
    if (!fullList(*p)) {
        if (p->Tete > 0) {
            p->Tete--;
        } else {
            for (int i = nbEltList(*p) + 1; i > 0; i--) {
                swapEltList(&p->Tabliste[i], &p->Tabliste[i - 1]);
            }
        }
        copie_element(&p->Tabliste[p->Tete], e);
        p->nbElt++;
    }
}

/**
 * @brief Ajoute un élément à la fin d'une liste
 * @param[in] p : Liste
 * @param[in] e : Element à ajouter
 */
void addTailList(liste *p, Elementliste e) {
    if (!fullList(*p)) {
        if (p->Tete + p->nbElt == DIMMAX) {
            for (int i = p->Tete-1; i < p->nbElt; i++) {
                swapEltList(&p->Tabliste[i], &p->Tabliste[i + 1]);
            }
            p->Tete--;
        }
        copie_element(&p->Tabliste[p->Tete+p->nbElt], e);
        p->nbElt++;
    }
}

/**
 * @brief Supprime le dernier élément d'une liste
 * @param[in] p : Liste
 */
void delTailList(liste *p) {
    Elementliste e, f;
    if (!emptyList(*p)) {
        p->nbElt--;
    }
}

/**
 * @brief Supprime le premier élément d'une liste
 * @param[in] p : Liste
 */
void delFrontList(liste *p) {
    if (!emptyList(*p)) {
        p->Tete++;
        p->nbElt--;
    }
}

/**
 * @brief Renvoie l'élément en tête d'une liste
 * @param[in] p : Liste
 * @param[out] e : Element renvoyé
 */
void headList(liste p, Elementliste *e) {
    if (!emptyList(p)) {
        pickEltList(p, e, 0);
    }
}

/**
 * @brief Renvoie le dernier élément d'une liste
 * @param[in] p : Liste
 * @param[out] e : Element renvoyé
 */
void tailList(liste p, Elementliste *e) {
    if (!emptyList(p)) {
        pickEltList(p, e, p.nbElt-1);
    }
}

/**
 * @brief Renvoie si la liste est vide
 * @param[in] p : Liste
 * @return bool true=vide, false=pas vide
 */
bool emptyList(liste p) {
    return p.nbElt == 0;
}

/**
 * @brief Renvoie si la liste est pleine (par rapport à la const DIMMAX)
 * @param[in] p : Liste
 * @return bool true=pleine, false=pas pleine
 */
bool fullList(liste p) {
    return p.nbElt == DIMMAX;
}

/**
 * @brief Affiche la liste sur le fichier fp
 * @param[in] p : Liste
 * @param[in] fp : Fichier où écrire
 */
void dumpList(liste p,FILE *fp) {
    Elementliste e;
    for (int i=0; i<p.nbElt; i++) {
        pickEltList(p, &e, i);
        afficher_element(e, fp);
    }
    fprintf(fp, "\n");
}

/**
 * @brief Echange deux éléments
 * @param[in,out] a : Element 1
 * @param[in,out] b : Element 2
 */
void swapEltList(Elementliste *a,Elementliste *b) {
    Elementliste c;
    copie_element(&c, *a);
    copie_element(a, *b);
    copie_element(b, c);
}

/**
 * @brief Trie une liste avec la méthode Bubble (décroissant)
 * @param[in,out] p : Liste à trier
 */
void bubbleSortList(liste *p) {
    for (int i=nbEltList(*p); i>0; i--) {
        bool sorted = true;
        for (int j=0; j<i; j++) {
            if (p->Tabliste[p->Tete+j].poids < p->Tabliste[p->Tete+j+1].poids) {
                swapEltList(&p->Tabliste[p->Tete+j+1], &p->Tabliste[p->Tete+j]);
                sorted = false;
            }
        }
        if (sorted) break;
    }
}

/**
 * @brief Récupère un élément d'une liste
 * @param[in] l : Liste
 * @param[out] e : Element
 * @param[in] index : Index de l'élément
 */
void pickEltList(liste l,Elementliste *e,int index) {
    if (nbEltList(l) > index) {
        copie_element(e, l.Tabliste[l.Tete+index]);
    }
    /*
    else {
        printf("ERR\n");
    }
     */
}

/**
 * @brief Cherche si un élément est dans une liste
 * @param[in] p : Liste où chercher
 * @param[in] e : Element à chercher
 * @return bool true=trouvé, false=pas trouvé
 */
bool belongEltList(liste p,Elementliste e) {
    Elementliste t_e;
    for (int i=0; i<p.nbElt; i++) {
        pickEltList(p, &t_e, i);
        if (cmp_elements(e, t_e)) {
            return true;
        }
    }
    return false;
}
