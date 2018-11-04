/**
 * @file liste.c
 * @brief 
 * @author Alexandre Saillet
 * @date 01/11/2018
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
    p->Tete = -1;
    p->nbElt = 0;
}

/**
 * @brief Ajoute un élément à la fin (en haut) d'une liste
 * @param[in] p : Liste
 * @param[in] e : Element à ajouter
 */
void addFrontList(liste *p, Elementliste e) {
    if (!fullList(*p)) {
        copie_element(&p->Tabliste[++p->Tete], e);
        p->nbElt++;
    }
}

/**
 * @brief Ajoute un élément au début (en bas) d'une liste
 * @param[in] p : Liste
 * @param[in] e : Element à ajouter
 */
void addTailList(liste *p, Elementliste e) {
    if (!fullList(*p)) {
        if (!emptyList(*p)) {
            for (int i=nbEltList(*p); i>0; i--) {
                swapEltList(&p->Tabliste[i], &p->Tabliste[i-1]);
            }
        }
        copie_element(&p->Tabliste[0], e);
        p->Tete++;
        p->nbElt++;
    }
}

/**
 * @brief Supprime le premier élément (en bas) d'une liste
 * @param[in] p : Liste
 */
void delTailList(liste *p) {
    Elementliste e, f;
    if (!emptyList(*p)) {
        for (int i=0; i<nbEltList(*p); i++) {
            pickEltList(*p, &e, i);
            pickEltList(*p, &f, i+1);
            swapEltList(&e, &f);
        }
        p->Tete--;
        p->nbElt--;
    }
}

/**
 * @brief Supprime le dernier élément (en haut) d'une liste
 * @param[in] p : Liste
 */
void delFrontList(liste *p) {
    if (!emptyList(*p)) {
        p->Tete--;
        p->nbElt--;
    }
}

/**
 * @brief Renvoie le dernier élément (en haut) d'une liste
 * @param[in] p : Liste
 * @param[out] e : Element renvoyé
 */
void headList(liste p, Elementliste *e) {
    if (!emptyList(p)) {
        pickEltList(p, e, p.Tete);
    }
}

/**
 * @brief Renvoie le premier élément (en bas) d'une liste
 * @param[in] p : Liste
 * @param[out] e : Element renvoyé
 */
void tailList(liste p, Elementliste *e) {
    if (!emptyList(p)) {
        pickEltList(p, e, 0);
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
    for (int i=0; i<=p.Tete; i++) {
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
 * @brief Trie une liste avec la méthode Bubble
 * @param[in,out] p : Liste à trier
 */
void bubbleSortList(liste *p) {
    for (int i=nbEltList(*p)-1; i>0; i--) {
        bool sorted = true;
        for (int j=0; j<i; j++) {
            if (p->Tabliste[j].poids > p->Tabliste[j+1].poids) {
                swapEltList(&p->Tabliste[j+1], &p->Tabliste[j]);
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
        copie_element(e, l.Tabliste[index]);
    } else {
        printf("ERR\n");
    }
}

/**
 * @brief Cherche un élément est dans une liste
 * @param[in] p : Liste où chercher
 * @param[in] e : Element à chercher
 * @return bool true=trouvé, false=pas trouvé
 */
bool belongEltList(liste p,Elementliste e) {
    Elementliste t_e;
    for (int i=0; i<p.Tete; i++) {
        pickEltList(p, &t_e, i);
        if (cmp_elements(e, t_e)) {
            return true;
        }
    }
    return false;
}
