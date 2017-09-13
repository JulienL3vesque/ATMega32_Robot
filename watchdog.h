#ifndef WATCHDOG_H
#define WATCHDOG_H

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

#include <avr/io.h>
#include <avr/interrupt.h>

/****************************************************************************************************/																
/*									D�claration des fonction										*/
/****************************************************************************************************/

/* Fonction permettant de faire l'initialisation du Watchdog */
/* Entr�e : Aucune entr�e 									 */
/* Sortie : Aucune sortie 									 */
void init_watchdog();

/* Fonction permettant de faire un reset du Watchdog */
/* Entr�e : Aucune entr�e 							 */
/* Sortie : Aucune sortie 							 */
void reset_watchdog();

#endif
