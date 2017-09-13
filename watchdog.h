#ifndef WATCHDOG_H
#define WATCHDOG_H

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

#include <avr/io.h>
#include <avr/interrupt.h>

/****************************************************************************************************/																
/*									Déclaration des fonction										*/
/****************************************************************************************************/

/* Fonction permettant de faire l'initialisation du Watchdog */
/* Entrée : Aucune entrée 									 */
/* Sortie : Aucune sortie 									 */
void init_watchdog();

/* Fonction permettant de faire un reset du Watchdog */
/* Entrée : Aucune entrée 							 */
/* Sortie : Aucune sortie 							 */
void reset_watchdog();

#endif
