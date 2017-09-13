/****************************************************************************************************/
/*																									*/
/*	Fonction : Ce programme permet de faire la conversion de l'angle reçu, la conversion de la  	*/
/*			   vitesse reçue et permet de faire le contrôle et de recevoir du feedback des 			*/
/*			   fonctionnalités du système.															*/
/*																									*/
/****************************************************************************************************/

/****************************************************************************************************/
/*									Déclaration des librairies										*/
/****************************************************************************************************/

#include <utils.h>
#include <avr/io.h>

/****************************************************************************************************/
/*									Déclaration des macros											*/
/****************************************************************************************************/

#define PI 3.141592

/****************************************************************************************************/
/*									Définition des fonctions										*/
/****************************************************************************************************/

/* Fonction permettant de faire la conversion de la valeur(0-180) de l'angle en degré (0-360)*/
float conv_angle (u08 angle180)
{
	float angle_deg;	  					/* Déclaration de la variable */

	angle_deg = ((float)angle180*2*PI)/180;	/* Conversion de l'angle radian en degré */

	return angle_deg;						/* Retourne l'angle converti */
}


/* Fonction permettant de faire la conversion de la vitesse(0-200) en pourcentage (-100% à 100%)*/
float conv_vitesse(u08 vitesse)
{
	float vitesse_conv;						/* Déclaration de la variable */

	vitesse_conv = ((float)vitesse-100)/100;/* Conversion de la vitesse en pourcentage */

	return vitesse_conv;					/* Retourne la vitesse converti */

}

/* Fonction permettant le clignotement de la LED 1 */
void toggle_led(u08 led)
{
	PORTB = (PORTB ^ (1<<led));
}

/* Fonction permettant de mettre une LED à 1 ou 0 */
void set_led(u08 led, u08 valeur)
{
	PORTB = (valeur<<led) | ((~(1<<led)) & PORTB);
}

