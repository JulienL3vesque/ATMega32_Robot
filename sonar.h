#ifndef SONAR_H
#define SONAR_H

/****************************************************************************************************/																
/*	Fonction : Les sonars doivent d�tecter les obstacles pr�sents devant le robot mobile.			*/
/****************************************************************************************************/

/****************************************************************************************************/																
/*									D�claration des librairies										*/
/****************************************************************************************************/

#include <utils.h>

/****************************************************************************************************/																
/*									D�claration des fonctions										*/
/****************************************************************************************************/

/* Fonction permettant de faire l'initialisation du sonar */
/* Entr�e : Aucune entr�e */
/* Sortie : Aucune sortie */
void init_sonar(void);

/* Fonction perttant de faire l'appel du nouveau_ping toutes les 50ms */
/* Entr�e : Re�oit nouveau_ping */
/* Sortie : Aucune sortie */
void executer_sonar(u08 nouveau_ping);

extern u16 distance_gauche;
extern u16 distance_droite;
extern float vitesse_max;

#endif
