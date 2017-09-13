#ifndef CALIBRATION_H
#define CALIBRATION_H

/****************************************************************************************************/																
/*																									*/
/*	Fonction :  La calibration permet d'�liminer les zones mortes pour la vitesse des moteurs.		*/
/*			    Ce programme calibre nos vitesses maximum et minimum en fonction des bits 			*/
/*			   	de directions DIR1 et DIR2 ainsi que le bit de calibration.							*/
/*																									*/
/****************************************************************************************************/

/****************************************************************************************************/																
/*									D�claration des librairies										*/
/****************************************************************************************************/

#include <utils.h>

/****************************************************************************************************/																
/*									D�claration des fonctions										*/
/****************************************************************************************************/

/* Fonction permettant de faire l'ex�cution de la calibration pour VmaxG plus et moins, VmaxD plus et moins, VminG plus et moins, VminD plus et moins */
/* Entr�e : Aucune entr�e */
/* Sortie : Aucune sortie */
void executer_calibration(void);

/* Fonction permettant de faire le calcul de V gauche */
/* Entr�e : V gauche moyen */
/* Sortie : Retourne y */
float calcul_Vg(s32 VGmoy);

/* Fonction permettant de faire le calcul de V droit */
/* Entr�e : V droit moyen */
/* Sortie : Retourne y */
float calcul_Vd(s32 VDmoy);

#endif
