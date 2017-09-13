#ifndef UART_H
#define UART_H

/****************************************************************************************************/																
/*																									*/
/*	Fonction :  Le UART sert � la r�ception des commandes de t�l�guidage et � la transmission		*/
/*			    d'informations.																		*/
/*																									*/
/****************************************************************************************************/

/****************************************************************************************************/																
/*									D�claration des librairies										*/
/****************************************************************************************************/

#include <avr/io.h>
#include <avr/interrupt.h>
#include <utils.h>

/****************************************************************************************************/																
/*									D�claration des macros											*/
/****************************************************************************************************/

#ifndef F_CPU
#define F_CPU            16000000UL     				 /* Crystal 16.000 Mhz */
#endif

#define UART_BAUD_RATE      9600      					 /* 9600 baud */
#define UART_BAUD_SELECT (F_CPU/(UART_BAUD_RATE*16l)-1)

/****************************************************************************************************/																
/*									D�claration des fonctions										*/
/****************************************************************************************************/

/* Fonction permettant l'initialisation du UART */
/* Entr�e : Aucune entr�e */
/* Sortie : Aucune sortie */
void uart_init(void);

/* Fonction permettant l'envoie du buffer 'buf' au UART pour le transmettre sur TX */
/* Entr�e : Re�oit le pointeur 'buf' et la variable 'size'*/
/* Sortie : Aucune sortie */
void uart_send(s08 *buf, u08 size);

/* Fonction permettant de convertir la vitesse de -100% � 100% */
/* Entr�e : Aucune entr�e */
/* Sortie : Retourne vitesse */
u08 get_vitesse();

/* Fonction permettant de convertir l'angle de 0 � 360 degr� */
/* Entr�e : Aucune entr�e */
/* Sortie : Retourne angle */
u08 get_angle();

#endif
