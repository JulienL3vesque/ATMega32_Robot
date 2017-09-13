#ifndef ADC_H
#define ADC_H

/****************************************************************************************************/																
/*																									*/
/*	Fonction :  Le convertisseur A/D (ADC) est un programme qui vérifie la vitesse des moteurs, 	*/
/*			    et qui retourne la vitesse par une boucle de rétroaction afin d'éviter les 			*/
/*				dépassements.																		*/
/*																									*/
/****************************************************************************************************/

/****************************************************************************************************/																
/*									Déclaration des librairies										*/
/****************************************************************************************************/

#include <avr/io.h>
#include <avr/interrupt.h>
#include <utils.h>
#include <moteur.h>

/****************************************************************************************************/																
/*									Déclaration des variables										*/
/****************************************************************************************************/

extern s32 Moyenne_G;
extern s32 Moyenne_D;

/****************************************************************************************************/																
/*									Déclaration des fonctions										*/
/****************************************************************************************************/

/* Fonction permettant de faire le calcul de la moyenne des valeurs reçues */
/* Entrée : Aucune entrée */
/* Sortie : Aucune sortie */
void calcul_moyenne();

/* Fonction permettant de faire l'initialisation de l'ADC */
/* Entrée : Aucune entrée */
/* Sortie : Aucune sortie */
void init_ADC(void);

/* Fonction permettant de faire la réinitialisation de la moyenne */
/* Entrée : Aucune entrée */
/* Sortie : Aucune sortie */
void reinitialiser_moyenne();

#endif
