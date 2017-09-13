/****************************************************************************************************/
/*																									*/
/*	Fonction : Ce programme permet de faire la conversion de l'angle re�u, la conversion de la  	*/
/*			   vitesse re�ue et permet de faire le contr�le et de recevoir du feedback des 			*/
/*			   fonctionnalit�s du syst�me.															*/
/*																									*/
/****************************************************************************************************/

/****************************************************************************************************/
/*									D�claration des librairies										*/
/****************************************************************************************************/

#include <utils.h>
#include <avr/io.h>

/****************************************************************************************************/
/*									D�claration des macros											*/
/****************************************************************************************************/

#define PI 3.141592

/****************************************************************************************************/
/*									D�finition des fonctions										*/
/****************************************************************************************************/

/* Fonction permettant de faire la conversion de la valeur(0-180) de l'angle en degr� (0-360)*/
float conv_angle (u08 angle180)
{
	float angle_deg;	  					/* D�claration de la variable */

	angle_deg = ((float)angle180*2*PI)/180;	/* Conversion de l'angle radian en degr� */

	return angle_deg;						/* Retourne l'angle converti */
}


/* Fonction permettant de faire la conversion de la vitesse(0-200) en pourcentage (-100% � 100%)*/
float conv_vitesse(u08 vitesse)
{
	float vitesse_conv;						/* D�claration de la variable */

	vitesse_conv = ((float)vitesse-100)/100;/* Conversion de la vitesse en pourcentage */

	return vitesse_conv;					/* Retourne la vitesse converti */

}

/* Fonction permettant le clignotement de la LED 1 */
void toggle_led(u08 led)
{
	PORTB = (PORTB ^ (1<<led));
}

/* Fonction permettant de mettre une LED � 1 ou 0 */
void set_led(u08 led, u08 valeur)
{
	PORTB = (valeur<<led) | ((~(1<<led)) & PORTB);
}

