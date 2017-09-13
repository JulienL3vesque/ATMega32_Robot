#ifndef UART_H
#define UART_H

/****************************************************************************************************/																
/*																									*/
/*	Fonction :  Le UART sert à la réception des commandes de téléguidage et à la transmission		*/
/*			    d'informations.																		*/
/*																									*/
/****************************************************************************************************/

/****************************************************************************************************/																
/*									Déclaration des librairies										*/
/****************************************************************************************************/

#include <avr/io.h>
#include <avr/interrupt.h>
#include <utils.h>

/****************************************************************************************************/																
/*									Déclaration des macros											*/
/****************************************************************************************************/

#ifndef F_CPU
#define F_CPU            16000000UL     				 /* Crystal 16.000 Mhz */
#endif

#define UART_BAUD_RATE      9600      					 /* 9600 baud */
#define UART_BAUD_SELECT (F_CPU/(UART_BAUD_RATE*16l)-1)

/****************************************************************************************************/																
/*									Déclaration des fonctions										*/
/****************************************************************************************************/

/* Fonction permettant l'initialisation du UART */
/* Entrée : Aucune entrée */
/* Sortie : Aucune sortie */
void uart_init(void);

/* Fonction permettant l'envoie du buffer 'buf' au UART pour le transmettre sur TX */
/* Entrée : Reçoit le pointeur 'buf' et la variable 'size'*/
/* Sortie : Aucune sortie */
void uart_send(s08 *buf, u08 size);

/* Fonction permettant de convertir la vitesse de -100% à 100% */
/* Entrée : Aucune entrée */
/* Sortie : Retourne vitesse */
u08 get_vitesse();

/* Fonction permettant de convertir l'angle de 0 à 360 degré */
/* Entrée : Aucune entrée */
/* Sortie : Retourne angle */
u08 get_angle();

#endif
