/****************************************************************************************************/																
/*	Fonction : Les sonars doivent détecter les obstacles présents devant le robot mobile.			*/
/****************************************************************************************************/

/****************************************************************************************************/																
/*									Déclaration des librairies										*/
/****************************************************************************************************/

#include <sonar.h>
#include <utils.h>
#include <i2c_caneva.h>
#include <avr/io.h>

/****************************************************************************************************/																
/*									Déclaration des macros											*/
/****************************************************************************************************/

#define SONAR_GAUCHE 0
#define SONAR_DROIT 1

#define REGISTRE_MSB 2
#define REGISTRE_LSB 3

#define ADDRESSE_SONAR_GAUCHE 0xE0
#define ADDRESSE_SONAR_DROIT 0xE2

#define GAIN_SONAR 12
#define RANGE_SONAR 100

#define DISTANCE_SEUIL_MAX 100
#define DISTANCE_SEUIL_MIN 50
#define DISTANCE_SEUIL_DETECTE 4000

/****************************************************************************************************/																
/*									Déclaration des variables										*/
/****************************************************************************************************/

u16 distance_gauche = 9999;
u16 distance_droite = 9999;
u16 distance_gauche_tmp = 0;
u16 distance_droite_tmp = 0;
float vitesse_max;

u08 sonar_en_cours = SONAR_GAUCHE;

/****************************************************************************************************/																
/*									Déclaration des fonctions										*/
/****************************************************************************************************/

/* Fonction permettant de faire le calcul de la vitesse maximale */
static void calcul_vitesse_max()
{
	u16 distance_min;
	if(distance_gauche<distance_droite)
	{
		distance_min = distance_gauche;
	}
	else
	{
		distance_min = distance_droite;
	}

	if(distance_min<DISTANCE_SEUIL_MIN)
	{
		vitesse_max = 0.0;
	}
	else
	{
		vitesse_max = ((float)distance_min-(float)DISTANCE_SEUIL_MIN)/(float)(DISTANCE_SEUIL_MAX-DISTANCE_SEUIL_MIN);
	}

}

/* Fonction permettant de faire l'initialisation du sonar */
void init_sonar()
{
	/* Change le gain du sonar à GAIN_SONAR du sonar gauche et le range à RANGE_SONAR */
	twiWriteCommand(ADDRESSE_SONAR_GAUCHE, 1, GAIN_SONAR, 0);
	twiWriteCommand(ADDRESSE_SONAR_GAUCHE, 2, RANGE_SONAR, 0);

	/* Même chose pour le sonar droit */
	twiWriteCommand(ADDRESSE_SONAR_DROIT, 1, GAIN_SONAR, 0);
	twiWriteCommand(ADDRESSE_SONAR_DROIT, 2, RANGE_SONAR, 0);

	sonar_en_cours = SONAR_GAUCHE;
	/* Envoie de ping pour le sonar gauche */
	twiWriteCommand(ADDRESSE_SONAR_GAUCHE, 0, 0x51, 0);


}


/* Fonction perttant de faire l'appel du nouveau_ping toutes les 50ms */
void executer_sonar(u08 nouveau_ping)
{
	i2c_command command;
	if(nouveau_ping)
	{
		if(sonar_en_cours==SONAR_GAUCHE)
		{
			/* Commandes pour lire le sonar gauche */
			twiWriteCommand(0xE0, REGISTRE_MSB, 0, 1);
			twiWriteCommand(0xE0, REGISTRE_LSB, 0, 1);

			sonar_en_cours = SONAR_DROIT;

			/* Envoie de ping pour le sonar droite */
			twiWriteCommand(0xE2, 0, 0x51, 0);

			//Ping envoyé
			toggle_led(3);


		}
		else if(sonar_en_cours==SONAR_DROIT)
		{
			/* Commandes pour lire le sonar droite */
			twiWriteCommand(0xE2, REGISTRE_MSB, 0, 1);
			twiWriteCommand(0xE2, REGISTRE_LSB, 0, 1);

			sonar_en_cours = SONAR_GAUCHE;

			/* Envoie de ping pour le sonar gauche */
			twiWriteCommand(0xE0, 0, 0x51, 0);

			//Ping envoyé
			toggle_led(5);
		}
	}

	command = twiReadCommand();

	/* Si twiReadCommand=0xFF, cela signifie que le buffer est vide */
	if(command.addr!=0xFF)
	{
		
		/* Sinon, on a reçu des données */
		if(command.reg==REGISTRE_MSB)
		{
			/* Le MSB est reçu en premier*/
			if(command.addr==ADDRESSE_SONAR_GAUCHE)
			{
				distance_gauche_tmp = command.data<<8;

			}
			else
			{
				distance_droite_tmp = command.data<<8;
			}
		}
		else
		{
			/* Ensuite le LSB */
			if(command.addr==ADDRESSE_SONAR_GAUCHE)
			{
				distance_gauche_tmp |= command.data;
				distance_gauche = distance_gauche_tmp;
				if(distance_gauche<=DISTANCE_SEUIL_DETECTE)
				{
					set_led(4, 0);
				}
				else
				{
					set_led(4, 1);
				}

			}
			else
			{
				distance_droite_tmp |= command.data;
				distance_droite = distance_droite_tmp;
				if(distance_droite<=DISTANCE_SEUIL_DETECTE)
				{
					set_led(2, 0);
				}
				else
				{
					set_led(2, 1);
				}

			}
			/* Recalcul de la vitesse max */
			calcul_vitesse_max();
		}
		
	}
}

