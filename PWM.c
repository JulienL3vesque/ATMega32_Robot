/****************************************************************************************************/
/*																									*/
/*	Fonction :  Ce programme permet d'envoyer la valeur du PWM de chaque moteurs 					*/
/*			    sur les ports de sortie OCR1A et OCR1B, afin de controler la vitesse des moteurs.  	*/
/*				Ce programme prend en compte les bits de directions pour chacun des moteurs.		*/
/*																									*/
/****************************************************************************************************/

/****************************************************************************************************/
/*									Déclaration des librairies										*/
/****************************************************************************************************/

#include <avr/io.h>
#include <PWM.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <utils.h>

/****************************************************************************************************/
/*									Déclaration des macros											*/
/****************************************************************************************************/

#define TOP_PWM 10000

/****************************************************************************************************/
/*									Déclaration des variable										*/
/****************************************************************************************************/

/* On doit d'abord faire des interruptions avec IRQ, avant d'appeler la fonction calculPWM */
u08 flag5ms = 0;

/****************************************************************************************************/
/*									Définition des fonctions										*/
/****************************************************************************************************/

/* Fonction permetttant de faire l'initiation du timer */
void init_timer(void)
{
	/* Configure le mode Fast PWM-16-bits ainsi que configurer le mode ouput des broches de sorties PD4 et PD5 */
    TCCR1A = (1<<WGM11)|(0<<WGM10)|(1<<COM1A1)|(0<<COM1A0)|(1<<COM1B1)|(0<<COM1B0);

	/* Configure le prescaler de CLK/8 ainsi que le mode Fast PWM-16-bits */
    TCCR1B = (1<<WGM12)|(1<<WGM13)|(1<<CS11)|(0<<CS10)|(0<<CS12)|(0<<ICNC1)|(0<<ICES1);

	/* Mettre ICR1 à la valeur du TOP */
	ICR1 = TOP_PWM; 					

	/* Activation de l'interruption à l'overflow */
	TIMSK = (TIMSK & 0xC3) | (1<<TOIE1); 
}

/* Fonction permetttant de configurer le PWM gauche */
void set_PWMg(float PWM)            
{

	OCR1A = PWM*TOP_PWM;            	/* Calcul du PWM de gauche et envoie cette valeur sur le Port de sortie ORC1A */

	if(PWM<0)
	{
		PORTD = (0x08)|(PORTD&0xF3);	/* On met le bit de direction DIRgauche1 (Port D Pin 2) à 0 et le bit de direction DIRgauche2 (Port D Pin 3) à 1. */ 
	}
	else
	{
		PORTD = (0x04)|(PORTD&0xF3);	/* On met le bit de direction DIRgauche1 (Port D Pin 2) à 1 et le bit de direction DIRgauche2 (Port D Pin 3) à 0. */
	}
}

/* Fonction permetttant de configurer le PWM droit */
void set_PWMd(float PWM)            
{
	OCR1B = PWM*TOP_PWM;             	/* Calcul du PWM de droite et envoie cette valeur sur le Port de sortie ORC1B */

	if(PWM<0)
	{
		PORTD = (0x80)|(PORTD&0x3F);	/* On met le bit de direction DIRdroite1 (Port D Pin 6) à 0 et le bit de direction DIRdroite2 (Port D Pin 7) à 1. */
	}
	else
	{
		PORTD = (0x40)|(PORTD&0x3F);	/* On met le bit de direction DIRdroite1 (Port D Pin 6) à 1 et le bit de direction DIRdroite2 (Port D Pin 7) à 0. */
	}
}


ISR(TIMER1_OVF_vect)
{
	flag5ms=1;                      /* Drapeau après le compte de 5 msec */
}

/* Fonction permetttant de lire le drapeau */
u08 read_flag(void)                 
{
	u08 flag;

	/* accès atomique */
	cli();		                    /* arrêt des interruptions */
	flag = flag5ms;                 /* stockage de la valeur du flag5ms */
	flag5ms = 0;                    /* remise à zéro du flag de 5 ms */
	sei();                          /* repartir les interruptions */

	return flag;

}


