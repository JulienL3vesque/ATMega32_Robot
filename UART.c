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
#include <UART.h>
#include <watchdog.h>

/****************************************************************************************************/
/*									D�claration des macros											*/
/****************************************************************************************************/

#define ETAT_ATTENTE 0
#define ETAT_VITESSE 1
#define ETAT_ANGLE 2

/****************************************************************************************************/
/*									D�claration des variables										*/
/****************************************************************************************************/

/* Variables globales au UART.c */
static volatile u08 uart_counter;
static volatile u08 vitesse = 100;
static volatile u08 angle = 0;

static volatile char etat = ETAT_ATTENTE;

/****************************************************************************************************/
/*									D�finition des fonctions 										*/
/****************************************************************************************************/

/* Routine d'interruption lorsque le UART a completement recu l'information du RX */
ISR(USART_RXC_vect)             
{
    register char led;

    led = UDR;                  /* Lis un byte (8 bits) dans le data buffer (UDR) et le mettre dans la variable led */
	reset_watchdog();			/* Appel de la fonction du reset du watchdog */
	UDR = led; // echo
    //PORTB = ~led;     /* output received byte to PortB (LEDs) */

	/* Communication normale : Commande de 3 Bytes [0xF1][Vitesse][Angle] */
	switch(etat)
	{
		case ETAT_ATTENTE:
			if(led==0xF1)
			{
				etat = ETAT_VITESSE;
			}
		break;
		case ETAT_VITESSE:
				etat = ETAT_ANGLE;
				vitesse = led;
		break;
		case ETAT_ANGLE:
				etat = ETAT_ATTENTE;
				angle = led;
				toggle_led(1);				/* Clignotement de la led lors de la commande re�ue du UART */
		break;
		default:
				etat = ETAT_ATTENTE;
		break;
	}

}

/* Fonction permettant l'envoie du buffer 'buf' au UART pour le transmettre sur TX */
void uart_send(s08 *buf, u08 size)          
{
#if 0
    if (!uart_counter)
	{
        /* �crit le premier byte du buffer */
        uart_data_ptr  = (u08*)buf;         /* D�clare le pointeur */
        uart_counter   = size;              /* D�clare le compteur */
        UDR = *buf;                         /* �crit un bytes (8 bits) dans UDR */
    }
#endif
}

/* Fonction permettant l'initialisation du UART */
void uart_init(void)
{
    /* Configure 'asynchronous operation, no parity, 1 stop bit, 8 data bits, Tx on rising edge' */
    UCSRC = (1<<URSEL)|(0<<UMSEL)|(0<<UPM1)|(0<<UPM0)|(0<<USBS)|(1<<UCSZ1)|(1<<UCSZ0)|(0<<UCPOL);
    /* Met � 'enable' RxD/TxD et les interruptions */
    UCSRB = (1<<RXCIE)|(0<<TXCIE)|(1<<RXEN)|(1<<TXEN)|(0<<UCSZ2);
    /* Met le baud rate � 9600 avec les registres UBRRH et UBRRL */
    UBRRH = (u08)(UART_BAUD_SELECT >> 8);
	/*  */
    UBRRL = (u08)(UART_BAUD_SELECT & 0x00FF);
}

/* Fonction permettant de convertir la vitesse de -100% � 100% */
u08 get_vitesse()                           
{
	return vitesse;			/* Retourne la vitesse */
}

/* Fonction permettant de convertir l'angle de 0 � 360 degr� */
u08 get_angle()                             
{
	return angle;			/* Retourne l'angle */
}
