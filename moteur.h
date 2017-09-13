#ifndef __MOTOR_H_
#define __MOTOR_H_

/****************************************************************************************************/																
/*																									*/
/*	Fonction :  Le CalculPWM permet de caluculer la valeur du duty cycle pour chaque moteurs 		*/
/*			    avec la vitesse désirée et l'angle désié que l'on a converti au préalable avec 		*/
/*				les fonctions conv_vitesse() et conv_angle().										*/
/*																									*/
/****************************************************************************************************/

/****************************************************************************************************/																
/*									Déclaration des macros											*/
/****************************************************************************************************/

#define Pi      (3.1415926535897932384626433832795)
#define RAYON   (9.525)
#define TS      (0.005)
#define Vmax    (80.0)
#define Tau     (0.5)

#define H11		(3.90148347975678) 
#define H12		(4.90148347975678)

#define H21		(1.1613504)
#define H22		(0.5806746734)

#define Fpwm (10000)

/****************************************************************************************************/																
/*									Déclaration des fonctions										*/
/****************************************************************************************************/

/* Fonction permetttant de faire le calcul du PWM */
/* Entrée : Reçoit la vitesse, l'angle, le Vgauche, le Vdroit, le Duty gauche et le Duty droit */
/* Sortie : Aucune sortie */
void CalculPWM(float Vitesse_D, float Angle_D, float Vg, float Vd, float *Duty_G, float *Duty_D);

#endif
