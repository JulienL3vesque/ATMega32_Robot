#ifndef PWM_H
#define PWM_H

/****************************************************************************************************/
/*																									*/
/*	Fonction :  Ce programme permet d'envoyer la valeur du PWM de chaque moteurs 					*/
/*			    sur les port de sortie OCR1A et OCR1B, afin de controler la vitesse des moteurs.  	*/
/*				Ce programme prend en compte les bits de directions pour chacun des moteurs.		*/
/*																									*/
/****************************************************************************************************/

/****************************************************************************************************/																
/*									Déclaration des librairies										*/
/****************************************************************************************************/
#include <utils.h>

/****************************************************************************************************/																
/*									Déclaration des fonctions										*/
/****************************************************************************************************/

/* Fonction permetttant de faire le calcul du PWM */
/* Entrée : Reçoit la vitesse, l'angle, le Vgauche, Vdroite, Duty gauche et Duty droit */
/* Sortie : Aucune sortie */
void CalculPWM(float Vitesse_D, float Angle_D, float Vg, float Vd, float *Duty_G, float *Duty_D);

/* Fonction permetttant de faire l'initiation du timer */
/* Entrée : Aucune entrée */
/* Sortie : Aucune sortie */
void init_timer(void);

/* Fonction permetttant de configurer le PWM gauche */
/* Entrée : Reçoit PWM */
/* Sortie : Aucune sortie */
void set_PWMg(float PWM);

/* Fonction permetttant de configurer le PWM droit */
/* Entrée : Reçoit PWM */
/* Sortie : Aucune sortie */
void set_PWMd(float PWM);

/* Fonction permetttant de lire le drapeau */
/* Entrée : Aucune entrée */
/* Sortie : Retourne le drapeau 'flag' */
u08 read_flag(void);

#endif
