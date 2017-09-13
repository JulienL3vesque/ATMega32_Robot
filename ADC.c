/****************************************************************************************************/																
/*																									*/
/*	Fonction :  Le convertisseur A/D (ADC) est un programme qui vérifie la vitesse des moteurs, 	*/
/*			    et qui retourne la vitesse par une boucle de rétroaction afin d'éviter les 			*/
/*				dépassements.																		*/
/*																									*/
/****************************************************************************************************/

/****************************************************************************************************/
/*									Déclaration des librairies										*/
/****************************************************************************************************/

#include <avr/io.h>
#include <ADC.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <utils.h>

/****************************************************************************************************/
/*									Déclaration des variables										*/
/****************************************************************************************************/

static volatile s16 i;
static volatile s16 j;
static volatile s32 totalG;
static volatile s32 totalD;
s32 Moyenne_G;
s32 Moyenne_D;

/****************************************************************************************************/
/*									Définition des fonctions										*/
/****************************************************************************************************/

/* Fonction permettant de faire l'initialisation du module de l'ADC */
void init_ADC(void)
{
	/* Configure le 'prescaler' à 16 afin d'avoir une fréquence de 125 kHz pour l'ADC et active les interruptions */
    ADCSRA = (1<<ADEN)|(1<<ADSC)|(1<<ADATE)|(0<<ADIF)|(1<<ADIE)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);

	/* Configure l'ADC en mode 'free-running' */
    SFIOR = (0<<ADTS2)|(0<<ADTS1)|(0<<ADTS0)|(SFIOR&0x0F);

	/* Initialise l'ADMUX à zéro */
	ADMUX = 0;

	/* Remise à zéro des variables */
	i = 0;
	j = 0;
	totalG = 0;
	totalD = 0;
}

/*Fonction permettant de faire la lecture du calcul de l'ADC */
ISR(ADC_vect)
{
	/* Déclarations de la variable Valeur, pour cela on concatène deux registres ADCL et ADCH */
	s16 Valeur;
	Valeur = (u16)ADCL;
	Valeur |= (u16)ADCH<<8;

	if (ADMUX == 0x00)	 			/* Si l'ADMUX égal à 0, c'est le canal 0 */
	{

		/* Récupération du bit de direction et le resultat du calcul de l'ADC (10 bits) et on le met dans la variable totalD */
		ADMUX |= (1<<MUX0);         /* Changement de canal, MUX0 = 1 */


		if((PINA&0x08)==0)          /* Si le bit de DIR Droite (PortA Pin3) est a zero, direction positive */
		{
			totalD += Valeur;       /* Accumulation des valeurs reçues de l'ADC avec le bit de direction positif*/
			j++;
		}
		else                        /* Si le bit de DIR Droite (PortA Pin3) est a un, direction negative */
		{
			totalD -= Valeur;       /* Accumulation des valeurs reçues de l'ADC avec le bit de direction negatif*/
			j++;
		}
	}
	else                            /* Si l'ADMUX égal à 1, c'est le canal 1 */
	{
		/* On prend le bit de direction et le resultat du calcul de l'ADC (10 bits) et on le met dans la variable totalG */
		ADMUX &= ~(1<<MUX0);        /* Changement de canal, MUX0 = 0 */


		if((PINA&0x04)==0)          /* Si le bit de DIR Gauche (PortA Pin2) est a zero, direction positive */
		{
			totalG += Valeur;       /* Accumulation des valeurs reçues de l'ADC avec le bit de direction positif*/
			i++;
		}
		else                        /* Si le bit de DIR Gauche (PortA Pin2) est a un, direction negative */
		{
			totalG -= Valeur;       /* Accumulation des valeurs reçues de l'ADC avec le bit de direction negatif*/
			i++;
		}
	}
}

/*	Fonction permettant de faire le calcul de la moyenne des valeurs accumulées par l'ADC */
void calcul_moyenne()
{
	/* Déclarations des variables utilisées dans la fonction */
	s16 i_temp;
	s16 j_temp;
	s32 totalG_temp;
	s32 totalD_temp;

	cli();								/* Arrêt des interruptions	*/
	i_temp = i;							/* Valeur de 'i' emmagasinée dans la variable temporaire 'i_temp'*/
	j_temp = j;							/* Valeur de 'j' emmagasinée dans la variable temporaire 'j_temp'*/
	totalG_temp = totalG;				/* Valeur total de gauche emmagasinée dans la variable temporaire 'totalG_temp'*/
	totalD_temp = totalD;				/* Valeur total de droite emmagasinée dans la variable temporaire 'totalD_temp'*/

	/* Remise à zéro des variables utilisées */
	i = 0;
	j = 0;
	totalG = 0;
	totalD = 0;
	sei();								/* Redémarrage des interruptions */

	Moyenne_G = totalG_temp/(i_temp);		/* Moyennage des valeurs de gauche */

	Moyenne_D = totalD_temp/(j_temp);		/* Moyennage des valeurs de droite */

}

/* Fonction permettant de faire la réinitialisation de la moyenne */
void reinitialiser_moyenne()
{
	cli();			/* Arrêt des interruptions	*/
	i = 0;
	j = 0;
	totalG = 0;
	totalD = 0;
	sei();			/* Redémarrage des interruptions */
}
