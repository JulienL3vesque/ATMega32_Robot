#ifndef SONAR_H
#define SONAR_H

/****************************************************************************************************/																
/*	Fonction : Les sonars doivent détecter les obstacles présents devant le robot mobile.			*/
/****************************************************************************************************/

/****************************************************************************************************/																
/*									Déclaration des librairies										*/
/****************************************************************************************************/

#include <utils.h>

/****************************************************************************************************/																
/*									Déclaration des fonctions										*/
/****************************************************************************************************/

/* Fonction permettant de faire l'initialisation du sonar */
/* Entrée : Aucune entrée */
/* Sortie : Aucune sortie */
void init_sonar(void);

/* Fonction perttant de faire l'appel du nouveau_ping toutes les 50ms */
/* Entrée : Reçoit nouveau_ping */
/* Sortie : Aucune sortie */
void executer_sonar(u08 nouveau_ping);

extern u16 distance_gauche;
extern u16 distance_droite;
extern float vitesse_max;

#endif
