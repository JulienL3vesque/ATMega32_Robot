/****************************************************************************************************/																
/*																									*/
/*	Fonction : Le Watchdog sert à la détection de problèmes lors du blocage du système. Il vérifie 	*/
/*			   le lien de communication entre le téléguidage et le robot. Lorsque le lien se brise, */
/*			   le Watchdog va redémarrer le système. 												*/
/*																									*/
/****************************************************************************************************/

/****************************************************************************************************/																
/*									Déclaration des librairies										*/
/****************************************************************************************************/

#include <watchdog.h>
#include <avr/wdt.h>

/****************************************************************************************************/																
/*									Définition des fonctions										*/
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


