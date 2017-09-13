/****************************************************************************************************/
/*    Title:   				Robot Mobile															*/
/*    Autheurs:   			Pénélope Laberge et Alexandre Grondin									*/
/*    Date de création :    Session ÉTÉ 2015														*/
/*	  Description : 		À l'aide d'un mocrocontrôleur ATMega 32, nous avons fait fonctionner 	*/
/*							un robot mobile à l'aide de téléguidage avec la détection d'obstacle.	*/
/*							Le déplacement est contrôlé par le téléguidange alors que les obstacles */
/*							sont détectés et évités de façon autonome. 								*/
/****************************************************************************************************/

/****************************************************************************************************/																
/*									Déclaration des librairies										*/
/****************************************************************************************************/

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <UART.h>
#include <PWM.h>
#include <utils.h>
#include <moteur.h>
#include <ADC.h>
#include <calibration.h>
#include <watchdog.h>
#include <i2c_caneva.h>
#include <sonar.h>

/****************************************************************************************************/																
/*									Programme principal												*/
/****************************************************************************************************/

int main(void)
{
	/* Déclarations des variables */
	char tableau_com[200];
	u08 compteur = 0;

	u08 compteur_twi = 0;
	u08 nouveau_ping = 0;
	float Duty_G;
	float Duty_D;
	float v_comm;
	float a_comm;
	float Vg;
	float Vd;
	int moy_G;
	int moy_D;
	int duty_Gi;

	u08 robot_enable = 1;
	tableau_com[0]=0xFE;


	DDRA = 0x10;      /* PortA output */
    DDRB = 0xff;      /* PortB output */
	DDRD = 0xff;

	PORTA = 0x00;
	PORTD = 0x00;
    PORTB = 0x00;     /* switch LEDs on */

	/* set enabled leds */
	set_led(6, 0);
	set_led(7, 1);


	init_ADC();
    uart_init();
	init_timer();

	init_watchdog();


    sei();         /* enable interrupts */
	
	executer_calibration();
	
	cli(); 

	init_TWI();

	init_sonar();

	sei();

	/* Boucle infinie */
    for (;;) 
	{   
		uart_send("Serial Data from AVR received###", 32);
	
		executer_sonar(nouveau_ping);

		nouveau_ping = 0;


		if(read_flag()==1) 				/* Si la lecture du drapeau est vraie */
		{
			compteur++;		
						
			compteur_twi++;

			if(compteur >=200)			/* Si le compteur est plus grand ou égal à 200 */
			{
				PORTB = (PORTB ^ 0x01); /* La LED 0 sera allumée (clignote) à chaque seconde lorsque le calcul 200*5ms est vrai */
				
				compteur = 0; 			
			}

			if(compteur_twi >= 10)
			{
				nouveau_ping = 1;
				compteur_twi = 0;
			}

			calcul_moyenne();			

			Vg = calcul_Vg(Moyenne_G);
			Vd = calcul_Vd(Moyenne_D);

			moy_G = Vg*100;		/* Conversion en pourcentage 0-100 pour l'affichage de la moyenne de gauche */

			moy_D = Vd*100;		/* Conversion en pourcentage 0-100 pour l'affichage de la moyenne de droite */

			v_comm = conv_vitesse(get_vitesse());
			if(v_comm>vitesse_max)
				v_comm = vitesse_max;

			a_comm = conv_angle(get_angle());

			CalculPWM(v_comm, a_comm, Vg, Vd, &Duty_G, &Duty_D);

			if(robot_enable)
			{

				duty_Gi = Duty_G*100;

				set_PWMg(Duty_G);
				set_PWMd(Duty_D);
			}
			else
			{
				PORTD = (0xCC)|(PORTD&0x33);
			}
			
		}
		

		/* Controle stop/start */
		if(!(PINA&0x40))
		{
			robot_enable = 1;
			set_led(6, 0);
			set_led(7, 1);
		}
		if(!(PINA&0x80))
		{
			robot_enable = 0;
			set_led(6, 1);
			set_led(7, 0);
		}

    }       
	
}

