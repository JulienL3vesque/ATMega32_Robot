#ifndef I2C_H
#define I2C_H

/****************************************************************************************************/																
/*									Déclaration des librairies										*/
/****************************************************************************************************/
#include <utils.h>

/****************************************************************************************************/																
/*									Déclaration des macros											*/
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
/*									Déclaration des fonctions										*/
/****************************************************************************************************/

/* Fonction permettant d'insérer dans le buffer out	 */
/* Entrée : Reçoit 'data' */
/* Sortie : Aucune sortie */
void putDataOutBuf(i2c_command data);

/* Fonction permettant de retirer du buffer out*/
/* Entrée : Aucune entrée */
/* Sortie : Retourne 'CircularBufferOut[CircularBufferOutIndex]' */
i2c_command getDataOutBuf(void);

/* Fonction permettant d'insérer dans le buffer in*/
/* Entrée : Reçoit 'data' */
/* Sortie : Aucune sortie */
void putDataInBuf(i2c_command data);

/* Fonction permettant de retirer du buffer in */
/* Entrée : Aucune entrée */
/* Sortie : Retourne 'CircularBufferIn[CircularBufferInIndex]'*/
i2c_command getDataInBuf(void);

/* Fonction permettant d'écrire sur le bus TWI */
/* Entrée : Reçoit les variables address, registre et data */
/* Sortie : Aucune sortie */
void twiWriteCommand(u08 address, u08 registre, u08 data, u08 read);

/* Fonction permettant de lire sur le bus TWI */
/* Entrée : Reçoit les variables address, registre et data */
/* Sortie : Aucune sortie */
i2c_command twiReadCommand();

/* Fonction permettant de faire l'initialisation du TWI */
/* Entrée : Aucune entrée */
/* Sortie : Aucune sortie */
void init_TWI(void);

#endif
