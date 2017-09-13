#ifndef I2C_H
#define I2C_H

/****************************************************************************************************/																
/*									D�claration des librairies										*/
/****************************************************************************************************/
#include <utils.h>

/****************************************************************************************************/																
/*									D�claration des macros											*/
/****************************************************************************************************/

#define CIRCULAR_BUFFER_SIZE 32

typedef struct 
{
	u08 addr;
	u08 reg;
	u08 read;
	u08 data;
} i2c_command;



/****************************************************************************************************/																
/*									D�claration des fonctions										*/
/****************************************************************************************************/

/* Fonction permettant d'ins�rer dans le buffer out	 */
/* Entr�e : Re�oit 'data' */
/* Sortie : Aucune sortie */
void putDataOutBuf(i2c_command data);

/* Fonction permettant de retirer du buffer out*/
/* Entr�e : Aucune entr�e */
/* Sortie : Retourne 'CircularBufferOut[CircularBufferOutIndex]' */
i2c_command getDataOutBuf(void);

/* Fonction permettant d'ins�rer dans le buffer in*/
/* Entr�e : Re�oit 'data' */
/* Sortie : Aucune sortie */
void putDataInBuf(i2c_command data);

/* Fonction permettant de retirer du buffer in */
/* Entr�e : Aucune entr�e */
/* Sortie : Retourne 'CircularBufferIn[CircularBufferInIndex]'*/
i2c_command getDataInBuf(void);

/* Fonction permettant d'�crire sur le bus TWI */
/* Entr�e : Re�oit les variables address, registre et data */
/* Sortie : Aucune sortie */
void twiWriteCommand(u08 address, u08 registre, u08 data, u08 read);

/* Fonction permettant de lire sur le bus TWI */
/* Entr�e : Re�oit les variables address, registre et data */
/* Sortie : Aucune sortie */
i2c_command twiReadCommand();

/* Fonction permettant de faire l'initialisation du TWI */
/* Entr�e : Aucune entr�e */
/* Sortie : Aucune sortie */
void init_TWI(void);

#endif
