/****************************************************************************************************/																
/*																									*/
/*	Fonction : Le Watchdog sert � la d�tection de probl�mes lors du blocage du syst�me. Il v�rifie 	*/
/*			   le lien de communication entre le t�l�guidage et le robot. Lorsque le lien se brise, */
/*			   le Watchdog va red�marrer le syst�me. 												*/
/*																									*/
/****************************************************************************************************/

/****************************************************************************************************/																
/*									D�claration des librairies										*/
/****************************************************************************************************/

#include <watchdog.h>
#include <avr/wdt.h>

/****************************************************************************************************/																
/*									D�finition des fonctions										*/
/****************************************************************************************************/

/* Fonction permettant de faire l'initialisation du Watchdog */
void init_watchdog()
{
	wdt_enable(3);
}

/* Fonction permettant de faire un reset du Watchdog */
void reset_watchdog()
{
	wdt_reset();
}


