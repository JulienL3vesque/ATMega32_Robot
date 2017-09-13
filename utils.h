#ifndef UTILS_H
#define UTILS_H

/****************************************************************************************************/																
/*																									*/
/*	Fonction : Ce programme permet de faire la conversion de l'angle re�u, la conversion de la  	*/
/*			   vitesse re�ue et permet de faire le contr�le et de recevoir du feedback des 			*/
/*			   fonctionnalit�s du syst�me.															*/
/*																									*/
/****************************************************************************************************/

/****************************************************************************************************/																
/*									D�claration des macros											*/
/****************************************************************************************************/

#define DIRg1 (PIND&0x04)
#define DIRg2 (PIND&0x08)
#define DIRd1 (PIND&0x40)
#define DIRd2 (PIND&0x80)
#define PWMg (PIND&0x10)
#define PWMd (PIND&0x20)
#define CAL (PINA&0x10)

/****************************************************************************************************/																
/*									D�claration des variables										*/
/****************************************************************************************************/

typedef unsigned char  u08;
typedef          char  s08;
typedef unsigned short u16;
typedef          short s16;
typedef unsigned long int   u32;
typedef          long int   s32;

/****************************************************************************************************/																
/*									D�claration des fonctions										*/
/****************************************************************************************************/

/* Fonction permettant de faire la conversion de la valeur(0-180) de l'angle en degr� (0-360) */
/* Entr�e : Angle re�u 'angle'																  */
/* Sortie : Angle converti en degr� 'angle_deg'												  */
float conv_angle (u08 angle180);

/* Fonction permettant de faire la conversion de la vitesse(0-200) en pourcentage (-100% � 100%) */
/* Entr�e : vitesse re�ue 'vitesse'														  		 */
/* Sortie : Vitesse convertie en pourcentage 'vitesse_conv'									  	 */
float conv_vitesse(u08 vitesse);

/* Fonction permettant le clignotement de la LED 1 									*/
/* Entr�e : la led utilis�e 'led' et la valeur � laquelle doit �tre la led 'valeur' */
/* Sortie : Aucune sortie													  	    */
void set_led(u08 led, u08 valeur);

/* Fonction permettant de mettre � 1 ou 0 */
/* Entr�e : la led utilis�e 'led'		  */
/* Sortie : Aucune sortie		  	      */
void toggle_led(u08 led);

#endif
