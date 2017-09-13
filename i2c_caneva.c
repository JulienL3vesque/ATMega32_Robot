/****************************************************************************************************/																
/*									Déclaration des librairies										*/
/****************************************************************************************************/
#include <avr/io.h>
#include "i2c_caneva.h"
#include <util/twi.h>
#include <avr/interrupt.h>
#include <avr/io.h>

/* Variables d'états pour interrupt */
static volatile i2c_command current_command;
typedef enum
{
	FIRST_START,
	READ_ADDR,
	READ_REG,
	SECOND_START,
	READ_ADDR_2,
	READ_DATA,
	WRITE_ADDR,
	WRITE_REG,
	WRITE_DATA
} i2c_state;

static volatile i2c_state etat;
/* Fin des variables d'états */

/****************************************************************************************************/																
/*									Déclaration des variables										*/
/****************************************************************************************************/

static volatile i2c_command CircularBufferOut[CIRCULAR_BUFFER_SIZE];
static volatile i2c_command CircularBufferIn[CIRCULAR_BUFFER_SIZE];
static volatile u08 CircularBufferOutEnd;
static volatile u08 CircularBufferOutIndex;
static volatile u08 CircularBufferInEnd;
static volatile u08 CircularBufferInIndex;

/****************************************************************************************************/																
/*									Définition des fonctions										*/
/****************************************************************************************************/

/* Fonction permettant de faire l'initialisation du TWI */
void init_TWI(void)
{
	/* Configure le mode avec une fréquence de 10 KHz */
    TWBR = 0xC6; 							/* C6 est égale a 198 avec le prescaler de 1 */
	
	TWCR = (0<<TWINT)|(0<<TWEA)|(0<<TWSTA)|(0<<TWSTO)|(1<<TWEN)|(1<<TWIE)|(TWCR&0x0A); /* Enable interrupt */

	TWSR = (TWSR & 0xFC)|(1);				/* Set le prescaler a 1 */

}

/******************************************************************************
* Insérer dans le buffer out								  
******************************************************************************/
void putDataOutBuf(i2c_command data){

	CircularBufferOutEnd++;
	CircularBufferOutEnd %= CIRCULAR_BUFFER_SIZE;
	CircularBufferOut[CircularBufferOutEnd] = data;

}


/******************************************************************************
 * Retirer du buffer out
 *****************************************************************************/
i2c_command getDataOutBuf(void){

	CircularBufferOutIndex++;
	CircularBufferOutIndex %= CIRCULAR_BUFFER_SIZE;
	return (i2c_command)CircularBufferOut[CircularBufferOutIndex];

}


/******************************************************************************
 * Insérer dans le buffer in
 *****************************************************************************/
void putDataInBuf(i2c_command ptr){

	CircularBufferInEnd++;
	CircularBufferInEnd %= CIRCULAR_BUFFER_SIZE;
	CircularBufferIn[CircularBufferInEnd] = ptr;

}


/******************************************************************************
 * Retirer du buffer in
 *****************************************************************************/
i2c_command getDataInBuf(void){

	CircularBufferInIndex++;
	CircularBufferInIndex %= CIRCULAR_BUFFER_SIZE;
	return CircularBufferIn[CircularBufferInIndex];	

}


/******************************************************************************
 * Écrire sur le bus twi
 *****************************************************************************/
void twiWriteCommand(u08 address, u08 registre, u08 data, u08 read)
{	
	i2c_command command;	
	u08 was_empty;

	command.addr = address;
	command.reg = registre;
	command.data = data;
	command.read = read;

	cli();
	
	/* Si le buffer n'est pas plein*/
	if((CircularBufferOutEnd+1)%CIRCULAR_BUFFER_SIZE!=CircularBufferOutIndex)
	{
		was_empty = CircularBufferOutIndex==CircularBufferOutEnd;
		putDataOutBuf(command);

		/* Si le buffer était vide, on envoie un start */
		if(was_empty)
		{
			etat = FIRST_START;
			TWCR &= ~(1<<TWSTO);
			TWCR |= (1<<TWSTA)|(1<<TWINT);
		}
	}
	sei();

}

/******************************************************************************
 * lire sur le bus
 *****************************************************************************/
i2c_command twiReadCommand()
{
	i2c_command command;
	cli();
	/* Regarde si le buffer est plein */
	if(CircularBufferInIndex==CircularBufferInEnd)
	{
		/* 'command.addr=0xFF' signifie que le buffer est vide */
		command.addr = 0xFF;
	}
	else
	{
		command = getDataInBuf();
	}
	sei();

	return command;
}




/******************************************************************************
 *
 *****************************************************************************/
ISR(TWI_vect) {
	
	u08 status  = TWSR & 0xF8;
	u08 tmp;

	switch (status) {
		case	0x08: /* Start Condition */
		case	0x10: /* Restart Condition */
			
			/* 
				Si  nous avons un start ou un restart condition alors il faut envoyer l'addr 
				qui est dans le buffer Out et Activer le bus sans start/stop 
			*/
			if(etat == SECOND_START)
			{
				TWDR = current_command.addr | 0x01;
				TWCR &= ~(1<<TWSTA);
				TWCR |= (1<<TWINT);
				etat = READ_ADDR_2;
			}
			else
			{
				current_command = getDataOutBuf();

				if(current_command.read)
				{
					etat = READ_ADDR;
				}
				else
				{
					etat = WRITE_ADDR;
				}

				TWDR = current_command.addr;
				tmp = current_command.addr;

				/* Marche et arrêt à zéro, TWINT à 1 pour 'clearer' l'interrupt, enable ACK */
				TWCR &= ~(1<<TWSTA);
				TWCR |= (1<<TWINT);
			}

			break;

		case	0x18: /* Address Write Ack */

			/* Écrit le #registre */
			TWDR = current_command.reg;

			if(etat==READ_ADDR)
			{
				etat = READ_REG;
			}
			else if(etat==WRITE_ADDR)
			{
				etat = WRITE_REG;
			}

			/* Marche et arrêt à zéro, TWINT à 1 pour clearer l'interrupt, enable ACK */
			TWCR |= (1<<TWINT);

			break;
		case	0x28: /* Data Write Ack */
		case	0x30: /* Date Write NoAck */
			
			/* 
				Si  nous avons un data ou une addr d'écrit sur le bus, ensuite il peut y avoir un autre data, 
				un stop ou un restart. Il faut donc lire le buffer pour savoir quoi faire et configure 
				le bus en conséquence 
			*/

			if(etat==READ_REG)
			{
				etat = SECOND_START;
				TWCR |= (1<<TWSTA);
				TWCR |= (1<<TWINT);
			}
			else if(etat==WRITE_REG)
			{
				etat = WRITE_DATA;
				TWDR = current_command.data;
				tmp = current_command.data;
				TWCR |= (1<<TWINT);
			}
			else if(etat==WRITE_DATA)
			{
				/* Est-ce qu'il y a une autre commande dans le buffer? */
				if(CircularBufferOutIndex!=CircularBufferOutEnd)
				{
					/* Restart(start à 1, stop 0) */
					TWCR |= (1<<TWSTA);
					TWCR |= (1<<TWINT);
					etat = FIRST_START;
				}
				else
				{
					/* Stop(start à 0, stop à 1) */
					TWCR &= ~(1<<TWSTA);
					TWCR |= (1<<TWINT)|(1<<TWSTO);
				}
			}
			break;

		case	0x50: /* Data Read Ack */
		case	0x58: /* Data Read NoAck */

			/* 
				Une lecture à été effectué sur le bus, il faut donc la récupérer 
			*/
				current_command.data = TWDR;
				tmp = current_command.data;
				putDataInBuf(current_command);

				/* Est-ce qu'il y a une autre commande dans le buffer? */
				if(CircularBufferOutIndex!=CircularBufferOutEnd)
				{
					/* Restart(start à 1, stop 0) */
					TWCR |= (1<<TWSTA);
					TWCR |= (1<<TWINT);
					etat = FIRST_START;
				}
				else
				{
					/* Stop(start à 0, stop à 1) */
					TWCR &= ~(1<<TWSTA);
					TWCR |= (1<<TWINT)|(1<<TWSTO);
				}

		case	0x40: /* Address Read Ack */


			
				/* 
					Puisqu'il n'y a pas de break dans les deux case 0x50 et 0x58, quand nous sommes ici
					nous avons soit lue la donnée ou envoyé l'addr à lire, il peut donc y avoir un stop, un
					start ou encore il faut placer le bus en mode lecture 
				*/

				etat = READ_DATA;
	
				/* Marche et arrêt à zéro, TWINT à 1 pour clearer l'interrupt, enable ACK */
				TWCR |= (1<<TWINT);

			break;

		case	0x48: /* Address Read NoAck */
		case	0x20: /* Address Write NoAck */
		default:


			/* 
				Ici l'un des deux sonars n'a pas répondu, il faut donc tout stoper ou faire un restart
			    pour la prochaine trame qui peut être dans le buffer 
			*/
			
				/* Est-ce qu'il y a une autre commande dans le buffer? */
				if(CircularBufferOutIndex!=CircularBufferOutEnd)
				{
					/* Restart(start à 1, stop 0) */
					TWCR |= (1<<TWSTA);
					TWCR |= (1<<TWINT);
					etat = FIRST_START;
				}
				else
				{
					/* Stop(start à 0, stop à 1) */
					TWCR &= ~(1<<TWSTA);
					TWCR |= (1<<TWINT)|(1<<TWSTO);
				}

			break;
	}
}
