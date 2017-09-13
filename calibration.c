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

#include <avr/io.h>
#include <calibration.h>
#include <PWM.h>
#include <ADC.h>
#include <avr/io.h>
#include <avr/interrupt.h>

/****************************************************************************************************/
/*									Déclaration des variables										*/
/****************************************************************************************************/

static s16 VmaxG_plus;
static s16 VminG_plus;
static s16 VmaxG_moins;
static s16 VminG_moins;
static s16 VmaxD_plus;
static s16 VminD_plus;
static s16 VmaxD_moins;
static s16 VminD_moins;
static float deltaVG_moins;
static float deltaVG_plus;
static float deltaVD_moins;
static float deltaVD_plus;

/****************************************************************************************************/
/*									Définition des fonctions										*/
/****************************************************************************************************/

/* Fonction permettant d'attendre un certain temps */
static void attendre(u08 compteur)
{
	while (compteur--)
	{
		while(!read_flag())
		{

		}
	}
}

/* Fonction permettant de faire l'exécution de la calibration pour VmaxG plus et moins, VmaxD plus et moins, VminG plus et moins, VminD plus et moins */
void executer_calibration(void)
{
	/* --------------------- Vmax Plus ----------------------*/
	PORTD = 0x44|(PORTD&0x33);			/* Bits DIR1 à 1 et DIR2 à 0 */
	PORTA = 0x10|(PORTA&0xEF);			/* Bit de CAL à 1 */
	attendre(50); 						/* Attendre 50*5=250ms */
	reinitialiser_moyenne(); 			/* Réinitialiser les valeurs lues par l'ADC */
	/* Atteinte du régime permanent */
	attendre(1); 						/* Attendre 1*5=5ms */
	calcul_moyenne();					/* Appel de la fonction du calcul de la moyenne */
	VmaxG_plus = Moyenne_G;				/* Vmax gauche plus est égal à la moyenne de gauche */
	VmaxD_plus = Moyenne_D;				/* Vmax droite plus est égal à la moyenne de droite */

	/* --------------------- Vmax Moins ----------------------*/
	PORTD = 0x88|(PORTD&0x33);			/* Bits DIR1 à 0 et DIR2 à 1 */
	PORTA = 0x10|(PORTA&0xEF);			/* Bit de CAL à 1 */
	attendre(50); 						/* Attendre 50*5=250ms */
	reinitialiser_moyenne(); 			/* Réinitialiser les valeurs lues par l'ADC */
	/* Atteinte du régime permanent */
	attendre(1); 						/* Attendre 1*5=5ms */
	calcul_moyenne();					/* Appel de la fonction du calcul de la moyenne */
	VmaxG_moins = Moyenne_G;			/* Vmax gauche moins est égal à la moyenne de gauche */
	VmaxD_moins = Moyenne_D;			/* Vmax droit moins est égal à la moyenne de gauche */

	/* --------------------- Vmin Plus ----------------------*/
	PORTD = 0x44|(PORTD&0x33);			/* Bits DIR1 à 1 et DIR2 à 0 */
	PORTA = 0x00|(PORTA&0xEF);			/* Bit de CAL à 0 */
	attendre(50); 						/* Attendre 50*5=250ms */
	reinitialiser_moyenne(); 			/* Réinitialiser les valeurs lues par l'ADC */
	/* Atteinte du régime permanent */
	attendre(1); 						/* Attendre 1*5=5ms */
	calcul_moyenne();					/* Appel de la fonction du calcul de la moyenne */
	VminG_plus = Moyenne_G;				/* Vmin gauche plus est égal à la moyenne de gauche */
	VminD_plus = Moyenne_D;				/* Vmin droit plus est égal à la moyenne de gauche */

	/* --------------------- Vmin Moins ----------------------*/
	PORTD = 0x88|(PORTD&0x33);			/* Bits DIR1 à 0 et DIR2 à 1 */
	PORTA = 0x00|(PORTA&0xEF);			/* Bit de CAL à 0 */
	attendre(50); 						/* Attendre 50*5=250ms */
	reinitialiser_moyenne(); 			/* Réinitialiser les valeurs lues par l'ADC */
	/* Atteinte du régime permanent */
	attendre(1); 						/* Attendre 1*5=5ms */
	calcul_moyenne();
	VminG_moins = Moyenne_G;			/* Vmin gauche moins est égal à la moyenne de gauche */
	VminD_moins = Moyenne_D;			/* Vmin droit moins est égal à la moyenne de gauche */

	/* Précalculs */
	deltaVG_plus = (float)1/((float)VmaxG_plus-(float)VminG_plus);
	deltaVG_moins = (float)1/((float)VmaxG_moins-(float)VminG_moins);
	deltaVD_plus = (float)1/((float)VmaxD_plus-(float)VminD_plus);
	deltaVD_moins = (float)1/((float)VmaxD_moins-(float)VminD_moins);
}

/* Fonction permettant de faire le calcul de V gauche */
float calcul_Vg(s32 VGmoy)
{
	float y = 0.0;

	/* Une interpolation est faite afin de trouver le VG réel. De plus, un 'clipping' est fait pour les zones de saturation et les zones mortes */
	if(VGmoy>0)								
	{
		y = ((float)VGmoy-(float)VminG_plus)*deltaVG_plus;

		if(y>1)								
		{
			y = 1;						
		}
		else if(y<0)						
		{
			y = 0;							
		}	
	}
	else								
	{
		y = ((float)VminG_moins-(float)VGmoy)*deltaVG_moins;
		
		if(y<-1)							
		{
			y = -1;
		}
		else if(y>0)
		{
			y = 0;
		}
	}

	return y;
}

/* Fonction permettant de faire le calcul de V droit */
float calcul_Vd(s32 VDmoy)
{
	/* Une interpolation est faite afin de trouver le VG réel. De plus, un 'clipping' est fait pour les zones de saturation et les zones mortes */
	float y = 0.0;

	if(VDmoy>0)
	{
		y = ((float)VDmoy-(float)VminD_plus)*deltaVD_plus;

		if(y>1)
		{
			y = 1;
		}
		else if(y<0)
		{
			y = 0;
		}
	}
	else
	{
		y = ((float)VminD_moins-(float)VDmoy)*deltaVD_moins;

		if(y<-1)
		{
			y = -1;
		}
		else if(y>0)
		{
			y = 0;
		}
	}

	return y;
}







