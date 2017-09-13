#ifndef ADC_H
#define ADC_H

/****************************************************************************************************/																
/*																									*/
/*	Fonction :  Le convertisseur A/D (ADC) est un programme qui v�rifie la vitesse des moteurs, 	*/
/*			    et qui retourne la vitesse par une boucle de r�troaction afin d'�viter les 			*/
/*				d�passements.																		*/
/*																									*/
/****************************************************************************************************/

/****************************************************************************************************/																
/*									D�claration des librairies										*/
/****************************************************************************************************/

#include <avr/io.h>
#include <avr/interrupt.h>
#include <utils.h>
#include <moteur.h>

/****************************************************************************************************/																
/*									D�claration des variables										*/
/****************************************************************************************************/

extern s32 Moyenne_G;
extern s32 Moyenne_D;

/****************************************************************************************************/																
/*									D�claration des fonctions										*/
/****************************************************************************************************/

/* Fonction permettant de faire le calcul de la moyenne des valeurs re�ues */
/* Entr�e : Aucune entr�e */
/* Sortie : Aucune sortie */
void calcul_moyenne();

/* Fonction permettant de faire l'initialisation de l'ADC */
/* Entr�e : Aucune entr�e */
/* Sortie : Aucune sortie */
void init_ADC(void);

/* Fonction permettant de faire la r�initialisation de la moyenne */
/* Entr�e : Aucune entr�e */
/* Sortie : Aucune sortie */
void reinitialiser_moyenne();

#endif
