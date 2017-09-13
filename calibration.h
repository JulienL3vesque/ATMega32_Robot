#ifndef CALIBRATION_H
#define CALIBRATION_H

/****************************************************************************************************/																
/*																									*/
/*	Fonction :  La calibration permet d'éliminer les zones mortes pour la vitesse des moteurs.		*/
/*			    Ce programme calibre nos vitesses maximum et minimum en fonction des bits 			*/
/*			   	de directions DIR1 et DIR2 ainsi que le bit de calibration.							*/
/*																									*/
/****************************************************************************************************/

/****************************************************************************************************/																
/*									Déclaration des librairies										*/
/****************************************************************************************************/

#include <utils.h>

/****************************************************************************************************/																
/*									Déclaration des fonctions										*/
/****************************************************************************************************/

/* Fonction permettant de faire l'exécution de la calibration pour VmaxG plus et moins, VmaxD plus et moins, VminG plus et moins, VminD plus et moins */
/* Entrée : Aucune entrée */
/* Sortie : Aucune sortie */
void executer_calibration(void);

/* Fonction permettant de faire le calcul de V gauche */
/* Entrée : V gauche moyen */
/* Sortie : Retourne y */
float calcul_Vg(s32 VGmoy);

/* Fonction permettant de faire le calcul de V droit */
/* Entrée : V droit moyen */
/* Sortie : Retourne y */
float calcul_Vd(s32 VDmoy);

#endif
